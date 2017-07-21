// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point,varargout] = pcdenoise(s)
	//	Remove noise from point cloud
	//
	//	Calling Sequence
	//	pointCloudOut = pcdenoise(pointCloudIn)
	//	[pointCloudOut inliners outliners] = pcdenoise(pointCloudIn)
	//
	//	Parameters
	//	pointCloudIn : Input point cloud
	//	pointCloudOut : Output point cloud
	//	inliners : Indices of inliner points
	//	outliners : Indices of outliner points
	//
	//	Description
	//	Function removes noise from input point cloud
	//
	//	Examples
	// s = pcread('data/noise.ply');
	//	[res inliners outliners] = pcdenoise(s);
	// pcshowpair(s,res)	
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1 & lhs ~= 3
		error(msprintf("Function expects either one or three output arguments:%d",lhs))
	elseif rhs ~=1
		error(msprintf("Function expects only one input argument"))
	end
	if lhs == 1
		[location count width height rgb xlimit ylimit zlimit dense]=raw_pcdenoise(s.Location,s.Color,s.is_dense,s.Height)
	else
		[location count width height rgb xlimit ylimit zlimit dense inliners outliners]=raw_pcdenoise(s.Location,s.Color,s.is_dense,s.Height)
		varargout(1) = inliners
		varargout(2) = outliners
	end
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
