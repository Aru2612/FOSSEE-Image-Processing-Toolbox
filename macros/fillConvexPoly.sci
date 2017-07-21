// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Abhilasha Sancheti, Shubheksha Jalan, Ebey Abraham
// Email: toolbox@scilab.in
function [out] = fillConvexPoly(img,pstData,npts,r_value,g_value,b_value,linetype,shift)
	//	Draw a filled convex polygon
	//
	//	Calling Sequence
	//	res = fillConvexPoly(src, points, npoints, R, G, B, linetype, shift)
	//
	//	Parameters
	//	src : Image
	//	points : Matrix of 2D cordinates defining the vertices of the polygon
	//	npoints : Number of vertices
	//	R, G, B : RGB values of the filled polygon
	//	linetype : Type of polygon boundaries
	//	shift : Number of fractional bits in vertex cordinates
	//	res : Output image with the filled polygon
	//
	//	Description
	//	Draws a filled convex polygon defined by the specified cordinates on the source image.
	//	
	//	Examples
	//	// generates a random pattern
	//	for i=1:3
	//		img(:,:,i) = ones(255,255);
	//	end
	//	rand('seed',getdate('s'));
	//	for i=1:10
	//		// draw triangles
	//		pts = rand(3,2) * 200;
	//		color = rand(1,3) * 200;
	//		img = fillConvexPoly(img,pts,3,color(1),color(2),color(3),8,0);
	//		// draw squares
	//		pts = rand(4,2) * 300;
	//		color = rand(1,3) * 200;
	//		img = fillConvexPoly(img,pts,3,color(1),color(2),color(3),8,0);
	//		// draw pentagons
	//		pts = rand(5,2) * 500;
	//		color = rand(1,3) * 200;
	//		img = fillConvexPoly(img,pts,3,color(1),color(2),color(3),8,0);
	//	end
	//	imshow(img)
	//	
	//	Authors
	//	Abhilasha Sancheti
	//	Shubheksha Jalan
	//	Ebey Abraham
	image = mattolist(img);
	a = raw_fillConvexPoly(image,pstData,npts,r_value,g_value,b_value,linetype,shift)
	d = size(a);
	for i=1:d
		out(:,:,i) = a(i);
	end
endfunction
