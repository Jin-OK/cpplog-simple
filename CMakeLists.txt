cmake_minimum_required(VERSION 3.10)
project(simplelog)

# 修改为 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
	add_definitions(-DSIMPLELOG_EXPORTS)
endif()

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加静态库和动态库
add_library(simplelog_static STATIC src/simplelog.cpp)
add_library(simplelog_shared SHARED src/simplelog.cpp)

# 设置头文件包含路径
target_include_directories(simplelog_static PUBLIC include)
target_include_directories(simplelog_shared PUBLIC include)

# 设置输出库文件名（不带lib前缀）
set_target_properties(simplelog_static PROPERTIES OUTPUT_NAME "simplelog")
set_target_properties(simplelog_shared PROPERTIES OUTPUT_NAME "simplelog")

# 添加测试程序
add_executable(logtest test/test.cpp)
target_link_libraries(logtest PRIVATE simplelog_shared)  # 链接动态库
# 或者链接静态库：target_link_libraries(logtest PRIVATE simplelog_static)

# 安装规则
install(TARGETS simplelog_static simplelog_shared logtest
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)