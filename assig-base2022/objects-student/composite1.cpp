// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 2
// 3D Engine Code
// *****************************************************************************************
//
// Composite1.cpp - House Building Implementation

#include "prefix.h"
#include "Composite1.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
Composite1::Composite1()
{
    setName("House Building");
    doorRotation = 0.0f;
    decorationSpin = 0.0f;
    
    // Load textures using available resources
    brickTexture = new texture("bricks2.jpg");
    roofTexture = new texture("Blue_Roof.jpg"); 
    doorTexture = new texture("boxtex.jpg");
    windowTexture = new texture("cloudy3.jpg");
    
    // Create house base
    base = new cube();
    base->setParent(this);
    base->setTexture(brickTexture);
    base->setDeformation(3.0f, 2.5f, 3.0f);
    base->setPosition(0, 0, 0);
    base->setColour(1.0f, 1.0f, 1.0f); // White to show texture properly
    
    // Create roof (pyramid-like)
    roof = new cube();
    roof->setParent(base);
    roof->setTexture(roofTexture);
    roof->setDeformation(3.5f, 1.0f, 3.5f);
    roof->setPosition(0, 3.0f, 0);
    roof->setRotation('y', 45);
    roof->setColour(1.0f, 1.0f, 1.0f); // White to show texture properly
    
    // Create front door
    door = new cube();
    door->setParent(base);
    door->setTexture(doorTexture);
    door->setDeformation(0.8f, 1.8f, 0.15f);
    door->setPosition(0, -0.3f, 3.1f);
    door->setColour(0.8f, 0.6f, 0.4f); // Brown tint
    
    // Create door knob
    doorknob = new sphere(10);
    doorknob->setParent(door);
    doorknob->setColour(1.0f, 1.0f, 0.0f); // Yellow
    doorknob->setDeformation(0.08f, 0.08f, 0.08f);
    doorknob->setPosition(0.6f, 0, 0.2f);
    
    // Create windows
    window1 = new cube();
    window1->setParent(base);
    window1->setTexture(windowTexture);
    window1->setDeformation(1.0f, 1.0f, 0.15f);
    window1->setPosition(-1.8f, 0.5f, 3.1f);
    window1->makeTransparent();
    window1->setColour(0.7f, 0.9f, 1.0f, 0.8f); // Light blue glass
    
    window2 = new cube();
    window2->setParent(base);
    window2->setTexture(windowTexture);
    window2->setDeformation(1.0f, 1.0f, 0.15f);
    window2->setPosition(1.8f, 0.5f, 3.1f);
    window2->makeTransparent();
    window2->setColour(0.7f, 0.9f, 1.0f, 0.8f); // Light blue glass
    
    // Create chimney
    chimney = new cylinder(12);
    chimney->setParent(base);
    chimney->setColour(0.7f, 0.3f, 0.3f); // Brick red
    chimney->setDeformation(0.4f, 2.0f, 0.4f);
    chimney->setPosition(2.2f, 4.0f, -1.0f);
    
    // Create decorative element (spinning torus)
    decoration = new torus(8, 6, 0.4f, 0.15f);
    decoration->setParent(base);
    decoration->setColour(1.0f, 0.5f, 0.0f, 0.8f); // Orange transparent
    decoration->setPosition(0, 4.5f, 0);
    decoration->makeTransparent();
    
    // Create window frame using extrusion
    windowFrame = new extrusion("window_profile.txt", "window_path.txt");
    windowFrame->setParent(window1);
    windowFrame->setColour(0.8f, 0.8f, 0.8f);
    windowFrame->setDeformation(1.2f, 1.2f, 0.5f);
    
    // Create roof trim using sweep
    roofTrim = new sweep("roof_profile.txt", 16);
    roofTrim->setParent(roof);
    roofTrim->setColour(0.6f, 0.4f, 0.2f); // Brown
    roofTrim->setDeformation(1.0f, 0.5f, 1.0f);
    roofTrim->setPosition(0, -0.3f, 0);
    
    // Add to shape vector
    gShapeVector.push_back(this);
}

// -----------------------------------------------------------------------------------------
// destructor
// -----------------------------------------------------------------------------------------
Composite1::~Composite1()
{
    delete brickTexture;
    delete roofTexture;
    delete doorTexture;
    delete windowTexture;
}

// -----------------------------------------------------------------------------------------
// hide - hides all child objects
// -----------------------------------------------------------------------------------------
void Composite1::hide()
{
    base->hide();
    roof->hide();
    door->hide();
    doorknob->hide();
    window1->hide();
    window2->hide();
    chimney->hide();
    decoration->hide();
    windowFrame->hide();
    roofTrim->hide();
    invisible = true;
}

// -----------------------------------------------------------------------------------------
// show - shows all child objects
// -----------------------------------------------------------------------------------------
void Composite1::show()
{
    base->show();
    roof->show();
    door->show();
    doorknob->show();
    window1->show();
    window2->show();
    chimney->show();
    decoration->show();
    windowFrame->show();
    roofTrim->show();
    invisible = false;
}

// -----------------------------------------------------------------------------------------
// animateDoor - animates the door swinging open and closed
// -----------------------------------------------------------------------------------------
void Composite1::animateDoor(float time)
{
    // Door swings open and closed in a cycle
    doorRotation = sin(time * 0.5f) * 45.0f; // Swing between 0 and 45 degrees
    door->setRotation('y', doorRotation);
}

// -----------------------------------------------------------------------------------------
// animateDecoration - animates the decorative torus spinning
// -----------------------------------------------------------------------------------------
void Composite1::animateDecoration(float time)
{
    // Decoration spins continuously
    decorationSpin = time * 60.0f; // 60 degrees per second
    decoration->setRotation('y', decorationSpin);
}

// -----------------------------------------------------------------------------------------
// updateAnimation - updates all animations for this composite
// -----------------------------------------------------------------------------------------
void Composite1::updateAnimation(float time)
{
    animateDoor(time);
    animateDecoration(time);
}