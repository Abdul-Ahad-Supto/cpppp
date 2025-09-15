// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// scene.cpp

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "constants.h"			// system-wide constants
#include "utility.h"			// general utility functions
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"

// #includes for geometry
#include "sweep.h"
#include "extrusion.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"
#include "terrain.h"
#include "billboard.h"
#include "plane.h"
#include "tsphere.h"
#include "cylinder.h"
#include "disc.h"

// Include composite objects
#include "Composite1.h"
#include "Composite2.h"

// -----------------------------------------------------------------------------------------
// global variables
// -----------------------------------------------------------------------------------------
extern ProgramMode		gProgramMode;							// initially, we're not animating
extern cameraClass		gCamera;								// the camera
extern object3d			*gSky;									// the global skybox
extern fog				*gFog;									// the global fog
extern viewfrustum		*gViewFrustum;							// the global view frustum object
extern float			gCurrentFrameTime;						// the time that the current animation frame was started

extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;

// -----------------------------------------------------------------------------------------
// variables that represent 3D objects being used in the animation
// -----------------------------------------------------------------------------------------
// Composite objects
Composite1 *car;
Composite2 *airplane;

// some lights
light *ambient, *light0, *light1, *light2;

// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
// This function constructs the objects required for the animation.  It is only called once
// when the program is first run.
// Use this to create child objects and bind them to their parents.
// -----------------------------------------------------------------------------------------

void constructScene()
{
	// create the lights first
	ambient = new light(GL_LIGHT_MODEL_AMBIENT);
	light0 = new light(GL_LIGHT0);
	light1 = new light(GL_LIGHT1);
    
	// Create composite objects
	car = new Composite1();
	airplane = new Composite2();
	
	// Position them in the scene
	car->setPosition(-15, 0, 0);      // Car on the left
	airplane->setPosition(15, 8, 0);  // Airplane on the right, elevated
}

// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
// This function is called whenever the animation is restarted.  Use it to reset objects
// to their starting position or size, or to reset any aspects of the objects that
// might have been altered during an animation sequence.
// -----------------------------------------------------------------------------------------

void resetScene()
{
	// initialise the camera
	gCamera.setPosition(0, 6, 25);    // Move camera back to see both objects
	gCamera.setTarget(0, 3, 0);       // Look at center point between objects
    
	ambient->setColour(0.5, 0.5, 0.5, 1.0);
    
	light0->turnOn();
	light0->setPosition(-10, 15, 10);
	light0->setColour(0.8, 0.8, 0.8, 1.0);
	light0->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light0->makePositional();
	light0->setLinearAttenuation(0.05);
	
	light1->turnOn();
	light1->setPosition(10, 15, 10);
	light1->setColour(0.8, 0.8, 0.8, 1.0);
	light1->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light1->makePositional();
	light1->setLinearAttenuation(0.05);
    
	// Reset composite objects to their initial state
	if (car) {
		car->resetAnimations();
		car->setPosition(-15, 0, 0);
		car->show(); // Make sure they're visible
	}
	
	if (airplane) {
		airplane->resetAnimations();
		airplane->setPosition(15, 8, 0);
		airplane->show(); // Make sure they're visible
	}
}

// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
// This function is called to animate objects ready for the next frame
// -----------------------------------------------------------------------------------------

void animateForNextFrame(float time, long frame)
{
	// Animate the car
	if (car) {
		car->animateWheelsSpin(kTimeBetweenAnimates);
		car->animateDoorsOpen(kTimeBetweenAnimates);
		car->animateCarMovement(kTimeBetweenAnimates);
	}
	
	// Animate the airplane
	if (airplane) {
		airplane->animatePropellerSpin(kTimeBetweenAnimates);
		airplane->animateLandingGearRetract(kTimeBetweenAnimates);
		airplane->animateFlightPattern(kTimeBetweenAnimates);
	}
	
	// Add some camera movement for a more dynamic view
	static float cameraAngle = 0.0f;
	cameraAngle += kTimeBetweenAnimates * 10.0f; // 10 degrees per second
	
	float cameraX = 25.0f * cos_d(cameraAngle);
	float cameraZ = 25.0f * sin_d(cameraAngle);
	gCamera.setPosition(cameraX, 8, cameraZ);
	gCamera.setTarget(0, 3, 0);
	
	// eventually stop
	if (time >= 45)
		gProgramMode = kpmFinished;
}