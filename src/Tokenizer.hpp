#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

enum class TokenType {
    Number,
    Variable,
    Operator,
    LeftParen,
    RightParen,
    Power
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &expression);

#endif // TOKENIZER_HPP
