// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Sukul Bagai, Ebey Abraham
// Email: toolbox@scilab.in
function [out]=rectangle(input_image , x_coordinate_of_point1 , y_coordinate_point1, x_coordinate_of_point2 , y_coordinate_point2 , r_value,g_value,b_value,thickness,linetype,shift)
         //	Draws a simple, thick, or filled up-right rectangle.
         //
         //	Calling Sequence
         //	res = rectangle(src,x1,y1,x2,y2,R,G,B,lineType,thickness,shift)
         //
         //	Parameters
         //	src : image
         //	x1 : x-cordinate of top left corner of rectangle
         //	y1 : y-cordinate of top left corner of rectangle
         //	x2 : x-cordinate of bottom right corner of rectangle
         //	y2 : y-cordinate of bottom right corner of rectangle
         //	R,G,B : rgb value of rectangle
         //	lineType : type of the line
         //	thickness : line thickness
         //	shift : Number of fractional bits in the point coordinates
         //
         //	Description
         //	The function rectangle draws a rectangle outline or a filled rectangle whose two opposite corners are (x1,y1) and (x2,y2)
         //
         //	Examples
         //	img = imread('images/coin_thresh.png');
         //	gray = cvtColor(img,'CV_BGR2GRAY');
         //	contours = findContours(gray,3,2,0,0);
         //	for i = 1:size(contours)
         //		rect = boundingRect(contours(i));
         //		x1 = rect(3);
         //		y1 = rect(4);
         //		x2 = x1 + rect(1);
         //		y2 = y1 + rect(2);
         //		img = rectangle(img,x1,y1,x2,y2,0,0,255,2,8,0);
         //	end
         //	imshow(img)
         //
         //	Authors
         //	Sukul Bagai
         //	Ebey Abraham
         input_image1=mattolist(input_image);
         a=raw_rectangle(input_image1 , x_coordinate_of_point1 , y_coordinate_point1, x_coordinate_of_point2 , y_coordinate_point2 , r_value,g_value,b_value,thickness,linetype,shift);
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end 
endfunction;
