// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 2
// 3D Engine Code
// *****************************************************************************************
//
// Composite2.h - Moving Car
//
// This file declares a composite car with animated wheels and movement

#ifndef _COMPOSITE2_H
#define _COMPOSITE2_H

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "cube.h"
#include "cylinder.h"
#include "sphere.h"
#include "torus.h"
#include "extrusion.h"
#include "sweep.h"
#include "texture.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class Composite2 : public object3d
{
private:
    // Child objects (at least 8 required)
    cube* carBody;        // Main car body
    cube* carTop;         // Car roof/top
    cube* windshield;     // Front windshield
    cube* backWindow;     // Back window
    cylinder* wheel1;     // Front left wheel
    cylinder* wheel2;     // Front right wheel
    cylinder* wheel3;     // Back left wheel
    cylinder* wheel4;     // Back right wheel
    sphere* headlight1;   // Left headlight
    sphere* headlight2;   // Right headlight
    extrusion* bumper;    // Car bumper (extrusion)
    sweep* exhaust;       // Exhaust pipe (sweep)
    
    // Textures
    texture* carTexture;
    texture* wheelTexture;
    texture* glassTexture;
    
    // Animation state
    float wheelRotation;
    float carPosition;
    float headlightGlow;
    
public:
    Composite2();
    virtual ~Composite2();
    
    // Required methods
    virtual void hide();
    virtual void show();
    
    // Animation methods
    void animateWheels(float time);
    void animateMovement(float time);
    void animateHeadlights(float time);
    void updateAnimation(float time);
};

#endif // _COMPOSITE2_H