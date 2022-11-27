/*#include <iostream>
#include <optional>
#include <utility>
#include <vector>
#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>
#include <vector>

template <typename T>
struct myTask {
    struct promise_type {
        T value_;
        ~promise_type() {}

        myTask<T> get_return_object() {
            return myTask<T> {
                .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend()
        {
            boolIsDone = true;
            return {};
        }

        void unhandled_exception() { std::terminate(); }

        std::suspend_always return_value(auto value) {
            value_ = value;
            return {};
        }

        bool boolIsDone = false;
        auto isDone() { return boolIsDone; }
    };

    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<promise_type> coro) const noexcept { coro.promise().boolIsDone = true; }
    void await_resume() const noexcept {}

    std::coroutine_handle<promise_type> h_;
    operator std::coroutine_handle<promise_type>() const { return h_; }
};

myTask<int> suspendableLocateValue(int key, std::vector<int>& array, bool interleave)
{
    int currentInt = 0;
    if (interleave = true)
    {
        //do something here
        co_await std::suspend_always{};
    }
    currentInt = array.at(key);
    co_return currentInt;
}

myTask<std::optional<int>> getValue(std::vector<int>& array, int key, bool interleave)
{
    //int result = array.at(key);
    int leaf;

    if (interleave = true)
    {
        leaf = co_await suspendableLocateValue(key, array, true);
    }

    co_return std::make_optional(leaf);
}

void minimalInterleavedExecution(std::vector<int>& lookup,
    std::vector<int>& keys,
    std::vector<std::optional<int>>& results,
    int groupsize)
{
    std::vector<std::coroutine_handle<myTask<std::optional<int>>::promise_type>> handles;

    for (int i = 0; i < groupsize; ++i)
    {
        handles.push_back(getValue(lookup, keys.at(i), true));
    }
    int notDone = groupsize;
    int i = groupsize;
    while (notDone > 0)
    {
        for (int handleIndex = 0; handleIndex < handles.size(); ++handleIndex)
        {
            if (!handles.at(handleIndex).promise().isDone())
            {
                handles.at(handleIndex).resume();
            }
            else
            {
                results.push_back(handles.at(handleIndex).promise().value_);
                if (i < keys.size())
                {
                    handles.at(handleIndex) = getValue(lookup, keys.at(i), true);
                    ++i;
                }
                else
                {
                    --notDone;
                    handles.erase(handles.begin() + handleIndex);
                    --handleIndex;
                }
            }
        }
    }
}

int main()
{
    std::vector<int> lookup = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    std::vector<int> keys = { 4, 2, 0, 6, 9, 0 };
    std::vector<std::optional<int>> results;

    minimalInterleavedExecution(lookup, keys, results, 4);
}*/