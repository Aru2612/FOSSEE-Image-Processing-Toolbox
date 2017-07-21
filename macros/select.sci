// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point] = select(s,indices)
	//	Select points by index
	//
	//	Calling Sequence
	//	pointCloud = select(s,indices)
	//
	//	Parameters
	//	s : pointCloud object
	//	indices : 1xN matric specifying the indices of the points to select
	//	pointCloud : Resulting point cloud with the selected points
	//
	//	Description
	//	Returns point cloud with only the points specified by the input indices
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
		error(msprintf("Function expects only two input arguments"))
	end
	[location count width height rgb xlimit ylimit zlimit dense]=raw_select(s.Location,s.Color,s.is_dense,indices,s.Height)
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
