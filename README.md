# chatserver1
工作在nginx（tcp）上的集群聊天服务器（redis消息队列）和客户端源代码（muduo）（mysql）


编译方式
cd build
rm -rf *
cmake ..
make

需要启动nginx服务器和redis服务器，启动mysql，需要配置nginx负载均衡
