#ifndef PARSER_HPP
#define PARSER_HPP

#include "Tokenizer.hpp"
#include <memory>
#include <functional>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate(double x) const = 0;
};

class NumberNode : public ASTNode {
    double value;
public:
    explicit NumberNode(double value);
    double evaluate(double) const override;
};

class VariableNode : public ASTNode {
public:
    double evaluate(double x) const override;
};

class BinaryOpNode : public ASTNode {
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
    char op;
public:
    BinaryOpNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right, char op);
    double evaluate(double x) const override;
};

class PowerNode : public ASTNode {
    std::shared_ptr<ASTNode> base;
    std::shared_ptr<ASTNode> exponent;
public:
    PowerNode(std::shared_ptr<ASTNode> base, std::shared_ptr<ASTNode> exponent);
    double evaluate(double x) const override;
};

class UnaryFuncNode : public ASTNode {
    std::shared_ptr<ASTNode> arg;
    std::function<double(double)> func;
public:
    UnaryFuncNode(std::shared_ptr<ASTNode> arg, std::function<double(double)> func);
    double evaluate(double x) const override;
};

class Parser {
    std::vector<Token> tokens;
    size_t pos;

    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
    std::shared_ptr<ASTNode> parsePrimary();

public:
    explicit Parser(std::vector<Token> tokens);
    std::shared_ptr<ASTNode> parse();
};

std::function<double(double)> parseFunction(const std::string &expression);

#endif