#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <functional>
#include <ctime>

using namespace std;

const int min_per_thread = 5;

template<typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator first, Iterator last, T& result){
        result = accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    const int length = last - first;

    if(!length) return init;

    const int max_threads = (length + min_per_thread - 1) / min_per_thread;

    int hardware_threads = thread::hardware_concurrency();
    hardware_threads = (hardware_threads == 0 ? 2 : hardware_threads);
    const int num_threads = min(hardware_threads, max_threads);

    cout << "using num of threads: " << num_threads << endl;

    const int block_size = length / num_threads;         // 这里不用管是否整除

    vector<T> results(num_threads);                      // 一个线程一个坑
    vector<std::thread> threads(num_threads - 1);        // 自身已经占用一个线程

    Iterator block_start = first;
    for(int i = 0; i < (num_threads - 1); ++i){
        Iterator block_end = block_start + block_size;   // end 指向当前块的末尾

        threads[i] = thread(accumulate_block<Iterator, T>(), 
                            block_start, block_end, ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results.back());

    for(auto& t: threads)
        t.join();
    
    return accumulate(results.begin(), results.end(), init);
}


int main(){
    const int length = 10000;
    vector<int> vec(length);
    for(int i = 0; i < length; ++i){
        vec[i] = i;
    }
    
    int total = parallel_accumulate(vec.begin(), vec.end(), 0);
    cout << total << endl;

    return 0;
}
