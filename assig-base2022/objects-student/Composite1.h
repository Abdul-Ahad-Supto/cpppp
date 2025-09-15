// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2022
// Assignment 2 - Mini Project
// *****************************************************************************************
//
// Composite1.h - Car Class
// This file declares a composite car object with 8+ child components
// Author: Student
//

#ifndef _COMPOSITE1_H
#define _COMPOSITE1_H

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "cube.h"
#include "cylinder.h"
#include "torus.h"
#include "sphere.h"
#include "extrusion.h"
#include "sweep.h"
#include "texture.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class Composite1 : public object3d
{
private:
    // Child objects (8+ components)
    cube* body;           // Main car body
    cube* hood;           // Car hood
    cube* roof;           // Car roof
    torus* wheel1;        // Front left wheel
    torus* wheel2;        // Front right wheel  
    torus* wheel3;        // Rear left wheel
    torus* wheel4;        // Rear right wheel
    cylinder* axle1;      // Front axle
    cylinder* axle2;      // Rear axle
    cube* door1;          // Left door
    cube* door2;          // Right door
    sphere* headlight1;   // Left headlight
    sphere* headlight2;   // Right headlight
    extrusion* windshield; // Front windshield
    sweep* exhaust;       // Exhaust pipe
    
    // Textures
    texture* carTexture;
    texture* wheelTexture;
    texture* glassTexture;
    
    // Animation parameters
    float wheelRotation;
    float doorAngle;
    float circleAngle;
    float circleRadius;
    
public:
    Composite1();                    // Constructor
    virtual ~Composite1();           // Destructor
    
    // Required hide/show methods
    virtual void hide();
    virtual void show();
    
    // Animation methods - independently animatable components
    void animateWheelsSpin(float deltaTime);     // Animate wheel spinning
    void animateDoorsOpen(float deltaTime);     // Animate doors opening/closing  
    void animateCarMovement(float deltaTime);   // Animate car moving in circle
    void resetAnimations();                     // Reset all animations
};

#endif // _COMPOSITE1_H