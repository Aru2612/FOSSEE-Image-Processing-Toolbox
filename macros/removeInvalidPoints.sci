// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point,indices] = removeInvalidPoints(s)
	//	Remove invalid points from a point cloud
	//
	//	Calling Sequence
	//	[OutputPointCloud,indices] = removeInvalidPoints(InputPointCloud)
	//	
	//	Parameters
	//	InputPointCloud : Input point cloud object which may contain invalid points
	//	OutputPointCloud : Resultant point cloud after removing invalid points
	//	indices : Indices of the valid points in input point cloud object
	//
	//	Description
	//	Return a point cloud object after Inf and Nan points from the input point cloud object
	//
	//	Examples
	//	//The first point in the file is Inf and the second point is NaN
	//	s = pcread('data/sphere.ply')
	//	[pt indices] = removeInvalidPoints(s);
	//	pt
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 2
		error(msprintf("Function expects only two output argument"))
	elseif rhs ~=1
		error(msprintf("Function expects only one input argument"))
	end
	[location count width height rgb xlimit ylimit zlimit dense indices]=raw_removeInvalidPoints(s.Location,s.Color,s.is_dense,s.Height)
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
