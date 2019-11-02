#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue> 
#include <thread>
namespace CCPlatform
{
    class fixed_thread_pool
    {
    public:
        //************************************
        // Method:    fixed_thread_pool
        // FullName:  CCPlatform::fixed_thread_pool::fixed_thread_pool
        // Access:    public 
        // Returns:   
        // Qualifier:
        // Parameter: size_t thread_count
        //************************************
        explicit fixed_thread_pool(size_t thread_count);
        //************************************
        // Method:    fixed_thread_pool
        // FullName:  CCPlatform::fixed_thread_pool::fixed_thread_pool
        // Access:    public 
        // Returns:   
        // Qualifier:
        //************************************
        fixed_thread_pool() = default;
        //************************************
        // Method:    fixed_thread_pool
        // FullName:  CCPlatform::fixed_thread_pool::fixed_thread_pool
        // Access:    public 
        // Returns:   
        // Qualifier:
        // Parameter: fixed_thread_pool & &
        //************************************
        fixed_thread_pool(fixed_thread_pool&&) = default;
        //************************************
        // Method:    ~fixed_thread_pool
        // FullName:  CCPlatform::fixed_thread_pool::~fixed_thread_pool
        // Access:    public 
        // Returns:   
        // Qualifier:
        //************************************
        ~fixed_thread_pool();
        //************************************
        // Method:    execute
        // FullName:  CCPlatform::fixed_thread_pool::execute
        // Access:    public 
        // Returns:   void
        // Qualifier:
        // Parameter: F & & task
        //************************************
        template <class F>
        void execute(F&& task)
        {
            {
                std::lock_guard<std::mutex> lk(data_->mtx_);
                data_->tasks_.emplace(std::forward<F>(task));
            }   
            data_->cond_.notify_one();
        }
    private:
        struct data
        {
            std::mutex mtx_;
            std::condition_variable cond_;
            bool is_shutdown_ = false;
            std::queue<std::function<void()>> tasks_;
        };
        std::shared_ptr<data> data_;
    };
}
