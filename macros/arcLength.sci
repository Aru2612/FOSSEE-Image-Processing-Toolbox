// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Priyanka Hiranandani, Ebey Abraham
// Email: toolbox@scilab.in
function result = arcLength(input_curve, closed)
	//	Calculates the perimeter of a closed contour or the curve length.
	//
	//	Calling Sequence
	//	res = arcLength(inputCurve, closed)
	//
	//	Parameters
	//	inputCurve : Input matrix points
	//	closed : Flag indicating whether the curve is closed or not.
	//	res : arc length of the curve
	//
	//	Description
	//	The function computes the closed contour perimeter or the curve length.
	//
	//	Examples
	//	img = imread('images/apple.png');
	//	contours = findContours(img,3,2,0,0);
	//	arc = list();
	//	for i = 1:size(contours)
	//		arc(i) = arcLength(contours(i),'True');
	//		printf("Contour #%d Arclength = %f\n",i,arc(i))
	//	end
	//
	//	Authors
	//	Priyanka Hiranandani
	//	Ebey Abraham	
	result = raw_arcLength(input_curve, closed)	
endfunction
