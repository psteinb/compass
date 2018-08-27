# small cmake module to help extracting the tag and head hash of the current source code tree
#
# find_git_root    ... tries to find the .git folder of this repo or any of it's parents
# git_ready        ... helper function that checks if the current directory is under version control by git
# git_describe     ... interface to git describe command line call, note only stdout is captured in the output variable
#

find_package(Git QUIET)

function(find_git_root _git_root)

  set(${_git_root} "GIT_ROOT_DIR-NOTFOUND")

  if(GIT_NOTFOUND)
    message(INFO "git not found on this system")
    return()
  endif()

  set(GIT_PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  set(GIT_PROJECT_ROOT "${GIT_PARENT_DIR}/.git")

  while(NOT EXISTS "${GIT_PROJECT_ROOT}")	# .git dir not found, search parent directories
    set(GIT_PREVIOUS_PARENT "${GIT_PARENT_DIR}")
    get_filename_component(GIT_PARENT_DIR ${GIT_PARENT_DIR} PATH)
    if(GIT_PARENT_DIR STREQUAL GIT_PREVIOUS_PARENT)
      # We have reached the root directory, we are not in git
      set(${_git_root} "GIT_ROOT_DIR-NOTFOUND" PARENT_SCOPE)
      return()
    endif()
    set(${_git_root} "${GIT_PARENT_DIR}/.git" PARENT_SCOPE)
    set(GIT_PROJECT_ROOT "${GIT_PARENT_DIR}/.git")
  endwhile()

endfunction()

function(git_ready _var)

  find_git_root(GIT_ROOT_DIR)

  if(IS_DIRECTORY ${GIT_ROOT_DIR})
    set(${_var} "True" PARENT_SCOPE)
  else()
    set(${_var} "False" PARENT_SCOPE)
  endif()

endfunction()

function(git_describe _var)

  find_git_root(GIT_ROOT_DIR)
  execute_process(COMMAND
    "${GIT_EXECUTABLE}"
    describe
    ${hash}
    ${ARGN}
    WORKING_DIRECTORY
    "${GIT_ROOT_DIR}"
    RESULT_VARIABLE
    res
    OUTPUT_VARIABLE
    out
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  set(${_var} "${out}" PARENT_SCOPE)
endfunction()
