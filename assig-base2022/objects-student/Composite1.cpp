// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2022
// Assignment 2 - Mini Project
// *****************************************************************************************
//
// Composite1.cpp - Car Class Implementation
// This file implements a composite car object with 8+ child components
// Author: Student
//

#include "prefix.h"
#include "Composite1.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// External globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// Constructor - Creates car with all child components
// -----------------------------------------------------------------------------------------
Composite1::Composite1()
{
    // Initialize the composite object
    setName("Car");
    setColour(1.0, 0.0, 0.0, 1.0); // Red car
    
    // Initialize animation parameters
    wheelRotation = 0.0f;
    doorAngle = 0.0f;
    circleAngle = 0.0f;
    circleRadius = 15.0f;
    
    // Load textures
    carTexture = new texture("boxtex.jpg");
    wheelTexture = new texture("boxtex.jpg");
    glassTexture = new texture("boxtex.jpg");
    
    // Create main car body (Component 1)
    body = new cube();
    body->setParent(this);
    body->setTexture(carTexture);
    body->setDeformation(4.0, 1.5, 2.0);  // Wide, low, deep
    body->setPosition(0, 1.0, 0);
    body->setColour(0.8, 0.2, 0.2, 1.0); // Dark red
    
    // Create car hood (Component 2)
    hood = new cube();
    hood->setParent(body);
    hood->setTexture(carTexture);
    hood->setDeformation(1.8, 0.3, 1.8);
    hood->setPosition(3.2, 0.9, 0);
    hood->setColour(0.8, 0.2, 0.2, 1.0);
    
    // Create car roof (Component 3)
    roof = new cube();
    roof->setParent(body);
    roof->setTexture(carTexture);
    roof->setDeformation(2.5, 1.0, 1.8);
    roof->setPosition(-0.5, 2.2, 0);
    roof->setColour(0.8, 0.2, 0.2, 1.0);
    
    // Create wheels (Components 4-7) - Independently animatable
    wheel1 = new torus(8, 8, 1.0, 0.3); // Front left
    wheel1->setParent(body);
    wheel1->setTexture(wheelTexture);
    wheel1->setPosition(2.5, -1.2, -2.3);
    wheel1->setRotation('x', 90);
    wheel1->setColour(0.2, 0.2, 0.2, 1.0); // Dark gray
    
    wheel2 = new torus(8, 8, 1.0, 0.3); // Front right  
    wheel2->setParent(body);
    wheel2->setTexture(wheelTexture);
    wheel2->setPosition(2.5, -1.2, 2.3);
    wheel2->setRotation('x', 90);
    wheel2->setColour(0.2, 0.2, 0.2, 1.0);
    
    wheel3 = new torus(8, 8, 1.0, 0.3); // Rear left
    wheel3->setParent(body);
    wheel3->setTexture(wheelTexture);  
    wheel3->setPosition(-2.5, -1.2, -2.3);
    wheel3->setRotation('x', 90);
    wheel3->setColour(0.2, 0.2, 0.2, 1.0);
    
    wheel4 = new torus(8, 8, 1.0, 0.3); // Rear right
    wheel4->setParent(body);
    wheel4->setTexture(wheelTexture);
    wheel4->setPosition(-2.5, -1.2, 2.3);
    wheel4->setRotation('x', 90);
    wheel4->setColour(0.2, 0.2, 0.2, 1.0);
    
    // Create axles (Components 8-9)
    axle1 = new cylinder(16); // Front axle
    axle1->setParent(body);
    axle1->setDeformation(0.2, 0.2, 5.0);
    axle1->setPosition(2.5, -1.2, 0);
    axle1->setRotation('z', 90);
    axle1->setColour(0.3, 0.3, 0.3, 1.0); // Gray
    
    axle2 = new cylinder(16); // Rear axle
    axle2->setParent(body);
    axle2->setDeformation(0.2, 0.2, 5.0);
    axle2->setPosition(-2.5, -1.2, 0);
    axle2->setRotation('z', 90);
    axle2->setColour(0.3, 0.3, 0.3, 1.0);
    
    // Create doors (Components 10-11) - Independently animatable
    door1 = new cube(); // Left door
    door1->setParent(body);
    door1->setTexture(carTexture);
    door1->setDeformation(2.0, 1.4, 0.1);
    door1->setPosition(0, 0.2, -2.1);
    door1->setOffset(-1.8, 0, 0); // Pivot point
    door1->setColour(0.7, 0.1, 0.1, 1.0);
    
    door2 = new cube(); // Right door  
    door2->setParent(body);
    door2->setTexture(carTexture);
    door2->setDeformation(2.0, 1.4, 0.1);
    door2->setPosition(0, 0.2, 2.1);
    door2->setOffset(-1.8, 0, 0);
    door2->setColour(0.7, 0.1, 0.1, 1.0);
    
    // Create headlights (Components 12-13)
    headlight1 = new sphere(12); // Left headlight
    headlight1->setParent(body);
    headlight1->setDeformation(0.4, 0.4, 0.4);
    headlight1->setPosition(4.5, 0.5, -1.5);
    headlight1->setColour(1.0, 1.0, 0.8, 1.0); // Yellowish white
    
    headlight2 = new sphere(12); // Right headlight
    headlight2->setParent(body);
    headlight2->setDeformation(0.4, 0.4, 0.4);
    headlight2->setPosition(4.5, 0.5, 1.5);
    headlight2->setColour(1.0, 1.0, 0.8, 1.0);
    
    // Create windshield using extrusion (Component 14)
    windshield = new extrusion("windshield_profile.txt", "windshield_path.txt");
    windshield->setParent(body);
    windshield->setTexture(glassTexture);
    windshield->setPosition(1.5, 2.8, 0);
    windshield->setRotation('x', -10); // Slight angle
    windshield->setColour(0.8, 0.9, 1.0, 0.7); // Semi-transparent blue
    windshield->makeTransparent();
    
    // Create exhaust pipe using sweep (Component 15)
    exhaust = new sweep("exhaust_profile.txt", 16);
    exhaust->setParent(body);
    exhaust->setPosition(-4.2, -0.5, -1.5);
    exhaust->setRotation('y', 180);
    exhaust->setColour(0.4, 0.4, 0.4, 1.0); // Dark gray
    
    // Add to global shape vector for rendering
    gShapeVector.push_back(this);
}

// -----------------------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------------------
Composite1::~Composite1()
{
    // Textures will be cleaned up automatically
    // Child objects will be cleaned up by their destructors
}

// -----------------------------------------------------------------------------------------
// Hide all child components
// -----------------------------------------------------------------------------------------
void Composite1::hide()
{
    invisible = true; // Hide this object
    
    // Hide all child components
    body->hide();
    hood->hide();
    roof->hide();
    wheel1->hide();
    wheel2->hide();
    wheel3->hide();
    wheel4->hide();
    axle1->hide();
    axle2->hide();
    door1->hide();
    door2->hide();
    headlight1->hide();
    headlight2->hide();
    windshield->hide();
    exhaust->hide();
}

// -----------------------------------------------------------------------------------------
// Show all child components  
// -----------------------------------------------------------------------------------------
void Composite1::show()
{
    invisible = false; // Show this object
    
    // Show all child components
    body->show();
    hood->show();
    roof->show();
    wheel1->show();
    wheel2->show();
    wheel3->show();
    wheel4->show();
    axle1->show();
    axle2->show();
    door1->show();
    door2->show();
    headlight1->show();
    headlight2->show();
    windshield->show();
    exhaust->show();
}

// -----------------------------------------------------------------------------------------
// Animation Method 1: Animate wheel spinning (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite1::animateWheelsSpin(float deltaTime)
{
    // Update wheel rotation based on car movement
    wheelRotation += deltaTime * 180.0f; // Rotate 180 degrees per second
    if (wheelRotation > 360.0f) wheelRotation -= 360.0f;
    
    // Apply rotation to all wheels
    wheel1->setRotation('x', 90, 'z', wheelRotation);
    wheel2->setRotation('x', 90, 'z', wheelRotation);
    wheel3->setRotation('x', 90, 'z', wheelRotation);
    wheel4->setRotation('x', 90, 'z', wheelRotation);
}

// -----------------------------------------------------------------------------------------
// Animation Method 2: Animate doors opening/closing (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite1::animateDoorsOpen(float deltaTime)
{
    // Oscillate door angle between 0 and 60 degrees
    static float doorDirection = 1.0f;
    doorAngle += doorDirection * deltaTime * 30.0f; // 30 degrees per second
    
    // Reverse direction at limits
    if (doorAngle > 60.0f) {
        doorAngle = 60.0f;
        doorDirection = -1.0f;
    }
    else if (doorAngle < 0.0f) {
        doorAngle = 0.0f;
        doorDirection = 1.0f;
    }
    
    // Apply door rotations (doors open outward)
    door1->setRotation('y', -doorAngle); // Left door opens left
    door2->setRotation('y', doorAngle);  // Right door opens right
}

// -----------------------------------------------------------------------------------------  
// Animation Method 3: Animate car moving in circle (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite1::animateCarMovement(float deltaTime)
{
    // Update circle position
    circleAngle += deltaTime * 45.0f; // 45 degrees per second = full circle in 8 seconds
    if (circleAngle > 360.0f) circleAngle -= 360.0f;
    
    // Calculate new position on circle
    float x = circleRadius * cos_d(circleAngle);
    float z = circleRadius * sin_d(circleAngle);
    
    // Set position and rotation to face movement direction
    setPosition(x, 0, z);
    setRotation('y', circleAngle + 90.0f); // Face forward along circle
}

// -----------------------------------------------------------------------------------------
// Reset all animations to initial state
// -----------------------------------------------------------------------------------------
void Composite1::resetAnimations()
{
    wheelRotation = 0.0f;
    doorAngle = 0.0f; 
    circleAngle = 0.0f;
    
    // Reset positions and rotations
    setPosition(0, 0, 0);
    setRotation('y', 0);
    
    // Reset wheel rotations
    wheel1->setRotation('x', 90);
    wheel2->setRotation('x', 90);
    wheel3->setRotation('x', 90);
    wheel4->setRotation('x', 90);
    
    // Reset door positions
    door1->setRotation('y', 0);
    door2->setRotation('y', 0);
}