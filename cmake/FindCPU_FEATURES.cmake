##extract a single line that contains the given pattern (starting from that patter)
function(extract_line LINESTART_PATTERN MULTILINE_STRING OUTPUT_VARIABLE)

STRING(FIND ${MULTILINE_STRING} "${PATTERN}" MATCH_OFFSET)
STRING(SUBSTRING ${MATCH_OFFSET} 0 ${MATCH_OFFSET} MULTILINE_NO_START)
STRING(FIND ${MULTILINE_NO_START} "\n" MULTILINE_RETURN_OFFSET)
STRING(SUBSTRING ${MULTILINE_NO_START} 0 ${MULTILINE_RETURN_OFFSET} MATCHING_LINE)
set(OUTPUT_VARIABLE ${MATCHING_LINE} PARENT_SCOPE)

endfunction(extract_line)

##extract system information from wmic.exe on Windows
function(wmic_get ATTRIBUTENAME RESULTVALUE)
EXEC_PROGRAM("wmic.exe" ARGS "cpu get ${ATTRIBUTENAME}" OUTPUT_VARIABLE WMIC_OUTPUT)
string(REGEX REPLACE " [ ]+" ";" WMIC_OUTPUT_CLEANED ${WMIC_OUTPUT})
set(WMIC_OUTPUT_LIST "${WMIC_OUTPUT_CLEANED};")
list(GET WMIC_OUTPUT_LIST 1 VALUEOFINTEREST)

string(STRIP "${VALUEOFINTEREST}" VALUEOFINTEREST)
set(${RESULTVALUE} ${VALUEOFINTEREST} PARENT_SCOPE)
#message(STATUS "[wmic_get] RESULT = ${VALUEOFINTEREST}")

endfunction(wmic_get)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
  EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)

  ##FIND VENDOR
  STRING(FIND ${CPUINFO} "vendor" VENDOR_TITLE_OFFSET)
  STRING(SUBSTRING ${CPUINFO} ${VENDOR_TITLE_OFFSET} 50 GUESSED_VENDOR_LINE)
  STRING(REGEX REPLACE "^vendor.*: ([a-zA-Z]+)\n.*" "\\1" VENDOR_TITLE ${GUESSED_VENDOR_LINE})
  message(STATUS "vendor found: ${VENDOR_TITLE}")
  set(CPU_VENDOR "${VENDOR_TITLE}" CACHE STRING "cpu vendor")

  ##FIND VENDOR
  STRING(FIND ${CPUINFO} "family" FAMILY_TITLE_OFFSET)
  STRING(SUBSTRING ${CPUINFO} ${FAMILY_TITLE_OFFSET} 50 GUESSED_FAMILY_LINE)
  STRING(REGEX REPLACE "^family.*: ([0-9]+)\n.*" "\\1" FAMILY_TITLE ${GUESSED_FAMILY_LINE})
  message(STATUS "family found: ${FAMILY_TITLE}")
  set(CPU_FAMILY "${FAMILY_TITLE}" CACHE STRING "cpu family")

  ##FIND MODEL NAME
  STRING(FIND ${CPUINFO} "model name" MODEL_NAME_OFFSET)
  STRING(SUBSTRING ${CPUINFO} ${MODEL_NAME_OFFSET} 100 GUESSED_MODEL_NAME_LINE)
  STRING(FIND ${GUESSED_MODEL_NAME_LINE} "\n" MODEL_NAME_RETURN_OFFSET)
  STRING(SUBSTRING ${GUESSED_MODEL_NAME_LINE} 0 ${MODEL_NAME_RETURN_OFFSET} GUESSED_MODEL_NAME_LINE)

  STRING(REGEX REPLACE "^model name.*: ([a-zA-Z]+.*)$" "\\1" MODEL_NAME ${GUESSED_MODEL_NAME_LINE})
  message(STATUS "model name found: ${MODEL_NAME}")
  set(CPU_MODEL_NAME "${MODEL_NAME}" CACHE STRING "cpu model name")

  ##FIND INSTRUCTIONS
  STRING(REGEX REPLACE "^.*(sse) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "sse" "${SSE_THERE}" SSE_TRUE)
  IF (SSE_TRUE)
    set(SSE_FOUND true CACHE BOOL "SSE available on host")
  ELSE (SSE_TRUE)
    set(SSE_FOUND false CACHE BOOL "SSE available on host")
  ENDIF (SSE_TRUE)

  STRING(REGEX REPLACE "^.*(sse2) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "sse2" "${SSE_THERE}" SSE2_TRUE)
  IF (SSE2_TRUE)
    set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
  ELSE (SSE2_TRUE)
    set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
  ENDIF (SSE2_TRUE)

  # /proc/cpuinfo apparently omits sse3 :(
  STRING(REGEX REPLACE "^.*[^s](sse3) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "sse3" "${SSE_THERE}" SSE3_TRUE)
  IF (NOT SSE3_TRUE)
    STRING(REGEX REPLACE "^.*(T2300).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "T2300" "${SSE_THERE}" SSE3_TRUE)
  ENDIF (NOT SSE3_TRUE)

  STRING(REGEX REPLACE "^.* (ssse3) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "ssse3" "${SSE_THERE}" SSSE3_TRUE)
  IF (SSE3_TRUE OR SSSE3_TRUE)
    set(SSE3_FOUND true CACHE BOOL "SSE3 available on host")
  ELSE (SSE3_TRUE OR SSSE3_TRUE)
    set(SSE3_FOUND false CACHE BOOL "SSE3 available on host")
  ENDIF (SSE3_TRUE OR SSSE3_TRUE)
  IF (SSSE3_TRUE)
    set(SSSE3_FOUND true CACHE BOOL "SSSE3 available on host")
  ELSE (SSSE3_TRUE)
    set(SSSE3_FOUND false CACHE BOOL "SSSE3 available on host")
  ENDIF (SSSE3_TRUE)

  STRING(REGEX REPLACE "^.* (sse4_1) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "sse4_1" "${SSE_THERE}" SSE41_TRUE)
  IF (SSE41_TRUE)
    set(SSE4_1_FOUND true CACHE BOOL "SSE4.1 available on host")
  ELSE (SSE41_TRUE)
    set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
  ENDIF (SSE41_TRUE)

  STRING(REGEX REPLACE "^.* (sse4_2) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "sse4_2" "${SSE_THERE}" SSE42_TRUE)
  IF (SSE42_TRUE)
    set(SSE4_2_FOUND true CACHE BOOL "SSE4.2 available on host")
  ELSE (SSE42_TRUE)
    set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
  ENDIF (SSE42_TRUE)

  if("${CPUINFO}" MATCHES ".*avx .*")
    set(AVX_FOUND true CACHE BOOL "AVX available on host")
  else()
    set(AVX_FOUND false CACHE BOOL "AVX available on host")
  endif()

  if("${CPUINFO}" MATCHES ".*avx2 .*")
    set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
  else()
    set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
  endif()

  if("${CPUINFO}" MATCHES ".*avx512f .*")
    set(AVX512F_FOUND true CACHE BOOL "AVX512F available on host")
  else()
    set(AVX512F_FOUND false CACHE BOOL "AVX512F available on host")
  endif()

#
  if(EXISTS "/sys/devices/system/cpu/cpu0/cache/index2/size")
    EXEC_PROGRAM(cat ARGS "/sys/devices/system/cpu/cpu0/cache/index2/size" OUTPUT_VARIABLE L2_SIZE_KB_STRING)

    if(${L2_SIZE_KB_STRING} MATCHES ".*[K|k]")
      string(REGEX REPLACE "[K|k]" "" L2_SIZE_KB ${L2_SIZE_KB_STRING})
      set(CPU_L2_SIZE_KB "${L2_SIZE_KB}" CACHE STRING "cpu L2 cache size in kB")
    else()
      if(${L2_SIZE_KB_STRING} MATCHES ".*[M|m]")
        string(REGEX REPLACE "[M|m]" "000" L2_SIZE_KB ${L2_SIZE_KB_STRING})
        set(CPU_L2_SIZE_KB "${L2_SIZE_KB}" CACHE STRING "cpu L2 cache size in kB")
      else()
        message(WARNING "unable to find unit prefix (K|M) in /sys/devices/system/cpu/cpu0/cache/index2/size:${L2_SIZE_KB_STRING} (assuming it's contents as expressed in kB, crossing fingers)")
        set(CPU_L2_SIZE_KB "${L2_SIZE_KB_STRING}" CACHE STRING "cpu L2 cache size in kB")
      endif()

    endif()

  else()
    message("unable to find /sys/devices/system/cpu/cpu0/cache/index2/size")
    set(CPU_L2_SIZE_KB "0" CACHE STRING "cpu L2 cache size in kB")
  endif()


ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE
    CPUINFO)

  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.leaf7_features" OUTPUT_VARIABLE
    LEAF7_CPUINFO)

  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.family" OUTPUT_VARIABLE
    CPU_FAMILY)

  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.vendor" OUTPUT_VARIABLE
    VENDOR_TITLE)

  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.brand_string" OUTPUT_VARIABLE
    MODEL_NAME)

  EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.cache.size" OUTPUT_VARIABLE
    CPU_L2_SIZE_KB)

  set(CPU_VENDOR "${VENDOR_TITLE}" CACHE STRING "cpu vendor")
  set(CPU_MODEL_NAME "${MODEL_NAME}" CACHE STRING "cpu model name")

  STRING(REGEX REPLACE "^.*[^S](SSE) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE" "${SSE_THERE}" SSE_TRUE)
  IF (SSE_TRUE)
    set(SSE_FOUND true CACHE BOOL "SSE2 available on host")
  ELSE (SSE_TRUE)
    set(SSE_FOUND false CACHE BOOL "SSE2 available on host")
  ENDIF (SSE_TRUE)

  STRING(REGEX REPLACE "^.*[^S](SSE2) .*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE2" "${SSE_THERE}" SSE2_TRUE)
  IF (SSE2_TRUE)
    set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
  ELSE (SSE2_TRUE)
    set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
  ENDIF (SSE2_TRUE)

  STRING(REGEX REPLACE "^.*[^S](SSE2).*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE2" "${SSE_THERE}" SSE2_TRUE)
  IF (SSE2_TRUE)
    set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
  ELSE (SSE2_TRUE)
    set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
  ENDIF (SSE2_TRUE)

  STRING(REGEX REPLACE "^.*[^S](SSE3).*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE3" "${SSE_THERE}" SSE3_TRUE)
  IF (SSE3_TRUE)
    set(SSE3_FOUND true CACHE BOOL "SSE3 available on host")
  ELSE (SSE3_TRUE)
    set(SSE3_FOUND false CACHE BOOL "SSE3 available on host")
  ENDIF (SSE3_TRUE)

  STRING(REGEX REPLACE "^.*(SSSE3).*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSSE3" "${SSE_THERE}" SSSE3_TRUE)
  IF (SSSE3_TRUE)
    set(SSSE3_FOUND true CACHE BOOL "SSSE3 available on host")
  ELSE (SSSE3_TRUE)
    set(SSSE3_FOUND false CACHE BOOL "SSSE3 available on host")
  ENDIF (SSSE3_TRUE)

  STRING(REGEX REPLACE "^.*(SSE4.1).*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE4.1" "${SSE_THERE}" SSE41_TRUE)
  IF (SSE41_TRUE)
    set(SSE4_1_FOUND true CACHE BOOL "SSE4.1 available on host")
  ELSE (SSE41_TRUE)
    set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
  ENDIF (SSE41_TRUE)

  STRING(REGEX REPLACE "^.*(SSE4.2).*$" "\\1" SSE_THERE ${CPUINFO})
  STRING(COMPARE EQUAL "SSE4.2" "${SSE_THERE}" SSE42_TRUE)
  IF (SSE42_TRUE)
    set(SSE4_2_FOUND true CACHE BOOL "SSE4.2 available on host")
  ELSE (SSE42_TRUE)
    set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
  ENDIF (SSE42_TRUE)

  if("${CPUINFO}" MATCHES ".*AVX.*")
    set(AVX_FOUND true CACHE BOOL "AVX available on host")
  else()
    set(AVX_FOUND false CACHE BOOL "AVX available on host")
  endif()

  if("${CPUINFO}" MATCHES ".*AVX2 .*")
    set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
  else()
    if("${LEAF7_CPUINFO}" MATCHES ".*AVX2 .*")
      set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
    else()
      set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
    endif()
  endif()

  if("${CPUINFO}" MATCHES ".*AVX512F .*")
    set(AVX512F_FOUND true CACHE BOOL "AVX512F available on host")
  else()
    if("${LEAF7_CPUINFO}" MATCHES ".*AVX512F .*")
      set(AVX512F_FOUND true CACHE BOOL "AVX512F available on host")
    else()
      set(AVX512F_FOUND false CACHE BOOL "AVX512F available on host")
    endif()
  endif()

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")

  #as an alternative to wmic, use
  #get_filename_component(_vendor_id "[HKEY_LOCAL_MACHINE\\Hardware\\Description\\System\\CentralProcessor\\0;VendorIdentifier]" NAME CACHE)
  #get_filename_component(_cpu_id "[HKEY_LOCAL_MACHINE\\Hardware\\Description\\System\\CentralProcessor\\0;Identifier]" NAME CACHE)

  wmic_get("Name" MODEL_NAME)
  string(STRIP ${MODEL_NAME} MODEL_NAME)
  set(CPU_MODEL_NAME "${MODEL_NAME}" CACHE STRING "cpu model name")

  wmic_get("Manufacturer" MODEL_VENDOR)
  set(CPU_VENDOR "${MODEL_VENDOR}" CACHE STRING "cpu model vendor")

  wmic_get("Family" MODEL_FAMILY)
  set(CPU_FAMILY "${MODEL_FAMILY}" CACHE STRING "cpu model family")

  wmic_get("L2CacheSize" L2_CACHE_SIZE)
  wmic_get("NumberOfCores" CPU_NPHYS_CORES)

  #dirty hack that I need to validate with other machines in Win7
  if(NOT "${L2_CACHE_SIZE}" STREQUAL "")
    if(${CPU_NPHYS_CORES} GREATER 1)
      math(EXPR L2_CACHE_SIZE "${L2_CACHE_SIZE}/${CPU_NPHYS_CORES}")
    endif()
    set(CPU_L2_SIZE_KB "${L2_CACHE_SIZE}" CACHE STRING "cpu L2 cache size in kB")
  else()
    message("unable to decipher L2 cache size")
  endif()
  set(CPU_L2_SIZE_KB "0" CACHE STRING "cpu L2 cache size in kB")
  set(CPU_VENDOR "" CACHE STRING "cpu model vendor")
  set(CPU_MODEL_NAME "" CACHE STRING "cpu model name")

  #thanks to the wonderful VC project (https://github.com/VcDevel/Vc)
  include (OptimizeForArchitecture)

  OFA_AutodetectHostArchitecture()
  OFA_HandleX86Options()


  list(FIND _available_vector_units_list "sse" SSE_INDEX)
  list(FIND _available_vector_units_list "sse2" SSE2_INDEX)
  list(FIND _available_vector_units_list "sse3" SSE3_INDEX)
  list(FIND _available_vector_units_list "ssse3" SSSE3_INDEX)
  list(FIND _available_vector_units_list "sse4.1" SSE4_1_INDEX)
  list(FIND _available_vector_units_list "sse4.2" SSE4_2_INDEX)
  list(FIND _available_vector_units_list "avx" AVX_INDEX)
  list(FIND _available_vector_units_list "avx2" AVX2_INDEX)
  list(FIND _available_vector_units_list "avx512f" AVX512F_INDEX)

  if(${SSE_INDEX} GREATER -1)
    set(SSE_FOUND    true  CACHE BOOL "SSE available on host")
  endif()
  if(${SSE2_INDEX} GREATER -1)
    set(SSE2_FOUND    true  CACHE BOOL "SSE2 available on host")
  endif()
  if(${SSE3_INDEX} GREATER -1)
    set(SSE3_FOUND    true  CACHE BOOL "SSE3 available on host")
  endif()
  if(${SSSE3_INDEX} GREATER -1)
    set(SSSE3_FOUND    true  CACHE BOOL "SSSE3 available on host")
  endif()
  if(${SSE4_1_INDEX} GREATER -1)
    set(SSE4_1_FOUND    true  CACHE BOOL "SSE4.1 available on host")
  endif()
  if(${SSE4_2_INDEX} GREATER -1)
    set(SSE4_2_FOUND    true  CACHE BOOL "SSE4.2 available on host")
  endif()
  if(${AVX_INDEX} GREATER -1)
  set(AVX_FOUND    true  CACHE BOOL "AVX available on host")
  endif()
  if(${AVX2_INDEX} GREATER -1)
    set(AVX2_FOUND    true  CACHE BOOL "AVX2 available on host")
  endif()

  if(${AVX512F_INDEX} GREATER -1)
    set(AVX512F_FOUND    true  CACHE BOOL "AVX512F available on host")
  endif()

  set(SSE_FOUND    true  CACHE BOOL "SSE available on host")
  set(SSE2_FOUND   false  CACHE BOOL "SSE2 available on host")
  set(SSE3_FOUND   false CACHE BOOL "SSE3 available on host")
  set(SSSE3_FOUND  false CACHE BOOL "SSSE3 available on host")
  set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
  set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
  set(AVX_FOUND false CACHE BOOL "AVX available on host")
  set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
  set(AVX512F_FOUND false CACHE BOOL "AVX512F available on host")

ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

message(STATUS "found hardware: ${CPU_VENDOR} ${CPU_MODEL_NAME}")
set(FOUND_FEATURES)

if(SSE_FOUND)
  list(APPEND FOUND_FEATURES "sse")
endif(SSE_FOUND)
if(SSE2_FOUND)
  list(APPEND FOUND_FEATURES "sse2")
endif(SSE2_FOUND)
if( SSE3_FOUND)
list(APPEND FOUND_FEATURES "sse3")
endif( SSE3_FOUND)
if( SSSE3_FOUND)
list(APPEND FOUND_FEATURES "ssse3")
endif( SSSE3_FOUND)
if( SSE4_1_FOUND)
list(APPEND FOUND_FEATURES "sse4.1")
endif( SSE4_1_FOUND)
if( SSE4_2_FOUND)
list(APPEND FOUND_FEATURES "sse4.2")
endif( SSE4_2_FOUND)
if( AVX_FOUND)
list(APPEND FOUND_FEATURES "avx")
endif( AVX_FOUND)
if( AVX2_FOUND)
list(APPEND FOUND_FEATURES "avx2")
endif( AVX2_FOUND)

if( AVX512F_FOUND)
list(APPEND FOUND_FEATURES "avx512f")
endif( AVX512F_FOUND)

message(STATUS "found hardware features: ${FOUND_FEATURES}")

mark_as_advanced(SSE_FOUND SSE2_FOUND SSE3_FOUND SSSE3_FOUND SSE4_1_FOUND SSE4_2_FOUND AVX_FOUND AVX2_FOUND AVX512F_FOUND CPU_VENDOR CPU_FAMILY CPU_MODEL_NAME CPU_L2_SIZE_KB)
