/********************************************************
Function   :bwconvexhull
Syntax     :B=bwconvexhull(A)
            B=bwconvexhull(A,"Object",n)
     n :4 or 8
Author: Tess  Zacharias, Ebey Abraham
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

  int opencv_bwconvhull(char *fname, unsigned long fname_len)
  {

    SciErr sciErr;
    int intErr = 0;
    int *piAddr2  = NULL;
    int *piAddr3  = NULL;
    char* pstData = NULL;
    int iRet    = 0;
    double n;
    //checking input argument
    CheckInputArgument(pvApiCtx, 1, 3);
    CheckOutputArgument(pvApiCtx, 1, 1) ;

    try
	{
	 Mat threshold_output;

    retrieveImage(threshold_output, 1);

    threshold_output.convertTo(threshold_output,CV_8UC1);

    int r = threshold_output.rows;
    int c = threshold_output.cols;

    for (int i = 0; i < r; i++)
    {
      for (int j = 0; j < c; j++)
      {
        int val = (int)(threshold_output.at<uchar>(i,j));
        if (!(val == 0 || val == 1 || val == 255))
        {
          Scierror(999,"Function takes only binary images.");
          return 0;
        }
      }
    }

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    int contours_size = contours.size();
    vector< Point > contour_points;

    //Get all contour points into a single vector
    for(size_t i = 0; i < contours_size ; i++)
    {
      contour_points.insert(contour_points.end(),contours[i].begin(),contours[i].end());
    }

    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    Scalar color = Scalar(255,255,255);
    /* if only 1 input argument line connectvity n will take default value 8 */
    if(nbInputArgument(pvApiCtx)==1)
    {
      vector< vector<Point> >hull_points(1);
      //Find convex hull of the contours points (Union)
      convexHull(contour_points,hull_points[0],false);
      drawContours( drawing, hull_points, 0 , color, -1);
    }
    else if(nbInputArgument(pvApiCtx)==3)
    {
      /* retrieve second argument  */
      sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
	    if(sciErr.iErr)
	    {
		    printError(&sciErr, 0);
		    return 0;
	    }
        if(isStringType(pvApiCtx, piAddr2))
	      {
          if(isScalar(pvApiCtx, piAddr2))
	        {
	          iRet = getAllocatedSingleString(pvApiCtx, piAddr2, &pstData);
          }
        }
        else
        {
          sciprint(" The second argument should be string  ");
          return 0;
        }
        if(strcasecmp(pstData,"Object")==0)
        {
          /*retrieve third argument */
          sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
          if (sciErr.iErr)
          {
            printError(&sciErr, 0);
            return 0;
          }
          intErr = getScalarDouble(pvApiCtx, piAddr3, &n);
          if(intErr)
          {
            return intErr;
          }
         // The error checks for the function
          if((n!=4)&&(n!=8))
          {
            sciprint("The value of line connectivity must be 8 or 4");
            return 0;
          }

          vector< vector<Point> >hull_points(contours_size);

          for(size_t i =0; i < contours_size; i++)
          {
            convexHull( Mat(contours[i]), hull_points[i], false );
            drawContours( drawing, hull_points, i , color,-1 , n );
          }

        }
        else
        {
          sciprint(" The second argument must be 'Object'");
          return 0;
        }
      }
    string tempstring = type2str(drawing.type());
    char *checker;
    checker = (char *)malloc(tempstring.size() + 1);
    memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
    returnImage(checker,drawing,1);
    free(checker);
    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);
	}
	catch(cv::Exception& e)
	{
  		const char* err=e.what();
  		sciprint("%s",err);
	}

    return 0;

 }
}
