#pragma once

#include <cstdlib>
#include <vector>
#include "vectors.h"

#define PI 3.14159265359f
#define DEG2RAD (PI / 180)


float randRange(float a, float b) {
    return (rand() / (float)RAND_MAX) * (b - a) + a;
}


int randRangeInt(int a, int b) {
    return rand() % (b - a + 1) + a;
}

std::vector<Vector3> getPolygon(int n, float radius = 1.0, float rotation = 0.0, Vector3 offset = { 0, 0, 0 }) {
    std::vector<Vector3> polygon(n);

    float angleStep = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        polygon[i].x = radius * cos(angleStep * i + rotation) + offset.x;
        polygon[i].y = radius * sin(angleStep * i + rotation) + offset.y;
        polygon[i].z = offset.z;
    }

    return polygon;
}

std::vector<Vector3> getRectangle(float width, float length, float rotation, float height = 1) {
    std::vector<Vector3> rectangle(4);

    rectangle[0] = { 0.0f, width / 2, height };
    rectangle[1] = { 0.0f, -width / 2, height };
    rectangle[2] = { length, -width / 2, height };
    rectangle[3] = { length, width / 2, height };

    for (auto& vertex : rectangle) {
        float x = vertex.x, y = vertex.y;
        vertex.x = cos(rotation) * x - sin(rotation) * y;
        vertex.y = sin(rotation) * x + cos(rotation) * y;
        vertex.z = height;
    }

    return rectangle;
}
