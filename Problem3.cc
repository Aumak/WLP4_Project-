#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Symbol table to keep track of variables
map<string, int> symbolTable;
int memoryOffset = 0;

// Function to generate MIPS code for binary operations
void generateMIPS(string op, string dest, string src1, string src2) {
    if (op == "PLUS") {
        cout << "	add " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "MINUS") {
        cout << "	sub " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "STAR") {
        cout << "	mul " << dest << ", " << src1 << ", " << src2 << endl;
    } else if (op == "SLASH") {
        cout << "	div " << src1 << ", " << src2 << endl;
        cout << "	mflo " << dest << endl;
    } else if (op == "PCT") {
        cout << "	div " << src1 << ", " << src2 << endl;
        cout << "	mfhi " << dest << endl;
    }
}

// Function to translate WLP4 parse tree to MIPS assembly
void translateExpression(vector<string> tokens) {
    if (tokens.size() == 3) { // Binary operations
        string src1 = "$t0";
        string src2 = "$t1";
        string dest = "$t2";
        generateMIPS(tokens[1], dest, src1, src2);
        cout << "	move $3, " << dest << endl; // Store result in return register
    }
}

int main() {
    cout << ".data" << endl;
    cout << ".text" << endl;
    cout << "	.globl wain" << endl;
    cout << "wain:" << endl;
    cout << "	move $t0, $a0" << endl; // First parameter
    cout << "	move $t1, $a1" << endl; // Second parameter

    vector<string> tokens = {"expr", "PLUS", "term"};
    translateExpression(tokens);

    cout << "	jr $31" << endl;
    return 0;
}
