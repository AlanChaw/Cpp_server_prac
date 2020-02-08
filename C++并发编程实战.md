<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->


- [C++并发编程实战笔记](#c%E5%B9%B6%E5%8F%91%E7%BC%96%E7%A8%8B%E5%AE%9E%E6%88%98%E7%AC%94%E8%AE%B0)
  - [1. 线程管理](#1-%E7%BA%BF%E7%A8%8B%E7%AE%A1%E7%90%86)
    - [1.1 线程管理基础](#11-%E7%BA%BF%E7%A8%8B%E7%AE%A1%E7%90%86%E5%9F%BA%E7%A1%80)
    - [1.2 向线程函数传参](#12-%E5%90%91%E7%BA%BF%E7%A8%8B%E5%87%BD%E6%95%B0%E4%BC%A0%E5%8F%82)
    - [1.3 转移线程所有权](#13-%E8%BD%AC%E7%A7%BB%E7%BA%BF%E7%A8%8B%E6%89%80%E6%9C%89%E6%9D%83)
    - [1.4 运行时决定线程数量](#14-%E8%BF%90%E8%A1%8C%E6%97%B6%E5%86%B3%E5%AE%9A%E7%BA%BF%E7%A8%8B%E6%95%B0%E9%87%8F)
    - [1.5 标识线程](#15-%E6%A0%87%E8%AF%86%E7%BA%BF%E7%A8%8B)
  - [2. 线程间共享数据](#2-%E7%BA%BF%E7%A8%8B%E9%97%B4%E5%85%B1%E4%BA%AB%E6%95%B0%E6%8D%AE)
    - [2.1 共享数据带来的问题](#21-%E5%85%B1%E4%BA%AB%E6%95%B0%E6%8D%AE%E5%B8%A6%E6%9D%A5%E7%9A%84%E9%97%AE%E9%A2%98)
    - [2.2 使用互斥量保护共享数据](#22-%E4%BD%BF%E7%94%A8%E4%BA%92%E6%96%A5%E9%87%8F%E4%BF%9D%E6%8A%A4%E5%85%B1%E4%BA%AB%E6%95%B0%E6%8D%AE)
    - [2.3 保护共享数据的替代设施](#23-%E4%BF%9D%E6%8A%A4%E5%85%B1%E4%BA%AB%E6%95%B0%E6%8D%AE%E7%9A%84%E6%9B%BF%E4%BB%A3%E8%AE%BE%E6%96%BD)
  - [4. 同步并发操作](#4-%E5%90%8C%E6%AD%A5%E5%B9%B6%E5%8F%91%E6%93%8D%E4%BD%9C)
    - [4.1 等待一个事件或其他事件](#41-%E7%AD%89%E5%BE%85%E4%B8%80%E4%B8%AA%E4%BA%8B%E4%BB%B6%E6%88%96%E5%85%B6%E4%BB%96%E4%BA%8B%E4%BB%B6)
    - [4.2 使用期望等待一次性事件](#42-%E4%BD%BF%E7%94%A8%E6%9C%9F%E6%9C%9B%E7%AD%89%E5%BE%85%E4%B8%80%E6%AC%A1%E6%80%A7%E4%BA%8B%E4%BB%B6)
    - [4.3 限定等待时间](#43-%E9%99%90%E5%AE%9A%E7%AD%89%E5%BE%85%E6%97%B6%E9%97%B4)
    - [4.4 使用同步操作简化代码(函数化编程和消息队列)](#44-%E4%BD%BF%E7%94%A8%E5%90%8C%E6%AD%A5%E6%93%8D%E4%BD%9C%E7%AE%80%E5%8C%96%E4%BB%A3%E7%A0%81%E5%87%BD%E6%95%B0%E5%8C%96%E7%BC%96%E7%A8%8B%E5%92%8C%E6%B6%88%E6%81%AF%E9%98%9F%E5%88%97)
  - [5. C++内存模型和原子类型操作](#5-c%E5%86%85%E5%AD%98%E6%A8%A1%E5%9E%8B%E5%92%8C%E5%8E%9F%E5%AD%90%E7%B1%BB%E5%9E%8B%E6%93%8D%E4%BD%9C)
    - [5.1 内存模型基础](#51-%E5%86%85%E5%AD%98%E6%A8%A1%E5%9E%8B%E5%9F%BA%E7%A1%80)
    - [5.2 C++中的原子操作和原子类型](#52-c%E4%B8%AD%E7%9A%84%E5%8E%9F%E5%AD%90%E6%93%8D%E4%BD%9C%E5%92%8C%E5%8E%9F%E5%AD%90%E7%B1%BB%E5%9E%8B)
    - [5.3 同步操作和强制排序](#53-%E5%90%8C%E6%AD%A5%E6%93%8D%E4%BD%9C%E5%92%8C%E5%BC%BA%E5%88%B6%E6%8E%92%E5%BA%8F)
  - [6. 基于锁的并发数据结构设计](#6-%E5%9F%BA%E4%BA%8E%E9%94%81%E7%9A%84%E5%B9%B6%E5%8F%91%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E8%AE%BE%E8%AE%A1)
  - [7. 无锁并发数据结构设计](#7-%E6%97%A0%E9%94%81%E5%B9%B6%E5%8F%91%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E8%AE%BE%E8%AE%A1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# C++并发编程实战笔记

## 1. 线程管理

### 1.1 线程管理基础

1. 线程函数就是线程的入口，main()函数就是初始线程的入口。通常是无参数无返回值的函数。使用 C++ 线程库启动线程，可以归结为构造 `std::thread` 对象：
    ```cpp
    void do_some_work();
    
    std::thread my_thread(do_some_work);
    ```

    与大多数标准库一样，传重载了函数调用运算符（）的类的对象也是可以的：
    ```cpp
    class background_task{
    public:
        void operator()(  ) const{
            do_something();
            do_something_else();
        }
    };

    background_task f;
    std::thread my_thread(f);
    ```
    也可以使用 lambda 表达式（就相当于传一个函数了）：
    ```cpp
    std::thread my_thread([]{
        do_something();
        do_something_else();
    })
    ```

2. 启动线程后，在线程对象被销毁之前，必须决定以何种方式等待线程结束，否则程序就会终止。因此，即使在线程被创建后发生异常，也要确保线程能够正确 join 或 detach。

3. 对于使用 join() 来同步时，要确保在线程对象创建后，join()调用之前，的异常安全性，可以使用 RAII：
    ```cpp
    class thread_guard{
        thread& t;
    public:
        explicit thread_guard(thread& _t)
            : t(_t) {}

        ~thread_guard(){
            if(t.joinable())
                t.join();
        }

        // 禁止拷贝操作
        thread_guard(const thread_guard&) = delete;
        thread_guard& operator=(const thread_guard&) = delete;
    }

    // 当调用线程函数时：
    void f(){
        int local_state = 0;
        thread t(my_func);

        do_some_thing();

        thread_guard g(t);
    }
    ```
    使用 RAII 时，相当于利用了一层 `thread_guard` 做封装，而一旦函数执行过程中，线程 `join()`之前，出现了任何异常，编译器也会自动调用 `thread_guard` 对象 `g` 的析构函数，从而确保线程能够正确加入.


4. 如果选择分离线程(detach)，就必须保证线程结束之前，线程所要访问到的数据都是有效的。例如，当前函数已经退出，函数中局部变量已经被销毁，而线程还没有结束，仍然尝试访问函数中局部变量。要解决这种问题，可以使线程函数功能齐全，将数据都复制到线程中，而非复制到共享数据中（使用一个可接受参数的线程函数）。

5. 如果线程分离，就不能与主线程直接产生交互，主线程也没有 `std::thread` 可以引用该线程。分离线程在后台运行 `joinable() == false`。只有 `joinable() == true` 的时候才可以选择对线程进行 `join()` 或 `detach()` 这种分离线程通常称为 __守护线程(daemon threads)： 没有任何显示的用户接口，并在后台运行的线程__。 


---
### 1.2 向线程函数传参

1. __这里有一个大坑：__ 标准约定 `std::thread` 构造时向函数对象传递实际参数的拷贝（支持移动语义），而不是转发实际参数。即使函数要求接受引用，在构造时传进去的依然是拷贝（这其实是 thread 类构造函数的问题），这种情况在一些编译器是可以通过编译的，但是在函数中修改所谓的引用时，修改的只是线程内部拷贝的引用。这种情况在有些编译环境下根本无法通过编译。所以要求在传引用时，使用 `std::ref()` 函数明确指明传的是引用才可以：

    ```cpp
    void fn(int& a);

    int a = 10;
    std::thread t(fn, std::ref(a));
    t.detach();
    ```
    这样函数 `fn()` 就会真正接收到一个变量 `a` 的引用。

2. 传参时的另一个问题：要注意参数要在传给线程函数前要初始化完成，以满足异常安全性，例如：

    ```cpp
    void f(int i, std::string s);

    std::thread t(f, 3, "hello");
    ```
    这里 "hello" 是作为字面值传入的，会由 `const char*` 被隐式转换成 `string` ，但是这个转换过程中可能会出现异常，所以，需要在调用 `std::thread()` 前就将其转换为 `string` 对象。 这其实与 [Effective C++ 17. 以独立语句将 newed 对象置入智能指针](https://github.com/AlanChaw/Cpp_notes/blob/master/Effective_C%2B%2B.md#17-%E4%BB%A5%E7%8B%AC%E7%AB%8B%E8%AF%AD%E5%8F%A5%E5%B0%86-newed-%E5%AF%B9%E8%B1%A1%E7%BD%AE%E5%85%A5%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88) 所说的情况是一样的，因为一旦中途出现异常会出问题。

---
### 1.3 转移线程所有权

1. 线程不允许拷贝，但允许移动（发生所有权在实例中的转移）。这一点与 `unique_ptr` 很像。 顺带一提，对这类支持移动但不支持拷贝的对象，可以通过 `std::move` 函数把一个对象移动给另一个空对象，但是不支持移动给另一个非空的对象。
    ```cpp
    using std::thread;
    using std::move;

    t1 = thread(func1);
    // 将 t1 所有权转移给 t2
    thread t2 = move(t1);      
    // 声明一个临时对象 thread(func2)，对于临时对象，会隐式调用移动操作
    t1 = thread(func2);             

    // 将 t2 所有权转移给一个空对象 t3，是可以的
    thread t3;
    t3 = move(t2);
    
    // 将 t3 所有权转移给一个非空对象，会使程序崩溃
    t1 = move(t3);
    ```

2. 支持移动的情况下，也就是说支持其所有权在函数内外进行转移，也就是说
    - 一个 `std::thread` 对象可以作为函数返回值
    - 可以将 `std::thread` 对象作为参数传递给函数

    也就是说，guard_thread 类还可以进行一些改进，即不使用 `std::thread` 指针作为成员，而是直接使用一个对象，这样在构造时直接传入一个线程对象，将这个线程对象的所有权转移给自身成员中的线程对象即可。

---
### 1.4 运行时决定线程数量

1. 函数 `std::thread::hardware_concurrency()` 可以返回能同时并发在一个程序中的线程数量。多核系统中返回的是CPU核心数量。系统信息无法获取时返回0。这个值可以帮助我们动态地、合理地选择开放多少个线程，非常有用。

2. 例子，实现一个并行版本的 `std::accumulate()` 累加器函数。[代码链接](./codes/parallel_accumulate.cpp)  
    - 因为不能从线程中返回一个值（因为对于分离线程，返回值就算有也拿不到，没意义），所以需要传递 results 的引用到线程中。或者通过地址来获取线程执行的结果（_期望（futures）_）

    - 当线程运行时，所有必要的信息都需要传到线程中去，包括存储计算结果的位置。有时候可以传递一个标识数。或者使用线程自身的标识符。

---
### 1.5 标识线程

1. 获取线程标识
    - 可以通过 `std::thread` 的 `get_id()` 来获取当前线程的 id
    
    - 在线程内部，调用：`std::this_thread::get_id()`，也可以获得线程 id

2. 线程 id 常用来检测当前线程是否需要进行一些操作，比如用线程分割工作，主线程可能要做一些与子线程不同的工作。标准库提供了 `std::hash<std::thread::id>` 容器，所以 id 可以用作哈希表的 key.

---
## 2. 线程间共享数据

### 2.1 共享数据带来的问题

1. __不变量（invariants）__：对于特殊结构体的描述。例如双向链表，每个节点有一个指针指向下一个节点，有一个指针指向前一个节点，这就是这个结构体的不变量。但是当操作”删除双向链表中的一个节点“在执行的过程中，这个不变量会被破坏。对于比较复杂的数据结构或一次更新要改动很大的数据结构，不变量更容易被破坏。 一旦一个线程破坏了不变量，此时另一个线程对该数据结构进行修改，会导致错误，这就是：__条件竞争__

2. __条件竞争__： 其形成取决于几个线程相对的执行顺序，每个线程都抢着完成自己的任务，当不变量遭到破坏时，就会产生竞争。例如，并发地去修改一个独立对象，数据竞争是未定义行为的起因。
    - 良性条件竞争：改变顺序也不会影响结果（不变量保持不变）
    - 恶性条件竞争：不变量会遭到破坏

3. 恶性条件竞争通常是时间敏感的，问题复现的几率相当低，只有当系统负载增加时，随着执行数量的增加，执行序列问题的复现才会增加。所以当程序以调试模式运行时，这种错误常常会完全消失。

4. 避免恶性条件竞争
    - 对数据结构采用某种保护机制，确保只有进行修改的线程才能看到不变量被破坏时的中间状态，对于其他线程而言，修改要么已经完成，要么还未开始（相当于事务的隔离性）。
    - 对数据结构和不变量的设计进行修改，修改完的结构必须能完成一系列不可分割的变化（无锁编程）。
    - 使用事务的方式去处理数据结构的更新（像数据库系统那样）。所需的数据和读取都存储在事务日志中，将之前的操作合为一步，再进行提交。这称作”软件事务内存“。这种方法C++中没有直接支持。

---
### 2.2 使用互斥量保护共享数据

(这个部分这本书讲的有些乱，感觉这作者本身没什么实际开发经验，需要再找资料学习完善)

1. 当访问共享数据前，使用互斥量将相关数据锁住，当访问结束后将数据解锁。其他线程想要访问加锁数据，都必须等到当前加锁线程将数据解锁后才能访问。 __互斥量__ 是 C++ 中一种最通用的数据保护机制，但互斥量自身也存在一些问题，例如会导致死锁，或对数据保护太多。

2. C++中可以直接使用 `std::mutex` 创建互斥量，调用其 `lock() unlock()` 函数进行加锁和解锁，但是直接调用会破坏异常安全性。所以还可以使用一个  RAII 的模板类 `std::lock_guard`，其会在构造时提供上锁的互斥量，在析构时进行解锁。
    ```cpp
    #include <list>
    #include <mutex>
    #include <algorithm>

    using namespace std;

    list<int> some_list;    // 全局变量
    mutex some_mutex;       // 保护全局变量的互斥量

    void add_to_list(int val){
        // 上锁，使这个函数中对数据的访问是互斥的
        lock_guard<mutex> guard(some_mutex);    
        some_list.push_back(val);
    }

    bool list_contains(int val_to_find){
        // 上锁
        lock_guard<mutex> guard(some_mutex);
        return find(some_list.begin(), some_list.end(), val_to_find);
    }
    ```
    这个只是个例子，多数情况下互斥量会与保护的数据放在同一个类中都作为 private 成员，而不是定义成全局变量。 这里有一个问题在于，当函数返回的是数据的指针或引用时，会破坏对数据的保护，因为函数一旦结束互斥锁就会被销毁，而函数调用者依然可以修改数据。（其实这里直接遵循 [Effective C++ 28. 避免返回指向对象内部成分的句柄](https://github.com/AlanChaw/Cpp_notes/blob/master/Effective_C%2B%2B.md#28-%E9%81%BF%E5%85%8D%E8%BF%94%E5%9B%9E%E6%8C%87%E5%90%91%E5%AF%B9%E8%B1%A1%E5%86%85%E9%83%A8%E6%88%90%E5%88%86%E7%9A%84%E5%8F%A5%E6%9F%84) 的要求即可） 

3. 所以，需要精心组织代码来保证线程安全。首先，不仅要保证成员函数不要返回内部对象的指针或引用。而且，也要检查成员函数是否通过指针或引用的方式来调用。再有，将保护数据作为一个运行时参数是更危险的（传递到用户提供的函数指针或函数对象）。总之，要记住一点： __切勿将受保护数据的指针或引用传递到互斥锁作用域之外，无论是函数返回值，还是存储在外部可见内存，亦或是以参数形式传递到用户提供的函数中。__

4. 就算使用了互斥量保护共享数据，依旧需要确定数据受到了保护，需要发现 __接口内在的条件竞争__。 例如对一个类似 `std::stack` 结构的栈，虽然 `empty()` 和 `size()` 在被调用并返回时的结果是正确的，但结果是不可靠的，因为当这些函数返回后，其他线程可以自由访问栈并对栈做修改，这样读取的结果就有问题。 （其实这就是数据库事务的隔离性问题中，幻影读的行为）。例如：
    ```cpp
    stack<int> s;
    if (! s.empty()){                   // 1
        int const value = s.top();      // 2
        s.pop();                        // 3
        do_something(value);
    }
    ```
    这样的代码在单线程下是安全的，但是有可能在读取到栈非空后（1），另一个线程把这个栈掏干了，回到这个线程本身，就再无法正常弹出数据（2，3）。这就是接口固有设计产生的问题。 可以选择把锁的粒度增大，但是这样会导致多线程带来的性能收益明显降低。  
    书中给出了一个解决办法，即：让 `pop()` 函数返回一个指针（`shared_ptr`）指向栈顶元素，另一个重载的 `pop(T& )` 接收一个栈中元素的引用，将栈顶元素赋值给该引用，然后弹出栈顶元素。[线程安全的栈，代码](./codes/thread_safe_stack.cpp)。

5. __死锁__
    - 当使用多个细粒度锁时，一旦一个给定操作需要两个或两个以上的互斥量，就会发生死锁，这与条件竞争完全相反——不同的两个线程互相等待，什么都没做。

    - 一种方法是控制加锁顺序，都按相同顺序加锁，但是有些时候无法提前预知所有需要用到的锁。而且情况一多，依然无法设计出好的加锁顺序。

    - C++ STL提供了 `std::lock`，允许一次锁住多个互斥量，并且没有死锁风险。例如：
        ```cpp
        #include <mutex>

        class BigObject;
        void swap(BigObject& lhs, BigObject& rhs);
        class X{
        private:
            Bigobject big;
            std::mutex mtx;

        public:
            X(BigObject const& _big)
                : big(_big) {}

            friend void swap(X& lhs, X& rhs){
                if(&lhs == &rhs)    return;

                // 首先锁住两个对象的互斥量
                std::lock(lhs.mtx, rhs.mtx);
                // 使用 RAII lock_guard 将互斥量封装
                // adopt_lock 表示将锁交给 lock_guard 对象管理，不需要创建新锁了
                std::lock_guard<std::mutex> lockA(lhs.m, std::adopt_lock);
                std::lock_guard<std::mutex> lockB(rhs.m, std::adopt_lock);

                swap(lhs.big, rhs.big);
            }
        }
        ```
    虽然 `std::lock` 可以帮助避免死锁，但是不能帮助你只获取其中一个锁（要么都不加锁，要么都加锁）。这就需要程序员的经验来避免死锁了。

6. 死锁进阶
    - __避免嵌套锁__： 一个线程已经获得一个锁时，再别去获取第二个。就算要获取多个锁，也要使用 `std::lock` 来同时上锁。

    - __避免在持有锁时调用用户提供的代码__：因为没有办法确定用户要做什么（例如调用用户传入的函数）。

    - __使用固定顺序获取锁__：当一定要获取两个或以上的锁，并且不能使用 `std::lock` 来同时获取时，要在每个线程上都以固定的顺序来获取。
    - __使用层次锁__：需要对应用进行分层，并且识别在给定层上所有可上锁的互斥量。当试图对一个互斥量上锁时，如果该层锁已被低层持有，是不允许上锁的。
    - 在无锁情况下也会产生死锁，例如每个 `std::thread` 对象调用 `join()`，就会使两个或多个线程互相等待，即产生一个等待循环，从而产生死锁。也可以用分层的办法解决，一个线程只需要等待比自己层级低的线程结束即可。

7. `std::unique_lock`
    - 这种锁更为灵活，其对象以独占所有权的方式管理 mutex 对象的上锁和解锁操作。它具有 `lock_guard` 的功能，且更为灵活，都禁止拷贝，允许移动。
    - `unique_lock` 可以自由控制加锁和解锁（构造时传入 `std::defer_lock` 表明构造时不加锁），但 `lock_guard` 只能在构造时加锁，析构时解锁。 只是开销会多一些，而且允许不带互斥量进行声明。

---
### 2.3 保护共享数据的替代设施

1. 除了互斥量以外，还有其他方法来保护共享数据。例如，为了保护一个数据的初始化过程而使用互斥量是没有必要的。

2. 保护共享数据的初始化
    - 使用双重检查模式加锁对对象进行延迟初始化仍然存在潜在的条件竞争。因此 C++ STL 提供了 `std::once_flag` 和 `std::call_once` 来处理。比起锁住互斥量，并显示地检查对象是否被初始化，每个线程只需使用 `std::call_once`，在其结束时，就能安全地知道对象已经被其他线程初始化了。这种方法比互斥量消耗资源更少。
        ```cpp
        std::shared_ptr<Resource> sptr;
        std::once_flag flag;

        void init_resource(){
            sptr.reset(new Resource);
        }

        void foo(){
            std::call_once(flag, init_resource);

            sptr->do_something(); ...
        }
        ```

3. 保护很少更新的数据结构
    - 对于很少更新的数据结构，只有在写的过程当中需要加锁，在其他时刻的并发读取操作都是线程安全的，如果还使用 `std::mutex` 进行加锁，会削减并发性能，因为读操作也会被上锁，这是不合理的。

    - 使用 __"读写锁"__,这种锁允许两种使用方式：一个”写者“线程独占资源的访问，而多个”读者“允许并发访问。 C++标准库还未支持，可以使用 `boost::shared_mutex` 来做同步。
        - 写操作，使用 `std::unique_lock<boost::shared_mutex>` 上锁，保证该更新线程的独占访问。
        - 读操作，使用 `boost::shared_lock<boost::shared_mutex>` 获取访问权。
        - 当一个线程拥有共享锁，想获取独占锁时，会一直尝试直到当前拥有独占锁的线程释放它的锁（忙等待）；当一个线程拥有独占锁，其他线程无法获取任何锁。

4. 嵌套锁
    - `std::recursive_mutex`，允许多次上锁和多次解锁。例如，当调用 lock() 三次时，也必须调用 unlock() 三次。

    - 嵌套锁一般用在可并发访问的类上，其用互斥量保护其成员数据，每个成员函数都会对互斥量上锁，然后完成对应功能，之后再解锁互斥量。

    - 作者：这种方法不推荐。

---

## 4. 同步并发操作

### 4.1 等待一个事件或其他事件

1. 当一个线程等待另一个线程完成任务时
    - 可以持续检查互斥量。但是这是一种资源浪费。
    - 在等待的线程做检查的间隙，使用 `std::this_thread::sleep_for()` 进行周期性间歇
        ```cpp
        bool flag;
        std::mutex mtx;

        void wait_for_flag(){
            std::unique_lock<std::mutex> lk(mtx);
            while(!flag){       // flag 没释放，一直轮询
                lk.unlock();    // 解锁
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                lk.lock();      // 再上锁
            }
        }
        ```
        在等待间隙做解锁，休眠后加锁，是为了让其他等待的线程有机会获得锁。在休眠过程中，线程没有浪费执行时间，但是问题在于休眠多久很难确定。

    - 使用C++ STL 提供的工具去等待事件的发生。通过 __设置条件变量__，当另一个线程触发事件时，唤醒等待线程。

2. 在 `<condition_variable>` 头文件中包括 `std::condition_variable` 和 `std::condition_variable_any` 两套条件变量的实现。前者仅限与 `std::mutex` 一起工作，后者可以和满足最低标准的互斥量一起工作，它也更加灵活，但开销也更大。一般能用前者就先用前者了，除非对灵活性有特殊要求。例如：
    ```cpp
    std::mutex mtx;
    std::queue<data_chunk> q;           // 两个线程间传递数据的队列
    std::condition_variable data_cond;

    void data_preparation_thread(){
        while(has_more_data()){
            const data_chunk data = prepare_data();
            std::lock_guard<std::mutex> lk(mtx);
            q.push(data);
            data_cond.notify_one();     // 对等待线程通知
        }
    }

    void data_processing_thread(){
        while(true){
            std::unique_lock<std::mutex> lk(mtx);   // (2)
            data_cond.wait(lk, 
                []{return !data_queue.empty();}    
            );                                      // (1)
            data_chunk data = q.front();
            q.pop();
            lk.unlock();

            process(data);
            if(is_last_chunk(data))
                break;
        }
    }
    ```
    (1). 这里调用 `std::condition_variable::wait()`，其接受锁和一个 lambda 表达式，其会检查数据队列 q 是否为空，如果不为空，说明已经准备好数据了，就不需要等待。也就是说，__处理数据的线程会一直等待条件满足并将自己挂起，直到准备数据的线程将数据压入队列，并发出通知__。

    (2). `wait()` 函数检查条件，如果条件不满足则将当前线程挂起，并且会 __解锁 lk 的互斥量__，只有当收到 `notify_one()` 发来的通知时，才再次获取互斥锁，并再次检查 lambda 表达式的条件，只有条件满足，才继续进行，否则释放锁并继续挂起。 所以，这里 __必须用 `unique_lock`，而不能用`lock_guard`__。 另外，这里在获取到数据后立刻对队列解锁，然后再做 `process(data)`，这也是 `unique_lock` 灵活性的一个体现。

    `wait()` 函数也可传入函数指针或重载了调用符的对象，不用非要用 lambda 表达式，只是因为 lambda 表达式其实就是一个匿名函数，往往更适合这种情况。要注意的是，考虑到可能会发生 __伪唤醒__（因为可能它收到了通知，但在这个时间差内条件又变为不满足了，就还要继续等待），所以最好不要用带有副作用的函数来做条件检查，因为这个函数可能会被执行若干次。

3. 使用条件变量构建线程安全的队列
    - `std::queue` 支持的操作包括
        - 构造函数、重载=、移动构造
        - 状态查询：empty(), size()
        - 元素查询：front(), back()
        - 修改：push(), pop(), emplace().   
            （empalce 与 push 的不同在于其直接接受右值，会为传入的右值自动移动构造，而 push 只接受左值并为左值拷贝构造）
    
    - 同之前的 stack 一样，为了避免在固有接口上带来的条件竞争，需要将 front() 和 pop() 合并成一个函数。与栈不同的是，当使用队列在多个线程中传递数据时，接收线程通常要等待数据的压入（当队列为空时）。这里提供 `try_pop()` 用于尝试弹出，总会直接返回。`wait_and_pop()` 会等待有值可检索的时候才返回。

    - [使用条件变量构建线程安全的队列-代码](./codes/thread_safe_queue.cpp)

    - 这种办法可以用来分解工作负载，并且只有一个线程对通知做出反应。当新数据准备完成时，`notify_one()` 会出发一个正在执行 wait() 的线程。告诉此线程去检查 wait() 的条件。

    - 当所有线程都在等待同一事件时，可以使用 `notify_all()` 来通知。

---
### 4.2 使用期望等待一次性事件

1. __期望（future）__：当一个线程需要等待一个特定的一次性事件时，在某种程度上来说它就需要知道这个事件在未来的表现形式。之后，这个线程会周期性地等待或检查是否触发（检查信息板）；在检查期间也会执行其他任务，直到对应的任务触发，等待期望的状态就会变为就绪（ready）。一个期望可能是数据相关的，也可能不是。当事件发生时，这个期望就不能被重置了。

2. C++ STL 提供两种期望。
    - __唯一期望__：`std::future<>`，一个对象只能与一个指定事件相关联。

    - __共享期望__：`std::shared_future<>`，可以关联多个事件。

    相当于是仿照智能指针的两种实现。而且期望对象本身不提供同步访问，多个线程需要访问一个独立的期望对象时，需要使用互斥量或类似机制进行保护。

3. 带返回值的后台任务：
    - 由于 `std::thread` 不提供直接接收返回值的机制。就需要 `std::async` 函数模板了（头文件 `<future>` 中）。当任务结果不着急要时，可以使用 `std::async` 启动一个异步任务，该函数会返回一个 `std::future` 对象，这个对象持有最终计算出来的结果。当需要这个值时只需调用其 `get()` 函数，这样会阻塞线程直到期望状态变为就绪为止，之后返回计算结果。例如：
        ```cpp
        #include <future>
        #include <iostream>

        int find_the_answer();
        void do_other_stuff();

        int main(){
            std::future<int> the_answer = std::async(find_the_answer);

            do_other_stuff();

            std::cout << "The answer is " << the_answer.get() << std::endl;
        }
        ```

    当然，`std::async` 也像 `std::thread` 一样，支持为函数传入参数，或使用对象的成员函数。各种情况下的使用方式：
    ```cpp
    #include <string>
    #include <future>
    struct X
    {
    void foo(int,std::string const&);
    std::string bar(std::string const&);
    };
    X x;
    auto f1=std::async(&X::foo,&x,42,"hello");  // 调用p->foo(42, "hello")，p是指向x的指针
    auto f2=std::async(&X::bar,x,"goodbye");  // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本
    struct Y
    {
    double operator()(double);
    };
    Y y;
    auto f3=std::async(Y(),3.141);  // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
    auto f4=std::async(std::ref(y),2.718);  // 调用y(2.718)
    X baz(X&);
    std::async(baz,std::ref(x));  // 调用baz(x)
    class move_only
    {
    public:
    move_only();
    move_only(move_only&&)
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&);
    move_only& operator=(move_only const&) = delete;

    void operator()();
    };
    auto f5=std::async(move_only());  // 调用tmp()，tmp是通过std::move(move_only())构造得到
    ```

    - 同时，也可以在创建时先不执行，而是延后执行：
        ```cpp
        auto f6=std::async(std::launch::async,Y(),1.2);  // 在新线程上执行
        auto f7=std::async(std::launch::deferred,baz,std::ref(x));  // 在wait()或get()调用时执行
        auto f8=std::async(
                    std::launch::deferred | std::launch::async,
                    baz,std::ref(x));  // 实现选择执行方式，这种是默认的
        auto f9=std::async(baz,std::ref(x));
        f7.wait();  //  调用延迟函数
        ```

4. __任务与期望__
    - `std::packaged_task<>` 对一个函数或可调用对象绑定一个期望。当该类的对象被调用，它就会调用相关函数或可调用的对象，将期望状态置为就绪，返回值也会被存储为相关数据。其模板参数是一个函数签名，例如 `int(string&, double)`。当构造一个 `std::packaged_task<>` 实例时，必须传入一个函数或可调用对象（重载了（）运算符）。支持隐式类型转换。
    
    - __例子：线程间传递任务__: 当一个线程需要更新界面时，它发出一条信息给正确的线程，让特定的线程来做界面更新。这里使用 `std::packaged_task<>`来实现，并且不需要发送自定义信息给GUI线程：
        ```cpp
        #include <deque>
        #include <mutex>
        #include <future>
        #include <thread>
        #include <utility>

        std::mutex m;
        std::deque<std::packaged_task<void()>> tasks;   // 任务队列

        bool gui_shutdown_message_reveived();
        void get_and_process_gui_message();

        void gui_thread(){
            // GUI线程，一直轮询，只要未收到关闭信息就一直循环
            while(!gui_shutdown_message_recevied()){
                get_and_process_gui_message();
                std::packaged_task<void()> task;
                {
                    std::lock_guard<std::mutex> lk(m);  // 加锁
                    if(tasks.empty())                   // 无任务，跳过
                        continue;
                    // 若有任务，取出任务
                    task = std::move(tasks.front());
                    tasks.pop_front();
                    // 这里执行到代码块末尾，会自动释放锁
                }
                // 执行取出的任务
                task();
            }
        }

        std::thread gui_bg_thread(gui_thread);
        
        // 将任务传入队列
        template<typename Func>
        std::future<void> post_task_for_gui_thread(Func f){
            // 提供一个打包好的任务
            std::packaged_task<void()> task(f);
            // 通过 get_future() 获取期望对象，因为函数返回值为 void，所以期望类型为 void
            std::future<void> res = task.get_future();

            std::lock_guard(std::mutex) lk(m);  // 队列上锁
            tasks.push_back(std::move(task));   // 添加新任务
            return res;
        }

        ```
        这里的期望和打包的任务是绑定的，将期望对象返回给当前线程，当前线程可以根据当前期望来判断GUI是否更新完成，或使用该期望等待GUI的更新。

5. __使用 `std::promise`__
    - 考虑一个线程用来处理多个网络连接的情况，来自不同端口的连接基本上以乱序处理，同时不同端口的数据报也以乱序方式进入队列。
    - `std::promise<T>` 提供设定值的方式，其类型T与 `std::future<T>` 对象相关联。一对这样的对象可以提供一个可行的机制：在期望上可以阻塞等待线程，同时，提供数据的线程可以使用组合中的“承诺”来对相关值进行设置，以及将期望的状态置为就绪。当承诺的值已经设置完毕(`set_value()`)，对应期望的状态变为就绪，并且可用于检索已存储的值。
    - __例子：单线程处理多接口__
        ```cpp
        #include <future>

        void process_connections(connection_set& connections){
            // 轮询，直到done()为止
            while(!done(connections)){
                // 依次检查每个连接
                for(connection_iterator connection = connections.begin();
                    connection != connections.end(); ++connection){
                
                    // 是否有传入的数据包（即网络请求）
                    if(connection->has_incoming_data()){    
                        data_packet data = connection->incoming();
                        // 将 id 映射到 promise
                        std::promise<payload_type>& p = connection->get_promise(data.id);
                        p.set_value(data.payload);
                    }

                    // 是否有需要传出的数据包
                    if(connection->has_outgoing_data()){
                        outgoing_packet data = connection->top_of_outgoing)queue();
                        connection->send(data.payload);
                        // 将承诺设置为 true，表示传输成功
                        data.promise.set_value(true);
                    }
                }

            }
        }
        ```
        其中 payload_type 是数据包的负载类型。  
        这里使用了 “承诺/期望” 组合方式，首先当有数据包（网络请求）传入时，拿到当前数据，使用当前数据的id取得对应的承诺对象，将承诺值设置为数据中的负载。 再检查是否有需要传回的数据包，如果有，则传回数据包，将承诺值设置为 true，表示传输成功。  
        通过 promise 对象的 `get_future()` 对象可以拿到对应的期望对象，可以以此判断对应的承诺是否执行完成。

6. 为期望存储异常
    - 当在异步调用一个函数(`std::async()`)时，如果该函数抛出一个异常，这个异常就会存储到“期望”的结果数据中，之后“期望”的状态将被设置为“就绪”，之后调用 get() 会抛出这个存储的异常。如果将函数打包到 `std::packaged_task<>` 任务包中，在这个任务被调用时，同样的事情也会发生。- `std::promise` 也提供同样的功能，当希望存入一个异常，而不是一个数值时，需要调用 `set_exception()` 函数，而不是 `set_value()`。例如：
        ```cpp
        extern std::promise<double> some_promise;
        try{
            some_promise.set_value(calculate_value());
        }catch(...){
            some_promise.set_exception(std::current_exception());
        }
        ```

    - `std::future` 有一定的局限性，当很多线程在等待时，只有一个线程能获取等待结果。当多个线程需要等待相同事件的结果，需要使用 `std::shared_future`。 这里就类似智能指针的 `shared_ptr`

7. __多个线程的等待__
    - 当调用某一个 `std::future` 对象的成员函数时，会让这个线程的数据和其他线程数据不同步。当多线程在没有额外同步的情况下，访问一个独立的 `std::future` 对象，会有数据竞争和未定义行为。因为 `std::future` 的 `get()` 函数只能被一次性地调用，只有一个独立的线程能够获取到返回结果，第一次调用后就没有结果可以获取了。

    - 这就要用到 `std::shared_future`了，在多个线程对该对象访问时，避免数据竞争导致的不同步，还是需要加锁。如果不加锁的话，也可以让每个线程都有独立的拷贝对象，这样每个线程访问自己的对象获取结果即可，这样共享同步结果是线程安全的。

    - 例如：对复杂的表格的并行执行，每个单元格有单一的终值，这个终值结果依赖于其他单元格，这时可以使用 `std::shared_future` 来引用其所依赖的单元格的数据。

    - 当 `std::future` 对象没有其他对象共享同步状态所有权，所有权必须使用 `std::move` 将所有权传递到 `std::shared_future`：
        ```cpp
        // 默认构造函数
        std::promise<int> p;

        std::future<int> f(p.get_future());     // 通过承诺 p 获取到期望对象 f
        assert(f.valid());      // 期望 f 合法
        std::shared_future<int> sf(std::move(f));   // 转移所有权
        assert(!f.valid());     // 期望 f 不再合法
        assert(sf.valid());     // 期望 sf 合法

        std::shared_future<int> sf(p.get_future());     // 支持隐式转移所有权
        // 或调用 std::future 的 share() 函数转移所有权给 sf
        std::shared_future<int> sf = p.get_future().share()
        ```
    
    - 直接隐式转换所有权或使用 share() 函数转移的好处在于，当 promise 的类型改变时，不需要再更改代码修改 future 的类型。

---
### 4.3 限定等待时间

之前的阻塞调用会阻塞一段不确定的时间，将线程挂起知道等待事件的发生。很多情况下，需要对等待时间进行一个限制。例如，对于用户交互进程，可以支持用户按下“取消”来直接终止等待。
- __“时延”的超时方式__
    - 指定一段时间（如30ms），以 `_for` 为后缀
- __"绝对"的超时方式__
    - 指定一个时间点，以 `_until` 为后缀

1. C++ STL 时钟，头文件 <chrono>
    - 提供了四种不同的信息：
        - 现在时间
        - 时间类型
        - 时钟节拍
        - 通过时钟节拍的分布，判断时钟是否稳定

    - 时钟的当前时间可以通过调用静态成员函数now()从时钟类中获取；例如，`std::chrono::system_clock::now()`是将返回系统时钟的当前时间

    - 其他对于 `std::chrono` 的介绍 略

2. __例子：等待一个条件变量（有超时功能）__
    ```cpp
    #include <condition_variable>
    #include <mutex>
    #include <chrono>

    std::condition_variable cv;
    bool done;
    std::mutex m;

    bool wait_loop(){
        auto const timeout = std::chrono::steady_clock::now() + 
                             std::chrono::milliseconds(500);
        std::unique_lock<std::mutex> lk(m);     // 上锁
        while(!done){
            // 超时自动跳出循环
            if(cv.wait_until(lk, timeout) == std::cv_status::timeout)
                break;
        }
        return done;        // 如果是正常执行完毕，则 true，如果是超时中断的，则 false
    }
    ```

3. 具有超时功能的函数
    - 对一个特定的线程添加一个延迟处理，当这个线程无所事事时，就不会占用可供其他线程处理的时间。就像之前的例子中使用的 `std::this_thread::sleep_for()` 和 `std::this_thread::sleep_until()`。有些事必须在指定时间范围内完成，所以耗时很重要。例如，每天早晨6.00打印工资条。

    - 超时可以配合条件变量或 future 一起使用。甚至可以在尝试获取一个互斥锁时使用，`std::timed_mutex` 和 `std::recursive_timed_mutex` 支持超时锁。它们提供 `try_lock_for()` 和 `try_lock_until()` 成员函数。

---
### 4.4 使用同步操作简化代码(函数化编程和消息队列)

这一章介绍了：__条件变量、future、packaged_task、promise__。这里介绍如何使用这些机制，来简化线程的同步操作。

1. __使用 future 的函数化编程__

    - __函数化编程__，这种编程方式中的函数结果只依赖于传入函数的参数，并不依赖外部状态。一个纯粹的函数不会改变任何外部状态。 尤其是当并行时，如果函数都是纯粹的，都不会涉及对共享数据的修改，就不存在条件竞争，也就没有必要使用互斥量对共享数据进行保护。 future 使得 _函数化编程模式并发化_ 在 c++ 中成为可能。一个“期望”对象可以在线程间互相传递，并允许其中一个计算结果依赖于另外一个的结果，而非对共享数据的显式访问。

    - 例子，函数化编程的快速排序，顺序版（递归实现）：
        ```cpp
        template<typename T>
        std::list<T> sequential_quick_sort(std::list<T> input){
            if(input.empty())   return input;

            std::list<T> ans;
            // 将输入列表的首个元素放入 ans 中
            ans.splice(ans.begin(), input, input.begin());
            // 获取轴值 pivot
            T const& pivot = *ans.begin();

            // 对列表重置，返回一个指向首元素的迭代器
            auto divide_point = std::partition(input.begin(), input.end(), 
                                [&](T const& t){return t < pivit;});

            std::list<T> lower_part;
            lower_part.splice(lower_part.end(), input, input.begin(),                           divide_point);
            auto new_lower(sequential_quick_sort(std::move(lower_part)));
            auto new_higher(sequential_quick_sort(std::move(input)));

            ans.splice(ans.end(), new_higher);    // 插入到 pivot 后边
            ans.splice(ans.begin(), new_lower);   // 插入到 pivot 前边

            return ans;
        }
        ```

        __函数化编程快速排序，并行版（使用期望，递归实现）__：
        ```cpp
        template<typename T>
        std::list<T> parallel_quick_sort(std::list<T> input){
            if(input.empty())   return input;

            std::list<T> ans;
            ans.splice(ans.begin(), input, input.begin());
            T const& pivot = *result.begin();

            auto divide_point = std::partition(input.begin(), input.end(),
                                [&](T const& t){return t < pivot;});
            
            std::list<T> lower_part;
            lower_part.splice(lower_part.end(), input, input.begin(),
                                divide_point);
            
            // 当前线程对 lower 部分，交给另一个线程对其进行排序
            std::future<std::list<T>> new_lower(
                                    std::async(&parallel_quick_sort<T>,
                                    std::move(lower_part))
                                    );
            
            // higher 部分，仍使用递归方式进行排序
            auto new_higher(parallel_quick_sort(std::move(input)));

            ans.splice(ans.end(), new_higher);
            ans.splice(ans.begin(), new_lower.get());   // 从 future 获取结果

            return ans;
        }
        ```
        最后对 lower 部分，需要调用 future::get() 函数去检索数值，如果未计算完，会等待该后台任务完成（线程同步），并且将结果移入 `splice()` 调用中。  
        有一个问题是，虽然使用了 `std::async`，进行异步调用，但是 `std::partition` 做了很多工作，这里仍然是顺序调用。但这样也已经足够好了。
    
    - 因为避开了共享易变数据，函数化编程可算作是并发编程的范型；并且也是通讯顺序进程(CSP,Communicating Sequential Processer[3],)的范型，这里线程理论上是完全分开的，也就是没有共享数据，但是有通讯通道允许信息在不同线程间进行传递。这种范型被Erlang语言所采纳，并且在MPI(Message Passing Interface，消息传递接口)上常用来做C和C++的高性能运算。



2. __使用消息传递的同步操作__

    - __通讯顺序进程(CSP,Communicating Sequential Processer)__：当没有共享数据，每个线程就可以进行独立思考，其行为纯粹基于其所接收到的信息。每个线程就都有一个状态机：当线程收到一条信息，它将会以某种方式更新其状态，并且可能向其他线程发出一条或多条信息，对于消息的处理依赖于线程的初始化状态。

    - __真正通讯顺序处理是没有共享数据的，所有消息都是通过消息队列传递__，但是因为C++线程共享一块地址空间，所以达不到真正通讯顺序处理的要求。这里就需要有一些约定了：作为一款应用或者是一个库的作者，我们有责任确保在我们的实现中，线程不存在共享数据。当然，为了线程间的通信，消息队列是必须要共享的，具体的细节可以包含在库中。

    - 例子，ATM机逻辑类的实现，这里所有信息传递所需的同步，完全包含在“信息传递”库中。
        - ATM机的状态机简化模型    
            <div align="center">
            <img src="./pics/atm.png" width="600" align=center />
            <br><br>
            </div>

        - 消息传递框架与完整的ATM示例  
            完整代码在 'codes/atm' 中

---

## 5. C++内存模型和原子类型操作

### 5.1 内存模型基础

1. C++程序中所有数据都由对象构成。
    - 每一个变量都是一个对象，包括作为其成员变量的对象
    - 每个对象至少战友一个内存位置
    - 基本类型都有确定的内存位置
    - 相邻位域是相同内存中的一部分

2. 当两个线程产生条件竞争时，为了避免条件竞争，一种方法是使用互斥量来确定访问顺序。另一种方式是使用 __原子操作同步机制__ 决定两个线程的访问顺序。当多于两个线程访问同一个内存地址时，对每个访问都需要定义一个顺序。如果不去规定两个不同线程对同一内存地址访问的顺序，那么访问就不是原子的；并且，当两个线程都是“作者”时，就会产生数据竞争和未定义行为。

3. __修改顺序__
    - 每一个在C++程序中的对象，都有(由程序中的所有线程对象)确定好的修改顺序，在的初始化开始阶段确定。在大多数情况下，这个顺序不同于执行中的顺序，但是在给定的执行程序中，所有线程都需要遵守这顺序。


---
### 5.2 C++中的原子操作和原子类型

1. __原子操作__ 是个不可分割的操作。 在系统的所有线程中，你是不可能观察到原子操作完成了一半这种情况的； 它要么就是做了，要么就是没做，只有这两种可能。

2. __标准原子类型__ 定义在头文件 `<atomic>` 中。 这些类型上的所有操作都是原子的，在语言定义中只有这些类型的操作是原子的，不过你可以用互斥锁来"模拟"原子操作。

---
### 5.3 同步操作和强制排序



---

## 6. 基于锁的并发数据结构设计



---
## 7. 无锁并发数据结构设计
