#include "discard.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main(){
    LOG_INFO << "pid = " << getpid();       // 在 unistd.h 头文件中
    EventLoop loop;
    InetAddress listenAddr(2007);

    DiscardServer server(&loop, listenAddr);
    server.start();
    loop.loop();
    
}
