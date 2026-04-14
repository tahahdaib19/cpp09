
#include "BitcoinExchange.hpp"




int main(int ac , char **av)

{
    if (ac !=2)
    {
        std::cout<<"invalid input"<<std::endl;
        return 1 ;
    }
    
    BitcoinExchange::calculate_exchange(av[1]);
    return 0;

}