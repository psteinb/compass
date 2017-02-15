#ifndef DETAIL_DETECT_COMPILER_H
#define DETAIL_DETECT_COMPILER_H

//for reference see: https://sourceforge.net/p/predef/wiki/Compilers/

#ifdef __GNUC__
#define COMPASS_CT_COMP_GCC
#endif

#ifdef __clang__
#define COMPASS_CT_COMP_CLANG
#endif

#if (defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD))
#define COMPASS_CT_COMP_MSVC
#endif

#ifdef __INTEL_COMPILER
#define COMPASS_CT_COMP_INTEL
#endif

//TODO: if needed, this is the header where the compiler version could be inferred

namespace compass {

    namespace compiletime {

        struct gnu_tag  {};
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

    }  // compiletime

}  // compass

#endif /* DETAIL_DETECT_COMPILER_H */
