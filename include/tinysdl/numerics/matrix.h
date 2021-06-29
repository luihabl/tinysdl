#pragma once 

#include <cmath>
#include <algorithm>

// M : rows
// N : columns

namespace TinySDL {
    
    template <typename T, size_t M, size_t N>
    struct Matrix {

        T data[M * N];
        size_t size() {return M * N;}

        Matrix normalized();
        T length();
        T distance_to(const Matrix<T, M, N> & other) const;
        

        void fill(T val) {std::fill_n(data, M * N, val);}

        T operator [](size_t i) const {return data[i];}
        T & operator [](size_t i) {return data[i];}

        static const Matrix zeros;
        static const Matrix ones;
        static const Matrix identity;
    };

    typedef Matrix<float, 2, 2> Mat2x2;
    typedef Matrix<float, 3, 2> Mat3x2;
    typedef Matrix<float, 3, 3> Mat3x3;
    typedef Matrix<float, 4, 4> Mat4x4;

    template <typename T, size_t M> using Vec = Matrix<T, M, 1>;
    typedef Vec<float, 2> Vec2;
    typedef Vec<float, 3> Vec3;
    typedef Vec<float, 4> Vec4;
    typedef Vec<uint8_t, 3> ByteVec3;
    typedef Vec<uint8_t, 4> ByteVec4;

    template <typename T, size_t M, size_t N>
    inline T Matrix<T, M, N>::length() {
        T sum_sqr = 0;
        for (const auto & e : data)
            sum_sqr += e * e;
        return sqrtf(sum_sqr);
    }

    template <typename T, size_t M, size_t N>
    inline T Matrix<T, M, N>::distance_to(const Matrix<T, M, N> & other) const {
        T sum_sqr = 0;
        T diff = 0;
        for (size_t i = 0; i < M * N; i++) {
            diff = other[i] - data[i];
            sum_sqr += diff * diff;
        }
        return sqrtf(sum_sqr);
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> Matrix<T, M, N>::normalized() {
        T len = length();
        return *this / len;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator+ (const Matrix<T, M, N> & a, const Matrix<T, M, N> & b) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = a.data[i] + b.data[i];
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator- (const Matrix<T, M, N> & a, const Matrix<T, M, N> & b) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = a.data[i] - b.data[i];
        return result;
    }
    
    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator- (const Matrix<T, M, N> & a) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = -a.data[i];
        return result;
    }
    

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator* (const Matrix<T, M, N> & a, const Matrix<T, M, N> & b) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = a.data[i] * b.data[i];
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator+ (const Matrix<T, M, N> & other, const T & val) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = other[i] + val;
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator+ (const T & val, const Matrix<T, M, N> & other) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = other[i] + val;
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator* (const Matrix<T, M, N> & other, const T & val) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = other[i] * val;
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator* (const T & val, const Matrix<T, M, N> & other) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = other[i] * val;
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator/ (const T & val, const Matrix<T, M, N> & other) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = val / other[i];
        return result;
    }

    template <typename T, size_t M, size_t N>
    inline Matrix<T, M, N> operator/ (const Matrix<T, M, N> & other, const T & val) {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M * N; i++) 
            result[i] = other[i] / val;
        return result;
    }

    namespace MatrixInit {

        template <typename T, size_t M, size_t N>
        inline Matrix<T, M, N> filled (T val) {
            Matrix<T, M, N> result;
            result.fill(val);
            return result;
        }

        template <typename T, size_t M, size_t N>
        inline Matrix<T, M, N> identity() {
            Matrix<T, M, N> id_matrix;
            id_matrix.fill(0.0f);
            
            for (size_t j = 0; j < N; j++)
                for (size_t i = 0; i < M; i++)
                    if (i == j) id_matrix[i + j * N] = 1.0f;

            return id_matrix;
        }
    }

    template <typename T, size_t M, size_t N> const Matrix<T, M, N> Matrix<T, M, N>::zeros = MatrixInit::filled<T, M, N>(0);
    template <typename T, size_t M, size_t N> const Matrix<T, M, N> Matrix<T, M, N>::ones = MatrixInit::filled<T, M, N>(1);
    template <typename T, size_t M, size_t N> const Matrix<T, M, N> Matrix<T, M, N>::identity = MatrixInit::identity<T, M, N>();
}