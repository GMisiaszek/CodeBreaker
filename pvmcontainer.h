#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "pvm3.h"
#include <memory>
#ifndef PVM_H
#define PVM_H
namespace pvm
{
    struct PvmContainer
    {
        int addHost(const char* hostname);
        std::vector<std::tuple<std::string, int, int>> hostInfo();
        std::string getPassword(int);
        char* transformStringToChar(std::string);
    };
} // end namespace pvm
#endif