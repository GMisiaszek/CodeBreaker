#include <iostream>
#include <string>
#include "pvm3.h"
#ifndef PVM_H
#define PVM_H
namespace pvm
{
    struct PvmContainer
    {
        int addHost(const char* hostname);
        void hostInfo();
    };
} // end namespace pvm
#endif