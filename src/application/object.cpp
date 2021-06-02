#include <random>

#include "object.h"
#include "Cloud.h"
#include "Helicopter.h"
#include "Plane.h"
#include "../engine/PhysicsBody.h"
#include "../misc/utils.h"

#define DEFAULT_PRIMITIVE_Z 1


SceneObject* object::getHelicopter(const std::string& name, const Vector3& bodyColor, const Vector3& propellerColor) {

    SceneObject* propeller = new SceneObject("propeller", getPropeller(propellerColor));
    SceneObject* smallPropeller = new SceneObject("small_propeller", getPropeller(propellerColor));
    SceneObject* body = new SceneObject(name + "_body", getHelicopterBody(bodyColor));

    smallPropeller->transform.translation.x = -1.72f;
    smallPropeller->transform.scale = 0.3f;

    float LIN_DRAG = 1e-3f;
    float ANG_DRAG = 1e-2f;
    float LIN_TERM = 0.9f;
    float ANG_TERM = 2 * PI;

    float PROPELLER_ANG_VELOCITY = 4 * PI;

    body->appendChild(propeller);
    body->appendChild(smallPropeller);
    body->addComponent<PhysicsBody>(KinematicProperties(0, 0, 0, 0, LIN_DRAG, ANG_DRAG, LIN_TERM, ANG_TERM));
   
    smallPropeller->addComponent<PhysicsBody>(KinematicProperties(0.0f, PROPELLER_ANG_VELOCITY));
    propeller->addComponent<PhysicsBody>(KinematicProperties(0.0f, PROPELLER_ANG_VELOCITY));

    body->addComponent<Helicopter>();
	return body;
}

SceneObject* object::getDrone(const std::string& name, const Vector3& bodyColor) {
    
    Primitive body = { getPolygon(4, PI / 4, {0, 0, 0}, {0.5f, 0.5f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive arm1 = { getPolygon(4, 0, {0, 0, 0}, {1.3f, 0.2f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive arm2 = { getPolygon(4, 0, {0, 0, 0}, {0.2f, 1.3f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };

    SceneObject* drone = new SceneObject(name, { body, arm1, arm2 });

    float propellerRadius = 1;
    float stepAngle = (float)PI / 2;

    for (int i = 1; i <= 4; i++) {
        SceneObject* prop = new SceneObject(name + "_prop_" + std::to_string(i), getPropeller(Color::LIGHT_GRAY, 0.1f, 3));
        prop->transform.scale = 0.5f;
        prop->addComponent<PhysicsBody>(KinematicProperties(0, PI));
        prop->transform.translation = { propellerRadius * cos(i * stepAngle), propellerRadius * sin(i * stepAngle) };

        drone->appendChild(prop);
    }

    drone->transform.rotation = PI / 4;
    drone->transform.scale = 0.1f;

    SceneObject* dronePivot = new SceneObject("drone_pivot");
    drone->addComponent<PhysicsBody>();
    drone->transform.translation.y = 0.8f;
    dronePivot->appendChild(drone);

    float angularVelocity = PI / 2;
    dronePivot->addComponent<PhysicsBody>(KinematicProperties(0, angularVelocity));

    return dronePivot;
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

SceneObject* object::getCloud(const std::string name, Vector2 origin) {
    
    size_t seed = std::hash<std::string>{}(name);

    std::default_random_engine generator(seed);
    std::normal_distribution<float> distribXCoord(0.8f, 0.6f);
    std::normal_distribution<float> distribYCoord(0.4f, 0.2f);

    const int numSubClouds = 8;

    std::vector<Primitive> cloudPrims;
    std::vector<Vector3> originCloud = getPolygon(32, 0, { 0, 0, 0 }, { utils::randRange(0.6f, 0.8f), 1 });

    cloudPrims.push_back(Primitive(originCloud, GL_TRIANGLE_FAN, Color::WHITE));

    for (int i = 0; i < numSubClouds-1; i++) {
        float curX = distribXCoord(generator);
        float curY = distribYCoord(generator);

        std::vector<Vector3> curSubCloud = getPolygon(32, 0, { curX, curY, 0 },
            { utils::randRange(0.8f, 1.2f), 1 });
        
        cloudPrims.push_back(Primitive(curSubCloud, GL_TRIANGLE_FAN, Color::WHITE));
    }

    SceneObject* cloud = new SceneObject(name, cloudPrims);

    cloud->transform.scale = 0.1f;
    cloud->transform.translation = origin;

    float terminalVelocity = 3.0f;

    cloud->addComponent<PhysicsBody>(KinematicProperties(utils::randRange(0.3f, 0.9f), 
        0, 0, 0, 0, 0, terminalVelocity));

    cloud->addComponent<Cloud>();

    return cloud;
}

SceneObject* object::getPlane(const std::string& name) {
    Vector3 A = {1, 0, DEFAULT_PRIMITIVE_Z};
    Vector3 B = {0.2f, -1, DEFAULT_PRIMITIVE_Z};
    Vector3 C = {0.4f, -0.2f, DEFAULT_PRIMITIVE_Z};
    Vector3 D = {-0.4f, -0.13f, DEFAULT_PRIMITIVE_Z};
    Vector3 E = {-1, -0.4f, DEFAULT_PRIMITIVE_Z};
    Vector3 F = {-0.7f, 0, DEFAULT_PRIMITIVE_Z};
    Vector3 G = {-1, 0.4f, DEFAULT_PRIMITIVE_Z};
    Vector3 H = {-0.4f, 0.12f, DEFAULT_PRIMITIVE_Z};
    Vector3 I = {0.4f, 0.2f, DEFAULT_PRIMITIVE_Z};
    Vector3 J = {0.2f, 1, DEFAULT_PRIMITIVE_Z};
    Vector3 K = {1.3f, 0, DEFAULT_PRIMITIVE_Z};

    Primitive front = { {A, J, I, C, B}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive middle = { {I, H, D, C}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive back = { {F, G, H, D, E}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive head = { {K, I, C}, GL_TRIANGLES, Color::LIGHT_GRAY };

    SceneObject* plane = new SceneObject(name, { head, front, middle, back });
    plane->addComponent<PhysicsBody>(KinematicProperties(1));
    plane->addComponent<Plane>();

    return plane;
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
