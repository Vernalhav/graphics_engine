#include <random>

#include "object.h"
#include "Cloud.h"
#include "Helicopter.h"
#include "Plane.h"
#include "Sun.h"
#include "../engine/PhysicsBody.h"
#include "../misc/utils.h"

#define DEFAULT_PRIMITIVE_Z 1


SceneObject* object::getHelicopter(const std::string& name, const glm::vec3& bodyColor, const glm::vec3& propellerColor) {

    SceneObject* propeller = new SceneObject("propeller", getPropeller(propellerColor));
    SceneObject* smallPropeller = new SceneObject("small_propeller", getPropeller(propellerColor));
    SceneObject* body = new SceneObject(name + "_body", getHelicopterBody(bodyColor));

    smallPropeller->transform.translation.x = -1.72f;
    smallPropeller->transform.scale = glm::vec3(0.3f);

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

SceneObject* object::getDrone(const std::string& name, const glm::vec3& bodyColor) {
    
    Primitive body = { getPolygon(4, PI / 4, {0, 0, 0}, {0.5f, 0.5f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive arm1 = { getPolygon(4, 0, {0, 0, 0}, {1.3f, 0.2f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive arm2 = { getPolygon(4, 0, {0, 0, 0}, {0.2f, 1.3f}), GL_TRIANGLE_FAN, Color::LIGHT_GRAY };

    SceneObject* drone = new SceneObject(name, { body, arm1, arm2 });

    float propellerRadius = 1;
    float stepAngle = (float)PI / 2;

    for (int i = 1; i <= 4; i++) {
        SceneObject* prop = new SceneObject(name + "_prop_" + std::to_string(i), getPropeller(Color::LIGHT_GRAY, 0.1f, 3));
        prop->transform.scale = glm::vec3(0.5f);
        prop->addComponent<PhysicsBody>(KinematicProperties(0, PI));
        prop->transform.translation = { propellerRadius * cos(i * stepAngle), propellerRadius * sin(i * stepAngle), 0 };

        drone->appendChild(prop);
    }

    drone->transform.rotation.z = PI / 4;
    drone->transform.scale = glm::vec3(0.1f);

    SceneObject* dronePivot = new SceneObject("drone_pivot");
    drone->addComponent<PhysicsBody>();
    drone->transform.translation.y = 0.8f;
    dronePivot->appendChild(drone);

    float angularVelocity = PI / 2;
    dronePivot->addComponent<PhysicsBody>(KinematicProperties(0, angularVelocity));

    return dronePivot;
}

SceneObject* object::getCloud(const std::string name, glm::vec2 origin) {
    
    size_t seed = std::hash<std::string>{}(name);

    std::default_random_engine generator(seed);
    std::normal_distribution<float> distribXCoord(0.8f, 0.6f);
    std::normal_distribution<float> distribYCoord(0.4f, 0.2f);

    const int numSubClouds = 8;

    std::vector<Primitive> cloudPrims;
    std::vector<glm::vec3> originCloud = getPolygon(32, 0, { 0, 0, 0 }, { utils::randRange(0.6f, 0.8f), 1 });

    cloudPrims.push_back(Primitive(originCloud, GL_TRIANGLE_FAN, Color::WHITE));

    for (int i = 0; i < numSubClouds-1; i++) {
        float curX = distribXCoord(generator);
        float curY = distribYCoord(generator);

        std::vector<glm::vec3> curSubCloud = getPolygon(32, 0, { curX, curY, 0 },
            { utils::randRange(0.8f, 1.2f), 1 });
        
        cloudPrims.push_back(Primitive(curSubCloud, GL_TRIANGLE_FAN, Color::WHITE));
    }

    SceneObject* cloud = new SceneObject(name, cloudPrims);

    cloud->transform.scale = glm::vec3(0.1f);
    cloud->transform.translation = { origin, 0 };

    float terminalVelocity = 3.0f;

    cloud->addComponent<PhysicsBody>(KinematicProperties(utils::randRange(0.3f, 0.9f), 
        0, 0, 0, 0, 0, terminalVelocity));

    cloud->addComponent<Cloud>();

    return cloud;
}

SceneObject* object::getPlane(const std::string& name) {
    glm::vec3 A = {1, 0, DEFAULT_PRIMITIVE_Z};
    glm::vec3 B = {0.2f, -1, DEFAULT_PRIMITIVE_Z};
    glm::vec3 C = {0.4f, -0.2f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 D = {-0.4f, -0.13f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 E = {-1, -0.4f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 F = {-0.7f, 0, DEFAULT_PRIMITIVE_Z};
    glm::vec3 G = {-1, 0.4f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 H = {-0.4f, 0.12f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 I = {0.4f, 0.2f, DEFAULT_PRIMITIVE_Z};
    glm::vec3 J = {0.2f, 1, DEFAULT_PRIMITIVE_Z};
    glm::vec3 K = {1.3f, 0, DEFAULT_PRIMITIVE_Z};

    Primitive front = { {A, J, I, C, B}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive middle = { {I, H, D, C}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive back = { {F, G, H, D, E}, GL_TRIANGLE_FAN, Color::LIGHT_GRAY };
    Primitive head = { {K, I, C}, GL_TRIANGLES, Color::LIGHT_GRAY };

    SceneObject* plane = new SceneObject(name, { head, front, middle, back });
    plane->addComponent<PhysicsBody>(KinematicProperties(1));
    plane->addComponent<Plane>();

    return plane;
}

SceneObject* object::getSun(const std::string& name) {
    
    Primitive innerCircle = { getPolygon(32), GL_TRIANGLE_FAN, {255, 127, 0} };
    Primitive crown = { getCrown(16, 1.2f, 1.6f), GL_TRIANGLE_FAN, {255, 255, 0} };

    SceneObject* sun = new SceneObject(name, { innerCircle, crown });
    
    sun->transform.scale = glm::vec3(0.2f);
    sun->transform.translation = { 0.5f, 0.5f, 0 };
    sun->addComponent<PhysicsBody>(KinematicProperties(0, PI / 4));
    sun->addComponent<Sun>(glm::vec3(255, 255, 0), glm::vec3(255, 180, 0));

    return sun;
}

std::vector<glm::vec3> object::getCrown(int nSpikes, float innerRadius, float outerRadius) {
    std::vector<glm::vec3> vertices = { {0, 0, DEFAULT_PRIMITIVE_Z} };

    float angleStep = 2 * PI / nSpikes;
    for (int i = 0; i < nSpikes; i++) {
        vertices.push_back({ innerRadius * cos(i * angleStep), innerRadius * sin(i * angleStep), DEFAULT_PRIMITIVE_Z });
        vertices.push_back({ outerRadius * cos((i + 0.5f) * angleStep), outerRadius * sin((i + 0.5f) * angleStep), DEFAULT_PRIMITIVE_Z });
    }

    vertices.push_back({ innerRadius * cos(0.0f), innerRadius * sin(0.0f), DEFAULT_PRIMITIVE_Z });

    return vertices;
}

std::vector<Primitive> object::getHelicopterBody(glm::vec3 color) {
    Primitive cockpit(getPolygon(4, PI / 4, { 0, 0, 0 }, { 0.5f, 0.3f }), GL_TRIANGLE_FAN, color);
    Primitive topGlass(getPolygon(3, 0, { 0.44f, 0, 0 }, { 0.175f, 0.25f }), GL_TRIANGLE_FAN, color);
    Primitive tail(getPolygon(4, PI / 4, { -1, 0, 0 }, { 1, 0.05f }), GL_TRIANGLE_FAN, color);

    return { cockpit, topGlass, tail };
}

std::vector<Primitive> object::getPropeller(glm::vec3 color, float width, int nPropellers) {
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

std::vector<glm::vec3> object::getPolygon(int n, float rotation, glm::vec3 offset, glm::vec2 scale) {
    std::vector<glm::vec3> polygon(n);

    float angleStep = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        polygon[i].x = scale.x * cos(angleStep * i + rotation) + offset.x;
        polygon[i].y = scale.y * sin(angleStep * i + rotation) + offset.y;
        polygon[i].z = DEFAULT_PRIMITIVE_Z;
    }

    return polygon;
}

std::vector<glm::vec3> object::getRectangle(float width, float length, float rotation) {
    std::vector<glm::vec3> rectangle(4);

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
