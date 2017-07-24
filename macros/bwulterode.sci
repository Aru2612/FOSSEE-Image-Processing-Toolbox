// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Vinay Bhat, Ebey Abraham
// Email: toolbox@scilab.in
function [dstImg] = bwulterode(srcImg)
	//	Ultimate erosion 
	//
	//	Calling Sequence
	//	imgOut = bwulterode(imgIn)
	//
	//	Parameters
	//	imgIn : Binary input image
	//	imgOut : Output image after erosion
	//
	//	Description
	//	Ultimate erosion is the regional maxima of the regional transform of the compliment of the input image imgIn.	
	//
	//	Examples
	//	img = imread('images/water_thresh.png');
	//	res = bwulterode(img);
	//	imshow(res)
	//
	//	Authors
	//	Vinay Bhat
	//	Ebey Abraham
	srcMat = mattolist(srcImg)
	out = raw_bwulterode(srcMat)
	channels = size(out)
	for i = 1:channels
		dstImg(:,:,i) = out(i)
	end
endfunction
