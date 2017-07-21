// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Priyanka Hiranandani, Ebey Abraham
// Email: toolbox@scilab.in
function result = borderInterpolate(p, len, borderType)
	//	Computes the location of the donor for an extrapolated pixel.
	//
	//	Calling Sequence
	//	pos = borderInterpolate(p, len, borderType)
	//
	//	Parameters
	//	p : Coordinate of the extrapolated pixel along one of the axes, likely <0 or >= len .
	//	len : Length of the image along the corresponding axis.
	//	borderType : Border type, one of the border types , except for BORDER_TRANSPARENT and BORDER_ISOLATED .
	//	pos : cordinate of donor pixel
	//
	//	Description
	//	The function returns the coordinate of a donor pixel of the specified extrapsolated pixel when using the specified extrapolation border mode.
	//
	//	Examples
	//	pos = borderInterpolate(-10,255,'BORDER_WRAP')
	//
	//	pos = borderInterpolate(350,255,'BORDER_REFLECT_101')
	//
	//	Authors
	//	Priyanka Hiranandani
	//	Ebey Abraham	
	result = raw_borderInterpolate(p, len, borderType)
endfunction
