#ifndef COMPASS_BIT_VIEW_H
#define COMPASS_BIT_VIEW_H

#include <climits>
#include <type_traits>

namespace compass {

    namespace utility
    {

        template <typename T>
        struct bit_view{

            T& value_;

            static const int width = sizeof(T)*CHAR_BIT;
            static_assert(std::is_integral<T>::value, "compass bitview used with non-integral type (not supported)");

            bit_view(T& _val):
                value_(_val){}


            bool test(int offset) const {

                bool value = false;
                if(offset>(width-1))
                    return value;

                const int mask = 1 << offset;
                value = value_ & mask;

                return value;
            }

            void set(int offset)  {

                if(offset>(width-1))
                    return ;

                const int mask = 1 << offset;
                value_ = value_ | mask;

                return;
            }

            T range(std::uint32_t _begin, std::uint32_t _end){

                T value = 0;
                if(_begin >= width || _end <= _begin)
                    return value;

                const T mask = ( (~value) - 1 ) << (_end-1);
                value = (value_ >> _begin) & ~mask;
                return value;


            }


        };

    }  // utility


}  // compass

#endif /* BIT_VIEW_H */
