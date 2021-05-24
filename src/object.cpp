#include "object.h"
#include "utils.h"


SceneObject* object::getHelicopter(float scale) {

    SceneObject* propeller = new SceneObject("propeller", getPropeller(0.08f, 1, 3));
    SceneObject* body = new SceneObject("body", getHelicopterBody());

    propeller->transform.translation.z = -0.1f;
    body->transform.translation.z = 0.2f;

    body->appendChild(propeller);
    body->transform.scale = scale;
   
    propeller->physicsBody.angularVelocity = 0.005f;

    body->physicsBody.forwardVelocity= 0.0001f;
    body->physicsBody.angularVelocity= 0.0001f;

	return body;
}

std::vector<Primitive> object::getHelicopterBody() {

    float scale = 1;

    Primitive cockpit(getPolygon(4, PI / 4, { 0, 0 }, { 0.5f, 0.3f }), GL_TRIANGLE_FAN, {0, 0, 255});
    Primitive topGlass(getPolygon(3, 0, { 0.44f, 0 }, { 0.175f, 0.25f }), GL_TRIANGLE_FAN, { 255, 0, 0 });
    Primitive tail(getPolygon(4, PI / 4, { -1, 0 }, { 1, 0.05f }), GL_TRIANGLE_FAN, { 0, 255, 0 });

    return { cockpit, topGlass, tail };
}

std::vector<Primitive> object::getPropeller(float width, float length, int nPropellers) {
    std::vector<Primitive> prop;

    float stepAngle = 2 * PI / nPropellers;

    for (int i = 0; i < nPropellers; i++) {
        prop.push_back(Primitive(
            getRectangle(width, length, i * stepAngle),
            GL_TRIANGLE_FAN,
            { 255, 255, 255 }
        ));
    }

    return prop;
}

std::vector<Vector3> object::getPolygon(int n, float rotation, Vector3 offset, Vector2 scale) {
    std::vector<Vector3> polygon(n);

    float angleStep = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        polygon[i].x = scale.x * cos(angleStep * i + rotation) + offset.x;
        polygon[i].y = scale.y * sin(angleStep * i + rotation) + offset.y;
        polygon[i].z = 0;
    }

    return polygon;
}

std::vector<Vector3> object::getRectangle(float width, float length, float rotation) {
    std::vector<Vector3> rectangle(4);

    rectangle[0] = { 0.0f, width / 2, 0};
    rectangle[1] = { 0.0f, -width / 2, 0};
    rectangle[2] = { length, -width / 2, 0};
    rectangle[3] = { length, width / 2, 0};

    for (auto& vertex : rectangle) {
        float x = vertex.x, y = vertex.y;
        vertex.x = cos(rotation) * x - sin(rotation) * y;
        vertex.y = sin(rotation) * x + cos(rotation) * y;
        vertex.z = 0;
    }

    return rectangle;
}
