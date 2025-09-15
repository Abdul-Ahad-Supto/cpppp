// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2022
// Assignment 2 - Mini Project  
// *****************************************************************************************
//
// Composite2.cpp - Airplane Class Implementation
// This file implements a composite airplane object with 8+ child components
// Author: Student
//

#include "prefix.h"
#include "Composite2.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// External globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// Constructor - Creates airplane with all child components
// -----------------------------------------------------------------------------------------
Composite2::Composite2()
{
    // Initialize the composite object
    setName("Airplane");
    setColour(0.8, 0.8, 0.9, 1.0); // Light blue/gray airplane
    
    // Initialize animation parameters
    propellerRotation = 0.0f;
    landingGearAngle = 0.0f;
    flightAngle = 0.0f;
    flightHeight = 8.0f;
    flightRadius = 20.0f;
    
    // Load textures
    planeTexture = new texture("boxtex.jpg");
    propellerTexture = new texture("boxtex.jpg");
    cockpitTexture = new texture("boxtex.jpg");
    
    // Create main fuselage (Component 1)
    fuselage = new cylinder(16);
    fuselage->setParent(this);
    fuselage->setTexture(planeTexture);
    fuselage->setDeformation(1.0, 1.0, 8.0); // Long cylindrical body
    fuselage->setRotation('z', 90); // Orient horizontally
    fuselage->setPosition(0, 2.0, 0);
    fuselage->setColour(0.9, 0.9, 1.0, 1.0); // Light blue/white
    
    // Create left wing (Component 2)
    wing1 = new cube();
    wing1->setParent(fuselage);
    wing1->setTexture(planeTexture);
    wing1->setDeformation(4.0, 0.2, 1.5);
    wing1->setPosition(0, -0.3, -5.5);
    wing1->setColour(0.8, 0.8, 0.9, 1.0);
    
    // Create right wing (Component 3)  
    wing2 = new cube();
    wing2->setParent(fuselage);
    wing2->setTexture(planeTexture);
    wing2->setDeformation(4.0, 0.2, 1.5);
    wing2->setPosition(0, -0.3, 5.5);
    wing2->setColour(0.8, 0.8, 0.9, 1.0);
    
    // Create tail wing (Component 4)
    tailWing = new cube();
    tailWing->setParent(fuselage);
    tailWing->setTexture(planeTexture);
    tailWing->setDeformation(2.5, 0.15, 0.8);
    tailWing->setPosition(-7.0, -0.2, 0);
    tailWing->setColour(0.8, 0.8, 0.9, 1.0);
    
    // Create vertical tail (Component 5)
    verticalTail = new cube();
    verticalTail->setParent(fuselage);
    verticalTail->setTexture(planeTexture);
    verticalTail->setDeformation(1.8, 2.0, 0.15);
    verticalTail->setPosition(-7.0, 1.5, 0);
    verticalTail->setColour(0.8, 0.8, 0.9, 1.0);
    
    // Create propeller hub (Component 6) - Independently animatable
    propeller = new cylinder(8);
    propeller->setParent(fuselage);
    propeller->setTexture(propellerTexture);
    propeller->setDeformation(0.8, 0.8, 0.3);
    propeller->setPosition(8.5, 0, 0);
    propeller->setColour(0.3, 0.3, 0.3, 1.0); // Dark gray
    
    // Create propeller blades (Components 7-9) - Part of propeller animation
    propBlade1 = new cube();
    propBlade1->setParent(propeller);
    propBlade1->setTexture(propellerTexture);
    propBlade1->setDeformation(0.1, 3.0, 0.1);
    propBlade1->setPosition(0, 0, 0);
    propBlade1->setColour(0.2, 0.2, 0.2, 1.0); // Dark gray
    
    propBlade2 = new cube();
    propBlade2->setParent(propeller);
    propBlade2->setTexture(propellerTexture);
    propBlade2->setDeformation(0.1, 3.0, 0.1);
    propBlade2->setPosition(0, 0, 0);
    propBlade2->setRotation('x', 60); // 60 degrees offset
    propBlade2->setColour(0.2, 0.2, 0.2, 1.0);
    
    propBlade3 = new cube();
    propBlade3->setParent(propeller);
    propBlade3->setTexture(propellerTexture);
    propBlade3->setDeformation(0.1, 3.0, 0.1);
    propBlade3->setPosition(0, 0, 0);
    propBlade3->setRotation('x', 120); // 120 degrees offset
    propBlade3->setColour(0.2, 0.2, 0.2, 1.0);
    
    // Create landing gear struts (Components 10-11) - Independently animatable
    landingGear1 = new cylinder(8); // Left landing gear
    landingGear1->setParent(fuselage);
    landingGear1->setDeformation(0.1, 2.0, 0.1);
    landingGear1->setPosition(1.0, -2.5, -2.0);
    landingGear1->setOffset(0, 1.0, 0); // Pivot point at top
    landingGear1->setColour(0.4, 0.4, 0.4, 1.0); // Gray
    
    landingGear2 = new cylinder(8); // Right landing gear  
    landingGear2->setParent(fuselage);
    landingGear2->setDeformation(0.1, 2.0, 0.1);
    landingGear2->setPosition(1.0, -2.5, 2.0);
    landingGear2->setOffset(0, 1.0, 0);
    landingGear2->setColour(0.4, 0.4, 0.4, 1.0);
    
    // Create landing gear wheels (Components 12-13)
    wheel5 = new sphere(8); // Left wheel
    wheel5->setParent(landingGear1);
    wheel5->setDeformation(0.6, 0.6, 0.6);
    wheel5->setPosition(0, -1.0, 0);
    wheel5->setColour(0.1, 0.1, 0.1, 1.0); // Black
    
    wheel6 = new sphere(8); // Right wheel
    wheel6->setParent(landingGear2);
    wheel6->setDeformation(0.6, 0.6, 0.6);
    wheel6->setPosition(0, -1.0, 0);
    wheel6->setColour(0.1, 0.1, 0.1, 1.0);
    
    // Create cockpit canopy using extrusion (Component 14)
    cockpit = new extrusion("cockpit_profile.txt", "cockpit_path.txt");
    cockpit->setParent(fuselage);
    cockpit->setTexture(cockpitTexture);
    cockpit->setPosition(3.0, 0.8, 0);
    cockpit->setColour(0.7, 0.9, 1.0, 0.6); // Semi-transparent blue
    cockpit->makeTransparent();
    
    // Create engine exhaust using sweep (Component 15)
    exhaust2 = new sweep("exhaust_profile.txt", 12);
    exhaust2->setParent(fuselage);
    exhaust2->setPosition(-8.0, -0.5, 0);
    exhaust2->setRotation('y', 180);
    exhaust2->setColour(0.3, 0.3, 0.4, 1.0); // Dark gray
    
    // Set initial position above ground
    setPosition(0, flightHeight, 0);
    
    // Add to global shape vector for rendering
    gShapeVector.push_back(this);
}

// -----------------------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------------------
Composite2::~Composite2()
{
    // Textures and child objects will be cleaned up automatically
}

// -----------------------------------------------------------------------------------------
// Hide all child components
// -----------------------------------------------------------------------------------------
void Composite2::hide()
{
    invisible = true; // Hide this object
    
    // Hide all child components
    fuselage->hide();
    wing1->hide();
    wing2->hide();
    tailWing->hide();
    verticalTail->hide();
    propeller->hide();
    propBlade1->hide();
    propBlade2->hide();
    propBlade3->hide();
    landingGear1->hide();
    landingGear2->hide();
    wheel5->hide();
    wheel6->hide();
    cockpit->hide();
    exhaust2->hide();
}

// -----------------------------------------------------------------------------------------
// Show all child components
// -----------------------------------------------------------------------------------------
void Composite2::show()
{
    invisible = false; // Show this object
    
    // Show all child components
    fuselage->show();
    wing1->show();
    wing2->show();
    tailWing->show();
    verticalTail->show();
    propeller->show();
    propBlade1->show();
    propBlade2->show();
    propBlade3->show();
    landingGear1->show();
    landingGear2->show();
    wheel5->show();
    wheel6->show();
    cockpit->show();
    exhaust2->show();
}

// -----------------------------------------------------------------------------------------
// Animation Method 1: Animate propeller spinning (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite2::animatePropellerSpin(float deltaTime)
{
    // Update propeller rotation - spin very fast like a real propeller
    propellerRotation += deltaTime * 720.0f; // 720 degrees per second (2 rotations/sec)
    if (propellerRotation > 360.0f) propellerRotation -= 360.0f;
    
    // Apply rotation to propeller hub and all blades together
    propeller->setRotation('x', propellerRotation);
}

// -----------------------------------------------------------------------------------------
// Animation Method 2: Animate landing gear retracting (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite2::animateLandingGearRetract(float deltaTime)
{
    // Oscillate landing gear between extended (0) and retracted (90 degrees)
    static float gearDirection = 1.0f;
    landingGearAngle += gearDirection * deltaTime * 60.0f; // 60 degrees per second
    
    // Reverse direction at limits
    if (landingGearAngle > 90.0f) {
        landingGearAngle = 90.0f;
        gearDirection = -1.0f;
    }
    else if (landingGearAngle < 0.0f) {
        landingGearAngle = 0.0f;
        gearDirection = 1.0f;
    }
    
    // Apply rotation to retract landing gear (rotate around attachment point)
    landingGear1->setRotation('z', landingGearAngle);
    landingGear2->setRotation('z', -landingGearAngle); // Mirror for right side
}

// -----------------------------------------------------------------------------------------
// Animation Method 3: Animate plane flying in pattern (Independent animation)
// -----------------------------------------------------------------------------------------
void Composite2::animateFlightPattern(float deltaTime)
{
    // Update flight angle for figure-8 pattern
    flightAngle += deltaTime * 30.0f; // 30 degrees per second
    if (flightAngle > 360.0f) flightAngle -= 360.0f;
    
    // Calculate figure-8 flight pattern
    float x = flightRadius * sin_d(flightAngle);
    float z = flightRadius * sin_d(2.0f * flightAngle) * 0.5f; // Half amplitude for figure-8
    float y = flightHeight + 2.0f * sin_d(flightAngle * 0.5f); // Slight altitude variation
    
    // Calculate banking angle based on turn rate
    float bankAngle = 15.0f * sin_d(2.0f * flightAngle); // Bank into turns
    
    // Set position and orientation
    setPosition(x, y, z);
    setRotation('y', flightAngle + 90.0f, 'z', bankAngle); // Face movement direction and bank
}

// -----------------------------------------------------------------------------------------
// Reset all animations to initial state
// -----------------------------------------------------------------------------------------
void Composite2::resetAnimations()
{
    propellerRotation = 0.0f;
    landingGearAngle = 0.0f;
    flightAngle = 0.0f;
    
    // Reset positions and rotations
    setPosition(0, flightHeight, 0);
    setRotation('y', 0, 'z', 0);
    
    // Reset propeller rotation
    propeller->setRotation('x', 0);
    
    // Reset landing gear positions (extended)
    landingGear1->setRotation('z', 0);
    landingGear2->setRotation('z', 0);
}