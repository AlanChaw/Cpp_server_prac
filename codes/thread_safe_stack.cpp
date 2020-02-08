/*
 基于 std::stack 实现的线程安全的 thread_safe_stack
 仅支持 push() 和 pop() 操作，且 pop() 提供两种版本
 */

#include <memory>
#include <mutex>
#include <stack>
#include <exception>

struct empty_stack: std::exception{
    const char* what() const throw(){
        return "empty stack.";
    };
};

template<typename T>
class thread_safe_stack{
public:
    // 构造函数
    thread_safe_stack()
        : data(std::stack<T>()) {}

    // 拷贝构造函数
    thread_safe_stack(const thread_safe_stack& rhs){
        std::lock_guard<std::mutex> lk(rhs.m);        // 锁住传进来的引用
        data = rhs.data;                              // 注意只拷贝了数据，不拷贝互斥量！
    }

    // 不支持直接赋值，因为互斥量不能复制
    thread_safe_stack& operator=(const thread_safe_stack&) = delete;

    void push(T new_value){
        std::lock_guard<std::mutex> lk(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex> lk(m);
        if(data.empty())    throw empty_stack();        // 栈空则抛出异常，锁是异常安全的

        // 修改前栈先分配出要返回的指针
        const std::shared_ptr<T> sptr(std::make_shared<T>(data.top()));
        data.pop();
        return sptr;
    }

    void pop(T& value){
        std::lock_guard<std::mutex> lk(m);
        if(data.empty())    throw empty_stack();

        value = data.top();
        data.pop();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lk(m);
        return data.empty();
    }

private:
    std::stack<T> data;
    mutable std::mutex m;
};
