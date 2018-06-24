#include <iomanip>
#include <iostream>
#include <string>

#include "CompileErrorException.h"
#include "Compiler.h"
#include "File.h"

using namespace std;

void PrintHelp();
void PrintVersion();
void PrintInfo(const int incVal, const string& incStr);

int main(int argv, char** args) {
    bool isShowHelp = false; // -h
    bool isShowVersion = false; // -v
    bool isCompileToBinary = false; // -b
    bool isSetOutputFileName = false; // -o
    bool isShowCompileInfo = false; // -i
    bool isErr = false;
    string outputFileName;
    string inputFileName;
    for (int i = 1; i < argv; i++) {
        string arg(args[i]);
        if (isSetOutputFileName == true && outputFileName.size() == 0) {
            outputFileName = arg;
        } else if (arg == "-h") {
            isShowHelp = true;
        } else if (arg == "-v") {
            isShowVersion = true;
        } else if (arg == "-b") {
            isCompileToBinary = true;
        } else if (arg == "-i") {
            isShowCompileInfo = true;
        } else if (arg == "-o") {
            if (i + 1 == argv) {
                isErr = true;
            }
            isSetOutputFileName = true;
        } else if (inputFileName.size() == 0) {
            inputFileName = arg;
        } else {
            isErr = true;
        }
    }
    if (isErr) {
        cerr << args[0] << endl;
        cerr << "error: unrecognized command line option or too much input files" << endl;
        cerr << "compilation terminated." << endl;
        return 1;
    } else if (argv == 1) {
        cerr << args[0] << endl;
        cerr << "fatal error: no input file" << endl;
        cerr << "compilation terminated." << endl;
        return 1;
    }
    if (isShowHelp) {
        PrintHelp();
    }
    if (isShowVersion) {
        PrintVersion();
    }
    if (inputFileName.size() == 0 && outputFileName.size()) {
        cerr << args[0] << endl;
        cerr << "fatal error: no input file" << endl;
        cerr << "compilation terminated." << endl;
        return 1;
    } else if (inputFileName.size() == 0) {
        return 0;
    }
    string input = File::Read(inputFileName);
    auto fn = (isShowCompileInfo ? PrintInfo : nullptr);
    Compiler c(input, fn);
    try {
        int line = c.Compile();
        cout << "Compile " << line << " instructions successfully." << endl;
    } catch (CompileErrorException e) {
        cerr << e.what();
        return 1;
    }
    if (outputFileName.size() == 0) {
        outputFileName = inputFileName.substr(0, inputFileName.find_last_of('.'));
        outputFileName += (isCompileToBinary ? ".bin.txt" : ".hex.txt");
    }
    if (File::Write(outputFileName, c.GetOutput(isCompileToBinary)) == false) {
        cerr << "Write file '" << outputFileName << "' fail" << endl;
        return 1;
    }
    return 0;
}

void PrintHelp() {
    cout << "Usage: asmc.exe [options] file" << endl
        << "Options:" << endl
        << "  -b\tOutput binary file, default output hexadecimal file" << endl
        << "  -h\tHelp information" << endl
        << "  -i\tShow all the compile information" << endl
        << "  -o\tOutput file name, default *.[hex|bin].txt" << endl
        << "  -v\tVersion information" << endl;
}

void PrintVersion() {
    cout << "assembly compiler version 1.0.0" << endl;
}

void PrintInfo(const int incVal, const string& incStr) {
    if (incVal == 0) {
        cout << "compile fail  <- " << incStr << endl;
        return;
    }
    cout << hex << setfill('0')
        << setw(2) << (incVal >> 24 & 0xFF) << ' '
        << setw(2) << (incVal >> 16 & 0xFF) << ' '
        << setw(2) << (incVal >> 8 & 0xFF) << ' '
        << setw(2) << (incVal & 0xFF) << "   <- "
        << incStr << endl << dec;
}
