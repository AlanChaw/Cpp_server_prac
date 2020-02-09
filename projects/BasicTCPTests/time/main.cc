#include "time.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main(){
    LOG_INFO << "pid " << getpid();
    EventLoop loop;
    InetAddress listenAddr(2007);
    TimeServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}