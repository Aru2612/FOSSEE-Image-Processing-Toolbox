//Author: Ebey Abraham
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

  int opencv_drawContours(char *fname, unsigned long fname_len)
  {
    SciErr sciErr;
    int intErr = 0;
    int *piAddrChild = NULL;
    int *piAddr1 = NULL;
    int *piAddr2 = NULL;
    int *piAddr3 = NULL;
    int *piAddr4 = NULL;
    int *piAddr5 = NULL;
    int *piAddr6 = NULL;

    double contourIdx = 0;
    double *color_mat = NULL;
    double thickness = 1;
    double linetype = 8;

    int num = 0;
    int iRows = 0;
    int iCols = 0;

    CheckInputArgument(pvApiCtx,4,6);
    CheckOutputArgument(pvApiCtx,1,1);
    int args = *getNbInputArgument(pvApiCtx);

    try
    {
      //Retrieving argument #1 (image)
      Mat temp,src;
      retrieveImage(temp,1);
      temp.convertTo(src,CV_8UC3);

      //Retrieving argument #2 (contours)
      sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr2);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      sciErr = getListItemAddress(pvApiCtx,piAddr2,1,&piAddrChild);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      //Number of contours
      sciErr = getListItemNumber(pvApiCtx,piAddr2,&num);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      vector< vector<Point> > contours(num);
      Point p;

      for(int i=0;i<num;i++)
      {
          double *arr = NULL;
          sciErr = getMatrixOfDoubleInList(pvApiCtx,piAddr2,i+1,&iRows,&iCols,&arr);
          if(sciErr.iErr)
          {
            printError(&sciErr,0);
            return 0;
          }
          for(int j=0;j<iRows;j++)
          {
            p.x = *(arr + j + 0);
            p.y = *(arr + j + iRows);
            contours[i].push_back(p);
          }
      }

      //Retrieving argument #3 (Contour Index)
      sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      intErr = getScalarDouble(pvApiCtx,piAddr3,&contourIdx);
      if(intErr)
      {
        return intErr;
      }

      //Retrieving argument #4 (Color)
      sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr4,&iRows,&iCols,&color_mat);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      Scalar color(*(color_mat + 2),*(color_mat + 1),*(color_mat + 0));

      if(args == 5)
      {
        //Retrieving argument #5 (Thickness)
        sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          return 0;
        }
        intErr = getScalarDouble(pvApiCtx,piAddr5,&thickness);
        if(intErr)
        {
          return intErr;
        }
      }

      if(args == 6)
      {
        //Retrieving argument #6 (Line Type)
        sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          return 0;
        }
        intErr = getScalarDouble(pvApiCtx,piAddr6,&linetype);
        if(intErr)
        {
          return intErr;
        }
      }

      vector<Vec4i> hierarchy;

      drawContours( src, contours, contourIdx-1, color, thickness, linetype, hierarchy );
      string tempstring = type2str(src.type());
      char *checker;
      checker = (char *)malloc(tempstring.size() + 1);
      memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
      returnImage(checker,src,1);
      free(checker);

      AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
      ReturnArguments(pvApiCtx);

    }
    catch(cv::Exception& e)
    {
      const char* err = e.what();
      Scierror(999,"%s",err);
    }

    return 0;
  }
}
