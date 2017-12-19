#ifndef _COMPASS_FIXTURES_H_
#define _COMPASS_FIXTURES_H_

#include <iostream>
#include <string>

#include "machine_info.hpp"

struct host_reference
{

  std::string	hostname		;

  std::string   expected_vendor         ;
  std::string   expected_brand          ;
  std::string   expected_device_name    ;
  bool      expected_has_sse	;
  bool      expected_has_sse2	;
  bool      expected_has_sse3	;
  bool      expected_has_sse4	;
  bool      expected_has_avx	;
  bool      expected_has_avx2	;
  int       expected_ncores		;
  int       expected_L1d_linesize		;

  host_reference():
    hostname(compass::tests::hostname()),
    expected_vendor  (""),
    expected_brand   (""),
    expected_device_name   (""),
    expected_has_sse (false),
    expected_has_sse2(false),
    expected_has_sse3(false),
    expected_has_sse4(false),
    expected_has_avx (false),
    expected_has_avx2(false),
    expected_ncores  (-1)
  {

    if(hostname.find("schorle") != std::string::npos){
      expected_vendor = "intel";
      expected_brand  = "Intel(R) Core(TM) i7-3520M CPU @ 2.90GHz";
      expected_device_name = "i7-3520M";
      expected_has_sse = true ;
      expected_has_sse2= true ;
      expected_has_sse3= true ;
      expected_has_sse4= true ;
      expected_has_avx = true ;
      expected_has_avx2= false ;
      expected_L1d_linesize= 42 ;

      expected_ncores = 4;
    }

    //travis host
    if(hostname.find("-gce-") != std::string::npos){
      expected_vendor = "intel";
      expected_brand  = "Intel(R) Xeon(R) CPU @ 2.30GHz";
      expected_device_name = "";
      expected_has_sse = true ;
      expected_has_sse2= true ;
      expected_has_sse3= true ;
      expected_has_sse4= true ;
      expected_has_avx = true ;
      expected_has_avx2= true ;
      expected_ncores = 2;
    }

    //windows machine
    if (hostname.find("scicomp-pc-3") != std::string::npos) {
      expected_vendor = "intel";
      expected_brand = "Intel(R) Xeon(R) CPU E3-1245 v3 @ 3.40GHz";
      expected_device_name = "E3-1245v3";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 8;
    }

    //OSX machine
    if (hostname.find("recovery-station") != std::string::npos) {
      expected_vendor = "intel";
      expected_brand = "Intel(R) Core(TM) i5-4570 CPU @ 3.20GHz";
      expected_device_name = "i5-4570";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 4;
    }

    if(hostname.find("falcon2") == 0){
      expected_vendor = "intel";
      expected_brand = "Intel(R) Xeon(R) CPU E5-2670 v3 @ 2.30GHz";
      expected_device_name = "E5-2670v3";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 24;

    }

    if(hostname.find("talisker") == 0){
      expected_vendor = "intel";
      expected_brand = "Intel(R) Xeon(R) CPU E5-2698 v4 @ 2.20GHz";
      expected_device_name = "E5-2698v4";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 40;

    }
  }

};

#endif /* _COMPASS_FIXTURES_H_ */
