#include "Tokenizer.hpp"
#include <cctype>
#include <stdexcept>

std::vector<Token> tokenize(const std::string &expression) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.length()) {
        char current = expression[i];

        if (std::isspace(current)) {
            ++i;
            continue;
        }

        if (std::isdigit(current) || current == '.') {
            size_t start = i;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                ++i;
            }
            tokens.push_back({TokenType::Number, expression.substr(start, i - start)});
        } else if (std::isalpha(current)) {
            size_t start = i;
            while (i < expression.length() && std::isalpha(expression[i])) {
                ++i;
            }

            const std::string readAlhaVal = expression.substr(start, i - start);
            tokens.push_back({TokenType::Variable, readAlhaVal});

        } else if (current == '*' && i + 1 < expression.length() && expression[i + 1] == '*') {
            tokens.push_back({TokenType::Power, "**"});
            i += 2;

        } else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '(' || current == ')') {
            TokenType type = TokenType::Operator;
            if (current == '(') type = TokenType::LeftParen;
            else if (current == ')') type = TokenType::RightParen;
            tokens.push_back({type, std::string(1, current)});
            ++i;

        } else {
            throw std::invalid_argument("Invalid character in expression");
        }
    }

    return tokens;
}
