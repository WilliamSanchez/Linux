#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <memory>
#include <stdexcept>

template<typename T>
class  trivial_thread_safe_stack
{
    std::stack<T> stk;
    std::mutex m;
private:
    /* data */
public:
    void push(T element)
    {
        std::lock_guard<std::mutex> lg(m);
        stk.push(element);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lg(m);
        stk.pop();
    }

    T& Top()
    {
        std::lock_guard<std::mutex> lg(m);
        stk.top();
    }


    bool empty()
    {
        std::lock_guard<std::mutex> lg(m);
        return stk.empty();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lg(m);
        return stk.size();
    }
};

