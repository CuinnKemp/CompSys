#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "ParseTree.h"

class Token : public ParseTree {
    public:
        Token(std::string type, std::string value);
};

#endif /*TOKEN_H*/