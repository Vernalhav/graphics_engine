#pragma once

#include <ostream>
#include "../misc/utils.h"

struct Vector2 {
    float x, y;

    Vector2(float x, float y) : x(x), y(y) { }
    Vector2() : x(0), y(0) { }

    Vector2 operator+(const Vector2& other) {
        return { x + other.x, y + other.y };
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 operator*(const float scale) {
        return { x * scale, y * scale };
    }

    Vector2& operator*=(const float scale) {
        x *= scale;
        y *= scale;
        return *this;
    }
};

struct Vector3 {
    float x, y, z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
    Vector3(float x, float y) : x(x), y(y), z(0) { }
    Vector3(Vector2 other) : Vector3(other.x, other.y) { }
    Vector3(float x) : x(x), y(0), z(1) { }
    Vector3() : x(0), y(0), z(1) { }
    
    static Vector3 interpolate(float t, const Vector3& a, const Vector3& b) {
        return { utils::interpolate(t, a.x, b.x), utils::interpolate(t, a.y, b.y), utils::interpolate(t, a.z, b.z) };
    }

    Vector3 operator+(const Vector3& other) {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 operator*(const float scale) {
        return { x * scale, y * scale, z * scale };
    }

    Vector3 operator/(const float scale) {
        return { x / scale, y / scale, z / scale };
    }

    Vector3& operator*=(const float scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }
    
    Vector3& operator/=(const float scale) {
        x /= scale;
        y /= scale;
        z /= scale;
        return *this;
    }
};

struct Vector4 {
    float x, y, z, w;

    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
    Vector4(float x, float y, float z) : x(x), y(y), z(z), w(1) { }
    Vector4() : x(0), y(0), z(0), w(1) { }

    Vector4 operator+(const Vector4& other) {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4 operator*(const float scale) {
        return { x * scale, y * scale, z * scale, w * scale };
    }

    Vector4& operator*=(const float scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
        return *this;
    }
};

static std::ostream& operator<<(std::ostream& out, Vector2 const& data) {
    out << "(" << data.x << ", " << data.y << ")";
    return out;
}

static std::ostream& operator<<(std::ostream& out, Vector3 const& data) {
    out << "(" << data.x << ", " << data.y << ", " << data.z << ")";
    return out;
}

static std::ostream& operator<<(std::ostream& out, Vector4 const& data) {
    out << "(" << data.x << ", " << data.y << ", " << data.z << ", " << data.w << ")";
    return out;
}