// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Sukul Bagai, Ebey Abraham
// Email: toolbox@scilab.in
function [rectMat]=boundingRect(points)
	//	Finds the minimal up-right bounding rectangle
	//
	//	Calling Sequence
	//	rectPts = boundingRect(points)
	//
	//	Parameters
	//	points : Input 2-D point set, stored in as a matrix.
	//	rectPts : Output array containing the width, height, x-cordinate and y-cordinate of the bounding rectangle in the same order
	//	
	//	Description
	//	The function calculates the minimal up-right bounding rectangle for a specified point set.
	//
	//	Examples
	//	pts = [1,1;3,4;5,6;10,10]
	//	rect_pts = boundingRect(pts)
	//
	//	img = imread('images/coin_thresh.png');
	//	gray = cvtColor(img,'CV_BGR2GRAY');
	//	contours = findContours(gray,3,2,0,0);
	//	for i = 1:size(contours)
	//		rect = boundingRect(contours(i));
	//		x1 = rect(3);
	//		y1 = rect(4);
	//		x2 = x1 + rect(1);
	//		y2 = y1 + rect(2);
	//		img = rectangle(img,x1,y1,x2,y2,0,0,255,2,8,0);
	//	end
	//	imshow(img)	
	//
	//	Authors
	//	Sukul Bagai
	//	Ebey Abraham
   	rectMat=raw_boundingRect(points);
endfunction
