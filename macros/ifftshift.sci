// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Tess Zacharias, Ebey Abraham
// Email: toolbox@scilab.in
function new_image = ifftshift(image)
	//	Inverse FFT
	//
	//	Calling Sequence
	//	res = ifftshift(img)
	//	
	//	Parameters
	//	img : Source Image
	//	res : Resultant image after applying inverse FFT shift
	//
	//	Description
	//	The function swaps the first quadrant with the third and the second quadrant with the fourth.
	//
	//	Examples
	//	img = imread('images/lena.jpeg');
	//	res = ifftshift(img);
	//	imshow(res)
	//
	//	Authors
	//	Tess Zacharias
	//	Ebey Abraham
	image_list = mattolist(image)
	out = raw_ifftshift(image_list)
	sz = size(out)
	for i = 1 : sz
		new_image(:, :, i) = out(i)
	end		
endfunction
