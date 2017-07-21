// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Priyanka Hiranandani, Ebey Abraham
// Email: toolbox@scilab.in
function output_curve = approxpolyDP(input_curve, epsilon, closed)
	//	Approximates a polygonal curve(s) with the specified precision.
	//	
	//	Calling Sequence
	//	approxCurve = approxpolyDP(inputCurve, epsilon, closed)
	//
	//	Parameters
	//	inputCurve : Input vector of a 2D point
	//	epsilon :  Parameter specifying the approximation accuracy. This is the maximum distance between the original curve and its approximation.	
	//	closed : If true, the approximated curve is closed (its first and last vertices are connected). Otherwise, it is not closed.
	//	approxCurve : Result of the approximation.
	//
	//	Description
	//	The functions approxPolyDP approximate a curve or a polygon with another curve/polygon with less vertices so that the distance between them is less or equal to the specified precision.
	//	It uses the Douglas-Peucker algorithm .
	//
	//	Examples
	//	img = imread('images/approx.jpg');
	//	gray = cvtColor(img,'CV_BGR2GRAY');
	//	thresh = threshold(gray,100,255,'THRESH_BINARY');
	//	contours = findContours(thresh,1,2,0,0);
	//	//Draw contours in red
	//	for i =1:size(contours)
	//		img = drawContours(img,contours,i,[255,0,0],2);
	//	end
	//	approx = list();
	//	//Draw approximated curves in blue
	//	for i =1:size(contours)
	//		epsilon = 0.1*arcLength(contours(i),'True');
	//		approx(i) = approxpolyDP(contours(i),epsilon,'True');
	//		img = drawContours(img,approx,i,[0,0,255],2);
	//	end
	//	imshow(img)
	//
	//	Authors
	//	Priyanka Hiranandani
	//	Ebey Abraham
	output_curve = raw_approxpolyDP(input_curve, epsilon, closed)	
endfunction
