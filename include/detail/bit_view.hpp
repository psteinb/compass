#ifndef BIT_VIEW_H
#define BIT_VIEW_H

#include <climits>
#include <traits>

namespace compass {

    namespace utility
    {

        template <typename T>
        struct bit_view{

            T& value_;

            static const int width = sizeof(T)*CHAR_BIT;
            static_assert(std::is_integral<T>::value, "compass ");

            bit_view(T& _val):
                value_(_val){}


            bool test(int offset){


            }


        };

    }  // utility


}  // compass

#endif /* BIT_VIEW_H */
