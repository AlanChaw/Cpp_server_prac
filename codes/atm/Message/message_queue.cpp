#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

#pragma once

namespace messaging{
    // 消息项的基础类
    struct message_base{
        virtual ~message_base(){}   // 抽象基类的虚析构函数
    };

    // 每个消息类型需要特化
    template<typename Msg>
    struct wrapped_message: message_base{
        Msg contents;

        explicit wrapped_message(Msg const& _contents)
            : contents(_contents)
            {}
    };

    // 我们的消息队列
    class queue{        
        std::mutex m;
        std::condition_variable c;
        std::queue<std::shared_ptr<message_base>> q;    // 指向 message_base 基类指针的队列

    public:
        template<typename T>
        void push(T const& msg){
            std::lock_guard<std::mutex> lk(m);
            q.push(std::make_shared<wrapped_message<T>>(msg));  // 包装已传递的信息，将指针存入队列
            c.notify_all();
        }

        std::shared_ptr<message_base> wait_and_pop(){
            std::unique_lock<std::mutex> lk(m);
            c.wait(lk, [&]{return !q.empty();});        // 队列为空时阻塞
            auto res = q.front();
            q.pop();
            return res;     // 返回队首消息
        }
    };
}


namespace messaging{
    // dispatcher 调度器类用于对消息进行调度
    class close_queue{};    // 用于关闭队列的消息

    // 模板化的调度器类
    template<typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher{
        queue* q;
        PreviousDispatcher* prev;
        Func f;
        bool chained;

        // 禁止拷贝
        TemplateDispatcher(TemplateDispatcher const&) = delete;     
        TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

        template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
        friend class TemplateDispatcher;    // 所有特化实例都是友元

        void wait_and_dispatch(){
            while(1){
                auto msg = q->wait_and_pop();
                if(dispatch(msg))       // 如果消息已经处理，则跳出循环
                    break;
            }
        }

        bool dispatch(std::shared_ptr<message_base> const& msg){
            // 检查消息类型，并调用函数
            if(wrapped_message<Msg>* wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())){
                f(wrapper->contents);       // 用传入的函数对象处理数据
                return true;
            }else{
                return prev->dispatch(msg);     // 链接到之前的调度器上
            }
        }

    public:
        // 移动构造
        TemplateDispatcher(TemplateDispatcher&& other)
            : q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained)
            {}
        
        TemplateDispatcher(queue* _q, PreviousDispatcher* _prev, Func&& _f)
            : q(_q), prev(_prev), f(std::forward<Func>(_f)), chained(false){
                _prev->chained = true;
            }
        
        // 可以链接其他处理器
        template<typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> 
        handle(OtherFunc&& of){                 
            return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
        }
        
        ~TemplateDispatcher() noexcept(false){
            if(!chained)
                wait_and_dispatch();
        }
    };

    // 普通调度器类
    class dispatcher{
        queue* q;
        bool chained;

        dispatcher(dispatcher const&) = delete;     // 禁止拷贝
        dispatcher& operator=(dispatcher const&) = delete;

        template<typename Dispatcher, typename Msg, typename Func>
        friend class TemplateDispatcher;

        void wait_and_dispatch(){
            while(1){       // 循环，等待调度信息
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        // 检查 close_queue 消息，然后抛出
        bool dispatch(std::shared_ptr<message_base> const& msg){
            if(dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
                throw close_queue();
            return false;
        }

    public:
        dispatcher(dispatcher&& other)              // 移动构造
            : q(other.q), chained(other.chained){
                other.chained = true;   // 源不能等待消息
            }

        explicit dispatcher(queue* _q)
            : q(_q), chained(false) {}
        
        // 使用 TemplateDispatcher 处理指定类型的消息
        template<typename Msg, typename Func>
        TemplateDispatcher<dispatcher, Msg, Func> 
        handle(Func && f){
            return TemplateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
        }

        ~dispatcher() noexcept(false){
            if(!chained)
                wait_and_dispatch();
        }
    };

    /*
        1. TemplateDispatcher<>类模板仿照了dispatcher类，二者几乎相同。特别是在析构函数上，都是调用wait_and_dispatch()等待处理消息。
        2. 对于 wait_and_dispatch()，在处理消息过程中，需要检查消息是否已经得到了处理，
            当已经处理了一条消息，处理过程就可以停止，这样就可以等待下一组消息的输入
        3. 对于 dispatch() 函数，当获取了一个和指定类型匹配的消息，就使用函数调用的方式来处理消息；如果消息类型不匹配，那么就链接前一个调度器
        4. 当在 handle() 函数中进行链接后，就允许处理多种类型的消息。
            在链接了之前的TemplateDispatcher<>实例后，当消息类型和当前的调度器类型不匹配的时候，调度链会依次的向前寻找类型匹配的调度器。
        
        5. 这种简单的架构允许你向队列推送任何类型的消息，并且调度器有选择的与接收端的消息进行匹配。
            同样，也允许为了推送消息，将消息队列的引用进行传递的同时，保持接收端的私有性。
    */
}

namespace messaging{
    // sender 类是一个队列指针的包装，用于发送信息
    class sender{
        queue *q;
    public:
        sender()
            : q(nullptr){}
        
        explicit sender(queue* _q)
            : q(_q){}
        
        template<typename Msg>
        void send(Msg const& msg){
            if(q)
                q->push(msg);       // 将发送的信息推到队列中
        }
    };

    // receiver 用于接收信息
    class receiver{
        queue q;        // 接受者拥有对应队列
    public:
        operator sender(){      // 允许将类中的队列隐式转化为一个 sender 队列
            return sender(&q);
        }

        dispatcher wait(){       // 等待对队列进行调度
            return dispatcher(&q);
        }
    };

    /*
        1. sender 只拥有消息队列的引用，而 receiver 是拥有一个队列。可以使用隐式转换获取 sender 引用的类。

        2. 在 wait() 中，创建了一个 dispatcher 对象引用 receiver 中的队列。这里对消息进行等待，以及对其进行调度
           由 wait() 返回的 dispatcher 实例将马上被销毁，销毁时析构函数调用 wait_and_dispatch()，循环等待调度信息

        3. 在消息传入后，其将消息传给 dispatch() 函数，这个函数会检查消息是否是一个 close_queue 消息，如果不是，其返回 false 表示消息未被处理。

        4. handle() 函数对消息进行处理。这是一个函数模板，并且消息类型不可推断，要指定需要处理的消息的类型，并且传入一个函数来处理消息。
    */

}
