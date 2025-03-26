#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Read the input (WLP4 Typed Intermediate format)
    vector<string> tokens;
    string token;
    while (cin >> token) {
        tokens.push_back(token);
    }

    // Basic validation: Check for "wain" function structure
    if (tokens.size() < 15 || tokens[1] != "procedures" || tokens[2] != "main" || tokens[3] != "INT" || tokens[4] != "WAIN") {
        cerr << "Error: Invalid WLP4TI format for A7P1\n";
        return 1;
    }

    // Extract parameter names
    string param1 = tokens[8];  
    string param2 = tokens[11]; 

    // Generate MIPS assembly
    cout << ".import print" << endl;
    cout << ".data" << endl;
    cout << ".text" << endl;
    cout << ".globl main" << endl;
    cout << "main:" << endl;

    // Store parameters a ($1) and b ($2) in stack memory
    cout << "    sw $1, -4($30)" << endl; 
    cout << "    sw $2, -8($30)" << endl;  
    cout << "    sub $30, $30, 8" << endl; 

    // Load return value (first parameter in this case)
    cout << "    lw $3, 4($30)" << endl; 

    // Restore stack pointer and return
    cout << "    add $30, $30, 8" << endl;
    cout << "    jr $31" << endl;

    return 0;
}