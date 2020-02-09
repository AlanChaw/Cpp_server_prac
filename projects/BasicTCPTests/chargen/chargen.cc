#include "chargen.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

ChargenServer::ChargenServer(EventLoop* loop,
                             const InetAddress& listenAddr,
                             bool print)
    : _server(loop, listenAddr, "ChargenServer"),
      _transferred(0),
      _startTime(Timestamp::now()){
          
        _server.setConnectionCallback(
            std::bind(&ChargenServer::onConnection, this, _1)
        );
        _server.setMessageCallback(
            std::bind(&ChargenServer::onMessage, this, _1, _2, _3)
        );
        _server.setWriteCompleteCallback(
            std::bind(&ChargenServer::onWriteComplete, this, _1)
        );

        // 每 3s 打印一次吞吐量
        if(print)
            loop->runEvery(3.0, std::bind(&ChargenServer::printThroughput, this));


        string line;
        for(int i = 33; i < 127; ++i)
            line.push_back(char(i));
        line += line;

        for(size_t i = 0; i < 127 - 33; ++i)
            _msg += line.substr(i, 72) + "\n";
    }

void ChargenServer::start(){
    _server.start();
}

void ChargenServer::onConnection(const TcpConnectionPtr& conn){
    LOG_INFO << "ChargenServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");

    if(conn->connected()){
        conn->setTcpNoDelay(true);
        conn->send(_msg);
    }
}

// 收到信息直接丢弃
void ChargenServer::onMessage(const TcpConnectionPtr& conn,
                              Buffer* buf,
                              Timestamp time){
    string message(buf->retrieveAllAsString());
      LOG_INFO << conn->name() << " discards " << message.size()
           << " bytes received at " << time.toString();
}

void ChargenServer::onWriteComplete(const TcpConnectionPtr& conn){
    _transferred += _msg.size();
    conn->send(_msg);
}

void ChargenServer::printThroughput(){
    Timestamp endTime = Timestamp::now();
    double time = timeDifference(endTime, _startTime);
    printf("%4.3f MiB/s\n", static_cast<double>(_transferred)/time/1024/1024);
    _transferred = 0;
    _startTime = endTime;
}
