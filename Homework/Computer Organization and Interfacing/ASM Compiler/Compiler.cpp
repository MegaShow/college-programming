#include <bitset>
#include <iomanip>

#include "CompileErrorException.h"
#include "Compiler.h"

using namespace std;

#define SIGNED_IMM false
#define UNSIGNED_IMM true
#define DEC_IMM false
#define HEX_IMM true

map<string, int> Compiler::OpCode = {
    { "add",   0b000000 },
    { "sub",   0b000001 },
    { "addi",  0b000010 },
    { "or",    0b010000 },
    { "and",   0b010001 },
    { "ori",   0b010010 },
    { "sll",   0b011000 },
    { "slt",   0b100110 },
    { "sltiu", 0b100111 },
    { "sw",    0b110000 },
    { "lw",    0b110001 },
    { "beq",   0b110100 },
    { "bltz",  0b110110 },
    { "j",     0b111000 },
    { "jr",    0b111001 },
    { "jal",   0b111010 },
    { "halt",  0b111111 }
};

set<string> Compiler::R = {
    "add",
    "sub",
    "or",
    "and",
    "sll",
    "slt",
    "jr"
};

set<string> Compiler::I = {
    "addi",
    "ori",
    "sltiu",
    "sw",
    "lw",
    "beq",
    "bltz"
};

set<string> Compiler::J = {
    "j",
    "jal",
    "halt"
};

Compiler::Compiler(string input, function<void(const int, const string&)> print) {
    this->print = print;
    stringstream ss;
    ss << input;
    char tmp[256];
    while (!ss.eof()) {
        ss.getline(tmp, 255);
        this->input.push_back(string(tmp));
    }
}

int Compiler::Compile() {
    for (size_t i = 0; i < input.size(); i++) {
        try {
            stringstream ss;
            string op;
            int rs = 0, rt = 0, rd = 0, sa = 0, inc = 0, imm = 0, addr = 0;
            ss << input[i];
            ss >> op;
            if (op.size() == 0) {
                continue;
            } else if (R.count(op)) {
                if (op == "jr") {
                    rs = ParseRegister(ss, '\n');
                } else if (op == "sll") {
                    rd = ParseRegister(ss, ',');
                    rt = ParseRegister(ss, ',');
                    sa = ParseInteger(ss, '\n', 5, UNSIGNED_IMM);
                } else {
                    rd = ParseRegister(ss, ',');
                    rs = ParseRegister(ss, ',');
                    rt = ParseRegister(ss, '\n');
                }
                inc = (OpCode[op] & 0x3F) << 26 | (rs & 0x1F) << 21 | (rt & 0x1F) << 16
                    | (rd & 0x1F) << 11 | (sa & 0x1F) << 6;
            } else if (I.count(op)) {
                if (op == "lw" || op == "sw") {
                    size_t lhs = input[i].find('(');
                    size_t rhs = input[i].find(')');
                    if (lhs == string::npos || rhs == string::npos || lhs >= rhs) {
                        throw string("Format should be '") + op + " rt, immediate(rs)'";
                    }
                    rt = ParseRegister(ss, ',');
                    imm = ParseInteger(ss, '(', 16, SIGNED_IMM);
                    rs = ParseRegister(ss, ')');
                } else if (op == "beq") {
                    rs = ParseRegister(ss, ',');
                    rt = ParseRegister(ss, ',');
                    imm = ParseInteger(ss, '\n', 16, SIGNED_IMM);
                } else if (op == "bltz") {
                    rs = ParseRegister(ss, ',');
                    imm = ParseInteger(ss, '\n', 16, SIGNED_IMM);
                } else if (op == "addi") {
                    rt = ParseRegister(ss, ',');
                    rs = ParseRegister(ss, ',');
                    imm = ParseInteger(ss, '\n', 16, SIGNED_IMM);
                } else {
                    rt = ParseRegister(ss, ',');
                    rs = ParseRegister(ss, ',');
                    imm = ParseInteger(ss, '\n', 16, UNSIGNED_IMM);
                }
                inc = (OpCode[op] & 0x3F) << 26 | (rs & 0x1F) << 21 | (rt & 0x1F) << 16 | (imm & 0xFFFF);
            } else if (J.count(op)) {
                if (op != "halt") {
                    addr = ParseInteger(ss, '\n', 26, UNSIGNED_IMM, HEX_IMM);
                    if (addr % 4 != 0) {
                        throw string("Address must be multiples of 4");
                    }
                }
                inc = (OpCode[op] & 0x3F) << 26 | ((addr >> 2) & 0x3FFFFF);
            } else {
                throw string("Invalid opcode '") + op + "'";
            }
            output.push_back(inc);
            if (print != nullptr) {
                print(inc, input[i]);
            }
        } catch(string e) {
            if (print != nullptr) {
                print(0, input[i]);
            }
            err.append(string("Line ") + to_string(i + 1) + ": " + input[i] + "\n");
            err.append(e + "\n");
        }
    }
    if (err.size()) {
        throw CompileErrorException(err);
    }
    return output.size();
}

string Compiler::GetOutput(bool isCompileToBinary) {
    stringstream ss;
    ss << hex << setfill('0');
    for (int val : output) {
        if (isCompileToBinary) {
            ss << bitset<8>(val >> 24 & 0xFF) << ' '
                << bitset<8>(val >> 16 & 0xFF) << ' '
                << bitset<8>(val >> 8 & 0xFF) << ' '
                << bitset<8>(val & 0xFF) << endl;
        } else {
            ss << setw(2) << (val >> 24 & 0xFF) << ' '
                << setw(2) << (val >> 16 & 0xFF) << ' '
                << setw(2) << (val >> 8 & 0xFF) << ' '
                << setw(2) << (val & 0xFF) << endl;
        }
    }
    return ss.str();
}

int Compiler::ParseInteger(stringstream& ss, char delim, int bits, bool isUnsigned, bool isHex) {
    char tmp[256];
    int val;
    stringstream sstmp;
    ss.getline(tmp, 255, delim);
    sstmp << tmp;
    if (isHex) {
        sstmp >> hex;
    }
    sstmp >> val;
    if (sstmp.fail() || !sstmp.eof()) {
        throw string("Invalid number '").append(tmp) + '\'';
    }
    if (isUnsigned) {
        if (val < 0 || val >= (1 << bits)) {
            throw string("Number '").append(to_string(val)) + "' overflow";
        }
    } else {
        if (val < - (1 << (bits - 1)) || val > (1 << (bits - 1)) - 1) {
            throw string("Number '").append(to_string(val)) + "' overflow";
        }
    }
    return val;
}

int Compiler::ParseRegister(stringstream& ss, char delim) {
    char tmp[256];
    string reg;
    size_t index;
    stringstream sstmp;
    int regVal;
    ss.getline(tmp, 255, delim);
    for (index = 0; tmp[index] != 0; index++) {
        if (tmp[index] != ' ' && tmp[index] != '\t' && tmp[index] != '\n') {
            break;
        }
    }
    if (tmp[index] == 0 || tmp[index] != '$') {
        throw string("Register must start with character '$'");
    }
    for (index++; tmp[index] != 0; index++) {
        if (tmp[index] != ' ' && tmp[index] != '\t' && tmp[index] != '\n') {
            reg.push_back(tmp[index]);
        } else {
            break;
        }
    }
    for ( ; tmp[index] != 0; index++) {
        if (tmp[index] != ' ' && tmp[index] != '\t' && tmp[index] != '\n') {
            throw string("Redundant characters '").append(tmp, index, string::npos) + '\'';
        }
    }
    sstmp << reg;
    sstmp >> regVal;
    if (sstmp.fail() || !sstmp.eof() || regVal < 0 || regVal > 31) {
        throw string("Invalid register number '").append(reg) + '\'';
    }
    return regVal;
}
