#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Symbol table for storing variable names and their stack offsets
map<string, int> symbolTable;
int memoryOffset = 0; // Stack offset for variables
int labelCounter = 0; // Counter for unique labels

// Generate a unique label for control flow
string generateLabel(const string &prefix) {
    return prefix + to_string(labelCounter++);
}

// Function to declare variables and assign values
void declareVariable(const string &var, int value) {
    memoryOffset -= 4; // Reserve space on stack
    symbolTable[var] = memoryOffset;
    cout << "\tli $t0, " << value << endl;   // Load immediate value
    cout << "\tsw $t0, " << memoryOffset << "($sp)" << endl; // Store in stack
}

// Function to assign one variable's value to another
void assignVariable(const string &var1, const string &var2) {
    if (symbolTable.find(var1) == symbolTable.end() || symbolTable.find(var2) == symbolTable.end()) {
        cerr << "Error: Undefined variable." << endl;
        return;
    }
    cout << "\tlw $t0, " << symbolTable[var2] << "($sp)" << endl;
    cout << "\tsw $t0, " << symbolTable[var1] << "($sp)" << endl;
}

// Generate MIPS assembly for binary operations
void generateMIPS(string op, string dest, string src1, string src2) {
    if (op == "PLUS") {
        cout << "\tadd " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "MINUS") {
        cout << "\tsub " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "STAR") {
        cout << "\tmul " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "SLASH") {
        cout << "\tdiv " << src1 << ", " << src2 << endl;
        cout << "\tmflo " << dest << endl;
    } else if (op == "PCT") {
        cout << "\tdiv " << src1 << ", " << src2 << endl;
        cout << "\tmfhi " << dest << endl;
    }
}

// Translate if-else control flow
void translateIfElse(string condition, vector<string> trueBlock, vector<string> falseBlock) {
    string elseLabel = generateLabel("ELSE");
    string endLabel = generateLabel("ENDIF");
    cout << "\t" << condition << elseLabel << endl;
    for (const auto &line : trueBlock) {
        cout << "\t" << line << endl;
    }
    cout << "\tb " << endLabel << endl;
    cout << elseLabel << ":" << endl;
    for (const auto &line : falseBlock) {
        cout << "\t" << line << endl;
    }
    cout << endLabel << ":" << endl;
}

// Translate while loop control flow
void translateWhileLoop(string condition, vector<string> body) {
    string startLabel = generateLabel("WHILE_START");
    string endLabel = generateLabel("WHILE_END");
    cout << startLabel << ":" << endl;
    cout << "\t" << condition << endLabel << endl;
    for (const auto &line : body) {
        cout << "\t" << line << endl;
    }
    cout << "\tb " << startLabel << endl;
    cout << endLabel << ":" << endl;
}

// Emit print syscall
void emitPrintln(string reg) {
    cout << "\tmove $a0, " << reg << endl;
    cout << "\tli $v0, 1" << endl;
    cout << "\tsyscall" << endl;
}

// Emit putchar syscall
void emitPutchar(string reg) {
    cout << "\tmove $a0, " << reg << endl;
    cout << "\tli $v0, 11" << endl;
    cout << "\tsyscall" << endl;
}

// Emit getchar syscall
void emitGetchar() {
    cout << "\tli $v0, 8" << endl;
    cout << "\tsyscall" << endl;
    cout << "\tmove $v1, $v0" << endl;
}

// ======================== Main Code Generator ========================
int main() {
    cout << ".import print" << endl;
    cout << ".text" << endl;
    cout << ".globl wain" << endl;
    cout << "wain:" << endl;

    // Stack pointer setup
    cout << "\taddi $sp, $sp, -32" << endl; // Allocate stack space

    // Problem 2: Declarations and Assignments
    declareVariable("c", 241);
    declareVariable("b", 0);
    declareVariable("a", 0);
    assignVariable("b", "c");
    assignVariable("a", "b");

    // Problem 4: If-else and while loop
    translateIfElse("blt $t1, $t2, ", {"li $t0, 1"}, {"li $t0, 241"});
    translateWhileLoop("blt $t1, $t2, ", {"addi $t1, $t1, 1"});

    // Problem 3: Arithmetic operation (a + b)
    generateMIPS("PLUS", "$t3", "$t1", "$t2");

    // Problem 5: I/O operations
    emitPrintln("$t3");
    emitGetchar();
    emitPutchar("$t2");

    // Restore stack pointer and return
    cout << "\taddi $sp, $sp, 32" << endl;
    cout << "\tjr $ra" << endl;
    return 0;
}
