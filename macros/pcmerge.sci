// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point] = pcmerge(s1,s2,gridSize)
	//	Merge two point clouds
	//
	//	Calling Sequence
	//	pointCloud = pcmerge(pointCloud1,pointCloud2,girdSize)
	//
	//	Parameters
	//	pointCloud1 : First point cloud
	//	pointCloud2 : Second point cloud
	//	gridSize : Parameter specifying the size of the grid used to filter the result
	//	pointCloud : Resultant point cloud after merging the two input point clouds
	//
	//	Description
	//	Merges the two input point clouds and applies a gird filter
	//
	//	Examples
	//	s1 = pcread('data/cycloidal.ply')
	//	s2 = pcread('data/teapot.ply')
	//	s = pcmerge(s1,s2,.1)
	//	pcshow(s.Location)	
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1
		error(msprintf("Function expects one output argument"))
	elseif rhs ~=3
		error(msprintf("Function expects three input arguments"))
	elseif gridSize <= 0
		error(msprintf("gridSize expected to be positive"))
	end
	[location count width height rgb xlimit ylimit zlimit dense]=raw_pcmerge(s1.Location,s1.Color,s1.is_dense,s1.Height,s2.Location,s2.Color,s2.is_dense,s2.Height,gridSize)
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
