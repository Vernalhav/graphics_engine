#pragma once
#include <vector>

#include "vectors.h"
#include "../engine/Transform.h"

struct Matrix3 {
    static const int DIM = 3;
    float matrix[DIM][DIM];

    Matrix3() {
        memset(matrix, 0, sizeof(matrix));
        for (int i = 0; i < DIM; i++)
            matrix[i][i] = 1;
    }

    Matrix3(const Matrix3& other) {
        memcpy(matrix, other.matrix, sizeof(matrix));
    }

    Matrix3(const Transform& transform) {
        *this = Matrix3();

        this->scale(transform.scale);
        this->rotate(transform.rotation);
        this->translate(transform.translation);
    }

    // Must be 3 x 3
    Matrix3(const std::vector<std::vector<float>>& values) {
        if (values.size() != DIM || values[0].size() != DIM) {
            *this = Matrix3();
            return;
        }

        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                matrix[i][j] = values[i][j];
            }
        }
    }

    float& operator()(int i, int j) {
        return matrix[i][j];
    }

    float operator()(int i, int j) const {
        return matrix[i][j];
    }

    Matrix3 operator*(const Matrix3& other) const {
        Matrix3 ans;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                float dot_product = 0;
                for (int k = 0; k < DIM; k++) {
                    dot_product += matrix[i][k] * other(k, j);
                }
                ans(i, j) = dot_product;
            }
        }

        return ans;
    }

    // this = other * this (left-multiplication)
    Matrix3& operator*=(const Matrix3& other) {
        Matrix3& thisMatrix = *this;
        Matrix3 ans = other * thisMatrix;

        memcpy(thisMatrix.matrix, ans.matrix, sizeof(thisMatrix.matrix));
        return thisMatrix;
    }

    void rotate(float angle) {
        Matrix3 rotation = { {
            { cos(angle), -sin(angle), 0 },
            { sin(angle),  cos(angle), 0 },
            { 0, 0, 1 }
        } };

        *this *= rotation;
    }

    void translate(const Vector3& offsets) {
        Matrix3 translation = { {
            { 1, 0, offsets.x },
            { 0, 1, offsets.y },
            { 0, 0, 1 }
        } };

        *this *= translation;
    }

    void translate(const Vector2& offsets) {
        Matrix3 translation = { {
            { 1, 0, offsets.x },
            { 0, 1, offsets.y },
            { 0, 0, 1}
        } };

        *this *= translation;
    }

    void scale(float s) {
        Matrix3 scale = { {
            {s, 0, 0},
            {0, s, 0},
            {0, 0, 1}
        } };

        *this *= scale;
    }
};
