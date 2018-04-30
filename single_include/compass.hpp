#ifndef _COMPASS_HPP_
#define _COMPASS_HPP_
#ifndef COMPASS_API_H
#define COMPASS_API_H
#ifndef COMPASS_DISPATCH_H_
#define COMPASS_DISPATCH_H_
#ifndef DETAIL_DETECT_OS_H
#define DETAIL_DETECT_OS_H




#if (defined(__linux) || defined(__linux__) || defined(__gnu_linux__))
#define COMPASS_CT_OS_LINUX
#endif

#if (defined(__APPLE__) || defined(__MACH__))
#define COMPASS_CT_OS_MACOS
#endif

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__))
#define COMPASS_CT_OS_WINDOWS
#endif
#ifndef COMPASS_DEFINITIONS_H
#define COMPASS_DEFINITIONS_H

namespace compass {

    namespace compiletime {


        static const int eax = 0;
        static const int ebx = 1;
        static const int ecx = 2;
        static const int edx = 3;

        struct unsupported_tag { static int dummy; };
        struct through_os_tag {};
    };

    namespace runtime {

    };

    namespace rt = runtime;
    namespace ct = compiletime;

};

#endif
namespace compass {

    namespace compiletime {

        struct linux_tag {};
        struct macos_tag {};
        struct windows_tag {};

        struct platform {

#ifdef COMPASS_CT_OS_LINUX
            typedef linux_tag type;
#endif

#ifdef COMPASS_CT_OS_MACOS
            typedef macos_tag type;
#endif

#ifdef COMPASS_CT_OS_WINDOWS
            typedef windows_tag type;
#endif

#if (!(defined(COMPASS_CT_OS_LINUX) || defined(COMPASS_CT_OS_MACOS) || defined(COMPASS_CT_OS_WINDOWS)))
            typedef unsupported_tag type;
            static_assert(true,
              "\ncompass is not aware of this operating system \nPlease create an issue under https://github.com/psteinb/compass\n\n");
#endif



        };

    }

}
#endif
#ifndef DETAIL_DETECT_COMPILER_H
#define DETAIL_DETECT_COMPILER_H



#ifdef __clang__
    #define COMPASS_CT_COMP_CLANG
#else

    #ifdef __INTEL_COMPILER
        #define COMPASS_CT_COMP_INTEL
    #else

      #ifdef __GNUC__
      #define COMPASS_CT_COMP_GCC
      #endif

   #endif

#endif

#if (defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD))
#define COMPASS_CT_COMP_MSVC
#endif




namespace compass {

    namespace compiletime {

        struct gnu_tag {};
        struct llvm_tag {};
        struct msvc_tag {};
        struct intel_tag {};

        struct toolchain {

#ifdef COMPASS_CT_COMP_CLANG
            typedef llvm_tag type;
#endif

#ifdef COMPASS_CT_COMP_GCC
            typedef gnu_tag type;
#endif

#ifdef COMPASS_CT_COMP_MSVC
            typedef msvc_tag type;
#endif

#ifdef COMPASS_CT_COMP_INTEL
            typedef intel_tag type;
#endif

        };

        static const bool is_gnu(){

            using current_toolchain_t = toolchain::type;

            bool value = std::is_same<current_toolchain_t,gnu_tag>::value;
            return value;

        }

        static const bool is_llvm(){

            using current_toolchain_t = toolchain::type;
            bool value = std::is_same<current_toolchain_t,llvm_tag>::value;
            return value;

        }

        static const bool is_msvc(){

            using current_toolchain_t = toolchain::type;
            bool value = std::is_same<current_toolchain_t,msvc_tag>::value;
            return value;

        }

        static const bool is_intel(){

            using current_toolchain_t = toolchain::type;
            bool value = std::is_same<current_toolchain_t,intel_tag>::value;
            return value;

        }

    }

}

#endif
#ifndef DETAIL_DETECT_ARCHITECTURE_H
#define DETAIL_DETECT_ARCHITECTURE_H







#if (defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64))
#define COMPASS_CT_ARCH_X86
#define COMPASS_CT_ARCH_64BITS

#undef COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__M_I86) || defined(_M_IX86))
#define COMPASS_CT_ARCH_X86
#undef COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(__powerpc64__) || defined(_ARCH_PPC64) || defined(__ppc64__))
#define COMPASS_CT_ARCH_POWER
#define COMPASS_CT_ARCH_64BITS
#define COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__PPC__) || defined(__ppc__))
#define COMPASS_CT_ARCH_POWER
#define COMPASS_CT_ARCH_UNSUPPORTED
#endif




#include <climits>

namespace compass {

    namespace compiletime {



        struct x86_tag {};
        struct arm_tag {};
        struct power_tag {};

        struct arch {

#ifdef COMPASS_CT_ARCH_X86
            typedef x86_tag type;
#endif

#ifdef COMPASS_CT_ARCH_UNSUPPORTED
            typedef unsupported_tag type;
            static_assert(std::is_same<compass::ct::arch::type,compass::ct::unsupported_tag>::value,
                          "\n\ncompass is not aware of this architecture \nPlease create an issue under https://github.com/psteinb/compass\n\n");
#endif

            const static int bitness = sizeof(void*)*CHAR_BIT;



        };

    }

}

#endif
#ifdef COMPASS_CT_ARCH_X86
#ifndef COMPASS_CT_PREPROCESSOR_IMPL_H_
#define COMPASS_CT_PREPROCESSOR_IMPL_H_



#ifndef WIN32

#if defined(__SSE2__) || defined(__SSE2_MATH__)
    #define COMPASS_CT_HAS_SSE2 1
   #endif

#if defined(__SSE3__) && defined(__SSSE3__)
    #define COMPASS_CT_HAS_SSE3 1
   #endif

#if defined(__SSE4_2__) && defined(__SSE4_1__)
    #define COMPASS_CT_HAS_SSE4 1
   #endif

#else

    #if _M_IX86_FP >= 2
        #define COMPASS_CT_HAS_SSE2 1
        #define COMPASS_CT_HAS_SSE3 1
        #define COMPASS_CT_HAS_SSE4 1
    #endif
#endif
#ifndef COMPASS_TAGS_H_
#define COMPASS_TAGS_H_


namespace compass {


    namespace feature {




        struct sse {};
        struct sse2 {};
        struct sse3 {};
        struct sse4 {};


        struct avx {};
        struct avx2 {};


    };


};
#endif
namespace compass {

  namespace compiletime {

    template<typename feature_t>
    struct has{
      static const bool enabled = false;
    };

    template<>
    struct has<feature::sse2>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE2
     true;
#else
     false;
#endif

    };

    template<>
    struct has<feature::sse3>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE3
     true;
#else
     false;
#endif

    };

    template<>
    struct has<feature::sse4>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE4
     true;
#else
     false;
#endif

    };

  };
};

#endif
#ifndef COMPASS_RT_X86_IMPL_H_
#define COMPASS_RT_X86_IMPL_H_
#ifndef COMPASS_RT_X86_CPUID_H



#ifdef COMPASS_CT_ARCH_X86
#define COMPASS_RT_X86_CPUID_H
#ifndef COMPASS_X86_CPUID_COMMON_H
#define COMPASS_X86_CPUID_COMMON_H

#ifndef COMPASS_CT_COMP_MSVC
#include "cpuid.h"

namespace compass {

  namespace runtime {

    static int extended_get_cpuid(std::uint32_t* regs,
                                  std::uint32_t in_eax = 0,
                                  std::uint32_t in_ecx = 0){

#ifdef __get_cpuid_count
      return __get_cpuid_count(in_eax,
                               in_ecx,
                               &regs[ct::eax],
                               &regs[ct::ebx],
                               &regs[ct::ecx],
                               &regs[ct::edx]);
#endif


      unsigned int clean_level = in_eax & 0x80000000;

      if (__get_cpuid_max (clean_level, 0) < in_eax)
        return 0;

      __cpuid_count(in_eax, in_ecx,
                    regs[ct::eax],
                    regs[ct::ebx],
                    regs[ct::ecx],
                    regs[ct::edx]
        );

      return 1;
    }

  };

};
#endif
#endif
#ifndef COMPASS_RT_X86_LLVM_CPUID_H_
#define COMPASS_RT_X86_LLVM_CPUID_H_



#ifdef COMPASS_CT_COMP_CLANG



#include <array>
#include <cstdint>

namespace compass {


  namespace runtime {

    static std::array<std::uint32_t,4> cpuid(std::uint32_t in_eax = 0,
                                             std::uint32_t in_ebx = 0,
                                             std::uint32_t in_ecx = 0,
                                             std::uint32_t in_edx = 0){

      std::array<std::uint32_t,4> regs = {in_eax,0,in_ecx,0};

      __cpuid_count(in_eax,
                    in_ecx,
                    regs[ct::eax],
                    regs[ct::ebx],
                    regs[ct::ecx],
                    regs[ct::edx]
        );

      if (in_eax >= 13)
        __cpuid_count (in_eax, 1, regs[ct::eax], regs[ct::ebx], regs[ct::ecx], regs[ct::edx]);
      else if (in_eax >= 7)
        __cpuid_count (in_eax, 0, regs[ct::eax], regs[ct::ebx], regs[ct::ecx], regs[ct::edx]);

      return regs;

    }



  };

};
#endif
#endif
#ifndef COMPASS_RT_X86_GNU_CPUID_H_



#ifdef COMPASS_CT_COMP_GCC

#define COMPASS_RT_X86_GNU_CPUID_H_




#include <array>
#include <cstdint>


namespace compass {

  namespace runtime {

    static std::array<std::uint32_t,4> cpuid(std::uint32_t in_eax = 0,
                                             std::uint32_t in_ebx = 0,
                                             std::uint32_t in_ecx = 0,
                                             std::uint32_t in_edx = 0){

      std::array<std::uint32_t,4> regs = {in_eax,0,in_ecx,0};







      int gnu_cpuid_rvalue = compass::runtime::extended_get_cpuid(regs.data(),
                                                              in_eax,
                                                              in_ecx);
      if(gnu_cpuid_rvalue < 1){
        return {0,0,0,0};
      }

      return regs;

    }

  };

};
#endif
#endif
#ifndef COMPASS_CT_MSVC_IMPL_H_



#ifdef COMPASS_CT_COMP_MSVC

#define COMPASS_CT_MSVC_IMPL_H_

#include "intrin.h"

#include <array>
#include <bitset>
#include <cstdint>



namespace compass {

  namespace runtime {



    static std::array<std::uint32_t, 4> cpuid(std::uint32_t in_eax = 0,
                                              std::uint32_t in_ebx = 0,
                                              std::uint32_t in_ecx = 0,
                                              std::uint32_t in_edx = 0) {

      std::array<std::uint32_t, 4> regs = { in_eax,in_ebx,in_ecx,in_edx };

      std::int32_t* regs_ptr = reinterpret_cast<std::int32_t*>(regs.data());
      __cpuidex(regs_ptr,
                (std::int32_t)in_eax,
          (std::int32_t)in_ecx
          );



      return regs;

    }


  };



};

#endif
#endif
#ifndef COMPASS_RT_X86_INTEL_CPUID_H_



#ifdef COMPASS_CT_COMP_INTEL

#define COMPASS_RT_X86_INTEL_CPUID_H_


#include <array>
#include <bitset>
#include <cstdint>



namespace compass {


  namespace runtime {




    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t in_eax = 0,
                                                    std::uint32_t in_ebx = 0,
                                                    std::uint32_t in_ecx = 0,
                                                    std::uint32_t in_edx = 0){

      static std::array<std::uint32_t,4> value = {~0};

      int cpuid_rvalue = compass::runtime::extended_get_cpuid(&value[0],in_eax,in_ecx);

      if(cpuid_rvalue < 1){
        value = {0,0,0,0};
        return value;
      } else {
        return value;
      }

    }

    static std::array<std::bitset<32>, 4> cpuid(std::uint32_t in_eax = 0,
													std::uint32_t in_ebx = 0,
													std::uint32_t in_ecx = 0,
													std::uint32_t in_edx = 0) {

			auto regs = cpuid_to_int(in_eax, in_ebx, in_ecx, in_edx);

			static std::array<std::bitset<32>, 4> value;

			value[ct::eax] = regs[ct::eax];
			value[ct::ebx] = regs[ct::ebx];
			value[ct::ecx] = regs[ct::ecx];
			value[ct::edx] = regs[ct::edx];

			return value;

    }
  };

};
#endif
#endif
#endif

#endif
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

            void set(int offset) {

                if(offset>(width-1))
                    return ;

                const int mask = 1 << offset;
                value_ = value_ | mask;

                return;
            }

            T range(std::uint32_t _begin, std::uint32_t _end) const {

                T value = 0;
                if(_begin >= width || _end <= _begin)
                    return value;

                const T mask = ~(~0 << (_end - _begin));
                value = (value_ >> _begin) & mask;
                return value;


            }


        };

    }


}

#endif
#ifndef COMPASS_RT_X86_SIZES_H_
#define COMPASS_RT_X86_SIZES_H_










#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;

      namespace size{


        class cacheline
        {

          std::vector<std::uint32_t> ebx_data_;

          cacheline():
            ebx_data_()
            {

              ebx_data_.reserve(3);
              std::uint32_t maxlevel = 8;
              std::uint32_t eax = 0;

              for(std::uint32_t l = 0;l<maxlevel;++l)
              {
                auto regs = cpuid(0x04,0,l);

                eax = regs[ct::eax];
                auto bv = bitview(eax);

                if(!bv.test(1))
                  continue;

                auto truelevel = bv.range(5,8);
                if(truelevel != l)
                  continue;

                ebx_data_.push_back(regs[ct::ebx]);
              }

            }

        public:

            static const cacheline& get(){
              static cacheline instance;
              return instance;
            }



          static std::uint32_t level(int _lvl, ct::x86_tag){

            auto reg = cacheline::get().ebx_data_.at(_lvl-1);

            std::uint32_t value = bitview(reg).range(0,11);

            return value + 1;
          }
        };

        class cache
        {

          std::vector<std::uint32_t> ebx_data_;
          std::vector<std::uint32_t> ecx_data_;

          cache():
            ebx_data_(),
            ecx_data_()
            {

              ebx_data_.reserve(3);
              ecx_data_.reserve(3);

              std::uint32_t maxlevel = 8;
              std::uint32_t eax = 0;

              for(std::uint32_t l = 0;l<maxlevel;++l)
              {
                auto regs = cpuid(0x04,0,l);

                eax = regs[ct::eax];
                auto bv = bitview(eax);

                if(!bv.test(1))
                  continue;

                auto truelevel = bv.range(5,8);
                if(truelevel != l)
                  continue;

                ebx_data_.push_back(regs[ct::ebx]);
                ecx_data_.push_back(regs[ct::ecx]);

              }

            }


        public:

          static const cache& get(){
            static cache instance;
            return instance;
          }

          static std::uint32_t level(int _lvl, ct::x86_tag){

            if(_lvl <= 0){
              std::cerr << "compass::size::cache requested invalid cache level (received: "<<
                _lvl << ", found on this host: [1," << cache::get().ebx_data_.size() + 1 << "]\n";
              return 0;
            }

            std::uint32_t index = _lvl - 1;

            if(!(index < cache::get().ebx_data_.size())){
              std::cerr << "compass::size::cache requested invalid cache level (received: "<<
                _lvl << ", found on this host: [1," << cache::get().ebx_data_.size() + 1 << "]\n";
              return 0;
            }


            std::uint32_t ebx = cache::get().ebx_data_[index];
            const bitview bv_ebx = bitview(ebx);
            const std::uint32_t ecx = cache::get().ecx_data_[index];

            std::uint32_t ways = 1 + bv_ebx.range(22,31);
            std::uint32_t partitions = 1 + bv_ebx.range(12,21);
            std::uint32_t line_size = 1 + bv_ebx.range(0,11);
            std::uint32_t sets = 1 + ecx;

            std::uint32_t value = ways*partitions*line_size*sets;

            return value;
          }
        };



      };
    };

  };

};
#endif
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;

      static bool works(ct::x86_tag) {

        auto regs = rt::cpuid(0);

        if(regs.size())
          return true;
        else
          return false;

      }


      static std::string vendor(ct::x86_tag) {


        std::array<std::uint32_t,4> regs = rt::cpuid(0);

        std::string vendor_name = "";

        if(!regs.empty()){
          vendor_name.resize(3*4);

          std::copy(reinterpret_cast<char*>(&regs[ct::ebx]),reinterpret_cast<char*>(&regs[ct::ebx])+4,
                    vendor_name.begin());
          std::copy(reinterpret_cast<char*>(&regs[ct::edx]),reinterpret_cast<char*>(&regs[ct::edx])+4,
                    vendor_name.begin()+4);
          std::copy(reinterpret_cast<char*>(&regs[ct::ecx]),reinterpret_cast<char*>(&regs[ct::ecx])+4,
                    vendor_name.begin()+8);
        }

        return vendor_name;


      }


      static std::string brand(ct::x86_tag) {

        std::string value = "";
        auto regs = rt::cpuid(0x80000000);
        if(regs[ct::eax] < 0x80000004)
          return value;

        value.resize(48);
        char* value_begin = &value[0];
        for(std::uint32_t i = 2; i<5;++i){
          auto ret = rt::cpuid(0x80000000 + i);

          for(std::uint32_t r = 0; r<4;++r){
            std::uint32_t* tgt = reinterpret_cast<std::uint32_t*>(value_begin + (i-2)*16u + r*4u);
            *tgt = ret[r];
          }

        }

        return value;

      }


      static std::string device_name(ct::x86_tag) {

        std::string brand_str = compass::runtime::detail::brand(ct::x86_tag());
        std::string vendor = compass::runtime::detail::vendor(ct::x86_tag());
        std::size_t find_pos = 0;
        if((find_pos = vendor.find("Genuine"))!=std::string::npos){
            vendor.erase(find_pos,7);
        }

        std::string value = "";

        if(brand_str.find(vendor) != std::string::npos){

          auto second_bracket_itr = brand_str.rfind(")");
          auto last_at_itr = brand_str.rfind("@");
          value = brand_str.substr(second_bracket_itr+1,last_at_itr-(second_bracket_itr+1));

          if((find_pos = value.find(" CPU "))!=std::string::npos){
            value.erase(find_pos,5);
          }

          if((find_pos = value.find(" CPU "))!=std::string::npos){
            value.erase(find_pos,5);
          }

          value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
        }
        return value;

      }


















      static bool has(feature::sse , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(std::count(regs.cbegin(), regs.cend(),0) == regs.size()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::edx]).test(25);
        return value;
      }

      static bool has(feature::sse2 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::edx]).test(26);
        return value;
      }

      static bool has(feature::sse3 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(9) |
          bitview(regs[ct::ecx]).test(0) |
          bitview(regs[ct::ecx]).test(3);
        return value;
      }


      static bool has(feature::sse4 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(19) |
          bitview(regs[ct::ecx]).test(20);

        return value;
      }

      static bool has(feature::avx , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(28);

        return value;
      }

      static bool has(feature::avx2 , ct::x86_tag){

        auto regs = rt::cpuid(7,0,0,0);

        bool value = bitview(regs[ct::ebx]).test(5);

        return value;
      }

    };

  };

};
#endif
#endif


#endif
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

        namespace size {

            struct cacheline{

                static std::uint32_t level(int _lvl){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cacheline::level(_lvl,current_arch_t());

                }
            };

            struct cache{

                static std::uint32_t level(int _lvl){

                    using current_arch_t = ct::arch::type;
                    return compass::runtime::detail::size::cache::level(_lvl,current_arch_t());

                }
            };


        };

    };

}

#endif
#endif
