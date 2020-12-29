#ifndef STATIC_PHYSICS_OBJ_H
#define STATIC_PHYSICS_OBJ_H

#include "globalPhysics.h"
#include "physicsObj.h"
class StaticPhysicsObj: public PhysicsObj{
	public:
	StaticPhysicsObj();
	virtual ~StaticPhysicsObj();
	StaticPhysicsObj(Vector3D* pos,Vector3D* rot,Collider* col);
	virtual CollisionType uponCollision();
};
#endif