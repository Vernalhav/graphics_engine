#include "object.h"
#include "graphics/PhysicsBody.h"
#include "misc/utils.h"
#include "application/Cloud.h"

#define DEFAULT_PRIMITIVE_Z 1


SceneObject* object::getHelicopter(const std::string& name, const Vector3& bodyColor, const Vector3& propellerColor) {

    SceneObject* propeller = new SceneObject("propeller", getPropeller(propellerColor));
    SceneObject* smallPropeller = new SceneObject("small_propeller", getPropeller(propellerColor));
    SceneObject* body = new SceneObject(name + "_body", getHelicopterBody(bodyColor));

    smallPropeller->transform.translation.x = -1.72f;
    smallPropeller->transform.scale = 0.3f;

    float LIN_DRAG = 0.25f;
    float ANG_DRAG = PI / 4;
    float LIN_TERM = 0.9f;
    float ANG_TERM = 2 * PI;

    float PROPELLER_ANG_VELOCITY = 4 * PI;

    body->appendChild(propeller);
    body->appendChild(smallPropeller);
    body->addComponent<PhysicsBody>(KinematicProperties(0, 0, 0, 0, LIN_DRAG, ANG_DRAG, LIN_TERM, ANG_TERM));
   
    smallPropeller->addComponent<PhysicsBody>(KinematicProperties(0.0f, PROPELLER_ANG_VELOCITY));
    propeller->addComponent<PhysicsBody>(KinematicProperties(0.0f, PROPELLER_ANG_VELOCITY));

	return body;
}

SceneObject* object::getSpinner() {
    SceneObject* prop1 = new SceneObject("p1", getPropeller());
    SceneObject* prop2 = new SceneObject("p2", getPropeller({ 0, 255, 0 }, 0.1f, 3));
    SceneObject* prop3 = new SceneObject("p2", getPropeller());
    SceneObject* shaft = new SceneObject("shaft", { { getPolygon(4, PI / 4, {0,0,0}, {0.7f, 0.05f}), GL_TRIANGLE_FAN, {255, 255, 255} } });

    prop1->transform.translation.x = 0.5f;
    prop2->transform.translation.x = -0.5f;
    prop3->transform.translation.x = 1;
    prop1->transform.scale = 0.5;
    prop2->transform.scale = 0.5;
    prop3->transform.scale = 0.5;

    shaft->addComponent<PhysicsBody>(KinematicProperties(0.0f, 0.001f));
    prop1->addComponent<PhysicsBody>(KinematicProperties(0.0f, 0.001f));
    prop2->addComponent<PhysicsBody>(KinematicProperties(0.0f, 0.001f));
    prop3->addComponent<PhysicsBody>(KinematicProperties(0.0f, 0.001f));

    shaft->appendChild(prop1);
    shaft->appendChild(prop2);
    prop2->appendChild(prop3);

    return shaft;
}

SceneObject* object::getCloud(std::string name, Vector2 origin) {
    
    std::vector<Vector3> c1 = getPolygon(32, 0, { 0, 0, 0 }, { 1.1, 1 });
    std::vector<Vector3> c2 = getPolygon(32, 0, { 0.4, 0.4, 0 }, { 0.8, 1 });
    std::vector<Vector3> c3 = getPolygon(32, 0, { -0.4, 0, 0 }, { 0.8, 1 });

    std::vector<Primitive> cloudPrims = { Primitive(c1, GL_TRIANGLE_FAN, Color::WHITE),
                                          Primitive(c2, GL_TRIANGLE_FAN, Color::WHITE),
                                          Primitive(c3, GL_TRIANGLE_FAN, Color::WHITE)};

    SceneObject* cloud = new SceneObject(name, cloudPrims);

    cloud->transform.scale = 0.1;
    cloud->transform.translation = origin;
    cloud->addComponent<PhysicsBody>(KinematicProperties(utils::randRange(0.1, 2.0)));

    cloud->addComponent<Cloud>();

    return cloud;
}

std::vector<Primitive> object::getHelicopterBody(Vector3 color) {

    float scale = 1;

    Primitive cockpit(getPolygon(4, PI / 4, { 0, 0 }, { 0.5f, 0.3f }), GL_TRIANGLE_FAN, color);
    Primitive topGlass(getPolygon(3, 0, { 0.44f, 0 }, { 0.175f, 0.25f }), GL_TRIANGLE_FAN, color);
    Primitive tail(getPolygon(4, PI / 4, { -1, 0 }, { 1, 0.05f }), GL_TRIANGLE_FAN, color);

    return { cockpit, topGlass, tail };
}

std::vector<Primitive> object::getPropeller(Vector3 color, float width, int nPropellers) {
    std::vector<Primitive> prop;

    float stepAngle = 2 * PI / nPropellers;

    for (int i = 0; i < nPropellers; i++) {
        prop.push_back(Primitive(
            getRectangle(width, 1, i * stepAngle),
            GL_TRIANGLE_FAN,
            color
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
        polygon[i].z = DEFAULT_PRIMITIVE_Z;
    }

    return polygon;
}

std::vector<Vector3> object::getRectangle(float width, float length, float rotation) {
    std::vector<Vector3> rectangle(4);

    rectangle[0] = { 0.0f, width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[1] = { 0.0f, -width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[2] = { length, -width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[3] = { length, width / 2, DEFAULT_PRIMITIVE_Z};

    for (auto& vertex : rectangle) {
        float x = vertex.x, y = vertex.y;
        vertex.x = cos(rotation) * x - sin(rotation) * y;
        vertex.y = sin(rotation) * x + cos(rotation) * y;
        vertex.z = DEFAULT_PRIMITIVE_Z;
    }

    return rectangle;
}
