// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [out] = drawContours(img,contours,contouridx,rgb,varargin)
	//	Draw contours
	//
	//	Calling Sequence
	//	res = drawContours(dst, contours, contourIdx, rgbMat, thickness = 1,linetype = 8)
	//
	//	Parameters
	//	dst : Image on which the contours have to be marked
	//	contours : List of contour, where each element is a Nx2 matrix of contour points
	//	contourIdx : 1-based index of the contour which is to be drawn
	//	rgbMat : 1x3 matrix defining the RGB values of the marking
	//	thickness : Thickness of the lines the contours are drawn with, negative values will fill the contour. Optional argument with default value as 1.
	//	linetype : Type of line used to draw the contour. Optional argument with default value as 8.
	//	res : Output image with the contour marked
	//
	//	Description
	//	Draws the contour specified by the contour index on the destination image. 
	//
	//	Examples
	//	//Read an 3-channel image
	//	img = imread('images/coin_thresh.png');
	//	//Convert to single channel grayscale to find contours
	//	gray = cvtColor(img,'CV_BGR2GRAY');
	//	contours = findContours(gray,3,2,0,0);
	//	//Draw all contours
	//	for i = 1:size(contours)
	//	img = drawContours(img,contours,i,[0,0,255]);
	//	end
	//	imshow(img) 	
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	[r c] = size(rgb)
	if lhs ~= 1
		error(msprintf("Function returns only one parameter"))
	elseif rhs < 4
		error(msprintf("Function takes at least 4 arguments"))
	elseif rhs > 6
		error(msprintf("Function takes at most 6 arguments"))
	elseif r~=1 | c~=3
		error(msprintf("Color should be a 1x3 matrix")) 
	end
	img = mattolist(img)
	if rhs == 4
		res = raw_drawContours(img,contours,contouridx,rgb)
	elseif rhs == 5
		res = raw_drawContours(img,contours,contouridx,rgb,varargin(1))
	elseif rhs == 6
		res = raw_drawContours(img,contours,contouridx,rgb,varargin(1),varargin(2))
	end
	channels = size(res)
	for i = 1:channels
		out(:,:,i) = res(i)
	end
	out = double(out)
endfunction
