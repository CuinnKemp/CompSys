#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    list<Token*> tokens;
    // tokens.push_back(new Token("keyword", "class"));
    // tokens.push_back(new Token("identifier", "Main"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "field"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "myFunc"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "b"));
    // // tokens.push_back(new Token("symbol", ","));
    // // tokens.push_back(new Token("keyword", "int"));
    // // tokens.push_back(new Token("identifier", "c"));
    // // tokens.push_back(new Token("symbol", ","));
    // // tokens.push_back(new Token("keyword", "int"));
    // // tokens.push_back(new Token("identifier", "d"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "var"));
    // tokens.push_back(new Token("keyword", "boolean"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("symbol", "}"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("keyword", "class"));
    // tokens.push_back(new Token("keyword", "Main"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "constructor"));
    // tokens.push_back(new Token("identifier", "Test"));
    // tokens.push_back(new Token("identifier", "new"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));
    // tokens.push_back(new Token("symbol", "}"));

    //param testing
    // tokens.push_back(new Token("keyword", "boolean"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "c"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("identifier", "test"));
    // tokens.push_back(new Token("identifier", "d"));
    tokens.push_back(new Token("keyword", "while"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("integerConstant", "1"));
    tokens.push_back(new Token("symbol", "+"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "+"));
    tokens.push_back(new Token("integerConstant", "1"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));



    

    try {
        CompilerParser parser(tokens);
        // ParseTree* result = parser.compileProgram();
        ParseTree* result = parser.compileWhile();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}