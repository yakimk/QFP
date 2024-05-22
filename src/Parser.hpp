// Parser.hpp

#pragma once

#include <unordered_map>
#include <functional>
#include <cmath>
#include <string>

using MathFunction = std::function<double(double)>;

const std::unordered_map<std::string, MathFunction> mathFunctions = {
    {"sin", [](double x) { return std::sin(x); }},
    {"cos", [](double x) { return std::cos(x); }},
    {"tan", [](double x) { return std::tan(x); }},
    {"asin", [](double x) { return std::asin(x); }},
    {"acos", [](double x) { return std::acos(x); }},
    {"atan", [](double x) { return std::atan(x); }},
    {"sinh", [](double x) { return std::sinh(x); }},
    {"cosh", [](double x) { return std::cosh(x); }},
    {"tanh", [](double x) { return std::tanh(x); }},
    {"exp", [](double x) { return std::exp(x); }},
    {"log", [](double x) { return std::log(x); }},
    {"log10", [](double x) { return std::log10(x); }},
    {"sqrt", [](double x) { return std::sqrt(x); }},
    // {"pow", [](double x, double y) { return std::pow(x, y); }},
    {"fabs", [](double x) { return std::fabs(x); }},
    {"ceil", [](double x) { return std::ceil(x); }},
    {"floor", [](double x) { return std::floor(x); }},
    {"round", [](double x) { return std::round(x); }},
    // {"fmod", [](double x, double y) { return std::fmod(x, y); }} 
};

double parseExpression(const std::string& expr, double x);