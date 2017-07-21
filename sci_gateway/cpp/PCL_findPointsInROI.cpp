/*Author-Ebey Abraham*/

#include <numeric>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sciprint.h>

using namespace std;
extern "C"
{
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "sciprint.h"

  int PCL_findPointsInROI(char *fname, unsigned long fname_len)
  {
    SciErr sciErr;
    int intErr = 0;
    int *piAddr1 = NULL;
    int *piAddr2 = NULL;
    int iRows1 = 0;
    int iCols1 = 0;
    int iRows2 = 0;
    int iCols2 = 0;

    double *points = NULL;
    double *ROI = NULL;

    CheckInputArgument(pvApiCtx,2,2);
    CheckOutputArgument(pvApiCtx,1,1);

    try
    {
      // get points
      sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr1,&iRows1,&iCols1,&points);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(iCols1 != 3)
      {
        Scierror(999,"Points should be a Nx3 matrix");
      }

     // get ROI
     sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
     if(sciErr.iErr)
     {
       printError(&sciErr,0);
       return 0;
     }
     sciErr = getMatrixOfDouble(pvApiCtx,piAddr2,&iRows2,&iCols2,&ROI);
     if(sciErr.iErr)
     {
       printError(&sciErr, 0);
       return 0;
     }
     if(iRows2 != 3 && iCols2 != 2)
     {
       Scierror(999,"ROI should be a 3x2 matrix");
     }

     double xMin = *(ROI + 0);
     double yMin = *(ROI + 1);
     double zMin = *(ROI + 2);
     double xMax = *(ROI + 3);
     double yMax = *(ROI + 4);
     double zMax = *(ROI + 5);

     vector<double> indices;
     for(int i =0; i < iRows1; i++)
     {
       double x = *(points + i);
       double y = *(points + i + iRows1);
       double z = *(points + i + 2*iRows1);
       if(xMin <= x && x <= xMax)
       {
         if(yMin <= y && y <= yMax)
         {
           if(zMin <= z && z <= zMax)
           {
             indices.push_back(i+1);
           }
         }
       }
     }
     int num = indices.size();
     double res[num];
     copy(indices.begin(),indices.end(),res);

     sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,num,1,res);
     if(sciErr.iErr)
     {
       printError(&sciErr,0);
       return 0;
     }

     AssignOutputVariable(pvApiCtx,1) = nbInputArgument(pvApiCtx) + 1;
     ReturnArguments(pvApiCtx);

   }
   catch(std::exception& e)
   {
     const char* err = e.what();
     Scierror(999,"%s",err);
   }
   return 0;
 }
}
