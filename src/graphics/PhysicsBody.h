#pragma once

#include <algorithm>

#include "../math/vectors.h"
#include "../misc/utils.h"
#include "SceneObject.h"

constexpr float DEFAULT_TERM_LIN_VEL = 1e-3f;
constexpr float DEFAULT_TERM_ANG_VEL = 1e-2f;

struct KinematicProperties {
	float forwardVelocity;
	float angularVelocity;
	float linearAcceleration;
	float angularAcceleration;
	float angularDrag;
	float linearDrag;
	float terminalLinearVelocity;
	float terminalAngularVelocity;

	KinematicProperties(float forwardVelocity = 0, float angularVelocity = 0,
		float linearAcceleration = 0, float angularAcceleration = 0,
		float linearDrag = 0, float angularDrag = 0,
		float terminalLinearVelocity = DEFAULT_TERM_LIN_VEL, float terminalAngularVelocity = DEFAULT_TERM_ANG_VEL)
		: forwardVelocity(forwardVelocity), angularVelocity(angularVelocity),
		linearAcceleration(linearAcceleration), angularAcceleration(angularAcceleration),
		linearDrag(linearDrag), angularDrag(angularDrag),
		terminalLinearVelocity(terminalLinearVelocity), terminalAngularVelocity(terminalAngularVelocity) { }

	void kinematicsUpdate();
};

class PhysicsBody: public Component {
public:
	KinematicProperties kinematics;

	PhysicsBody(SceneObject* obj)
		: Component(obj), kinematics() { }


	PhysicsBody(SceneObject* obj, KinematicProperties kinematics)
		: Component(obj), kinematics(kinematics) { }

	void update();
};