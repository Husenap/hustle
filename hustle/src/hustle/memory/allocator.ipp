namespace hustle {

namespace allocators {

template <class PrimaryAlloc, class FallbackAlloc>
class fallback : private PrimaryAlloc, private FallbackAlloc {
public:
    virtual ~fallback() = default;
    char* allocate(std::size_t n, std::align_val_t a) {
        char* p = PrimaryAlloc::allocate(n, a);
        if (!p) p = FallbackAlloc::allocate(n, a);
        return p;
    }
    void deallocate(char* p, std::size_t n, std::align_val_t a) {
        if (PrimaryAlloc::owns(p, n)) {
            PrimaryAlloc::deallocate(p, n, a);
        } else {
            FallbackAlloc::deallocate(p, n, a);
        }
    }
    bool owns(char* p) {
        return PrimaryAlloc::owns(p) || FallbackAlloc::owns(p);
    }
};

template <std::size_t Size = 1 << 6>
class stack {
    static inline char mData[Size];
    char*              mCurrentPosition;

public:
    stack() { mCurrentPosition = mData; }
    virtual ~stack() = default;

    char* allocate(std::size_t n, std::align_val_t a) {
        const auto n1 = roundToAligned(n, a);
        if (n1 > static_cast<std::size_t>((mData + Size) - mCurrentPosition)) {
            return nullptr;
        }
        mCurrentPosition += n1;
        return mCurrentPosition - n1;
    }
    void deallocate(char* p, std::size_t n, std::align_val_t a) {
        if (p + roundToAligned(n, a) == mCurrentPosition) {
            mCurrentPosition = p;
        }
    }
    bool owns(char* p, std::size_t) { return p >= mData && p < mData + Size; }

private:
    std::size_t roundToAligned(std::size_t n, std::align_val_t a) {
        if (static_cast<std::size_t>(a) == 0) return n;

        const auto remainder = n % static_cast<std::size_t>(a);
        if (remainder == 0) return n;

        return n + static_cast<std::size_t>(a) - remainder;
    }
};

class heap {
public:
    virtual ~heap() = default;
    char* allocate(std::size_t n, std::align_val_t a) {
        return static_cast<char*>(::operator new(n, a));
    }
    void deallocate(char* p, std::size_t n, std::align_val_t a) {
        ::operator delete(p, n, a);
    }
};

template <class ParentAlloc, std::size_t MinSize, std::size_t MaxSize>
class freelist : private ParentAlloc {
    struct Node {
        Node* next = nullptr;
    };
    Node* mRoot = nullptr;

public:
    char* allocate(std::size_t n, std::align_val_t a) {
        if ((n >= MinSize) && (n <= MaxSize)) {
            if (mRoot) {
                auto p = reinterpret_cast<char*>(mRoot);
                mRoot  = mRoot->next;
                return p;
            } else {
                return ParentAlloc::allocate(MaxSize, a);
            }
        }
        return ParentAlloc::allocate(n, a);
    }
    void deallocate(char* p, std::size_t n, std::align_val_t a) {
        if ((n < MinSize) || (n > MaxSize)) {
            return ParentAlloc::deallocate(p, n, a);
        }
        auto node  = reinterpret_cast<Node*>(p);
        node->next = mRoot;
        mRoot      = node;
    }
    bool owns(char* p, std::size_t n) {
        return ((n >= MinSize) && (n <= MaxSize)) || ParentAlloc::owns(p, n);
    }
};

template <std::size_t Threshold, class SmallAlloc, class LargeAlloc>
class segregator : private SmallAlloc, private LargeAlloc {
public:
    char* allocate(std::size_t n, std::align_val_t a) {
        if (n <= Threshold) {
            return SmallAlloc::allocate(n, a);
        }
        return LargeAlloc::allocate(n, a);
    }
    void deallocate(char* p, std::size_t n, std::align_val_t a) {
        if (n <= Threshold) {
            return SmallAlloc::deallocate(p, n, a);
        }
        return LargeAlloc::deallocate(p, n, a);
    }
};

}  // namespace allocators

template <
    class T,
    class Alloc = allocators::segregator<
        1024 * 1024,
        allocators::segregator<
            65536,
            allocators::freelist<allocators::heap, 17, 65536>,
            allocators::freelist<allocators::heap, 65537, 1024 * 1024>>,
        allocators::
            freelist<allocators::heap, 1024 * 1024 + 1, 1024 * 1024 * 32>>>
class allocator : public std::allocator<T>, private Alloc {
    using Base     = std::allocator<T>;
    using Pointer  = std::allocator_traits<Base>::pointer;
    using SizeType = std::allocator_traits<Base>::size_type;

public:
    using value_type = T;

    allocator()          = default;
    virtual ~allocator() = default;

    template <typename U>
    allocator(const allocator<U>& other)
        : Base(other) {}

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

    Pointer allocate(SizeType n) {
        return reinterpret_cast<Pointer>(
            Alloc::allocate(n * sizeof(T), std::align_val_t(alignof(T))));
    }

    void deallocate(Pointer p, SizeType n) {
        Alloc::deallocate(reinterpret_cast<char*>(p),
                          n * sizeof(T),
                          std::align_val_t(alignof(T)));
    }
};

}  // namespace hustle
