namespace hustle {

template <typename T>
class allocator : public std::allocator<T> {
    using Base     = std::allocator<T>;
    using Pointer  = std::allocator_traits<Base>::pointer;
    using SizeType = std::allocator_traits<Base>::size_type;

public:
    allocator() = default;

    template <typename U>
    allocator(const allocator<U>& other)
        : Base(other){};

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

    Pointer allocate(SizeType n) {
        mMemoryUsed += n * sizeof(T);
        return Base::allocate(n);
    }

    void deallocate(Pointer p, SizeType n) {
        mMemoryUsed -= n * sizeof(T);
        Base::deallocate(p, n);
    }

    SizeType get_memory_usage() const { return mMemoryUsed; }

private:
    SizeType mMemoryUsed = {};
};

}  // namespace hustle