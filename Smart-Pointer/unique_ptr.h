// 简单的unique_ptr的实现，可以运行cpprefrence页面的所有示例

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cstddef>
#include <memory>
#include <utility>

inline namespace my_smart_pointer {

template <typename T, typename D = std::default_delete<T>> class unique_ptr {
  public:
    explicit unique_ptr(T *p = nullptr, const D &d = D())
        : ptr(p), deleter(d) {}
    unique_ptr(std::nullptr_t) noexcept : ptr(nullptr) {}

    // 移动构造和移动赋值
    unique_ptr(unique_ptr &&up) noexcept
        : ptr(up.ptr), deleter(std::move(up.deleter)) {
        up.ptr = nullptr;
    }
    unique_ptr &operator=(unique_ptr &&up) noexcept {
        swap(up);
        return *this;
    }

    // 禁用复制构造和复制赋值
    unique_ptr(unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &) = delete;

    ~unique_ptr() noexcept { reset(); }

    // 释放资源，返回原始指针，不再管理该指针
    T *release() noexcept { return std::exchange(ptr, nullptr); }

    // 释放当前的资源，接受并管理一个新的原始指针
    void reset(T *p = nullptr) noexcept {
        // 防止自赋值
        if (ptr != p) {
            deleter(ptr);
            p = ptr;
        }
    }

    // 交换两个 unique_ptr 的内容
    void swap(unique_ptr &up) noexcept {
        using std::swap;
        swap(ptr, up.ptr);
        swap(deleter, up.deleter);
    }

    // 返回原始指针
    T *get() const noexcept { return ptr; }

    // 转换为 bool 类型，判断是否为空指针
    explicit operator bool() const noexcept { return ptr != nullptr; }

    // 重载 * 运算符，解引用原始指针
    T &operator*() const { return *ptr; }

    // 重载 -> 运算符，访问原始指针的成员
    T *operator->() const noexcept { return ptr; }

  private:
    T *ptr = nullptr;
    D deleter;
};

// 模板偏特化，支持数组类型
template <typename T, typename D> class unique_ptr<T[], D> {
  public:
    explicit unique_ptr(T *p = nullptr, const D &d = D())
        : ptr(p), deleter(d) {}
    unique_ptr(std::nullptr_t) noexcept : ptr(nullptr) {}

    // 移动构造和移动赋值
    unique_ptr(unique_ptr &&up) noexcept
        : ptr(up.ptr), deleter(std::move(up.deleter)) {
        up.ptr = nullptr;
    }
    unique_ptr &operator=(unique_ptr<T> &&up) noexcept {
        swap(up);
        return *this;
    }

    // 禁用复制构造和复制赋值
    unique_ptr(unique_ptr &up) = delete;
    unique_ptr &operator=(unique_ptr &u) = delete;

    ~unique_ptr() noexcept { reset(); }

    T &operator[](size_t idx) const { return *(ptr + idx); }

    // 释放资源，返回原始指针，不再管理该指针
    T *release() noexcept { return std::exchange(ptr, nullptr); }

    // 释放当前的资源，接受并管理一个新的原始指针
    void reset(T *p = nullptr) noexcept {
        // 防止自赋值
        if (ptr != p) {
            deleter(ptr);
            ptr = p;
        }
    }

    // 交换两个 unique_ptr 的内容
    void swap(unique_ptr &up) noexcept {
        using std::swap;
        swap(ptr, up.ptr);
        swap(deleter, up.deleter);
    }

    // 返回原始指针
    T *get() const noexcept { return ptr; }

    // 转换为 bool 类型，判断是否为空指针
    explicit operator bool() const noexcept { return ptr != nullptr; }

    // 重载 * 运算符，解引用原始指针
    T &operator*() const { return *ptr; }

    // 重载 -> 运算符，访问原始指针的成员
    T *operator->() const noexcept { return ptr; }

  private:
    T *ptr;
    D deleter;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args &&...args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // namespace my_smart_pointer

#endif // UNIQUE_PTR_H
