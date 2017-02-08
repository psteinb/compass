#ifndef _COMPASS_FIXTURES_H_
#define _COMPASS_FIXTURES_H_

#include <iostream>
#include <string>
#include "boost/asio.hpp"

struct host_reference
{

  std::string	hostname		;
  
  std::string 	expected_vendor		;
  std::string 	expected_brand 		;
  bool 		expected_has_sse	;
  bool 		expected_has_sse2	;
  bool 		expected_has_sse3	;
  bool 		expected_has_sse4	;
  bool 		expected_has_avx	;
  bool 		expected_has_avx2	;
  int  		expected_ncores		;
  
  host_reference():
    hostname(boost::asio::ip::host_name()),
    expected_vendor  (""),
    expected_brand   (""),
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
      expected_has_sse = true ;
      expected_has_sse2= true ;
      expected_has_sse3= true ;
      expected_has_sse4= true ;
      expected_has_avx = true ;
      expected_has_avx2= false ;
      expected_ncores = 4;
    }

    //travis host
    if(hostname.find("-gce-") != std::string::npos){
      expected_vendor = "intel";
      expected_brand  = "Intel(R) Xeon(R) CPU @ 2.30GHz";
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
      expected_brand = "Intel(R) Xeon(R) CPU @ 2.30GHz";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 4;
    }

    //OSX machine
    if (hostname.find("recovery-station") != std::string::npos) {
      expected_vendor = "intel";
      expected_brand = "Intel(R) Xeon(R) CPU @ 2.30GHz";
      expected_has_sse = true;
      expected_has_sse2 = true;
      expected_has_sse3 = true;
      expected_has_sse4 = true;
      expected_has_avx = true;
      expected_has_avx2 = true;
      expected_ncores = 4;
    }
    
  }
  
};

#endif /* _COMPASS_FIXTURES_H_ */
