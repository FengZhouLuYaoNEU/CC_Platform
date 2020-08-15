#include <cstdint>
template<typename T, uint32_t ID = 0>
class singleton final
{
  singleton() = delete;
  ~singleton() = delete;
  constexpr singleton(singleton&) =delete;
  singleton& operator=(const singleton&) = delete;
  constexpr singleton(singleton&&) =delete;
  singleton& operator=(const singleton&&) = delete;
public:
    static T& inst()
    {
        return x;
    }
private:
    static T x;
};
template<typename T, uint32_t ID>
T singleton<T, ID>::x;
