#include <iostream>
#include <string>
#include <cmath>
#include <functional>

// Function to parse a mathematical expression and return a corresponding function
double parseExpression(const std::string& expr, double x) {
    // Redefine the input expression by replacing all occurrences of 'x' with "_x"
    std::cout <<"starting "<< expr << '\n';
    std::string updatedExpr = expr;
    size_t pos = updatedExpr.find("x");
    while (pos != std::string::npos) {
        updatedExpr.replace(pos, 1, std::to_string(x));
        pos = updatedExpr.find("x", pos + 1);
    }
    std::cout << "updated "<< updatedExpr << '\n';
    double res = std::atof(updatedExpr.c_str());
    std::cout << "res "<< res << '\n';
    return res;
    // Return the lambda function that evaluates the parsed expression
    // return [updatedExpr](double _x) {
    //     return std::atof(updatedExpr.c_str());
    // };
}