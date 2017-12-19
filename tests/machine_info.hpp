#ifndef MACHINE_INFO_H
#define MACHINE_INFO_H

//using suggestions from https://stackoverflow.com/questions/504810/how-do-i-find-the-current-machines-full-hostname-in-c-hostname-and-domain-info

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <unistd.h>
#endif


namespace compass {

    namespace tests {

        std::string hostname(){

            std::string value = "";
            value.resize(255);
            char Name[150];

#ifdef WIN32
            TCHAR infoBuf[150];
            DWORD bufCharCount = 150;
            // memset(Name, 0, 150);
            std::fill()
            if( GetComputerName( infoBuf, &bufCharCount ) )
            {
                // for(int i=0; i<150; i++)
                // {
                //     Name[i] = infoBuf[i];
                // }
                std::copy(&infoBuf[0],&infoBuf[0] + 150, value.data());
            }
#else
            gethostname(&value[0], 255);
#endif
            //strncpy(machineName,Name, 150);
            return value;
        }

    };

};

#endif /* MACHINE_INFO_H */
