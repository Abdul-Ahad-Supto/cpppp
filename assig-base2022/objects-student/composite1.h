// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 2
// 3D Engine Code
// *****************************************************************************************
//
// Composite1.h - House Building
//
// This file declares a composite house building with animated elements

#ifndef _COMPOSITE1_H
#define _COMPOSITE1_H

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
class Composite1 : public object3d
{
private:
    // Child objects (at least 8 required)
    cube* base;           // House base
    cube* roof;           // House roof
    cube* door;           // Front door
    cube* window1;        // Window 1
    cube* window2;        // Window 2
    cylinder* chimney;    // Chimney
    sphere* doorknob;     // Door knob
    torus* decoration;    // Decorative element
    extrusion* windowFrame; // Window frame (extrusion)
    sweep* roofTrim;      // Roof trim (sweep)
    
    // Textures
    texture* brickTexture;
    texture* roofTexture;
    texture* doorTexture;
    texture* windowTexture;
    
    // Animation state
    float doorRotation;
    float decorationSpin;
    
public:
    Composite1();
    virtual ~Composite1();
    
    // Required methods
    virtual void hide();
    virtual void show();
    
    // Animation methods
    void animateDoor(float time);
    void animateDecoration(float time);
    void updateAnimation(float time);
};

#endif // _COMPOSITE1_H