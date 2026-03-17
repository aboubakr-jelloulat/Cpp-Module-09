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


bool RPN::isOperator(const std::string &token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOperator(const std::string &op, int a, int b)
{
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("division by zero");
        return a / b;
    }
    throw std::invalid_argument("unknown operator: " + op);
}

int RPN::evalRPN(const std::string &expression)
{
    std::stack<int>  stack;
    std::stringstream stream(expression);
    std::string       token;

    while (stream >> token)
    {
        if (token.length() == 1 && std::isdigit(token[0]))
        {
            stack.push(token[0] - '0');
        }
        else if (isOperator(token))
        {
            if (stack.size() < 2)
                throw std::logic_error("not enough operands for operator '" + token + "'");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            stack.push(applyOperator(token, a, b));
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
