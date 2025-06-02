#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    template<size_t Rows, size_t Cols, Arithmetic T>
    struct Matrix
    {
        //Stores elements in row major
        T mat[Rows * Cols] {};

        Matrix() = default;

        /*
            Makes an Identiy Matrix if called on a square matrix.

            USEAGE:
                Matrix<4, 4, float>::Identity();
                OR
                Mat4f::Identity();

            RESULT:
                1 0 0 0
                0 1 0 0
                0 0 1 0
                0 0 0 1
        */
        static Matrix<Rows, Cols, T> Identity()
        {
            Matrix<Rows, Cols, T> result;
            if(Cols == Rows)
            {
                for(size_t i = 0; i < Rows; i++)
                {
                    result(i + 1, i + 1) = T{1};
                }
            }
            return result;
        }

        //TODO: Just temp later move into a debug libary!
        std::string ToString()
        {
            std::string result;
            for (int i = 0; i < Rows * Cols; i++)
            {
                result += " " + std::to_string(mat[i]);
            }

            return result;
        }

        /*
            Access matrix element at the given row and column.

            USEAGE:
                Matrix<4, 4, float> mat;
                float result = mat(3, 3);

            NOTE:
                - Indexing is 1-based
                - The Matrix is Row-Major
        */
        T& operator()(size_t row, size_t col) 
        {
            return mat[(row - 1) * Cols + (col - 1)];
        }

        /*
            Access matrix element at the given row and column.

            USEAGE:
                Matrix<4, 4, float> mat;
                float result = mat(3, 3);

            NOTE:
                - Indexing is 1-based
                - The Matrix is Row-Major
        */
        const T& operator()(size_t row, size_t col) const 
        {
            return mat[(row - 1) * Cols + (col - 1)];
        }

        
    };

    // Creates a 4x4 float matrix
    using Mat4f = Matrix<4, 4, float>;
}