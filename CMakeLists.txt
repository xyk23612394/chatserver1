cmake_minimum_required(VERSION 2.0)
project(chatserver1)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
# 设置可执行文件最终存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 配置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
link_directories(/usr/lib64/mysql)

# 设置需要编译的源文件列表
# set(SRC_LIST muduo_server.cpp)

# 把.指定路径下的所有源文件名称放入变量名SRC_LIST中
# aux_source_directory(. SRC_LIST

# 表示生成可执行文件server由SRC_LIST变量所定义的源文件编译而来
# 表示server这个目标程序需要连接muduo_net muduo_base pthread这三个库文件
# target_link_libraries(server muduo_net muduo_base pthread)

#加载子目录
add_subdirectory(src)