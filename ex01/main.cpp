
#include "RPN.hpp"




int main(int ac , char **av)

{
    if (ac !=2)
    {
        std::cerr<<"invalid input"<<std::endl;
        return 1 ;
    }

    RPN::apply_rpn(av[1]);
    
   
    return 0;

}