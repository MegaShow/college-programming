#include "x509.hpp"

std::vector<std::string> X509::parseKey;
std::vector<Value> X509::parseValue;

const std::string X509::BASE64_TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const std::string X509::CERT_BEGIN = "-----BEGIN CERTIFICATE-----";
const std::string X509::CERT_END = "-----END CERTIFICATE-----";
const std::map<std::string, std::string> X509::OBJECT_ID = {
    { "1.2.840.113549.1.1.1", "RSA encryption" },
    { "1.2.840.113549.1.1.11", "sha256WithRSAEncryption" },
    { "1.3.6.1.4.1.11129.2.4.2", "x.509 extension for certificate transparency SCTs" },
    { "1.3.6.1.5.5.7.1.1", "id-pe-authorityInfoAccess" },
    { "1.3.6.1.5.5.7.2.1", "id-qt-cps: OID for CPS qualifier" },
    { "1.3.6.1.5.5.7.3.1", "id_kp_serverAuth" },
    { "1.3.6.1.5.5.7.3.2", "id_kp_clientAuth" },
    { "1.3.6.1.5.5.7.48.1", "OCSP" },
    { "1.3.6.1.5.5.7.48.2", "id-ad-caIssuers" },
    { "2.5.4.3", "id-at-commonName" },
    { "2.5.4.6", "id-at-countryName" },
    { "2.5.4.10", "id-at-organizationName" },
    { "2.5.4.11", "id-at-organizationalUnitName" },
    { "2.5.29.14", "Subject Key Identifier" },
    { "2.5.29.15", "Key Usage" },
    { "2.5.29.17", "Subject Alternative Name" },
    { "2.5.29.19", "Basic Constraints" },
    { "2.5.29.32", "Certificate Policies" },
    { "2.5.29.35", "Authority Key Identifier" },
    { "2.5.29.37", "Extended key usage" },
    { "2.16.840.1.114412.1.2", "Digicert EV" },
    { "2.23.140.1.2.1", "domain-validated" }
};

X509::X509(std::string filename) {
    std::ifstream in(filename);
    std::stringstream buffer;
    std::string str;
    buffer << in.rdbuf();
    str = buffer.str();
    size_t index = str.find(CERT_BEGIN);
    while (index != std::string::npos) {
        size_t start = index + CERT_BEGIN.length();
        size_t end = str.find(CERT_END, start);
        std::string rawStr = str.substr(start, end - start);
        rawStr.erase(std::remove(rawStr.begin(), rawStr.end(), '\n'), rawStr.end());
        rawStr.erase(std::remove(rawStr.begin(), rawStr.end(), '\r'), rawStr.end());
        raw.push_back(rawStr);
        index = str.find(CERT_BEGIN, end);
    }
}

size_t X509::size() {
    return raw.size();
}

std::string X509::getBase64String(size_t i) {
    return raw[i];
}

void X509::parse(size_t i) {
    std::vector<uint8_t> bytes = decodeBase64(raw[i]);
    parseKey.clear();
    parseValue.clear();
    parseDer(bytes);
}

void X509::parseDer(std::vector<uint8_t> v) {
    if (v.size() == 0) {
        return;
    }
    for (size_t i = 0, len; i < v.size(); i += len) {
        uint8_t type = v[i++];
        if ((v[i] & 0x80) == 0) {
            len = v[i++];
        } else if (v[i] == 0x80) {
            len = 0;
            i++;
        } else {
            size_t lenLen = v[i++] & 0x7f;
            for (size_t j = i; j < i + lenLen; j++) {
                len = (j == i ? 0 : len << 8) | v[j];
            }
            i += lenLen;
        }
        // std::cout << std::hex << unsigned(type) << ' ' << len << std::endl;
        Value value;
        value.type = type;
        switch (type) {
            case 0x01: { // BOOLEAN
                parseKey.push_back("Boolean");
                for (size_t j = i; j < i + len; j++) {
                    value.val.push_back(v[j]);
                }
                parseValue.push_back(value);
                break;
            }
            case 0x02: { // INTEGER
                parseKey.push_back("Integer");
                for (size_t j = i; j < i + len; j++) {
                    value.val.push_back(v[j]);
                }
                parseValue.push_back(value);
                break;
            }
            case 0x04: { // OCTET STRING
                if (parseKey.back() != "OctetString") {
                    parseKey.push_back("OctetString");
                    parseDer(std::vector<uint8_t>(v.begin() + i, v.begin() + i + len));
                    parseKey.push_back("OctetStringEnd");
                    break;
                }
            }
            case 0x03: // BIT STRING
            case 0x80: { // CERT VERSION
                parseKey.push_back("BitString");
                std::stringstream ss;
                for (size_t j = i + (type == 0x03 ? 1 : 0); j < i + len; j++) {
                    ss << std::setfill('0') << std::setw(2) << std::hex << unsigned(v[j]);
                }
                value.str = ss.str();
                parseValue.push_back(value);
                break;
            }
            case 0x05: { // NULL
                break;
            } 
            case 0x06: { // OBJECT IDENTIFIER
                parseKey.push_back("ObjectId");
                std::stringstream ss;
                unsigned int k = 0;
                for (size_t j = i; j < i + len; j++) {
                    k = k << 7 | (v[j] & 0x7f);
                    if ((v[j] & 0x80) == 0) {
                        if (ss.str().empty()) {
                            ss << std::min(k / 40, unsigned(2)) << '.' << k - 40 * std::min(k / 40, unsigned(2));
                        } else {
                            ss << '.' << k;
                        }
                        k = 0;
                    }
                }
                value.str = ss.str();
                parseValue.push_back(value);
                break;
            }
            case 0x13: // PRINTABLE STRING
            case 0x82: { // CERT ID
                parseKey.push_back("PrintableString");
                for (size_t j = i; j < i + len; j++) {
                    value.str += v[j];
                }
                parseValue.push_back(value);
                break;
            }
            case 0x17: { // UTC TIME
                parseKey.push_back("UtcTime");
                for (size_t j = i; j < i + len; j++) {
                    value.str += v[j];
                }
                parseValue.push_back(value);
                break;
            }
            case 0x30: { // SEQUENCE
                parseKey.push_back("Sequence");
                parseDer(std::vector<uint8_t>(v.begin() + i, v.begin() + i + len));
                parseKey.push_back("SequenceEnd");
                break;
            }
            case 0x31: { // SET
                parseKey.push_back("Set");
                parseDer(std::vector<uint8_t>(v.begin() + i, v.begin() + i + len));
                break;
            }
            case 0xa0: { // VERSION
                parseKey.push_back("Version");
                parseDer(std::vector<uint8_t>(v.begin() + i, v.begin() + i + len));
                break;
            }
            case 0xa3: { // EXTENSION
                parseKey.push_back("Extensions");
                parseDer(std::vector<uint8_t>(v.begin() + i, v.begin() + i + len));
                parseKey.push_back("ExtensionsEnd");
            }
        }
    }
}

const std::vector<std::string> HINT = {
    "Certificate",
    "TBSCertificate",
    "Version",
    "SerialNumber",
    "Signature",
    "Issuer",
    "Validity",
    "Subject",
    "SubjectPublicKeyInfo",
    "Algorithm",
    "Key"
};

void X509::print() {
    int sequence = 0, count = 0;
    bool extensions = false;
    for (size_t k = 0, v = 0; k < parseKey.size(); k++) {
        // std::cout << parseKey[k] << std::endl;
        if (parseKey[k] == "SequenceEnd") {
            sequence--;
        } else if (parseKey[k] == "ExtensionsEnd") {
            sequence--;
            extensions = false;
        } else {
            std::cout << std::string(sequence * 2, ' ');
        }
        if (parseKey[k] == "Sequence" && extensions == false) {
            sequence++;
            std::cout << HINT[count++] << ":" << std::endl;
        } else if (parseKey[k] == "Version" && ++k < parseKey.size() && parseKey[k] == "Integer") {
            std::cout << HINT[count++] << ": " << unsigned(parseValue[v++].val[0] + 1) << std::endl;
        } else if (parseKey[k] == "Integer") {
            std::stringstream ss;
            for (auto &val : parseValue[v].val) {
                ss << std::setfill('0') << std::setw(2) << std::hex << unsigned(val);
            }
            std::cout << HINT[count++] << ": " << ss.str() << std::endl;
            v++;
        } else if (parseKey[k] == "ObjectId") {
            if (OBJECT_ID.count(parseValue[v].str) == 0) {
                std::cout << std::endl << "Unknown object id: " << parseValue[v].str << std::endl;
                return;
            }
            std::cout << OBJECT_ID.at(parseValue[v++].str) << std::endl;
        } else if (parseKey[k] == "Set" && ++k < parseKey.size() && parseKey[k] == "Sequence" &&
            ++k < parseKey.size() && parseKey[k] == "ObjectId" && ++k < parseKey.size() && parseKey[k] == "PrintableString" &&
            ++k < parseKey.size() && parseKey[k] == "SequenceEnd") {
            if (OBJECT_ID.count(parseValue[v].str) == 0) {
                std::cout << std::endl << "Unknown object id: " << parseValue[v].str << std::endl;
                return;
            }
            std::cout << OBJECT_ID.at(parseValue[v].str) << ": " << parseValue[v+1].str << std::endl;
            v += 2;
        } else if (parseKey[k] == "UtcTime") {
            std::cout << (k+1 < parseKey.size() && parseKey[k+1] == "UtcTime" ? "from" : "to") << ": 20";
            for (size_t j = 0; j < parseValue[v].str.size(); j++) {
                std::cout << parseValue[v].str[j];
                if (j == 1 || j == 3) {
                    std::cout << '-';
                } else if (j == 5) {
                    std::cout << ' ';
                } else if (j == 7 || j == 9) {
                    std::cout << ':';
                }
            }
            v++;
            std::cout << std::endl;
        } else if (parseKey[k] == "BitString") {
            std::cout << "BitString:" << std::endl;
            for (size_t j = 0; j < parseValue[v].str.size(); j += 60) {
                std::cout << std::string(sequence * 2 + 2, ' ');
                std::cout << parseValue[v].str.substr(j, 60) << std::endl;
            }
            v++;
        } else if (parseKey[k] == "Extensions" && ++k < parseKey.size() && parseKey[k] == "Sequence") {
            sequence++;
            extensions = true;
            std::cout << "Extensions:" << std::endl;
        } else if (parseKey[k] == "Sequence" && extensions == true && ++k < parseKey.size() && parseKey[k] == "ObjectId") {
            sequence++;
            if (OBJECT_ID.count(parseValue[v].str) == 0) {
                std::cout << std::endl << "Unknown object id: " << parseValue[v].str << std::endl;
                return;
            }
            std::cout << OBJECT_ID.at(parseValue[v++].str) << ":" << std::endl;
        } else if (parseKey[k] == "OctetString") {
            int s = 1;
            bool init = true, noouput = true;
            while (s != 0 && ++k < parseKey.size()) {
                if (parseKey[k] == "Sequence" || parseKey[k] == "OctetString") {
                    s++;
                } else if (parseKey[k] == "SequenceEnd" || parseKey[k] == "OctetStringEnd") {
                    s--;
                } else if (parseKey[k] == "BitString" || parseKey[k] == "PrintableString") {
                    noouput = false;
                    if (init) {
                        init = false;
                    } else {
                        std::cout << std::string(sequence * 2, ' ');
                    }
                    for (size_t j = 0; j < parseValue[v].str.size(); j += 60) {
                        std::cout << std::string(j == 0 ? 0 : sequence * 2, ' ');
                        std::cout << parseValue[v].str.substr(j, 60) << std::endl;
                    }
                    v++;
                } else if (parseKey[k] == "ObjectId") {
                    noouput = false;
                    if (init) {
                        init = false;
                    } else {
                        std::cout << std::string(sequence * 2, ' ');
                    }
                    if (OBJECT_ID.count(parseValue[v].str) == 0) {
                        std::cout << std::endl << "Unknown object id: " << parseValue[v].str << std::endl;
                        return;
                    }
                    std::cout << OBJECT_ID.at(parseValue[v++].str) << std::endl;
                }
            }
            if (noouput) {
                std::cout << '\r';
            }
        } else if (parseKey[k] == "Boolean") {
            std::cout << (parseValue[v++].val[0] != 0 ? "True" : "False") << std::endl;
        }
    }
}

std::vector<uint8_t> X509::decodeBase64(std::string base64) {
    std::vector<uint8_t> res;
    while (base64.length() % 4) {
        base64 += '=';
    }
    for (size_t i = 0; i < base64.length(); i += 4) {
        uint8_t src[4];
        for (size_t j = 0; j < 4; j++) {
            if (base64[i+j] == '=') {
                src[j] = 0;
            } else {
                src[j] = BASE64_TABLE.find(base64[i+j]);
            }
        }
        res.push_back((src[0] << 2) | (src[1] >> 4 & 0x3));
        res.push_back((src[1] << 4) | (src[2] >> 2 & 0xf));
        res.push_back((src[2] << 6) | src[3]);
    }
    return res;
}
