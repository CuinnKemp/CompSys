#include "CompilerParser.h"
#include <iostream>
using namespace std;


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currentItr = this->tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (have("keyword","class")){
        next();
        current();
        if(current()->getType() == "identifier"){
            ParseTree* res = compileClass();
            return res;
        } else{
            throw ParseException();
        }
    }
    throw ParseException();
    return nullptr;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* res = new ParseTree("class", "");
    res->addChild(new ParseTree("keyword", "class"));
    res->addChild(new ParseTree("identifier",  current()->getValue()));
    next();
    if (have("symbol", "{")){
        res->addChild(new ParseTree("symbol", "{"));
        res->addChild(compileClassVarDec());
    } else{
        throw ParseException();
        return NULL;
    }

    if (!have("symbol", "}")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree("symbol", "}"));
    
    return res;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* res = new ParseTree("classVarDec", "");
    
    next();
    while (currentItr != tokens.end() && !have("symbol", "}")){
        if (have("keyword", "function")){
            res->addChild(compileSubroutine());

        } else{
            res->addChild(new ParseTree(current()->getType(), current()->getValue()));
        }
        next();
    }

    return res;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* res = new ParseTree("subroutine", "");
    res->addChild(new ParseTree("keyword", "function"));

    next();
    if (current()->getType() != "keyword"){
        throw ParseException();
    }
    res->addChild(new ParseTree("keyword", current()->getValue()));

    next();
    if (current()->getType() != "identifier"){
        throw ParseException();
    }
    res->addChild(new ParseTree("identifier", current()->getValue()));

    next();
    if (!have("symbol", "(")){
        throw ParseException();
    }
    res->addChild(new ParseTree("symbol", "("));
    
    next();
    res->addChild(compileParameterList());

    if (!have("symbol", ")")){
        throw ParseException();
    }
    res->addChild(new ParseTree("symbol", ")"));

    next();
    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    res->addChild(compileSubroutineBody());


    return NULL;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* res = new ParseTree("parameterList", "");
    while (currentItr != tokens.end() && !have("symbol", ")")){
        if (have("keyword", "var")){
            res->addChild(compileVarDec());
            if (!have("symbol", ";")){
                throw ParseException();
                return NULL;
            }
            next();
            continue;
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
    }
    return res;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* res = new ParseTree("symbol", "{");
    while (currentItr != tokens.end() && !have("symbol", "}")){
        next();
        res->addChild(new ParseTree(current()->getType(), current()->getValue()));
    }
    return res;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* res = new ParseTree("keyword", "var");
    while (currentItr != tokens.end() && !have("symbol", ";")){
        next();
        res->addChild(new ParseTree(current()->getType(), current()->getValue()));
    }

    return res;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (currentItr != tokens.end()) {
        ++currentItr;
    } else {
        // You've reached the end of the list, and trying to advance is unsafe.
        // You can choose to throw an exception or handle this situation accordingly.
        throw ParseException(); // or some other appropriate action
    }
}
void CompilerParser::prev(){
    if (currentItr != tokens.begin()) {
        --currentItr;
    } else {
        // You've reached the end of the list, and trying to advance is unsafe.
        // You can choose to throw an exception or handle this situation accordingly.
        throw ParseException(); // or some other appropriate action
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (currentItr != tokens.end()) {
        return *currentItr;
    } else {
        // You've reached the end of the list, and trying to access the current token is unsafe.
        // You can choose to throw an exception or handle this situation accordingly.
        throw ParseException(); // or some other appropriate action
    }
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if (current()->getType() == expectedType && current()->getValue() == expectedValue){
        return true;
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (!this->have(expectedType, expectedValue)){
        throw ParseException();
        return NULL;
    }
    Token* hold = this->current();
    this->next();

    return hold;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
