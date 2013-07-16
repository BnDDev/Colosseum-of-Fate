#ifndef BND_H
#define BND_H

namespace BnD {
    constexpr size_t FILENAME_MAX_LEN = 256;

    template<int... I> struct Indices {};
    template<int N, int... I> struct BuildIndices : BuildIndices<N - 1, N - 1, I...> {};
    template<int... I> struct BuildIndices<0, I...> : Indices<I...> {};
    template<int N> using ExpandIndices = typename BuildIndices<N>::Indices;
}

#endif // BND_H
