/*
muduo 给用户提供的两个主要的类
TcpServer：用于编写服务器类
TcpClient：用于编写客户端类

*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
基于muduo网络库开发服务器
组合TcpServer对象
创建Eventloop事件循环对象指针
明确TcpServer需要的参数
在当前服务器类的构造中注册回调

*/

class ChatServrer
{
public:
    ChatServrer(EventLoop * loop,
                const InetAddress &listenAddr,
                const string &nameArg)
                :_server(loop,listenAddr,nameArg),_loop(loop)
                {
                    // 给服务器注册用户连接的创建和断开回调
                    _server.setConnectionCallback(std::bind(&ChatServrer::onConnection,this,_1));
                    // 给服务器注册用户的读写事件回调
                    _server.setMessageCallback(std::bind(&ChatServrer::onMessage,this,_1,_2,_3));

                    //设置服务器端的线程数量 1个I/O线程，3个worker线程
                    _server.setThreadNum(4);
                }
    //开启事件的循环
    void start()
    {
        _server.start();
    }

private:
    //专门处理用户的连接创建和断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr&conn)
    {
        if (conn->connected())
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" <<endl;
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:offline" <<endl;
            conn->shutdown(); // close(fd)
            // _loop->quit();
        }
            
    }
    void onMessage(const TcpConnectionPtr &conn,Buffer *buffer,Timestamp time)
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data : " << buf << " time " << time.toString() << endl;
        conn->send(buf);
    }
    TcpServer _server;
    EventLoop *_loop;
};


int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServrer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop(); //epoll_wait以阻塞的方式等待新用户的连接，已连接用户的读写事件等
    return 0;
}