#include "collider.h"
Collider::Collider(){
	type=ColliderType::none;
}
Collider::~Collider(){

}
Collider::Collider(ColliderType ct){
	type=ct;
}
ColliderType Collider::getColliderType(){
	return type;
}
int Collider::checkCollision(Vector3D* a,Vector3D* b,Collider* c,Vector3D* d,Vector3D* e){
	return 0;
}

//returns a point on the line of the two plains provide a normal and point for each plane
//user must perform cross product to get a vector in direction of intersection line
//user must check and handle the paralell plane and same plane cases
//Matrix:
//[ Nax Nay Naz | Pa*Na]
//[ Nbx Nby Nbz | Pb*Nb]
Vector3D Collider::collideTwoPlanes(Vector3D normalA,Vector3D pointA,Vector3D normalB,Vector3D pointB){
	Vector3D output=Vector3D();
	double matrix[2][4];
	matrix[0][0]=normalA.x;
	matrix[0][1]=normalA.y;
	matrix[0][2]=normalA.z;
	matrix[0][3]=V3Ddot(normalA,pointA);
	matrix[1][0]=normalB.x;
	matrix[1][1]=normalB.y;
	matrix[1][2]=normalB.z;
	matrix[1][3]=V3Ddot(normalB,pointB);
	//start solving the matrix
	if(matrix[0][0]==0){
		if(matrix[1][0]==0){
			if(matrix[0][1]==0){
				if(matrix[1][1]==0){
					//[ 0 0 ? ?]
					//[ 0 0 ? ?]
					//have reached a case the user has to check for
					//the planes are parallel
					return output;
				}else{
					//[ 0 0 _ ?]
					//[ 0 _ ? ?]
					output.x=0.0;
					output.z=matrix[0][3]/matrix[0][2];
					output.y=(matrix[1][2]==0)?(matrix[1][3]/matrix[1][2]):((matrix[1][3]-(matrix[1][2]*output.z))/matrix[1][1]);
				}
			}else{
				//[ 0 _ ? ?]
				//[ 0 ? ? ?]
				if(matrix[1][1]==0){
					//[ 0 _ ? ?]
					//[ 0 0 ? ?]
					output.z=pointB.z;
					output.y=(matrix[0][3]-(matrix[0][2]*output.z))/matrix[0][1];
					output.x=0.0;
				}else{
					//[ 0 _ ? ?]
					//[ 0 _ ? ?]
					if(matrix[0][2]==0){
						//[ 0 _ 0 ?]
						//[ 0 _ ? ?]
						output.y=pointA.y;
						output.x=0.0;
						output.z=(matrix[1][2]==0)?(output.z=0.0):((matrix[1][3]-(matrix[1][2]*output.y))/matrix[1][2]);
					}else{
						if(matrix[1][2]==0){
							//[ 0 _ _ ?]
							//[ 0 _ 0 ?]
							output.x=0.0;
							output.y=matrix[1][3]/matrix[1][1];
							output.z=(matrix[0][3]-(matrix[0][1]*output.y))/matrix[0][2];
						}else{
							//[ 0 _ _ ?]
							//[ 0 _ _ ?]
							output.x=0.0;
							matrix[0][2]==matrix[0][2]/matrix[0][1];
							matrix[0][3]==matrix[0][3]/matrix[0][1];
							matrix[0][1]=1.0;
							matrix[1][2]=matrix[1][2]-(matrix[0][2]*matrix[1][1]);
							matrix[1][3]=matrix[1][3]-(matrix[0][3]*matrix[1][1]);
							matrix[1][1]=0.0;
							//[ 0 1 _ ?]
							//[ 0 0 _ ?]
							output.z=matrix[1][3]/matrix[1][2];
							output.y=matrix[0][3]-(matrix[0][2]*output.z);
							
						}
					}
				}
			}
		}else{
			if(matrix[0][1]==0){
				//[ 0 0 _ ?] (0,0,0) is not a normal
				//[ _ ? ? ?]
				output.z=pointA.z;
				//solve for the other values
				output.y=0.0;
				output.x=(matrix[1][3]-(matrix[1][2]*output.z))/matrix[1][0];
			}else{
				//[ 0 _ _ ?]
				//[ _ ? ? ?]
				if(matrix[1][1]==0){
					//[ 0 _ _ ?]
					//[ _ 0 ? ?]
					if(matrix[1][2]==0){
						//[ 0 _ _ ?]
						//[ _ 0 0 ?]
						output.x=matrix[1][3]/matrix[1][0];
						output.y=0.0;
						output.z=matrix[0][3]/matrix[0][2];
					}else{
						//[ 0 _ _ ?]
						//[ _ 0 _ ?]
						output.z=0.0;
						output.y=matrix[0][3]/matrix[0][1];
						output.x=matrix[1][3]/matrix[1][0];
					}
				}else{
					//[ 0 _ _ ?]
					//[ _ _ ? ?]
					if(matrix[1][2]==0){
						//[ 0 _ _ ?]
						//[ _ _ 0 ?]
						output.y=0.0;
						output.x=matrix[1][3]/matrix[1][0];
						output.z=matrix[1][2]/matrix[1][2];
						
					}else{
						//[ 0 _ _ ?]
						//[ _ _ _ ?]
						matrix[0][2]=matrix[0][2]/matrix[0][1];
						matrix[0][3]=matrix[0][3]/matrix[0][1];
						matrix[0][1]=1.0;
						matrix[1][2]=matrix[1][2]-(matrix[0][1]*matrix[1][1]);
						matrix[1][3]=matrix[1][3]-(matrix[0][1]*matrix[1][1]);
						matrix[1][1]=0.0;
						//[ 0 1 _ ?]
						//[ _ 0 _ ?]
						output.x=matrix[1][3]/matrix[1][0];
						output.y=matrix[0][3];
						output.z=0.0;
						
					}
				}
			}
		}
	}else{
		//[ _ ? ? ?]
		//[ ? ? ? ?]
		if(matrix[1][0]==0){
			//[ _ ? ? ?]
			//[ 0 ? ? ?]
			if(matrix[1][1]==0){
				//[ _ ? ? ?]
				//[ 0 0 _ ?]
				output.z=matrix[1][3]/matrix[1][2];
			}else{
				//[ _ ? ? ?]
				//[ 0 _ ? ?]
				if(matrix[0][1]==0){
					//[ _ 0 ? ?]
					//[ 0 _ ? ?]
					output.x=matrix[0][3]/matrix[0][0];
					output.y=matrix[1][3]/matrix[1][1];
					output.z=0.0;
				}else{
					//[ _ _ ? ?]
					//[ 0 _ ? ?]
					output.z=0.0;
					output.y=matrix[1][3]/matrix[1][1];
					output.x=(matrix[0][3]-(matrix[0][1]*output.y))/matrix[0][0];
				}
			}
		}else{
			//[ _ ? ? ?]
			//[ _ ? ? ?]
			if(matrix[0][1]==0){
				//[ _ 0 ? ?]
				//[ _ ? ? ?]
				if(matrix[1][1]==0){
					//[ _ 0 ? ?]
					//[ _ 0 ? ?]
					if(matrix[0][2]==0){
						//[ _ 0 0 ?]
						//[ _ 0 ? ?]
						if(matrix[1][2]==0){
							//[ _ 0 0 ?]
							//[ _ 0 0 ?]
							//paralell planes
						}else{
							//[ _ 0 0 ?]
							//[ _ 0 _ ?]
							output.x=matrix[0][3]/matrix[0][0];
							output.y=0.0;
							output.z=(matrix[1][3]-(matrix[1][0]*output.x))/matrix[1][3];
						}
					}else{
						//[ _ 0 _ ?]
						//[ _ 0 ? ?]
						if(matrix[1][2]==0){
							//[ _ 0 _ ?]
							//[ _ 0 0 ?]
							output.x=matrix[1][3]/matrix[1][0];
							output.y=0.0;
							output.z=(matrix[0][3]-(matrix[0][0]*output.x))/matrix[0][3];
						}else{
							//[ _ 0 _ ?]
							//[ _ 0 _ ?]
							matrix[0][2]=matrix[0][2]/matrix[0][0];
							matrix[0][3]=matrix[0][3]/matrix[0][0];
							matrix[0][0]=1;
							matrix[1][2]=matrix[1][2]-(matrix[0][2]*matrix[1][0]);
							matrix[1][3]=matrix[1][3]-(matrix[0][3]*matrix[1][0]);
							matrix[1][0]=0;
							//[ 1 0 _ ?]
							//[ 0 0 _ ?]
							output.y=0.0;
							output.z=matrix[1][3]/matrix[1][2];
							output.x=matrix[0][3]-(matrix[0][2]*output.z);
						}
					}
				}else{
					//[ _ 0 ? ?]
					//[ _ _ ? ?]
					output.z=0.0;
					output.x=matrix[0][3]/matrix[0][0];
					output.y=(matrix[1][3]-(matrix[1][0]*output.x))/matrix[1][0];
				}
			}else{
				//[ _ _ ? ?]
				//[ _ ? ? ?]
				if(matrix[1][1]==0){
					//[ _ _ ? ?]
					//[ _ 0 ? ?]
					output.z=0.0;
					output.x=matrix[1][3]/matrix[1][0];
					output.y=(matrix[0][3]-(matrix[0][0]*output.x))/matrix[0][0];
				}else{
					//[ _ _ ? ?]
					//[ _ _ ? ?]
					matrix[0][1]=matrix[0][1]/matrix[0][0];
					matrix[0][2]=matrix[0][2]/matrix[0][0];
					matrix[0][3]=matrix[0][3]/matrix[0][0];
					matrix[0][0]=1;
					//[ 1 _ ? ?]
					//[ _ _ ? ?]
					matrix[1][1]=matrix[1][1]-(matrix[0][1]*matrix[1][0]);
					matrix[1][2]=matrix[1][2]-(matrix[0][2]*matrix[1][0]);
					matrix[1][3]=matrix[1][3]-(matrix[0][3]*matrix[1][0]);
					matrix[1][0]=0;
					//[ 1 _ ? ?]
					//[ 0 _ ? ?]
					output.z=0.0;
					output.y=matrix[1][3]/matrix[1][1];
					output.x=matrix[0][3]-(matrix[0][1]*output.y);
				}
			}
		}
	}
	return output;
}
