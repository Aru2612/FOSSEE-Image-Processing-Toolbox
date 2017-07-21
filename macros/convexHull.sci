// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Sukul Bagai, Abhilasha Sancheti, Ebey Abraham
// Email: toolbox@scilab.in
function [out]=convexHull(pstData,clkwise,returnpoints)
	//	Finds the convex hull of a point set.
	//
	//	Calling Sequence
	//	hull = canvexHull(points, clockwise, returnPoints)
	//
	//	Parameters
	//	points : Input 2D point set
	//	clockwise : Orientation flag. If it is 1, the output convex hull is oriented clockwise. Otherwise, it is oriented counter-clockwise. The assumed coordinate system has its X axis pointing to the right, and its Y axis pointing upwards.	
	//	returnPoints : Operation flag. In case of a matrix, when the flag is true, the function returns convex hull points. Otherwise, it returns indices of the convex hull points.
	//	hull : Output 2D point set containing the convex hull points
	//
	//	Description
	//	The functions find the convex hull of a 2D point set.
	//
	//	Examples
	//	img = imread('images/coin_thresh.png');
	//	gray = cvtColor(img,'CV_BGR2GRAY');
	//	//find the contours points
	//	contours = findContours(gray,3,2,0,0);
	//	//find the convex hull of the contour points
	//	hull = list();
	//	for i = 1:size(contours)
	//		hull(i) = convexHull(contours(i),1,1);
	//	end
	// //mark the hulls
	//	for i = 1:size(hull)
	//	img = drawContours(img,hull,i,[0,0,255]);
	//	end
	// imshow(img)
	//
	//	Authors
	//	Abhilasha Sancheti
	//	Sukul Bagai
	//	Ebey Abraham	
	out=raw_convexHull(pstData,clkwise,returnpoints);       
endfunction;
