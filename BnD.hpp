#ifndef BND_HPP
#define BND_HPP

#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <array>

namespace BnD {
    template<int... I> struct Indices {};
    template<int N, int... I> struct BuildIndices : BuildIndices<N - 1, N - 1, I...> {};
    template<int... I> struct BuildIndices<0, I...> : Indices<I...> {};
    template<int N> using ExpandIndices = typename BuildIndices<N>::Indices;

    constexpr size_t FILENAME_MAX_LEN = 256;

    template<class CLASS, typename T, size_t S, size_t N = S> struct VecImpl : VecImpl<CLASS, T, S, N - 1> {};
    template<class CLASS, typename T, size_t S> struct VecImpl<CLASS, T, S, 0> : std::array<T, S> {
        const T* operator&() const { return reinterpret_cast<const T*>(this); }
        inline CLASS& self() { return *static_cast<CLASS*>(const_cast<VecImpl<CLASS, T, S, 0>*>(this)); }

        // TODO: define vector operators
    };
    template<class CLASS, typename T, size_t S> struct VecImpl<CLASS, T, S, 1> : VecImpl<CLASS, T, S, 0> {
        inline T& x() { return this->self()[0]; }
        inline T& r() { return this->self()[0]; }
        inline CLASS& x(const T& v) { return (this->self()[0] = v, this->self()); }
        inline CLASS& r(const T& v) { return (this->self()[0] = v, this->self()); }
    };
    template<class CLASS, typename T, size_t S> struct VecImpl<CLASS, T, S, 2> : VecImpl<CLASS, T, S, 1> {
        inline T& y() { return this->self()[1]; }
        inline T& g() { return this->self()[1]; }
        inline CLASS& y(const T& v) { return (this->self()[1] = v, this->self()); }
        inline CLASS& g(const T& v) { return (this->self()[1] = v, this->self()); }
    };
    template<class CLASS, typename T, size_t S> struct VecImpl<CLASS, T, S, 3> : VecImpl<CLASS, T, S, 2> {
        inline T& z() { return this->self()[2]; }
        inline T& b() { return this->self()[2]; }
        inline CLASS& z(const T& v) { return (this->self()[2] = v, this->self()); }
        inline CLASS& b(const T& v) { return (this->self()[2] = v, this->self()); }
    };
    template<class CLASS, typename T, size_t S> struct VecImpl<CLASS, T, S, 4> : VecImpl<CLASS, T, S, 3> {
        inline T& w() { return this->self()[3]; }
        inline T& a() { return this->self()[3]; }
        inline CLASS& w(const T& v) { return (this->self()[3] = v, this->self()); }
        inline CLASS& a(const T& v) { return (this->self()[3] = v, this->self()); }
    };

    // BnD::Vec<TYPE, SIZE> (default SIZE = 3)
    template<typename T, size_t S = 3> struct Vec : VecImpl<Vec<T, S>, T, S> {};

    template<class CLASS, typename T, size_t R, size_t C> struct MatImpl : std::array<Vec<T, C>, R> {
        const T* operator&() const { return reinterpret_cast<const T*>(this); }
        inline CLASS& self() { return *static_cast<CLASS*>(const_cast<MatImpl<CLASS, T, R, C>*>(this)); }

        // TODO: define matrix operators
    };
    template<class CLASS, typename T, size_t S> struct MatSquareImpl : MatImpl<CLASS, T, S, S> {
        template<int... Rs> static constexpr std::array<T, S> _makeIRows(Indices<Rs...>, size_t Cs) { return {((T)(Cs == Rs ? 1.0 : 0.0))...}; }
        template<int... Cs> static constexpr std::array<std::array<T, S>, S> _makeIdentity(Indices<Cs...>) { return {_makeIRows(BuildIndices<sizeof...(Cs)>{}, Cs)...}; }
        static constexpr CLASS IdentityMat() { return _makeIdentity(BuildIndices<S>{}); }

        // TODO: define multiply operators for matrices other than square
        CLASS operator *(const MatSquareImpl<CLASS, T, S>& mat) {
            CLASS ret = this->self();
            ret *= mat;
            return ret;
        }
        CLASS& operator *=(const MatSquareImpl<CLASS, T, S>& mat) {
            Vec<T, S> val;
            for(size_t r = 0; r < S; r++) {
                for(size_t c = 0; c < S; c++)
                    for(size_t i = (val[c] = 0.0, 0); i < S; i++)
                        val[c] += (*this)[i][r] * mat[c][i];
                for(size_t c = 0; c < S; c++)
                    (*this)[c][r] = val[c];
            }
            return this->self();
        }
        CLASS& Identity() {
            for(size_t r = 0; r < S; r++)
                for(size_t c = 0; c < S; c++)
                    (*this)[c][r] = (T)(r == c ? 1.0 : 0.0);
            return this->self();
        }
    };
    template<class CLASS, typename T> struct Mat4Impl : MatSquareImpl<CLASS, T, 4> {
        static constexpr const size_t S = 4;

        CLASS& Translate(size_t axis, T value) {
            assert(axis < S);
            for(size_t r = 0; r < S; r++)
                (*this)[S - 1][r] += value * (*this)[axis][r];
            return this->self();
        }
        CLASS& Scale(size_t axis, T value) {
            assert(axis < S);
            for(size_t r = 0; r < S; r++)
                (*this)[axis][r] *= value;
            return this->self();
        }
        CLASS& Rotate(size_t axis, T value) {
            assert(axis < S);
            T mc = cos(value);
            T ms = sin(value);
            uint8_t t1 = (axis + 1) % 3;
            uint8_t t2 = (axis + 2) % 3;
            for(size_t r = 0; r < S; r++) {
                T ov = (*this)[t2][r];
                (*this)[t2][r] = mc * (*this)[t2][r] - ms * (*this)[t1][r];
                (*this)[t1][r] = mc * (*this)[t1][r] + ms * ov;
            }
            return this->self();
        }
    };

    // BnD::Mat<TYPE, ROWS, COLS> (default COLS = ROWS, default ROWS = 4)
    template<typename T, size_t R = 4, size_t C = R> struct Mat : MatImpl<Mat<T, R, C>, T, R, C> {};
    template<typename T, size_t S> struct Mat<T, S, S> : MatSquareImpl<Mat<T, S>, T, S> {};
    template<typename T> struct Mat<T, 4> : Mat4Impl<Mat<T, 4>, T> {};

    template<typename T> struct Vertex {
        BnD::Vec<T, 3> position;
        BnD::Vec<T, 3> coords;
        BnD::Vec<T, 3> normals;
    };

    namespace Mesh {
        enum FLAGS {
            POSITION = 0x0,
            NORMALS = 0x1,
            TEXTURE = 0x2
        };
        template<typename T, typename I, uint8_t D, uint8_t C = 3, uint8_t F = 0> struct GenericMesh {
            using Vertex = BnD::Vec<BnD::Vec<T, D>, 1 + ((F & NORMALS) / NORMALS) + ((F & TEXTURE) / TEXTURE)>;
            using Face = BnD::Vec<I, C>;
            static constexpr const uint8_t Flags = F;
            I vertexCount;
            I faceCount;
            Vertex* vertices;
            Face* faces;
        };
    }

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

#endif // BND_HPP
