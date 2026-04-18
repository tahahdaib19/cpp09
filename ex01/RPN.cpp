

#include "RPN.hpp"


RPN::RPN(void)
{
}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return (*this);
}

RPN::~RPN(void)
{
}



void RPN::apply_rpn(std::string str)
{
    std::stack<int> s;
    std::string opetrations = "+ - * /";
    std::istringstream iss(str);
    std::string token;

    while (iss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (s.size() < 2)
            {
                std::cerr << "Error\n";
                return;
            }
            
            int b = s.top();
            s.pop();
            int a = s.top();
            s.pop();

            if (token == "+")
                s.push(a + b);
            else if (token == "-")
                s.push(a - b);
            else if (token == "*")
                s.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                {
                    std::cerr<<"Error: division by zero\n";
                    return;
                }
                s.push(a / b);
            }
        }

        else if(token.size() == 1 && isdigit(token[0]))
            s.push(atoi(token.c_str()));
        else
        {
            std::cerr<<"Error\n";
            return;
        }
    }

    if (s.size() != 1)
    {
        std::cerr<<"Error\n";
        return;
    }

    std::cout << s.top() << "\n";
}
