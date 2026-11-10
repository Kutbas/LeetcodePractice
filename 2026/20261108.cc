#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>
#include <set>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    // 1
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N);
        auto g = f;

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(g[i - 1], f[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 2
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 3
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> hash;
        vector<int> ret;

        for (auto n : nums1)
            hash[n]++;
        for (auto n : nums2)
            if (hash[n]-- > 0)
                ret.push_back(n);

        return ret;
    }
};

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <utility>
#include <stdexcept>
#include <atomic>
#include <type_traits>
#include <memory> // for  shared_ptr /  make_shared

class ThreadPool
{
public:
    // ============ 构造函数 ============
    // 创建 threads 个工作线程，线程启动后立即进入"等待任务"状态
    explicit ThreadPool(size_t threads) : _stop(false)
    {
        // 参数校验：线程数至少为 1，否则任务将永远无法被消费
        if (threads == 0)
            throw invalid_argument("ThreadPool requires at least 1 thread");

        for (size_t i = 0; i < threads; ++i)
        {
            // 每个工作线程执行相同的循环逻辑（消费者）
            _workers.emplace_back([this]
                                  {
                while (true)
                {
                     function<void()> task;
                    {
                        // 加锁保护任务队列
                         unique_lock< mutex> lock(this->_queue_mutex);

                        // 条件变量等待：
                        //   - 被 notify 唤醒后重新检查谓词
                        //   - 谓词为 true 时（_stop 或队列非空）继续执行
                        //   - 否则继续阻塞，避免虚假唤醒
                        this->_cv.wait(lock, [this] {
                            return this->_stop || !this->_tasks.empty();
                        });

                        // 线程池已停止且没有待处理任务 → 线程退出
                        if (this->_stop && this->_tasks.empty())
                            return;

                        // 从队列头部取出一个任务（用 move 避免拷贝）
                        task =  move(this->_tasks.front());
                        this->_tasks.pop();
                    }
                    // 注意：执行任务时已释放锁，保证其他线程可继续取任务

                    // 执行任务；若任务抛异常，packaged_task 会把异常存入 future
                    task();
                } });
        }
    }

    // ============ 提交任务 ============
    // 模板方法：接受任意可调用对象 F 和任意参数 Args...
    // 返回  future<返回值类型>，调用方可通过 get() 获取结果或捕获异常
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args)
        -> future<invoke_result_t<F, Args...>>
    {
        // 推导返回类型（C++17： invoke_result_t）
        using return_type = invoke_result_t<F, Args...>;

        // 用 packaged_task 包装任务：它能把返回值/异常写入关联的 future
        // 用 shared_ptr 是因为：
        //   1) packaged_task 只可移动不可拷贝
        //   2)  function 要求可拷贝
        // 包装成 lambda 后被  function 持有，生命周期安全
        auto task = make_shared<packaged_task<return_type()>>(
            bind(forward<F>(f), forward<Args>(args)...));

        // 在提交前获取 future，避免与工作线程竞争
        future<return_type> res = task->get_future();
        {
            unique_lock<mutex> lock(_queue_mutex);

            // 已停止的线程池不允许再提交任务
            if (_stop)
                throw runtime_error("enqueue on stopped ThreadPool");

            // 将任务压入队列；lambda 捕获 shared_ptr，保证 task 存活
            _tasks.emplace([task]()
                           { (*task)(); });
        }

        // 唤醒一个等待中的工作线程（若有空闲线程）
        _cv.notify_one();
        return res;
    }

    // ============ 析构函数 ============
    // 流程：设置停止标志 → 唤醒所有线程 → join 等待线程结束
    ~ThreadPool()
    {
        {
            unique_lock<mutex> lock(_queue_mutex);
            _stop = true;
        } // 缩小锁作用域，之后不再需要 _queue_mutex

        // 唤醒所有线程，让它们在检查到 _stop 且队列空后退出
        _cv.notify_all();

        // 等待所有工作线程退出（确保任务执行完、资源正确回收）
        for (thread &worker : _workers)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    // 线程池持有线程/锁等不可拷贝资源，禁用拷贝语义
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

private:
    // 工作线程列表
    vector<thread> _workers;
    // 任务队列：用  function<void()> 统一存放所有已包装的任务
    queue<function<void()>> _tasks;

    // 同步原语
    mutex _queue_mutex;     // 保护 _tasks
    condition_variable _cv; // 任务到达/停止时通知工作线程

    // 停止标志：atomic 保证多线程可见性
    // 也可用 mutex 保护，但 atomic 更轻量
    atomic<bool> _stop;
};

#endif // THREAD_POOL_H