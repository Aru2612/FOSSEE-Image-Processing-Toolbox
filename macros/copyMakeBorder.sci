// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [out] = copyMakeBorder(img, top, bottom, left, right, borderType, color_mat)
	//	Draw borders
	//
	//	Calling Sequence
	//	res = copyMakeBorder(src, top, bottom, left, right, borderType, color_mat)
	//
	//	Parameters
	//	src : Source image on which border is to be drawn
	//	top : Number of pixels to be extapolated to the top of the image
	//	bottom : Number of pixels to be extapolated to the bottom of the image
	//	left : Number of pixels to be extapolated to the left of the image
	//	right : Number of pixels to be extapolated to the right of the image
	//	borderType : The type of the border to be drawn.
	//	color_mat : RGB matrix denoting the color scheme of the border
	//	res : Resulting image after the border is drawn
	//	
	//	Description
	//	The function draws a border of the specified border type
	//
	//	Examples
	//	img = imread('images/lena.jpeg');
	//	res = copyMakeBorder(img,100,100,100,100,'BORDER_WRAP',[0,0,0]);
	//	imshow(res)
	//
	//	Authors
	//	Ebey Abraham
	img = mattolist(img)
	res = raw_copyMakeBorder(img, top, bottom, left, right, borderType, color_mat)
	channel = size(res)
	for i = 1:channel
		out(:,:,i) = res(i)
	end
	out = double(out)
endfunction
