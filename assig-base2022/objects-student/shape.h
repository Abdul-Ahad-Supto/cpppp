// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2018
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: HXP
//
// shape.h
//
// This file declares the class for shape objects, based on the
// generic 3D object


#ifndef _shape_H
#define _shape_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "sphere.h"
#include "cube.h"


// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class shape : public object3d
{
public:
						shape();
		virtual void	hide(void);
		virtual void	show(void);

private:
	sphere* head,*body,*left_arm,*right_arm;

};


#endif // _shape_H

