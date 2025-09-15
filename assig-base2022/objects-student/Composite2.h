// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2022
// Assignment 2 - Mini Project
// *****************************************************************************************
//
// Composite2.h - Airplane Class
// This file declares a composite airplane object with 8+ child components
// Author: Student
//

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
    // Child objects (8+ components)
    cylinder* fuselage;      // Main airplane body
    cube* wing1;             // Left wing
    cube* wing2;             // Right wing
    cube* tailWing;          // Tail wing
    cube* verticalTail;      // Vertical tail
    cylinder* propeller;     // Propeller hub
    cube* propBlade1;        // Propeller blade 1
    cube* propBlade2;        // Propeller blade 2
    cube* propBlade3;        // Propeller blade 3
    cylinder* landingGear1;  // Landing gear strut 1
    cylinder* landingGear2;  // Landing gear strut 2
    sphere* wheel5;          // Landing gear wheel 1
    sphere* wheel6;          // Landing gear wheel 2
    extrusion* cockpit;      // Cockpit canopy
    sweep* exhaust2;         // Engine exhaust
    
    // Textures
    texture* planeTexture;
    texture* propellerTexture;
    texture* cockpitTexture;
    
    // Animation parameters
    float propellerRotation;
    float landingGearAngle;
    float flightAngle;
    float flightHeight;
    float flightRadius;
    
public:
    Composite2();                    // Constructor
    virtual ~Composite2();           // Destructor
    
    // Required hide/show methods
    virtual void hide();
    virtual void show();
    
    // Animation methods - independently animatable components
    void animatePropellerSpin(float deltaTime);      // Animate propeller spinning
    void animateLandingGearRetract(float deltaTime); // Animate landing gear retracting
    void animateFlightPattern(float deltaTime);      // Animate plane flying in pattern
    void resetAnimations();                          // Reset all animations
};

#endif // _COMPOSITE2_H