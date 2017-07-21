// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Tess Zacharias, Ebey Abraham
// Email: toolbox@scilab.in
function [out] = bwconvhull(image,varargin)
	//	Generate convex hull image from binary image
	//
	//	Calling Sequence
	//	hull = bwconvhull(img)
	//	hull = bwconvhull(img,'Object',n)
	//
	//	Parameters
	//	img : 2-D array of points in vector or mask form
	//	'Object' : Compute the convex hull of each connected component of 'img' individually. 'hull' contains the convex hulls of each connected component.
	//	n : Connectivity
	//
	//	Description
	//	Generate convex hull image from binary image either taking individual connected components or taking all the components together.	
	//
	//	Examples
	//	img = imread('images/coin_thresh.png');
	//	img = cvtColor(img,'CV_BGR2GRAY');
	//	res1 = bwconvhull(img);
	//	imshow(res1)
	//	res2 = bwconvhull(img,'Object',4);
	//	figure;
	//	imshow(res2)
	//
	//	Authors
	//	Ebey Abraham
	//	Tess Zacharias
	[lhs rhs] = argn(0)
	if lhs > 1
		error(msprintf("Too many output arguments. Returns only 1 argument."))
	elseif rhs ~= 1 & rhs ~= 3
		error(msprintf("Functon accepts either 1 or 3 arguments."))
	end
	image = mattolist(image)
	if rhs == 1
		ans = raw_bwconvhull(image)
	else
		ans = raw_bwconvhull(image, varargin(1), varargin(2))
	end
	channel = size(ans)
	for i = 1 : channel
		out(:,:,i) = ans(i)
	end
	out = double(out)
endfunction
	
	
