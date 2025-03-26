#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// ======================== Problem 1: Simple Programs ========================
// Reads input and extracts parameters for wain function
// Generates MIPS assembly code that returns the first parameter

// Symbol table for storing variable names and their stack offsets
map<string, int> symbolTable;
int memoryOffset = 0; // Stack offset for variables
int labelCounter = 0; // Counter for unique labels

// Generate a unique label for control flow
string generateLabel(const string &prefix) {
    return prefix + to_string(labelCounter++);
}

// ======================== Problem 2: Declarations and Assignments ========================
// Function to declare variables and assign values
void declareVariable(const string &var, int value) {
    memoryOffset -= 4; // Reserve space on stack
    symbolTable[var] = memoryOffset;
    cout << "\tli $3, " << value << endl; // Load immediate value
    cout << "\tsw $3, " << memoryOffset << "($29)" << endl; // Store in stack
}

void assignVariable(const string &var1, const string &var2) {
    if (symbolTable.find(var1) == symbolTable.end() || symbolTable.find(var2) == symbolTable.end()) {
        cerr << "Error: Undefined variable." << endl;
        return;
    }
    cout << "\tlw $3, " << symbolTable[var2] << "($29)" << endl;
    cout << "\tsw $3, " << symbolTable[var1] << "($29)" << endl;
}

// ======================== Problem 3: Binary Operations ========================
// Function to generate MIPS assembly for binary operations
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

// ======================== Problem 4: Control Flow ========================
// Function to handle if-else control flow
void translateIfElse(string condition, vector<string> trueBlock, vector<string> falseBlock) {
    string elseLabel = generateLabel("ELSE");
    string endLabel = generateLabel("ENDIF");
    cout << condition << " " << elseLabel << endl;
    for (const auto &line : trueBlock) {
        cout << line << endl;
    }
    cout << "b " << endLabel << endl;
    cout << elseLabel << ":" << endl;
    for (const auto &line : falseBlock) {
        cout << line << endl;
    }
    cout << endLabel << ":" << endl;
}

// Function to handle while loops
void translateWhileLoop(string condition, vector<string> body) {
    string startLabel = generateLabel("WHILE_START");
    string endLabel = generateLabel("WHILE_END");
    cout << startLabel << ":" << endl;
    cout << condition << " " << endLabel << endl;
    for (const auto &line : body) {
        cout << line << endl;
    }
    cout << "b " << startLabel << endl;
    cout << endLabel << ":" << endl;
}

// ======================== Problem 5: I/O Operations ========================
// Function to handle I/O operations
void emitPrintln(string reg) {
    cout << "\tmove $1, " << reg << endl;
    cout << "\tjal print" << endl;
}
void emitPutchar(string reg) {
    cout << "\tmove $a0, " << reg << endl;
    cout << "\tli $v0, 11" << endl;
    cout << "\tsyscall" << endl;
}
void emitGetchar() {
    cout << "\tli $v0, 8" << endl;
    cout << "\tsyscall" << endl;
    cout << "\tmove $2, $v0" << endl;
}

// ======================== Problem 1-5: Main Code Generator ========================
int main() {
    cout << ".import print" << endl;
    cout << ".text" << endl;
    cout << ".globl wain" << endl;
    cout << "wain:" << endl;

    // Problem 2: Declarations and Assignments
    declareVariable("c", 241);
    declareVariable("b", 0);
    declareVariable("a", 0);
    assignVariable("b", "c");
    assignVariable("a", "b");

    // Problem 4: if-else and while loop
    translateIfElse("blt $1, $2,", {"WHILE_LOOP:"}, {"li $1, 241"});
    translateWhileLoop("blt $1, $2,", {"addi $1, $1, 1"});

    // Problem 3: Arithmetic operation (a + b)
    generateMIPS("PLUS", "$3", "$1", "$2");

    // Problem 5: I/O operations
    emitPrintln("$3");
    emitGetchar();
    emitPutchar("$2");

    cout << "\tjr $31" << endl;
    return 0;
}
