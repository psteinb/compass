#ifndef COMPASS_DEFINITIONS_H
#define COMPASS_DEFINITIONS_H

namespace compass {

    namespace compiletime {

        //cpuid register locations
        static const int eax = 0;
        static const int ebx = 1;
        static const int ecx = 2;
        static const int edx = 3;


    };

    namespace runtime {
        //empty for now
    };

    namespace rt = runtime;
    namespace ct = compiletime;

};

#endif /* DEFINITIONS_H */
