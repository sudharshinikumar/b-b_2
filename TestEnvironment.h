#ifndef OSGVE_TESTENVIRONMENT
#define OSGVE_TESTENVIRONMENT

#include <osgVirtualEnvironment/VirtualEnvironment.h>
#include <osgVirtualEnvironment/VirtualObject.h>
#include "BodyCredential.h"
#include "BodyHandler.h"
#include "TrackedSphere.h"
#include "Cube.h"
#include "make\MSVC 100\Brick.h"
class TestEnvironment : public osgve::VirtualEnvironment
{
	public:
		TestEnvironment();
Brick *brick1;
Brick *brick2;
Brick *brick3;
Brick *brick4;
Brick *brick5;
Brick *brick6;
Brick *brick7;
Brick *brick8;
Brick *brick9;
Brick *brick10;
Brick *brick11;
Brick *brick12;
Brick *brick13;
Brick *brick14;
Brick *brick15;
Brick *brick16;
Brick *brick17;
Brick *brick18;
Brick *brick19;
Brick *brick20;
Brick *brick[20];
	Cube *roofCube;
        Cube *leftCube;
        Cube *rightCube;
        Cube *backCube;
        Cube *floorCube;
		osg::Group* objectGroup;
	protected:
		virtual const char* getName() const { return "Test Environment"; }
		virtual void create();
		virtual void setup();
		virtual void update();


	private:
		
		
		void normalCallback();
		void swapCallback();
		void leftCallback();
		void rightCallback();
		
		//TrackedSphere* leftHand;
	    TrackedSphere* paddle;
		void testCallback();
};


#endif