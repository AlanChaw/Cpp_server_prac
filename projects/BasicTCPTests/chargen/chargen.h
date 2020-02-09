#pragma once

#include "muduo/net/TcpServer.h"

// 只发送数据，不接收数据。但发送速度不能快过客户端接收速度。
// 三个半事件中的那半个： 消息发送完成 事件

class ChargenServer{
public:
    ChargenServer(muduo::net::EventLoop* loop,
                  const muduo::net::InetAddress& listenAddr,
                  bool print = false);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time);

    void onWriteComplete(const muduo::net::TcpConnectionPtr& conn);
    void printThroughput();

    muduo::net::TcpServer _server;

    muduo::string _msg;
    int64_t _transferred;
    muduo::Timestamp _startTime;
};
