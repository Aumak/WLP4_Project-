#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int labelCount = 0; // Counter for unique labels
map<string, int> symbolTable; // Maps variables to memory locations

string generateLabel(const string &prefix) {
    return prefix + to_string(labelCount++);
}

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

void translateCondition(string op, string reg1, string reg2) {
    if (op == "==") cout << "beq " << reg1 << ", " << reg2 << ", ";
    else if (op == "!=") cout << "bne " << reg1 << ", " << reg2 << ", ";
    else if (op == "<") cout << "blt " << reg1 << ", " << reg2 << ", ";
    else if (op == "<=") cout << "ble " << reg1 << ", " << reg2 << ", ";
    else if (op == ">") cout << "bgt " << reg1 << ", " << reg2 << ", ";
    else if (op == ">=") cout << "bge " << reg1 << ", " << reg2 << ", ";
}

int main() {
    cout << "wain:" << endl;
    
    // if-else logic for `if (a < b) { while (a < b) { a = a + 1; } } else { a = 241; }`
    translateIfElse("blt $1, $2,", {"WHILE_LOOP:"}, {"li $1, 241"});
    translateWhileLoop("blt $1, $2,", {"addi $1, $1, 1"});
    
    cout << "move $3, $1" << endl;
    cout << "jr $31" << endl;
    return 0;
}