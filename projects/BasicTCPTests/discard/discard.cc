#include "discard.h"
#include "muduo/base/Logging.h"

using namespace muduo;
using namespace muduo::net;

// public
DiscardServer::DiscardServer(EventLoop* loop, 
                             const InetAddress& listenAddr)
    : _server(loop, listenAddr, "DiscardServer"){

        // 绑定TCP服务的三个半事件中的： 消息、数据到达 两个事件的回调函数
        _server.setConnectionCallback(std::bind(&DiscardServer::onConnection, this, _1));
        _server.setMessageCallback(std::bind(&DiscardServer::onMessage, this, _1, _2, _3));
    }

void DiscardServer::start(){
    _server.start();
}


// private
void DiscardServer::onConnection(const TcpConnectionPtr& conn){
    LOG_INFO << "DiscardServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
}

void DiscardServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time){
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " discards " << msg.size()
             << " bytes received at " << time.toString();
}
