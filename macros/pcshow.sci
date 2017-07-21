// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Ebey Abraham
// Email: toolbox@scilab.in
function pcshow(mat,varargin)
	//	Display point cloud
	//
	//	Calling Sequence
	//	pcshow(XYZ,C)
	//
	//	Parameters
	//	XYZ : Mx3 matrix specifying the points in the point cloud
	//	C : Matrix or string defining the color map
	//
	//	Description
	//	Function displays a point cloud object
	//
	//	Examples
	//	s = pcread('data/teapot.ply')
	//	pcshow(s.Location,'red')
	//	
	//	Authors
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	mat_size = size(mat)
	no_pts = mat_size(1)
	cols = mat_size(2)
	if cols ~= 3
		error(msprintf('Argument #1 should be a M*3 matrix'))
	end
	x = mat(1:no_pts)
	y = mat(no_pts+1:2*no_pts)
	z = mat(2*no_pts+1:3*no_pts)
	drawlater()
	xgrid(color(200,200,200),1,1)
	if rhs == 1
		param3d(x, y, z, alpha = 55, theta = 55)
		p = gce();
		p.line_mode = 'off';
		p.mark_mode = 'on';
	elseif rhs == 2
		if type(varargin(1)) == 10
			param3d(x, y, z, alpha = 55, theta = 55)
			p = gce();
			p.line_mode = 'off';
			p.mark_mode = 'on';
			p.mark_style = 0
			p.thickness = 3
			p.mark_foreground = color(varargin(1))
		elseif type(varargin(1)) == 1
			rgb_mat = varargin(1)
			s = size(rgb_mat)
			rows = s(1)
			cols = s(2)
			if rows == 1 & cols == 3 
				if rgb_mat >= [0,0,0] & rgb_mat <= [255,255,255]
					//rgb_mat = varargin(1) * 255
					param3d(x, y, z, alpha = 55, theta = 55)
					p = gce();
					p.line_mode = 'off';
					p.mark_mode = 'on';
					p.mark_style = 0
					p.thickness = 3
					p.mark_foreground = color(rgb_mat(1),rgb_mat(2),rgb_mat(3))
				else
					error(msprintf('Element out of range 0.0 <= value <=255.0'))
				end
			elseif rows == no_pts & cols == 3
				for i=1:no_pts
					param3d(x(i), y(i), z(i), alpha = 55, theta = 55)
					p = gce()
					p.line_mode = 'off';
					p.mark_mode = 'on';
					p.mark_style = 0
					p.thickness = 3
					r = rgb_mat(i)
					g = rgb_mat(i+rows)
					b = rgb_mat(i+2*rows)
					if [0,0,0]<=[r,g,b] & [r,g,b]<=[255,255,255]	
						p.mark_foreground = color(r,g,b)
					else 
						error(msprintf('Element out of range 0.0 <= value <=255.0'))
					end
				end
			else
				error(msprintf('No of rows equal to 1 or equal to number of points'))
			end
		elseif type(varargin(1)) == 17
			i_mat = varargin(1)
			s = size(i_mat)
			size_mat = s(1) * s(2)
			if size_mat == no_pts
				for i=1:no_pts
					param3d(x(i), y(i), z(i), alpha = 55, theta = 55)
					p = gce()
					p.line_mode = 'off';
					p.mark_mode = 'on';
					p.mark_style = 0
					p.thickness = 3
					r = i_mat(i)
					g = i_mat(i+size_mat)
					b = i_mat(i+2*size_mat)
					p.mark_foreground = color(r,g,b)
				end
			else
				error(msprintf('M * N should be equal to number of points'))
			end
		else
			error(msprintf('Invalid argument #2'))
		end
	elseif rhs > 2
		error(msprintf('Too many input arguments'))
	end	 
	drawnow()
endfunction
