// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Sukul Bagai, Abhilasha Sancheti, Ebey Abraham
// Email: toolbox@scilab.in
function [out]=clipLine(width, height, x1 , y1 , x2,y2)
	//	Clips the line against the image rectangle.
	//
	//	Calling Sequence
	//	res = clipline(width, height, x1, y1, x2, y2)
	//
	//	Parameters
	//	width : width of the image
	//	height : height of the image
	//	x1 : x-cordinate of first end of the line
	//	y1 : y-cordinate of first end of the line
	//	x2 : x-cordinate of second end of the line
	//	y2 : y-cordinate of second end of the line
	//	res : boolean output value
	//
	//	Description
	//	The functions clipLine calculate a part of the line segment that is entirely within the specified rectangle. 
	//	They return false if the line segment is completely outside the rectangle. Otherwise, they return true . 
	//	
	//	Examples
	//	clipLine(10,10,1,2,5,9)
	//	//will give True
	//
	//	clipLine(10,10,28,25,26,12)
	//	//will give False
	//
	//	Authors
	//	Sukul Bagai
	//	Abhilasha Sancheti
	//	Ebey Abraham 
     out=raw_clipLine(width, height, x1 , y1 , x2,y2);
endfunction;
