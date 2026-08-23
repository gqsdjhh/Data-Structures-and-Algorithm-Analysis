cmake_minimum_required(VERSION 3.20)

project(data_structures_analysis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# MinGW/WinLibs builds need matching runtime DLLs next to each exe.
# Otherwise Windows may load an older mismatched MinGW from PATH and crash.
function(copy_mingw_runtime target)
  if (MSVC OR NOT WIN32)
    return()
  endif()

  get_filename_component(_cxx_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
  foreach(_dll libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)
    set(_dll_path "${_cxx_bin_dir}/${_dll}")
    if (EXISTS "${_dll_path}")
      add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${_dll_path}"
          "$<TARGET_FILE_DIR:${target}>"
        COMMENT "Copy runtime DLL: ${_dll_path}")
    endif()
  endforeach()
endfunction()

# 收集 code/ 下的所有演示程序，每个 .cpp 生成一个可执行文件
file(GLOB_RECURSE _demo_sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/code/*.cpp")

foreach(_src IN LISTS _demo_sources)
  get_filename_component(_name "${_src}" NAME_WE)
  add_executable(${_name} "${_src}")
  copy_mingw_runtime(${_name})
endforeach()
