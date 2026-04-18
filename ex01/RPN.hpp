#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
 #include <stdlib.h>


class RPN
{
private:

public:
    RPN(void);
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN(void);

    static void apply_rpn(std::string str);
};

#endif