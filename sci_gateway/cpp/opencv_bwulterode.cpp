/********************************************************
Author: Vinay Bhat, Ebey Abraham
********************************************************
Usage: return_image = bwulterode(input_image)
********************************************************/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
extern "C"
{
  	#include "api_scilab.h"
  	#include "Scierror.h"
  	#include "BOOL.h"
  	#include <localization.h>
  	#include "sciprint.h"
  	#include "../common.h"
  	void bwulterode_imreconstruct(Mat, Mat, Mat&);
  	int opencv_bwulterode(char *fname, unsigned long fname_len)
  	{
    		SciErr sciErr;
    		int intErr = 0;
    		int *piAddr = NULL;
    		//checking input argument
    		CheckInputArgument(pvApiCtx, 1, 1);
    		CheckOutputArgument(pvApiCtx, 1, 1);
    		try
    		{
      			// Get the input image from the Scilab environment
      			Mat gray_image, fin_image, m, image;
      			retrieveImage(gray_image, 1);
      			gray_image.convertTo(gray_image,CV_8UC1);
      			for (int i = 0; i < gray_image.rows; i++)
      			{
        			for (int j = 0; j < gray_image.cols; j++)
        			{
          				int val = (int)(gray_image.at<uchar>(i,j));
          				if (!(val == 0 || val == 1 || val == 255))
          				{
            					sciprint("Please enter binary image. Value = %d @ (%d, %d)",val,i,j);
            					return 0;
          				}
        			}
      			}
      			if (gray_image.type() != CV_8UC1)
      			{
        			Mat temp;
        			temp = gray_image.clone();
        			cvtColor(temp, gray_image, CV_BGR2GRAY);
      			}
      			distanceTransform(gray_image, image, CV_DIST_L2, DIST_MASK_5);
     			subtract(image, 1, gray_image);
      			bwulterode_imreconstruct(image, gray_image, m);
      			subtract(image, m, gray_image);
      			fin_image = gray_image * 255;
      			string tempstring = type2str(fin_image.type());
      			char *checker;
      			checker = (char *)malloc(tempstring.size() + 1);
      			memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
      			returnImage(checker, fin_image, 1);
			//Free Memory
      			free(checker);
      			//Assigning the list as the Output Variable
      			AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
      			//Returning the Output Variables as arguments to the Scilab environment
      			ReturnArguments(pvApiCtx);
    		}
    		catch(cv::Exception& e)
    		{
      			const char* err = e.what();
      			sciprint("%s",err);
    		}
    		return 0;

  	}
  	void bwulterode_imreconstruct(Mat g, Mat f, Mat& dest)
  	{
    		Mat m0, m1, m;
    		m1 = f;
    		do 
		{
      			m0 = m1.clone();
      			dilate(m0, m, Mat());
      			min(g, m, m1);
    		} while(countNonZero(m1 != m0) != 0);
    		dest = m1.clone();
  	}
}

/* ==================================================================== */
