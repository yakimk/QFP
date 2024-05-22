#include "Parser.hpp"
#include <stdexcept>
#include <cmath>

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate(double) const {
    return value;
}

double VariableNode::evaluate(double x) const {
    return x;
}

BinaryOpNode::BinaryOpNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right, char op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

double BinaryOpNode::evaluate(double x) const {
    double leftVal = left->evaluate(x);
    double rightVal = right->evaluate(x);
    switch (op) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
        default: throw std::invalid_argument("Unknown operator");
    }
}

PowerNode::PowerNode(std::shared_ptr<ASTNode> base, std::shared_ptr<ASTNode> exponent)
    : base(std::move(base)), exponent(std::move(exponent)) {}

double PowerNode::evaluate(double x) const {
    return std::pow(base->evaluate(x), exponent->evaluate(x));
}

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), pos(0) {}

std::shared_ptr<ASTNode> Parser::parse() {
    return parseExpression();
}

std::shared_ptr<ASTNode> Parser::parseExpression() {
    auto left = parseTerm();
    while (pos < tokens.size() && (tokens[pos].type == TokenType::Operator && (tokens[pos].value == "+" || tokens[pos].value == "-"))) {
        char op = tokens[pos].value[0];
        ++pos;
        auto right = parseTerm();
        left = std::make_shared<BinaryOpNode>(std::move(left), std::move(right), op);
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parseTerm() {
    auto left = parseFactor();
    while (pos < tokens.size() && (tokens[pos].type == TokenType::Operator && (tokens[pos].value == "*" || tokens[pos].value == "/"))) {
        char op = tokens[pos].value[0];
        ++pos;
        auto right = parseFactor();
        left = std::make_shared<BinaryOpNode>(std::move(left), std::move(right), op);
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parseFactor() {
    auto left = parsePrimary();
    while (pos < tokens.size() && tokens[pos].type == TokenType::Power) {
        ++pos;
        auto right = parsePrimary();
        left = std::make_shared<PowerNode>(std::move(left), std::move(right));
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parsePrimary() {
    if (pos >= tokens.size()) throw std::invalid_argument("Unexpected end of expression");

    if (tokens[pos].type == TokenType::Number) {
        double value = std::stod(tokens[pos].value);
        ++pos;
        return std::make_shared<NumberNode>(value);
    }

    if (tokens[pos].type == TokenType::Variable) {
        ++pos;
        return std::make_shared<VariableNode>();
    }

    if (tokens[pos].type == TokenType::LeftParen) {
        ++pos;
        auto node = parseExpression();
        if (pos >= tokens.size() || tokens[pos].type != TokenType::RightParen) {
            throw std::invalid_argument("Missing closing parenthesis");
        }
        ++pos;
        return node;
    }

    throw std::invalid_argument("Unexpected token");
}

std::function<double(double)> parseFunction(const std::string &expression) {
    auto tokens = tokenize(expression);
    Parser parser(std::move(tokens));
    auto ast = parser.parse();
    return [ast](double x) {
        return ast->evaluate(x);
    };
}
