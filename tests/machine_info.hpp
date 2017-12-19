#ifndef MACHINE_INFO_H
#define MACHINE_INFO_H

//using suggestions from https://stackoverflow.com/questions/504810/how-do-i-find-the-current-machines-full-hostname-in-c-hostname-and-domain-info

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <unistd.h>
#endif

#include <cctype>
#include <algorithm>

namespace compass {

    namespace tests {

        std::string hostname(){

            std::string value = "";
            value.resize(255);

#ifdef WIN32
            TCHAR infoBuf[150];
            DWORD bufCharCount = 150;
			std::fill(value.begin(), value.end(), ' ');
            if( GetComputerName( infoBuf, &bufCharCount ) )
            {
            
                std::copy(&infoBuf[0],&infoBuf[0] + 150, value.begin());
            }
#else
            gethostname(&value[0], 255);
#endif
			std::transform(value.begin(), value.end(), value.begin(),
				[](unsigned char c) {return std::tolower(c); }
				);
            return value;

        }

    };

};

#endif /* MACHINE_INFO_H */
