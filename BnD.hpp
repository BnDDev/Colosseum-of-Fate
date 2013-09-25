#ifndef BND_H
#define BND_H

#include <cstdlib>

namespace BnD {
    constexpr size_t FILENAME_MAX_LEN = 256;

    template<typename T, int S> struct Vec {
        T v[S];
    };

    template<typename T> struct Vec<T, 2> {
        union {
            struct { T v[2]; };
            struct { T x, y; };
        };
    };

    template<typename T> struct Vec<T, 3> {
        union {
            struct { T v[3]; };
            struct { T x, y, z; };
            struct { T r, g, b; };
        };
    };

    template<typename T> struct Vec<T, 4> {
        union {
            struct { T v[4]; };
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
        };
    };

    template<typename T, int C, int R = C> struct Mat {
        T v[C][R];
    };

    template<int... I> struct Indices {};
    template<int N, int... I> struct BuildIndices : BuildIndices<N - 1, N - 1, I...> {};
    template<int... I> struct BuildIndices<0, I...> : Indices<I...> {};
    template<int N> using ExpandIndices = typename BuildIndices<N>::Indices;

    template<class C, int MAX = 256> class MemoryPool : public C {
    private:
        static void* unused[MAX];
        static size_t length;
    public:
        static void FreeUnused() {
            while(length) free(unused[--length]);
        }
        void* operator new(size_t size) {
            if(length) return unused[--length];
            else return malloc(size);
        }
        void operator delete(void* p) {
            if(length != MAX) unused[length++] = p;
            else free(p);
        }
    };
}

#endif // BND_H
