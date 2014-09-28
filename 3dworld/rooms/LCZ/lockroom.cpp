#include "../room.h"
#include "lockroom.h"

RMesh* lockroom::baseRMesh = nullptr;

void lockroom::setBase(RMesh* inRme) {
	if (lockroom::baseRMesh==nullptr) {
		lockroom::baseRMesh = inRme;
	}
}

lockroom* lockroom::createNew(irr::core::vector3df inPosition,char inAngle) {
	lockroom* retRoom = new lockroom;

	retRoom->node = room::getNewNode(lockroom::baseRMesh->mesh); retRoom->node->setVisible(true);
	retRoom->getSelector(lockroom::baseRMesh->mesh);
	retRoom->node->setPosition(inPosition);
	retRoom->node->setRotation(irr::core::vector3df(0,inAngle*90.f,0));
	retRoom->angle = inAngle;

	//Add the Bullet rigid body
	retRoom->node->updateAbsolutePosition();
	irr::core::vector3df irrPos = retRoom->node->getAbsolutePosition();
	btVector3 btPos(irrPos.X, irrPos.Y, irrPos.Z);
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btPos);
	btQuaternion btRot;
	irr::core::vector3df irrRot = retRoom->node->getRotation();
	btRot.setEulerZYX(irrRot.Z*irr::core::DEGTORAD,irrRot.Y*irr::core::DEGTORAD,irrRot.X*irr::core::DEGTORAD);
	Transform.setRotation(btRot);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

	btVector3 localInertia;
	lockroom::baseRMesh->shape->calculateLocalInertia(0.0, localInertia);

	retRoom->rbody = new btRigidBody(0.0, MotionState, lockroom::baseRMesh->shape, localInertia);
	room::dynamics->sharedRegisterRBody(retRoom->node,retRoom->rbody,0.f);

	retRoom->rbody->setFriction(1.f);
	retRoom->rbody->setRollingFriction(1.f);
	return retRoom;
}

const std::vector<irr::video::SLight>& lockroom::getPointLights() {
	return lockroom::baseRMesh->pointlights;
}
