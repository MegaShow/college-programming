#include "x509.hpp"

int main(int argv, char** args) {
    if (argv != 2) {
        std::cerr << "Input parameters invalid." << std::endl;
        return 1;
    }
    X509 cert(args[1]);
    for (size_t i = 0; i < cert.size(); i++) {
        cert.parse(i);
        cert.print();
    }
}
