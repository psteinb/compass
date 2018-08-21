#ifndef COMPASS_RT_X86_SIZES_H_
#define COMPASS_RT_X86_SIZES_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/rt/x86_meta.hpp"
#include "detail/rt/x86_cpuid.hpp"
#include "detail/tags.hpp"
#include "detail/bit_view.hpp"
#include "detail/definitions.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;
      using current_arch_t = ct::arch::type;

      namespace size{

//for now this always refers to data cache
        class cacheline
        {

          std::vector<std::uint32_t> sizes_in_bytes_;

	  void on_intel(){

	    std::uint32_t maxlevel = 8;//maximum - 1 that can be mapped to 3 bits in eax[7:5]
              std::uint32_t eax = 0;
	      sizes_in_bytes_.reserve(maxlevel);
              
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

                		
		std::uint32_t value = bitview(regs[ct::ebx]).range(0,11);
		sizes_in_bytes_.push_back(value);

              }

	  }

	  void on_amd(){

	    sizes_in_bytes_.reserve(3);
	      
	    auto regs = cpuid(0x80000005);

	    std::uint32_t ecx = regs[ct::ecx];
	    auto bv = bitview(ecx);//L1data cache
	    std::uint32_t linesize = bv.range(0,7);
	    if(!linesize)//this is not a data cache, as the L1 cacheline size is 0
	      return;

	    sizes_in_bytes_.push_back(linesize);

	    auto l23regs = cpuid(0x80000006);
	    ecx = l23regs[ct::ecx];
	    auto bv2 = bitview(ecx);//L2 cache
	    linesize = bv2.range(0,7);
	    
	    sizes_in_bytes_.push_back(linesize);

	    auto bv3 = bitview(l23regs[ct::edx]);//L3 cache
	    linesize = bv3.range(0,7);
	    
	    sizes_in_bytes_.push_back(linesize);

	  }

          cacheline():
            sizes_in_bytes_()
            {

              
	      auto brand = compass::runtime::detail::vendor( current_arch_t() );

	      if(brand.find("AMD") != std::string::npos){
		on_amd();
	      }

	      if(brand.find("Intel") != std::string::npos){
		on_intel();
	      }

            }

        public:

          static const cacheline& get(){
            static cacheline instance;
            return instance;
          }

          static std::uint32_t levels_available(ct::x86_tag){
            return cacheline::get().sizes_in_bytes_.size();
          }

          static std::uint32_t level(int _lvl, ct::x86_tag){

            auto value = cacheline::get().sizes_in_bytes_.at(_lvl-1);

            return value;
          }
        };

        class cache
        {

	  std::vector<std::uint32_t> sizes_in_bytes_;
          
	  //TODO: refactor this sooner than later
	  void on_intel() {
	    
              std::uint32_t eax = 0;
              std::uint32_t maxlevel = 8;//maximum - 1 that can be mapped to 3 bits in eax[7:5]
	      sizes_in_bytes_.reserve(8);
	      
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

		std::uint32_t ebx = regs[ct::ebx];
		const bitview bv_ebx = bitview(ebx);
		const std::uint32_t ecx = regs[ct::ecx];

		std::uint32_t ways = 1 + bv_ebx.range(22,31);
		std::uint32_t partitions = 1 + bv_ebx.range(12,21);
		std::uint32_t line_size = 1 + bv_ebx.range(0,11);
		std::uint32_t sets = 1 + ecx;

		std::uint32_t value = ways*partitions*line_size*sets;

		sizes_in_bytes_.push_back(value);
              }

	  }

	  void on_amd(){

	    sizes_in_bytes_.reserve(3);
	      
	    auto regs = cpuid(0x80000005);

	    std::uint32_t ecx = regs[ct::ecx];
	    auto bv = bitview(ecx);//L1data cache
	    std::uint32_t test_linesize = bv.range(0,7);
	    if(!test_linesize)//this is not a data cache, as the L1 cacheline size is 0
	      return;

	    sizes_in_bytes_.push_back(bv.range(24,31)*1024);//AMD puts the numbers in kB

	    auto l23regs = cpuid(0x80000006);
	    ecx = l23regs[ct::ecx];
	    auto bv2 = bitview(ecx);//L2 cache
	    auto l2size = bv2.range(16,31);
	    l2size &= 0xffff;

	    sizes_in_bytes_.push_back(l2size*1024);//AMD puts the numbers in kB

	    auto bv3 = bitview(l23regs[ct::edx]);
	    auto l3size = bv3.range(19,31);//AMD manual says bits [18,31], experiments on a Ryzen Threadripper 1900X showed that [19,31] gives the right result
	    l3size *= 512*1024;
	    sizes_in_bytes_.push_back(l3size);//AMD puts the numbers in kB

	  }


          cache():
	    sizes_in_bytes_()
            {

	      
	      auto brand = compass::runtime::detail::vendor( current_arch_t() );

	      if(brand.find("AMD") != std::string::npos){
		on_amd();
	      }

	      if(brand.find("Intel") != std::string::npos){
		on_intel();
	      }
		  
            }


        public:

          static const cache& get(){
            static cache instance;
            return instance;
          }

          static std::uint32_t levels_available(ct::x86_tag){
            return cache::get().sizes_in_bytes_.size();
          }

          static std::uint32_t level(int _lvl, ct::x86_tag){

            if(_lvl <= 0){
              std::cerr << "compass::size::cache requested invalid cache level (received: "<<
                _lvl << ", found on this host: [1," << cache::get().sizes_in_bytes_.size() + 1 << "]\n";
              return 0;
            }

            std::uint32_t index = _lvl - 1;

            if(!(index < cache::get().sizes_in_bytes_.size())){
              std::cerr << "compass::size::cache requested invalid cache level (received: "<<
                _lvl << ", found on this host: [1," << cache::get().sizes_in_bytes_.size() + 1 << "]\n";
              return 0;
            }

            return cache::get().sizes_in_bytes_[index];
          }
        };



      };
    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_SIZES_H_ */
