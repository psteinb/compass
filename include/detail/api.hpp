#ifndef COMPASS_API_H
#define COMPASS_API_H

#include "detail/dispatch.hpp"
#include "detail/definitions.hpp"

#include <type_traits>
#include <cstdint>
#include <string>
#include <thread>

namespace compass {

    namespace runtime {


        static bool works() {

            using current_arch_t = ct::arch::type;
            return detail::works(current_arch_t());

        }

        static std::string vendor() {

            using current_arch_t = ct::arch::type;
            return detail::vendor(current_arch_t());

        }

        static std::string brand() {

            using current_arch_t = ct::arch::type;
            return detail::brand(current_arch_t());

        }

        static std::string device_name() {

            using current_arch_t = ct::arch::type;
            return detail::device_name(current_arch_t());

        }


        static std::uint32_t threads() {

            return std::thread::hardware_concurrency();

        }


        template <typename feature_t>
        static bool has(feature_t) {

            using current_arch_t = ct::arch::type;
            return detail::has(feature_t(),current_arch_t());

        }


        namespace detail {

            static std::uint32_t accumulate(std::uint32_t value){
                return value;
            }

            template < typename T, typename... features_t >
            static std::uint32_t accumulate(std::uint32_t value,
                                        T head,
                                        features_t... tail)
            {

                std::uint32_t local = compass::runtime::has(head);
                value = (value <<= 1) | local;

                return accumulate(value,tail...);

            }

        };


        template <typename... feature_t>
        static std::uint32_t accumulate(feature_t... features) {

            static const int pack_size = sizeof...(features);
            static_assert(pack_size <= 32, "[compass::runtime::accumulate] unable to handle more than 32 features" );

            std::uint32_t value = compass::runtime::detail::accumulate( 0u, features...);
            return value;

        }

        namespace size {

            struct cacheline{

                static std::uint32_t levels_available(){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cacheline::levels_available(current_arch_t());

                }

                static std::uint32_t level(int _lvl){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cacheline::level(_lvl,current_arch_t());

                }
            };

            struct cache{

                static std::uint32_t levels_available(){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cache::levels_available(current_arch_t());

                }

                static std::uint32_t level(int _lvl){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cache::level(_lvl,current_arch_t());

                }
            };


        };//size

    };//namespace runtime

} // compass

#endif /* API_H */
