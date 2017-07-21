// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Authors: Sukul Bagai, Abhilasha Sancheti, Shubheksha Jalan, Ebey Abraham
// Email: toolbox@scilab.in
function [out] = canny(input_image ,threshold1, threshold2, aperture , gradient)
	//	Find edges in the given image
	//
	//	Calling Sequence
	//	edge = canny(img_src,threshold1,threshold2,apertureSize,gradientFlag)
	//
	//	Parameters
	//	img_src : input image with either 3 or 4 channels
	//	threshold1 : first threshold for hysteresis procedure
	//	threshold2 : second threshold for hysteresis procedure
	// apertureSize : aperture size
	// gradientFlag : a flag, indicating whether a more accurate <latex> L_2 </latex> norm = <latex> \sqrt{{\frac{dI}{dx}}^2 + {\frac{dI}{dy}}^2} </latex> should be used to calculate the image gradient magnitude ( L2gradient=true ), or whether the default <latex> L_1 </latex> norm = <latex> |\frac{dI}{dx}| + |\frac{dI}{dy}|  </latex>
	// edge : output image marked with the detected edges.
	//
	// Description
	// The function finds edges in the input image image and marks them in the output map edges using the Canny algorithm. 
	// The smallest value between threshold1 and threshold2 is used for edge linking.
	//	The largest value is used to find initial segments of strong edges.
	//
	//	Examples
	// //read input image
	//	img = imread('images/water_coins.jpg');
	//	//get edges
	// 	res = canny(img,100,255,3,1);
	//	//resulting image marked with the edges
	// 	imshow(res)
	//
	// Authors
	// Sukul Bagai
	//	Abhilasha Sancheti
	//	Shubheksha Jalan
	//	Ebey Abraham
	[lhs rhs] = argn(0)
	if lhs ~= 1
		error(msprintf("Function returns only 1 argument"))
	elseif rhs~=5
		error(msprintf("Function takes only 5 input arguments"))
	end
	input_image1 = mattolist(input_image)
	a = raw_canny(input_image1 ,threshold1, threshold2, aperture, gradient)
	dimension = size(a)
	for i = 1:dimension
		out(:,:,i) = a(i)
	end   
	out = double(out) 
endfunction
