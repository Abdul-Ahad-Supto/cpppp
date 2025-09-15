// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2018
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: HXP
//
// shape.cpp
//
// This file defines the class for shape objects



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "shape.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
	/*sphere* head,*body,*left_arm,*right_arm;*/
shape::shape()
{
	// Initialise the object's state
	setName("shape");
	body=new sphere(50);
	body->setDeformation(2.0,3.0,1.0);
	body->setColour(1.0,1.0,1.0);
	body->setParent(this);

	head=new sphere(50);
	head->setColour(1.0,1.0,1.0);
	head->setParent(body);
	head->setPosition(0,4.0,0.0);

	left_arm=new sphere(20);
	left_arm->setColour(1.0,1.0,0.0);
	left_arm->setParent(body);
	left_arm->setDeformation(2.0,0.2,0.2);
	left_arm->setPosition(1.0,2.0,0.0);
	left_arm->setOffset(2.0,0.0,0.0);
	left_arm->setRotation('z',-30);
	left_arm->setParent(body);

	right_arm=new sphere(20);
	right_arm->setColour(1.0,1.0,0.0);
	right_arm->setParent(body);
	right_arm->setDeformation(2.0,0.2,0.2);
	right_arm->setPosition(-1.0,2.0,0.0);
	right_arm->setOffset(-2.0,0.0,0.0);
	right_arm->setRotation('z',30);
	right_arm->setParent(body);

	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}

void shape::hide()
{
	head->hide();
	body->hide();
	right_arm->hide();
	left_arm->hide();
}

void shape::show()
{
	head->show();
	body->show();
	right_arm->show();
	left_arm->show();
}


