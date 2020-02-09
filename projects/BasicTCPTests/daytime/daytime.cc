#include "daytime.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"


using namespace muduo;
using namespace muduo::net;

// 只要处理三个半事件中的 “连接已建立” 事件

DaytimeServer::DaytimeServer(EventLoop* loop, const InetAddress& listenAddr)
    : _server(loop, listenAddr, "DaytimeServer")
    {
        _server.setConnectionCallback(
            std::bind(&DaytimeServer::onConnection, this, _1)
        );
        _server.setMessageCallback(
            std::bind(&DaytimeServer::onMessage, this, _1, _2, _3)
        );
    }

void DaytimeServer::start(){
    _server.start();
}

void DaytimeServer::onConnection(const TcpConnectionPtr& conn)
{
  LOG_INFO << "DaytimeServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected())
  {
    conn->send(Timestamp::now().toFormattedString() + "\n");
    conn->shutdown();
  }
}

void DaytimeServer::onMessage(const TcpConnectionPtr& conn,
                              Buffer* buf,
                              Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " discards " << msg.size()
           << " bytes received at " << time.toString();
}
