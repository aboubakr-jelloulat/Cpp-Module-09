#pragma once

#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>

class RPN
{
    RPN();
    RPN(const RPN &oth);
    RPN &operator=(const RPN &oth);
    virtual ~RPN();

    static bool isOperator(const std::string &token);
    static int  applyOperator(const std::string &op, int a, int b);

public:
    static int evalRPN(const std::string &expression);
};
