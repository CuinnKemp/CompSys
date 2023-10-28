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
        
        if(current()->getType() == "identifier" || current()->getValue() == "Main" || current()->getValue() == "main"){
            prev();
            ParseTree* res = compileClass();
            return res;
        } else{
            // cout << "4" << endl;
            throw ParseException();
        }
    }
    // cout << "5" << endl;
    throw ParseException();
    return nullptr;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    
    ParseTree* res = new ParseTree("class","");
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    while (currentItr != tokens.end() && !have("symbol", "}")){
        if (have("keyword", "function") || have("keyword", "method") || have("keyword", "constructor")){
            res->addChild(compileSubroutine());
        } else if (have("keyword", "static") || have("keyword", "field")){
            res->addChild(compileClassVarDec());
        } else {
            // res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
            throw ParseException();
        }

        next();
    }


    if (!have("symbol", "}")){
        // cout << "7" << endl;
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    return res;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* res = new ParseTree("classVarDec","");
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && !(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();

    while (currentItr != tokens.end() && have("symbol", ",")){
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        if (!(current()->getType() == "identifier")){
            throw ParseException();
            return NULL;
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return res;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    
    ParseTree* res = new ParseTree("subroutine","");
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    if (current()->getType() != "keyword" && current()->getType() != "identifier"){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (current()->getType() != "identifier"){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    
    if (!have("symbol", "(")){
        // cout << "8" << endl;
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (!have("symbol", ")")){
        res->addChild(compileParameterList());
    }
    
    if (!have("symbol", ")")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    
    next();
    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    res->addChild(compileSubroutineBody());

    return res;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* res = new ParseTree("parameterList","");

    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    
    if (current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    
    if (!have("symbol", ",")){
        return res;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    while (currentItr != tokens.end() && !have("symbol", ")")){
        if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
            throw ParseException();
            return NULL;
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        
        
        if (current()->getType() != "identifier"){
            throw ParseException();
            return NULL;
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();

        
        if (have("symbol", ",") ){
            res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
            next();
            if (have("symbol", ")")){
                throw ParseException();
            }
        }
        
    }
    return res;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* res = new ParseTree("subroutineBody","");
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    while (currentItr != tokens.end() && !have("symbol", "}")){
        if (have("keyword", "var")){
            res->addChild(compileVarDec());
            next();
            continue;
        }
        res->addChild(compileStatements());
    }
    if (!have("symbol", "}")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    return res;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* res = new ParseTree("varDec","");
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();

    while (currentItr != tokens.end() && have("symbol", ",")){
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        if (!(current()->getType() == "identifier")){
            throw ParseException();
            return NULL;
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
        return NULL;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return res;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* res = new ParseTree("statements","");
    
    while (have("keyword", "let") || have("keyword", "if") || have("keyword", "while") || have("keyword", "do") || have("keyword", "return")){
        if (current()->getType() == "keyword"){
            if (current()->getValue() == "let"){
                res->addChild(compileLet());
            } else if (current()->getValue() == "if"){
                res->addChild(compileIf());
            } else if (current()->getValue() == "while"){
                res->addChild(compileWhile());
            } else if (current()->getValue() == "do"){
                res->addChild(compileDo());
            } else if (current()->getValue() == "return"){
                res->addChild(compileReturn());
            } else{
                throw ParseException();
                return NULL;
            }
            next();
        }
    }


    return res;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* res = new ParseTree("letStatement","");
    if (!have("keyword", "let")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (current()->getType() != "identifier"){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    if (have("symbol", "[")){
        res->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        res->addChild(compileExpression());
        next();
        if (!have("symbol", "]")){
            throw ParseException();
        }
        res->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
    }
    

    if (!have("symbol", "=")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileExpression());
    next();
    
    if (!have("symbol", ";")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return res;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* res = new ParseTree("ifStatement","");

    if (!have("keyword", "if")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    if (!have("symbol", "(")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileExpression());
    next();

    if (!have("symbol", ")")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileStatements());
    
    if (!have("symbol", "}")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("keyword", "else")){
        return res;
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
        
    

    res->addChild(compileStatements());

    if (!have("symbol", "}")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return res;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* res = new ParseTree("whileStatement","");
    if (!have("keyword", "while")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "(")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileExpression());
    next();

    if (!have("symbol", ")")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileStatements());
    next();

    if (!have("symbol", "}")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));


    return res;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* res = new ParseTree("doStatement","");

    if (!have("keyword", "do")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileExpression());
    next();
    
    if (!have("symbol", ";")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return res;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* res = new ParseTree("returnStatement","");

    if (!have("keyword", "return")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    res->addChild(compileExpression());
    next();
    
    if (!have("symbol", ";")){
        throw ParseException();
    }
    res->addChild(new ParseTree(current()->getType(), current()->getValue() ));


    return res;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* res = new ParseTree("expression", "");
    if (have("keyword", "skip")){
        res->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        return res;
    }
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
        // cout << "1" << endl;
        throw ParseException(); // or some other appropriate action
    }
}
void CompilerParser::prev(){
    if (currentItr != tokens.begin()) {
        --currentItr;
    } else {
        // You've reached the end of the list, and trying to advance is unsafe.
        // You can choose to throw an exception or handle this situation accordingly.
        // cout << "2" << endl;
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
        // cout << "2" << endl;
        throw ParseException(); // or some other appropriate action
    }
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    try{
        if (current()->getType() == expectedType && current()->getValue() == expectedValue){
            return true;
        }
    } catch (...){
        return false;
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
        // cout << "3" << endl;
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
