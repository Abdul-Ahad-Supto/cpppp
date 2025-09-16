// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 2
// 3D Engine Code
// *****************************************************************************************
//
// Composite2.cpp - Moving Car Implementation

#include "prefix.h"
#include "Composite2.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
Composite2::Composite2()
{
    setName("Moving Car");
    wheelRotation = 0.0f;
    carPosition = -20.0f; // Start position
    headlightGlow = 0.0f;
    
    // Load textures
    carTexture = new texture("redbluecheck.jpg");
    wheelTexture = new texture("ground.jpg");
    glassTexture = new texture("cloudy3.jpg");
    
    // Create car body
    carBody = new cube();
    carBody->setParent(this);
    carBody->setTexture(carTexture);
    carBody->setDeformation(2.5f, 0.8f, 1.2f);
    carBody->setPosition(0, 0.5f, 0);
    
    // Create car top/roof
    carTop = new cube();
    carTop->setParent(carBody);
    carTop->setTexture(carTexture);
    carTop->setDeformation(0.8f, 0.7f, 0.9f);
    carTop->setPosition(0, 1.0f, 0.1f);
    
    // Create windshield
    windshield = new cube();
    windshield->setParent(carTop);
    windshield->setTexture(glassTexture);
    windshield->setDeformation(0.85f, 0.6f, 0.1f);
    windshield->setPosition(0, 0, 0.8f);
    windshield->makeTransparent();
    windshield->setColour(0.7f, 0.9f, 1.0f, 0.6f);
    
    // Create back window
    backWindow = new cube();
    backWindow->setParent(carTop);
    backWindow->setTexture(glassTexture);
    backWindow->setDeformation(0.85f, 0.6f, 0.1f);
    backWindow->setPosition(0, 0, -0.8f);
    backWindow->makeTransparent();
    backWindow->setColour(0.7f, 0.9f, 1.0f, 0.6f);
    
    // Create wheels
    wheel1 = new cylinder(12);
    wheel1->setParent(carBody);
    wheel1->setTexture(wheelTexture);
    wheel1->setRotation('z', 90);
    wheel1->setDeformation(0.4f, 0.2f, 0.4f);
    wheel1->setPosition(1.5f, -0.6f, 0.8f);
    
    wheel2 = new cylinder(12);
    wheel2->setParent(carBody);
    wheel2->setTexture(wheelTexture);
    wheel2->setRotation('z', 90);
    wheel2->setDeformation(0.4f, 0.2f, 0.4f);
    wheel2->setPosition(-1.5f, -0.6f, 0.8f);
    
    wheel3 = new cylinder(12);
    wheel3->setParent(carBody);
    wheel3->setTexture(wheelTexture);
    wheel3->setRotation('z', 90);
    wheel3->setDeformation(0.4f, 0.2f, 0.4f);
    wheel3->setPosition(1.5f, -0.6f, -0.8f);
    
    wheel4 = new cylinder(12);
    wheel4->setParent(carBody);
    wheel4->setTexture(wheelTexture);
    wheel4->setRotation('z', 90);
    wheel4->setDeformation(0.4f, 0.2f, 0.4f);
    wheel4->setPosition(-1.5f, -0.6f, -0.8f);
    
    // Create headlights
    headlight1 = new sphere(8);
    headlight1->setParent(carBody);
    headlight1->setColour(1.0f, 1.0f, 0.8f);
    headlight1->setDeformation(0.15f, 0.15f, 0.15f);
    headlight1->setPosition(2.3f, 0.2f, 0.4f);
    
    headlight2 = new sphere(8);
    headlight2->setParent(carBody);
    headlight2->setColour(1.0f, 1.0f, 0.8f);
    headlight2->setDeformation(0.15f, 0.15f, 0.15f);
    headlight2->setPosition(2.3f, 0.2f, -0.4f);
    
    // Create bumper using extrusion
    bumper = new extrusion("bumper_profile.txt", "bumper_path.txt");
    bumper->setParent(carBody);
    bumper->setColour(0.2f, 0.2f, 0.2f); // Dark gray
    bumper->setDeformation(1.0f, 0.3f, 1.0f);
    bumper->setPosition(2.2f, -0.3f, 0);
    
    // Create exhaust pipe using sweep
    exhaust = new sweep("exhaust_profile.txt", 8);
    exhaust->setParent(carBody);
    exhaust->setColour(0.3f, 0.3f, 0.3f); // Gray metal
    exhaust->setDeformation(0.5f, 0.5f, 0.5f);
    exhaust->setPosition(-2.3f, -0.4f, 0.6f);
    
    // Add to shape vector
    gShapeVector.push_back(this);
}

// -----------------------------------------------------------------------------------------
// destructor
// -----------------------------------------------------------------------------------------
Composite2::~Composite2()
{
    delete carTexture;
    delete wheelTexture;
    delete glassTexture;
}

// -----------------------------------------------------------------------------------------
// hide - hides all child objects
// -----------------------------------------------------------------------------------------
void Composite2::hide()
{
    carBody->hide();
    carTop->hide();
    windshield->hide();
    backWindow->hide();
    wheel1->hide();
    wheel2->hide();
    wheel3->hide();
    wheel4->hide();
    headlight1->hide();
    headlight2->hide();
    bumper->hide();
    exhaust->hide();
    invisible = true;
}

// -----------------------------------------------------------------------------------------
// show - shows all child objects
// -----------------------------------------------------------------------------------------
void Composite2::show()
{
    carBody->show();
    carTop->show();
    windshield->show();
    backWindow->show();
    wheel1->show();
    wheel2->show();
    wheel3->show();
    wheel4->show();
    headlight1->show();
    headlight2->show();
    bumper->show();
    exhaust->show();
    invisible = false;
}

// -----------------------------------------------------------------------------------------
// animateWheels - animates wheel rotation
// -----------------------------------------------------------------------------------------
void Composite2::animateWheels(float time)
{
    wheelRotation = time * 180.0f; // Rotate wheels
    
    wheel1->setRotation('z', 90);
    wheel1->setRotation('x', wheelRotation, 'z', 90);
    
    wheel2->setRotation('z', 90);
    wheel2->setRotation('x', wheelRotation, 'z', 90);
    
    wheel3->setRotation('z', 90);
    wheel3->setRotation('x', wheelRotation, 'z', 90);
    
    wheel4->setRotation('z', 90);
    wheel4->setRotation('x', wheelRotation, 'z', 90);
}

// -----------------------------------------------------------------------------------------
// animateMovement - animates car movement along the road
// -----------------------------------------------------------------------------------------
void Composite2::animateMovement(float time)
{
    // Move car from left to right and loop back
    carPosition = -20.0f + (time * 8.0f); // 8 units per second
    if (carPosition > 30.0f) {
        carPosition = -20.0f; // Reset position
    }
    
    setPosition(carPosition, 0, 0);
}

// -----------------------------------------------------------------------------------------
// animateHeadlights - animates headlight glow effect
// -----------------------------------------------------------------------------------------
void Composite2::animateHeadlights(float time)
{
    // Pulsing headlight effect
    headlightGlow = 0.8f + 0.2f * sin(time * 4.0f);
    
    headlight1->setColour(headlightGlow, headlightGlow, 0.8f);
    headlight2->setColour(headlightGlow, headlightGlow, 0.8f);
}

// -----------------------------------------------------------------------------------------
// updateAnimation - updates all animations for this composite
// -----------------------------------------------------------------------------------------
void Composite2::updateAnimation(float time)
{
    animateWheels(time);
    animateMovement(time);
    animateHeadlights(time);
}