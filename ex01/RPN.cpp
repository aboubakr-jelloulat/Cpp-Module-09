#include "RPN.hpp"


RPN::RPN() {}

RPN::RPN(const RPN &oth)
{
    (void)oth;
}

RPN &RPN::operator=(const RPN &oth)
{
    (void)oth;
    return *this;
}

RPN::~RPN() {}


int RPN::evalRPN(const std::string &expression)
{
    std::stack<int>   stack;
    std::stringstream stream(expression);
    std::string       token;

    while (stream >> token)
    {
        if (token.length() == 1 && std::isdigit(token[0]))
        {
            stack.push(token[0] - '0');
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
                throw std::logic_error("not enough operands to do this operation");

            int b = stack.top();
            stack.pop();

            int a = stack.top();
            stack.pop();

            if (token == "+")
                stack.push(a + b);
            else if (token == "-")
                stack.push(a - b);
            else if (token == "*")
                stack.push(a * b);
            else
            {
                if (b == 0)
                    throw std::runtime_error("division by zero");
                stack.push(a / b);
            }
        }
        else
        {
            throw std::invalid_argument("invalid token : " + token);
        }
    }

    if (stack.size() != 1)
        throw std::logic_error("invalid expression: too many operands");

    return stack.top();
}

