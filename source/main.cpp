/******************************************************************************
** File: main.cpp
** Project: 3D Collaborative Game
** Date Created: 4 July 2020
** Description: Holds the main function of the whole program
******************************************************************************/



#include "gameEngine.h"
#include <iostream>

using namespace std;

/******************************************************************************
** Function: main
** Description: This is the start of the entire program. 
** Parameters: int argc holds the number of arguments, char **argv holds the 
** string of characters that hold the arguments
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
#include "physicsTestKit.h"
using namespace std;
int main (int argc, char **argv) {
	PhysicsObj** pObjs=new PhysicsObj*[2];
	string tmp1="FallingBox";
	DynamicTestObj* fallingBox=new DynamicTestObj(tmp1,new Vector3D(0.0,3,0.0),new BoxCollider(1.0,1.0,1.0));
	string tmp2="StaticBox";
	StaticTestObj* staticBox=new StaticTestObj(tmp2,new Vector3D(0.0,0.0,0.0),new BoxCollider(2.0,2.0,2.0));
	pObjs[0]=fallingBox;
	pObjs[1]=staticBox;
	for(int i=0;i<20;i++){
		cout<<endl<<endl;
		fallingBox->update(pObjs,2,0,0.02);
		fallingBox->dumpInfo();
		staticBox->dumpInfo();
		
	}
	delete fallingBox;
	delete staticBox;
	string finalTemp;
	cin>>finalTemp;

	return 0;
}
