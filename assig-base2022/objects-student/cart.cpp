// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// cart.cpp
//
// This file defines the class for cart objects



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "cart.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
    //cylinder * pole1,*pole2;
    //tcube *bottom,*front,*side1,*side2;
    //torus *wheel1,*wheel2;
    //texture *wood;
cart::cart()
{
	// Initialise the object's state
	setName("cart");
	wood=new texture("boxtex.jpg");
	bottom=new tcube;
	bottom->setTexture(wood);
	bottom->setParent(this);
	bottom->setDeformation(1.0,0.1,1.0);
	
	side1=new tcube;
	side1->setTexture(wood);
	side1->setDeformation(1.0,0.5,0.1);
	side1->setParent(bottom);
	side1->setPosition(0,0.4,-1.1);


	side2=new tcube;
	side2->setTexture(wood);
	side2->setDeformation(1.0,0.5,0.1);
	side2->setParent(bottom);
	side2->setPosition(0,0.4,1.1);

	front=new tcube;
	front->setTexture(wood);
	front->setParent(bottom);
	front->setDeformation(0.1,0.5,1.2);
	front->setPosition(1.1,0.4,0);
	
	pole1=new cylinder(100);
	pole1->setParent(bottom);
	pole1->setDeformation(0.1,2.0,0.1);
	pole1->setRotation('z',90);
	pole1->setPosition(-1.0,-0.2,-1);

	pole2=new cylinder(100);
	pole2->setParent(bottom);
	pole2->setDeformation(0.1,2.0,0.1);
	pole2->setRotation('z',90);
	pole2->setPosition(-1.0,-0.2,1);

	wheel1=new torus(5,5,0.5,0.1);
	wheel1->setParent(bottom);
	wheel1->setRotation('x',90);
	wheel1->setPosition(0,0,-1.3);

	wheel2=new torus(5,5,0.5,0.1);
	wheel2->setParent(bottom);
	wheel2->setRotation('x',90);
	wheel2->setPosition(0,0,1.3);
	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}

void cart::hide()
{
	bottom->hide ();
	pole1->hide();
	pole2->hide();
	front->hide();
	side1->hide();
	side2->hide();
	wheel1->hide();
	wheel2->hide();
}

void cart::show()
{
		bottom->show ();
		pole1->show();
		pole2->show();
		front->show();
		side1->show();
		side2->show();
		wheel1->show();
		wheel2->show();	
}


