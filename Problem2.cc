#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class CodeGenerator {
private:
    map<string, int> symbolTable; 
    int offset = 0; 

public:
    void declareVariable(const string &var, int value) {
        offset -= 4; 
        symbolTable[var] = offset;
        cout << "li $3, " << value << endl; 
        cout << "sw $3, " << offset << "($29)" << endl; 
    }

    void assignVariable(const string &var1, const string &var2) {
        if (symbolTable.find(var1) == symbolTable.end() || symbolTable.find(var2) == symbolTable.end()) {
            cerr << "Error: Undefined variable." << endl;
            return;
        }
        cout << "lw $3, " << symbolTable[var2] << "($29)" << endl;
        cout << "sw $3, " << symbolTable[var1] << "($29)" << endl;
    }
    
    void generateReturn(const string &var) {
        if (symbolTable.find(var) == symbolTable.end()) {
            cerr << "Error: Undefined return variable." << endl;
            return;
        }
        cout << "lw $3, " << symbolTable[var] << "($29)" << endl; 
    }
};

int main() {
    CodeGenerator gen;
    
    // Simulating the input program
    gen.declareVariable("c", 241);
    gen.declareVariable("b", 0);
    gen.declareVariable("a", 0);
    
    gen.assignVariable("b", "c");
    gen.assignVariable("a", "b");
    
    gen.generateReturn("a");
    
    return 0;
}
