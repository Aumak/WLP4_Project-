#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class CodeGenerator {
private:
    vector<string> mipsCode;
    int labelCounter = 0;
    
    string generateLabel(const string &prefix) {
        return prefix + to_string(labelCounter++);
    }

public:
    void emit(const string &instruction) {
        mipsCode.push_back(instruction);
    }

    void emitImport() {
        emit(".import print");
    }
    
    void emitGetchar() {
        emit("li $v0, 8");
        emit("syscall");
        emit("move $2, $v0");  // Store result in $2
    }
    
    void emitPutchar(const string &reg) {
        emit("move $a0, " + reg);
        emit("li $v0, 11");
        emit("syscall");
    }
    
    void emitPrintln(const string &reg) {
        emit("move $1, " + reg);
        emit("jal print");
    }
    
    void generateCode() {
        for (const auto &line : mipsCode) {
            cout << line << endl;
        }
    }
};

int main() {
    CodeGenerator generator;
    generator.emitImport();
    
    // Example usage
    generator.emit("main:");
    generator.emit("li $t0, 10"); // Load integer 10 into $t0
    generator.emit("li $t1, 20"); // Load integer 20 into $t1
    generator.emitPrintln("$t0"); // println(t0)
    generator.emitGetchar();      // getchar()
    generator.emitPutchar("$2");  // putchar(getchar())
    generator.emit("li $v0, 10"); // Exit syscall
    generator.emit("syscall");
    
    generator.generateCode();
    return 0;
}
