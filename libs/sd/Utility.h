#pragma once

#define SD_MAKE_NONCOPYABLE(c) \
private:                       \
    c(const c &) = delete;     \
    c &operator=(const c &) = delete;

#define ASSERT assert
#define ASSERT_NOT_REACHED() ASSERT(false)

namespace SD {

auto exchange(auto &a, auto &&b)
{
    auto tmp = move(a);
    a = move(b);
    return tmp;
}

template<typename T>
inline T &&move(T &arg)
{
    return static_cast<T &&>(arg);
}

template<typename T>
struct RemoveReference {
    typedef T Type;
};
template<class T>
struct RemoveReference<T &> {
    typedef T Type;
};
template<class T>
struct RemoveReference<T &&> {
    typedef T Type;
};

template<class T>
inline constexpr T &&forward(typename RemoveReference<T>::Type &param)
{
    return static_cast<T &&>(param);
}

} // namespace SD

using SD::move;
using SD::forward;
using SD::exchange;