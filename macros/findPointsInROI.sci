// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [out] = findPointsInROI(s,ROI)
	//	Find points within a ROI
	//
	//	Calling Sequence
	//	indices = findPointsInROI(s,ROI)
	//
	//	Parameters
	//	s : pointCloud object
	//	ROI : 3x2 matrix defining the ROI
	//	indices : Indices of points within the specified ROI
	//
	//	Description
	//	Function returns the indices of the points which lie within the ROI. 
	//
	//	Examples
	//	s1 = pcread('data/teapot.ply')
	//	ROI = findPointsInROI(s1,[-1,1;-1,1;-1,1]);
	//	s2 = select(s1,ROI)
	//	pcshowpair(s1,s2)
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1
		error(msprintf("Function expects only one output argument"))
	elseif rhs ~=2
		error(msprintf("Function expects only two input arguments."))
	end
	out = raw_findPointsInROI(s.Location,ROI)
endfunction
