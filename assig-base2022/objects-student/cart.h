// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// cart.h
//
// This file declares the class for cart objects, based on the
// generic 3D object


#ifndef _cart_H
#define _cart_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"

#include "cylinder.h"
#include "tcube.h"
#include "torus.h"
#include "texture.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class cart : public object3d
{
	public:
						cart();
		virtual void hide();
		virtual void show();
private:
    cylinder * pole1,*pole2;
    tcube *bottom,*front,*side1,*side2;
    torus *wheel1,*wheel2;
    texture *wood;

};


#endif // _cart_H

