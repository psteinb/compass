#ifndef COMPASS_RT_X86_SIZES_H_
#define COMPASS_RT_X86_SIZES_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/rt/x86_cpuid.hpp"
#include "detail/tags.hpp"
#include "detail/bit_view.hpp"
#include "detail/definitions.hpp"

#include <iostream>
#include <string>
#include <algorithm>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;

      namespace size{

//for now this always refers to data cache
        class cacheline
        {

          std::vector<std::uint32_t> ebx_data_;

          cacheline():
            ebx_data_()
            {

              ebx_data_.reserve(3);
              std::uint32_t maxlevel = 8;//maximum - 1 that can be mapped to 3 bits in eax[7:5]
              std::uint32_t eax = 0;

              for(std::uint32_t l = 0;l<maxlevel;++l)
              {
                auto regs = cpuid(0x04,0,l);

                eax = regs[ct::eax];
                auto bv = bitview(eax);

                if(!bv.test(1))//this is not a data cache
                  continue;

                auto truelevel = bv.range(5,8);
                if(truelevel != l)//this is the wrong level
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

              std::uint32_t maxlevel = 8;//maximum - 1 that can be mapped to 3 bits in eax[7:5]
              std::uint32_t eax = 0;

              for(std::uint32_t l = 0;l<maxlevel;++l)
              {
                auto regs = cpuid(0x04,0,l);

                eax = regs[ct::eax];
                auto bv = bitview(eax);

                if(!bv.test(1))//this is not a data cache
                  continue;

                auto truelevel = bv.range(5,8);
                if(truelevel != l)//this is the wrong level
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
    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_SIZES_H_ */
