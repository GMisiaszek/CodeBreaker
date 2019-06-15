#include "pvmcontainer.h"
#include <vector>
#include <string>
#include <sstream>
#include <pvm3.h>
#include <cstring>
#include <memory>
#define SLAVENAME "slave.o"

namespace pvm
{
    int PvmContainer::addHost(const char* hostname)
    {
        int result = 0;
        int info;
        char *hosts[] = {const_cast<char*>(hostname)};
        pvm_addhosts(hosts, 1, &info);
        std::cout<<info<<std::endl;
        return info;
    }
    std::vector<std::tuple<std::string, int, int>> PvmContainer::hostInfo()
    {
        int numberOfHosts;
        int numberOfArchitectures;
        std::vector<std::tuple<std::string, int, int>> hosts;
        struct pvmhostinfo* hostInfo;
        pvm_config(&numberOfHosts, &numberOfArchitectures, &hostInfo);
        std::cout<<hostInfo->hi_name<<std::endl;
        for(int i = 0; i < numberOfHosts; ++i)
        {
           auto inputTuple = std::make_tuple(hostInfo[i].hi_name, hostInfo[i].hi_speed, hostInfo[i].hi_tid);
           hosts.push_back(std::move(inputTuple)); 
        }
        return hosts;
    }
    std::string PvmContainer::getPassword(int slavenum)
    {
        int myTid;
        int nProc;
        int tids[slavenum];
        char password[20];
        pvm_catchout(stdout);
        std::cout<<"AAA";
        nProc = pvm_spawn(SLAVENAME, NULL, PvmTaskDefault, "", slavenum, tids);
        myTid = pvm_mytid();
        if(slavenum > nProc) 
          slavenum = nProc;  

        int tries = 0;
        while(tries < 27)
        {
        for(int i = 0; i < slavenum; i++)
        {
            std::string beg = "";
            std::string end = "";
            beg += static_cast<char>(97+tries) + "aa";
            end += static_cast<char>(97+tries) + "zz";
            pvm_initsend(PvmDataDefault);
            pvm_pkint(&myTid, 1, 1);
	 		pvm_pkstr(const_cast<char*>(beg.c_str()));
            pvm_pkstr(const_cast<char*>(end.c_str()));
            pvm_send(tids[i], 3);
            beg.clear();
            end.clear();
            tries++;

        }
        for(int i = 0; i < slavenum; i++)
        {
            pvm_recv(-1, 4);
            pvm_upkstr(password);
            std::string sPwd(password);
            if(sPwd != "")
            {
                return password;
            }
        }
        }
        std::string beg;
        std::string end;
        beg += static_cast<char>(105);
        end += static_cast<char>(105);
        beg += "aa";
        end += "zz";
        beg += end;
        auto passwords = transformStringToChar(beg);
        pvm_initsend(PvmDataDefault);
        pvm_pkint(&myTid, 1, 1);
	 	pvm_pkstr(passwords);
        pvm_send(tids[0], 3);
        pvm_recv(-1,4);
        pvm_upkstr(password);
        delete[] passwords;
        return password;

    }

    char* PvmContainer::transformStringToChar(std::string str)
    {
        const char* str_c = str.c_str();
        char* strc = new char(str.size()+1);
        std::strcpy(strc, str_c);
        return strc;
    } 
}