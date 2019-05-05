#include "pvmcontainer.h"
#include <pvm3.h>

namespace pvm
{
    int PvmContainer::addHost(const char* hostname)
    {
        int result = 0;
        struct pvmhostinfo *hostp;
        int info[2];
        char *hosts[] = {const_cast<char*>(hostname)};
        result = pvm_addhosts(hosts, 1, info);
        std::cout<<result<<std::endl;
        return result;
    }
    void PvmContainer::hostInfo()
    {
        int numberOfHosts;
        int numberOfArchitectures;
        struct pvmhostinfo* hostInfo;
        pvm_config(&numberOfHosts, &numberOfArchitectures, &hostInfo);
        std::cout<<hostInfo->hi_name<<std::endl;
    }
}