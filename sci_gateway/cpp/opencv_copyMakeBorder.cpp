#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
extern "C"
{
  	#include "api_scilab.h"
  	#include "Scierror.h"
  	#include "BOOL.h"
  	#include <localization.h>
  	#include <sciprint.h>
  	#include "../common.h"
  	int opencv_copyMakeBorder(char *fname, unsigned long fname_len)
  	{
    		SciErr sciErr;
    		int intErr = 0;
    		int *piAddr1 = NULL;
    		int *piAddr2 = NULL;
    		int *piAddr3 = NULL;
    		int *piAddr4 = NULL;
    		int *piAddr5 = NULL;
    		int *piAddr6 = NULL;
    		int *piAddr7 = NULL;
    		int *piLen = NULL;
    		int iRows = 0;
    		int iCols = 0;
    		int borderType = 0;
    		double top = 0;
    		double bottom = 0;
    		double right = 0;
    		double left = 0;
    		double *color_mat = NULL;
    		char **pstData = NULL;
    		CheckInputArgument(pvApiCtx,7,7);
    		CheckOutputArgument(pvApiCtx,1,1);
    		try
    		{
      			//retrieve image
      			Mat img,dst;
      			retrieveImage(img,1);
      			//retrieve top extrapolation
      			sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr,0);
      			}
      			intErr = getScalarDouble(pvApiCtx,piAddr2,&top);
      			if(intErr)
      			{
        			printError(&sciErr,0);
      			}
      			//retrieve bottom extrapolation
      			sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr,0);
      			}
      			intErr = getScalarDouble(pvApiCtx,piAddr3,&bottom);
      			if(intErr)
      			{
        			printError(&sciErr,0);
      			}
      			//retrieve left extrapolation
      			sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr,0);
      			}
      			intErr = getScalarDouble(pvApiCtx,piAddr4,&left);
      			if(intErr)
      			{
        			printError(&sciErr,0);
      			}
      			//retrieve right extrapolation
      			sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr,0);
      			}
      			intErr = getScalarDouble(pvApiCtx,piAddr5,&right);
      			if(intErr)
      			{
        			printError(&sciErr,0);
      			}
      			//retrieve border type
      			sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr,0);
      			}
      			sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
      			if (sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			sciErr = getMatrixOfString(pvApiCtx, piAddr6, &iRows, &iCols, NULL, NULL);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			piLen = (int*)malloc(sizeof(int) * iRows * iCols);
      			//second call to retrieve length of each string
      			sciErr = getMatrixOfString(pvApiCtx, piAddr6, &iRows, &iCols, piLen, NULL);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			pstData = (char**)malloc(sizeof(char*) * iRows * iCols);
      			for(int i = 0 ; i < iRows * iCols ; i++)
      			{
        			pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
      			}
      			//third call to retrieve data
      			sciErr = getMatrixOfString(pvApiCtx, piAddr6, &iRows, &iCols, piLen, pstData);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			if(!strcmp(pstData[0],"BORDER_REFLECT_101"))
      			{
        			borderType=BORDER_REFLECT_101;
      			}
      			else if(!strcmp(pstData[0],"BORDER_WRAP"))
      			{
        			borderType=BORDER_WRAP;
      			}
      			else if(!strcmp(pstData[0],"BORDER_TRANSPARENT"))
      			{
        			borderType= BORDER_TRANSPARENT;
      			}
      			else if(!strcmp(pstData[0],"BORDER_CONSTANT"))
      			{
        			borderType= BORDER_CONSTANT;
      			}
      			else if(!strcmp(pstData[0],"BORDER_REFLECT"))
      			{
        			borderType= BORDER_REFLECT;
      			}
      			else if(!strcmp(pstData[0],"BORDER_REFLECT101"))
      			{
        			borderType= BORDER_REFLECT101;
      			}
      			else if(!strcmp(pstData[0],"BORDER_ISOLATED"))
      			{
        			borderType= BORDER_ISOLATED;
      			}
      			else if(!strcmp(pstData[0],"BORDER_DEFAULT"))
      			{
        			borderType= BORDER_DEFAULT;
      			}
      			else if(!strcmp(pstData[0],"BORDER_REPLICATE"))
      			{
        			borderType= BORDER_REPLICATE;
      			}
      			else
      			{
        			Scierror(999,"Invalid border type\n");
      			}
      			//retrieve color
      			sciErr = getVarAddressFromPosition(pvApiCtx,7,&piAddr7);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
     			sciErr = getMatrixOfDouble(pvApiCtx,piAddr7,&iRows,&iCols,&color_mat);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			Scalar color(*(color_mat + 2),*(color_mat + 1),*(color_mat + 0));
      			dst = img;
      			copyMakeBorder( img, dst, top, bottom, left, right, borderType, color);
      			string tempstring = type2str(dst.type());
      			char *checker;
      			checker = (char *)malloc(tempstring.size() + 1);
      			memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
      			returnImage(checker,dst,1);
			//Free Memory
			free(pstData);
			free(piLen);
      			free(checker);
      			AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
      			ReturnArguments(pvApiCtx);

    		}
    		catch(cv::Exception& e)
    		{
      			const char* err = e.what();
      			Scierror(999,"%s",err);
    		}
  	}
}
