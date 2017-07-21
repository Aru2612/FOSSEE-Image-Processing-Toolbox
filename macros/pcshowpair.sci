// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function pcshowpair(pc1,pc2)
	//	Display two point clouds
	//
	//	Calling Sequence
	//	pcshowpair(s1,s2)
	//
	//	Parameters
	//	s1 : First point cloud
	//	s2 : Second point cloud
	//
	//	Description
	//	Displays two point clouds together to visualize their difference. The first point cloud is displayed in magenta color and the second point cloud is displayed in green.
	//
	//	Examples
	//	s1 = pcread('data/teapot.ply')
	//	s2 = pcread('data/sphere.ply')
	//	pcshowpair(s1,s2)
	//	
	//	Authors
	//	Ebey Abraham	
	if type(pc1) ~= 17
		error(msprintf('Argument #1 should be pointCloud object'))
	elseif type(pc2) ~= 17
		error(msprintf('Argument #2 should be pointCloud object'))	
	end
	pc1_points = pc1.Location
	pc2_points = pc2.Location
	pcshow(pc1_points,'scilabmagenta2')
	pcshow(pc2_points,'scilabgreen2')
endfunction
