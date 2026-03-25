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

public:
    static int evalRPN(const std::string &expression);
};
