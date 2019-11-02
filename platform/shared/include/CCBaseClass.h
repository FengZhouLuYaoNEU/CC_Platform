#pragma once
namespace CCPlatform
{
    /**
    * @class non_copyable 
    * @brief
    * copy not allowed
    * @author FengZhouLuYao
    * @note
    */
    class non_copyable
    {
    protected:
        non_copyable() = default;
        ~non_copyable() = default;
    private:
        non_copyable(const non_copyable&) = delete;
        void operator=(const non_copyable&) = delete;
    };
}
