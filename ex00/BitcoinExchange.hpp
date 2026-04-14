
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <limits>
enum input_status
{
    INVALID_LINE_FORMAT,
    INVALID_DATE_FORMAT,
    INVALID_VALUE_FORMAT,
    VALID_LINE
};
class BitcoinExchange
{
private:

public:
    BitcoinExchange(void);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange(void);
    static void calculate_exchange(std::string input);

};

#endif