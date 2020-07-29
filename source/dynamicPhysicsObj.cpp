#include "dynamicPhysicsObj.h"

DynamicPhysicsObj::DynamicPhysicsObj(){
	PhysicsObj();
	this->velocity=Vector3D(0.0,0.0,0.0);
	this->acceleration=Vector3D(0.0,0.0,0.0);
	this->angularVelocity=Vector3D(0.0,0.0,0.0);
}

DynamicPhysicsObj::DynamicPhysicsObj(Vector3D position, Vector3D rotation, Collider collider){
	PhysicsObj(position,rotation,collider);
	this->velocity=Vector3D(0.0,0.0,0.0);
	this->acceleration=Vector3D(0.0,0.0,0.0);
	this->angularVelocity=Vector3D(0.0,0.0,0.0);
}

DynamicPhysicsObj::DynamicPhysicsObj(Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D rotation, Vector3D angularVelocity, Collider collider){
	PhysicsObj(position,rotation,collider);
	this->velocity=velocity;
	this->acceleration=acceleration;
	this->angularVelocity=angularVelocity;
}

void DynamicPhysicsObj::update(PhysicsObj* collisionList,long collisionListSize,long currentNum,double deltaT){
	//update all the values;
	velocity=velocity+acceleration.scale(deltaT);
	position=position+velocity.scale(deltaT);
	rotation=rotation+angularVelocity.scale(deltaT);
	if(!velocity.isZero() || !angularVelocity.isZero()){
		//check for collision
		for(long i=0;i<collisionListSize;i++){
			if(i!=currentNum){
				if(checkCollision(collisionList[i].getCollider(),collisionList[i].getPosition(),collisionList[i].getRotation())!=0){
					//a collision has occured
				}
			}
		}
	}
}

CollisionType DynamicPhysicsObj::uponCollision() {
	CollisionType stop;
	return stop;
}