// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point] = pctransform(s,tform)
	//	Transform a point cloud
	//
	//	Calling Sequence
	//	pointCloudOut = pctransform(pointCloudIn, tform)
	//
	//	Parameters
	//	pointCloudIn : Input point cloud
	//	pointCloudOut : Output point cloud
	// tform : affine 3D object specifying the transformation
	//
	//	Description
	//	Returns a transformed point cloud
	//
	//	Examples
	// s = pcread('data/teapot.ply');
	//	A = [cos(%pi/4) sin(%pi/4) 0 0; ...
   //  	-sin(%pi/4) cos(%pi/4) 0 0; ...
   //	  	0 0 1 0; ...
   //  	0 0 0 1];
	//	tform = affine3d(A);
	//	s1 = pctransform(s,tform);
	//	pcshowpair(s,s1)
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1
		error(msprintf("Function expects only one output argument"))
	elseif rhs ~=2
		error(msprintf("Function expects only two input arguments"))
	end
	[location count width height rgb xlimit ylimit zlimit dense]=raw_pctransform(s.Location,s.Color,s.is_dense,s.Height,tform.T)
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
