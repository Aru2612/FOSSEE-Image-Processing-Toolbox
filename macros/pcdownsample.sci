// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function [point] = pcdownsample(s,filterType,param)
	//	Downsample a point cloud
	//
	//	Calling Sequence
	//	pointCloudOut = pcdownsample(pointCloudIn, 'random', percentage)
	//	pointCloudOut = pcdownsample(pointCloudIn, 'gridAverage', gridStep)
	//
	//	Parameters
	//	pointCloudIn : Input point cloud
	//	pointCloudOut : Output point cloud
	// 'random' : Downsample cloud using random sampling
	//	percentage : Percentage of input point cloud that should be present in ouput cloud
	//	'gridAverage' : Downsample using grid filter
	//	gridStep : Size of grid
	//
	//	Description
	//	Downsamples a point cloud using the specified method
	//
	//	Examples
	// //Downsample using random sampling
	// s = pcread('data/teapot.ply');
	// res = pcdownsample(s,'random',10)
	//	pcshowpair(s,res)
	// 
	//	//Downsample using box grid
	// s = pcread('data/teapot.ply');
	// res = pcdownsample(s,'random',10)
	//	pcshowpair(s,res)
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1
		error(msprintf("Function expects one output argument"))
	elseif rhs ~=3
		error(msprintf("Function expects three input arguments"))
	elseif param <= 0
		error(msprintf("Arg #3 expected to be positive"))
	end
	
	if filterType == 'random'
		c = 1	
	elseif filterType == 'gridAverage'
		c = 2
	else
		error(msprintf("Wrong value for arg #2"))
	end
	
	[location count width height rgb xlimit ylimit zlimit dense]=raw_pcdownsample(s.Location,s.Color,s.is_dense,s.Height,int32(c),param)
	point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit);
endfunction
