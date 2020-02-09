#include "time.h"

#include "muduo/base/Logging.h"
#include "muduo/net/Endian.h"

using namespace muduo;
using namespace muduo::net;

// 只要处理三个半事件中的 “连接已建立” 事件

TimeServer::TimeServer(EventLoop* loop, const InetAddress& listenAddr)
    : _server(loop, listenAddr, "TimeServer")
    {
        _server.setConnectionCallback(
            std::bind(&TimeServer::onConnection, this, _1)
        );
        _server.setMessageCallback(
            std::bind(&TimeServer::onMessage, this, _1, _2, _3)
        );
    }

void TimeServer::start(){
    _server.start();
}

void TimeServer::onConnection(const TcpConnectionPtr& conn)
{
  LOG_INFO << "TimeServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected())
  {
    time_t now = ::time(NULL);
    int32_t be32 = sockets::hostToNetwork32(static_cast<int32_t>(now));
    conn->send(&be32, sizeof be32);
    conn->shutdown();
  }
}

void TimeServer::onMessage(const TcpConnectionPtr& conn,
                              Buffer* buf,
                              Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " discards " << msg.size()
           << " bytes received at " << time.toString();
}
