*******************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 2
// 3D Engine Code
// *****************************************************************************************
//
// scene.cpp - Updated with composite objects

#include "prefix.h"
#include "constants.h"
#include "utility.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"

// Include geometry classes
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
extern ProgramMode		gProgramMode;
extern cameraClass		gCamera;
extern object3d			*gSky;
extern fog				*gFog;
extern viewfrustum		*gViewFrustum;
extern float			gCurrentFrameTime;
extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;

// -----------------------------------------------------------------------------------------
// scene objects
// -----------------------------------------------------------------------------------------
// Composite objects
Composite1 *house1, *house2, *house3, *house4, *house5;
Composite2 *car1, *car2;

// Environment objects
plane *road;
plane *ground;

// Lights
light *ambient, *light0, *light1, *light2;

// Textures
texture *roadTexture;
texture *groundTexture;
texture *skyTexture;

// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
void constructScene()
{
    // Create the lights first
    ambient = new light(GL_LIGHT_MODEL_AMBIENT);
    light0 = new light(GL_LIGHT0);
    light1 = new light(GL_LIGHT1);
    light2 = new light(GL_LIGHT2);
    
    // Create skybox - try multiple approaches
    gSky = nullptr;
    
    // First try: Look for cloudy1.jpg to cloudy6.jpg for skybox
    try {
        gSky = new skybox("cloudy");
    } catch (...) {
        // If skybox fails, create a simple sky sphere
        tsphere *skyDome = new tsphere(20);
        try {
            skyDome->setTexture(new texture("cloudy3.jpg"));
        } catch (...) {
            // If no cloud texture, just use a blue color
            skyDome->setColour(0.5f, 0.7f, 1.0f);
        }
        skyDome->setDeformation(80.0f, 80.0f, 80.0f);
        skyDome->setPosition(0, 0, 0);
        gSky = skyDome;
    }
    
    vectr fogColor;
    fogColor.set(0.7f, 0.8f, 0.9f, 1.0f); // Light blue-gray fog
    gFog = new fog(40.0f, 80.0f, fogColor);
    
    // Load textures using available resources
    roadTexture = new texture("ground.jpg");
    groundTexture = new texture("ground.jpg");
    
    // Create road (black strip across the scene)
    road = new plane();
    road->setTexture(roadTexture);
    road->setDeformation(50.0f, 1.0f, 8.0f);
    road->setPosition(0, -1.45f, 0);
    road->setRotation('x', -90);
    road->setColour(0.3f, 0.3f, 0.3f); // Darker road color
    
    // Create ground plane
    ground = new plane();
    ground->setTexture(groundTexture);
    ground->setDeformation(60.0f, 1.0f, 40.0f);
    ground->setPosition(0, -1.5f, 0);
    ground->setRotation('x', -90);
    ground->setColour(0.4f, 0.6f, 0.3f); // Grass color
    
    // Create houses (Composite1 objects) - arranged like in screenshot
    house1 = new Composite1();
    house1->setPosition(-15.0f, 0, 8.0f);
    house1->setRotation('y', 15);
    
    house2 = new Composite1();
    house2->setPosition(-8.0f, 0, 12.0f);
    house2->setRotation('y', -20);
    
    house3 = new Composite1();
    house3->setPosition(5.0f, 0, 10.0f);
    house3->setRotation('y', 30);
    
    house4 = new Composite1();
    house4->setPosition(12.0f, 0, 8.0f);
    house4->setRotation('y', -10);
    
    house5 = new Composite1();
    house5->setPosition(-5.0f, 0, -12.0f);
    house5->setRotation('y', 45);
    
    // Create cars (Composite2 objects)
    car1 = new Composite2();
    car1->setPosition(-20.0f, 0, 2.0f);
    
    car2 = new Composite2();
    car2->setPosition(-25.0f, 0, -2.0f);
    car2->setRotation('y', 180); // Facing opposite direction
}

// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
void resetScene()
{
    // Initialize the camera for better view
    gCamera.setPosition(0, 15, 25);
    gCamera.setTarget(0, 0, 0);
    
    // Set up better lighting
    ambient->setColour(0.4f, 0.4f, 0.5f, 1.0f);
    
    light0->turnOn();
    light0->setPosition(-15, 20, 10);
    light0->setColour(1.0f, 0.95f, 0.8f, 1.0f);
    light0->setSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
    light0->makePositional();
    light0->setLinearAttenuation(0.02f);
    
    light1->turnOn();
    light1->setPosition(15, 20, -10);
    light1->setColour(0.9f, 0.9f, 1.0f, 1.0f);
    light1->setSpecularColour(0.8f, 0.8f, 1.0f, 1.0f);
    light1->makePositional();
    light1->setLinearAttenuation(0.02f);
    
    light2->turnOn();
    light2->setPosition(0, 25, 0);
    light2->setColour(0.6f, 0.6f, 0.7f, 1.0f);
    light2->setSpecularColour(0.5f, 0.5f, 0.6f, 1.0f);
    light2->makePositional();
    light2->setLinearAttenuation(0.01f);
    
    // Reset all composite objects to their starting positions
    if (house1) house1->setPosition(-15.0f, 0, 8.0f);
    if (house2) house2->setPosition(-8.0f, 0, 12.0f);
    if (house3) house3->setPosition(5.0f, 0, 10.0f);
    if (house4) house4->setPosition(12.0f, 0, 8.0f);
    if (house5) house5->setPosition(-5.0f, 0, -12.0f);
    
    if (car1) car1->setPosition(-20.0f, 0, 2.0f);
    if (car2) {
        car2->setPosition(-25.0f, 0, -2.0f);
        car2->setRotation('y', 180);
    }
}

// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
void animateForNextFrame(float time, long frame)
{
    // Animate all composite objects
    if (house1) house1->updateAnimation(time);
    if (house2) house2->updateAnimation(time + 0.5f); // Offset animation
    if (house3) house3->updateAnimation(time + 1.0f);
    if (house4) house4->updateAnimation(time + 1.5f);
    if (house5) house5->updateAnimation(time + 2.0f);
    
    if (car1) car1->updateAnimation(time);
    if (car2) car2->updateAnimation(time + 3.0f); // Different timing for second car
    
    // Slower camera movement for better view
    float cameraAngle = time * 5.0f; // Slower rotation
    float cameraRadius = 30.0f;
    float cameraHeight = 15.0f + 5.0f * sin(time * 0.3f); // Slight height variation
    float cameraX = cos(cameraAngle * 3.14159f / 180.0f) * cameraRadius;
    float cameraZ = sin(cameraAngle * 3.14159f / 180.0f) * cameraRadius;
    
    gCamera.setPosition(cameraX, cameraHeight, cameraZ);
    gCamera.setTarget(0, 2, 0);
    
    // Subtle lighting changes for atmosphere
    float lightIntensity = 0.7f + 0.2f * sin(time * 0.1f);
    light0->setColour(lightIntensity, lightIntensity * 0.95f, lightIntensity * 0.8f, 1.0f);
    light1->setColour(lightIntensity * 0.9f, lightIntensity * 0.9f, lightIntensity, 1.0f);
    
    // Eventually stop the animation
    if (time >= 45)
        gProgramMode = kpmFinished;
}