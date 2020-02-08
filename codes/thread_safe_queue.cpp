/*
    基于 std::queue，使用条件变量构建线程安全的队列 thread_safe_queue
    提供两种 pop， try_pop() 立即返回， wait_and_pop() 等待队列中有值时才返回
*/

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class thread_safe_queue{

    std::queue<T> q;
    mutable std::mutex mtx;
    std::condition_variable cond;

public:
    thread_safe_queue()
        : q(std::queue<T>()) {}
    
    // 拷贝构造函数
    thread_safe_queue(const thread_safe_queue& rhs){
        std::lock_guard<std::mutex> lk(rhs.mtx);
        q = rhs.q;
    }

    // 不支持直接赋值
    thread_safe_queue& operator=(const thread_safe_queue&) = delete;

    void push(T new_value){
        std::lock_guard<std::mutex> lk(mtx);
        q.push(new_value);
        cond.notify_one();      // 压栈后，发出通知
    }

    // try_pop() 的两个重载版本，立即返回。
    bool try_pop(T& value){
        std::lock_guard<std::mutex> lk(mtx);
        if(q.empty())   return false;

        value = q.front();
        q.pop();
        return true;
    }

    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lk(mtx);
        if(q.empty())   return std::shared_ptr<T>();

        std::shared_ptr<T> sptr(std::make_shared<T>(q.front()));
        q.pop();
        return sptr;
    }

    /* *** 关键部分 ***
       wait_and_pop() 的两个重载版本。
       wait_and_pop() 在队列为空时会一直等待
    */
    void wait_and_pop(T& value){
        std::unique_lock<std::mutex> lk(mtx);       // 这里必须用互斥锁
        cond.wait(lk, 
            [this]{ return !q.empty(); }           // 队列不为空才能继续执行
        );

        value = q.front();
        q.pop();
    }

    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lk(mtx);
        cond.wait(lk, 
            [this]{ return !q.empty(); }
        );

        std::shared_ptr<T> sptr(std::make_shared<T>(q.front()));
        q.pop();
        return sptr;
    }


    bool empty() const{
        std::lock_guard<std::mutex> lk(mtx);
        return q.empty();
    }

};
