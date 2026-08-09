cmake_minimum_required(VERSION 3.16)
project(algorithm_cpp LANGUAGES CXX)

# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 默认 Debug 构建（带调试信息，方便断点调试）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 跨平台通用警告选项
add_compile_options(-Wall -Wextra)

# 递归收集 graph/ 下所有 .cpp（排除 build 目录）
file(GLOB_RECURSE ALGO_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/graph/*.cpp"
)
list(FILTER ALGO_SOURCES EXCLUDE REGEX ".*[/\\\\]build[/\\\\].*")

if(NOT ALGO_SOURCES)
  message(FATAL_ERROR "未在 graph/ 目录下找到任何 .cpp 源文件")
endif()

# 每个 .cpp 生成一个独立可执行文件，目标名 = 父目录_文件名
foreach(src IN LISTS ALGO_SOURCES)
  get_filename_component(src_dir "${src}" DIRECTORY)
  get_filename_component(parent_dir "${src_dir}" NAME)
  get_filename_component(file_name "${src}" NAME_WE)
  set(target "${parent_dir}_${file_name}")
  add_executable("${target}" "${src}")
  message(STATUS "添加目标: ${target}  <-  ${src}")
endforeach()
