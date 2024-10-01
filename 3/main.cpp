#include <iostream>
#include <memory>
#include <cstddef>

class A {
public:
    static void* operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }

    static void operator delete(void* p) {
        std::cout << "operator delete!" << std::endl;
        ::operator delete(p);
    }
};

template <class T>
struct custom_allocator {
    typedef T value_type;
    custom_allocator() noexcept {}
    template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
    T* allocate (std::size_t n) {
        return reinterpret_cast<T*>( ::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        ::operator delete(p);
    }

};

int main() {
    auto sp = std::allocate_shared<A>(custom_allocator<A>());
    return 0;
}

