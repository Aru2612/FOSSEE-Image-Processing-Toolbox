/*Author-Ebey Abraham*/

#include <numeric>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sciprint.h>
#include <sys/stat.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/exceptions.h>
#include <pcl/common/common.h>

using namespace pcl;
using namespace std;
extern "C"
{
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include "sciprint.h"

  int PCL_pcmerge(char *fname, unsigned long fname_len)
  {
    SciErr sciErr;
    int intErr = 0;

    // Variables for cloud 1
    int *piAddr1 = NULL;    // Points
    int *piAddr2 = NULL;    //Color
    int *piAddr3 = NULL;    //Dense
    int *piAddr4 = NULL;
    int iRows1 = 0;
    int iCols1 = 0;
    int iRows2 = 0;
    int iCols2 = 0;

    double *points_1 = NULL;
    double *color_1 = NULL;
    int dense_1 = 0;
    int height_1 = 0;

    // Variables for cloud 2
    int *piAddr5 = NULL;    // Points
    int *piAddr6 = NULL;    //Color
    int *piAddr7 = NULL;    //Dense
    int *piAddr8 = NULL;
    int iRows5 = 0;
    int iCols5 = 0;
    int iRows6 = 0;
    int iCols6 = 0;

    double *points_2 = NULL;
    double *color_2 = NULL;
    int dense_2 = 0;
    int height_2 = 0;

    // Variables for grid box
    int *piAddr9 = NULL;
    double gridSize = 0;

    CheckInputArgument(pvApiCtx,9,9);
    CheckOutputArgument(pvApiCtx,9,9);

    try
    {
      // Retreive cloud 1
      /*******************************************************************************************************/
      // get points
      sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr1,&iRows1,&iCols1,&points_1);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(iCols1 != 3)
      {
        Scierror(999,"Points should be a Nx3 matrix");
      }

      // get colors
      sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr2,&iRows2,&iCols2,&color_1);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(iCols2 != 3)
      {
        Scierror(999,"Color should be a Nx3 matrix");
      }

      if(iRows1 != iRows2)
      {
        Scierror(999,"Size of Points and Color should be same");
      }

      // get is_dense
      sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      intErr = getScalarBoolean(pvApiCtx,piAddr3,&dense_1);
      if(intErr)
      {
        printError(&sciErr,0);
        return 0;
      }

      // height_1
      sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      intErr = getScalarInteger32(pvApiCtx,piAddr4,&height_1);
      if(intErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      /*******************************************************************************************************/

      // Retreive cloud 2
      /*******************************************************************************************************/
      // get points
      sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr5,&iRows5,&iCols5,&points_2);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(iCols5 != 3)
      {
        Scierror(999,"Points should be a Nx3 matrix");
      }

      // get colors
      sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      sciErr = getMatrixOfDouble(pvApiCtx,piAddr6,&iRows6,&iCols6,&color_2);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(iCols6 != 3)
      {
        Scierror(999,"Color should be a Nx3 matrix");
      }

      if(iRows5 != iRows6)
      {
        Scierror(999,"Size of Points and Color should be same");
      }

      // get is_dense
      sciErr = getVarAddressFromPosition(pvApiCtx,7,&piAddr7);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      intErr = getScalarBoolean(pvApiCtx,piAddr7,&dense_2);
      if(intErr)
      {
        printError(&sciErr,0);
        return 0;
      }

      // height_2
      sciErr = getVarAddressFromPosition(pvApiCtx,8,&piAddr8);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      intErr = getScalarInteger32(pvApiCtx,piAddr8,&height_2);
      if(intErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      /*******************************************************************************************************/

      // Retreive grid size
      sciErr = getVarAddressFromPosition(pvApiCtx,9,&piAddr9);
      if(sciErr.iErr)
      {
        printError(&sciErr,0);
        return 0;
      }
      intErr = getScalarDouble(pvApiCtx,piAddr9,&gridSize);
      if(intErr)
      {
        printError(&sciErr,0);
        return 0;
      }



      // Creating cloud points

      // Cloud 1
      /*******************************************************************************************************/
      PointCloud<PointXYZRGB> cloud_1;

      cloud_1.width = iRows1;
      cloud_1.height = height_1;

      if(dense_1)
      {
        cloud_1.is_dense = true;
      }
      else
      {
        cloud_1.is_dense = false;
      }

      int size1 = iRows1 * height_1;
      cloud_1.points.resize(size1);

      for(int i=0; i<size1; i++)
      {
        cloud_1.points[i].x = *(points_1 + i);
        cloud_1.points[i].y = *(points_1 + i + size1);
        cloud_1.points[i].z = *(points_1 + i + 2*size1);
        cloud_1.points[i].r = *(color_1 + i);
        cloud_1.points[i].g = *(color_1 + i + size1);
        cloud_1.points[i].b = *(color_1 + i + 2*size1);
      }
      /*******************************************************************************************************/

      // Cloud 2
      /*******************************************************************************************************/
      PointCloud<PointXYZRGB> cloud_2;

      cloud_2.width = iRows5;
      cloud_2.height = height_2;

      if(dense_2)
      {
        cloud_2.is_dense = true;
      }
      else
      {
        cloud_2.is_dense = false;
      }

      int size2 = iRows5 * height_2;
      cloud_2.points.resize(size2);

      for(int i=0; i<size2; i++)
      {
        cloud_2.points[i].x = *(points_1 + i);
        cloud_2.points[i].y = *(points_1 + i + size2);
        cloud_2.points[i].z = *(points_1 + i + 2*size2);
        cloud_2.points[i].r = *(color_1 + i);
        cloud_2.points[i].g = *(color_1 + i + size2);
        cloud_2.points[i].b = *(color_1 + i + 2*size2);
      }
      /*******************************************************************************************************/

      // Merging Clouds
      PointCloud<PointXYZRGB> cloud;
      cloud = cloud_1;
      cloud += cloud_2;

      // Apply grid filter
      PointCloud<PointXYZRGB>::Ptr output (new PointCloud<PointXYZRGB> ());
      VoxelGrid<PointXYZRGB> vg;
      PointCloud<PointXYZRGB>::Ptr cloudptr (new PointCloud<PointXYZRGB> (cloud));
      vg.setInputCloud (cloudptr);
      float x = (float)(gridSize);
      vg.setLeafSize(x,x,x);
      vg.filter(*output);

      // Variable to return cloud point properties
      int width;
      int height;
      int num_points;
      double *selected_points;
      double *rgbValues;
      double *xLimit;
      double *yLimit;
      double *zLimit;
      bool is_dense;

      height = output->height;
      width = output->width;
      num_points = output->points.size();
      is_dense = output->is_dense;

      selected_points=(double *)malloc(sizeof(double)*num_points*3);
      rgbValues=(double *)malloc(sizeof(double)*num_points*3);
      xLimit=(double *)malloc(sizeof(double)*1*2);
      yLimit=(double *)malloc(sizeof(double)*1*2);
      zLimit=(double *)malloc(sizeof(double)*1*2);

      PointCloud<PointXYZRGB>::iterator it;
      int i;
      for ( it = output->points.begin(),i=0; it!=output->points.end(); ++it,++i)
      {
        *(selected_points + i) = (*it).x;
        *(selected_points + i + num_points) = (*it).y;
        *(selected_points + i + 2*num_points) = (*it).z;

        *(rgbValues + i) = (*it).r;
        *(rgbValues + i + num_points) = (*it).g;
        *(rgbValues + i + 2*num_points) = (*it).b;
      }

      //get limits of the data points
      PointXYZRGB minLimit,maxLimit;
      getMinMax3D(*output,minLimit,maxLimit);

      *(xLimit)=minLimit.x;
      *(xLimit + 1)=maxLimit.x;

      *(yLimit)=minLimit.y;
      *(yLimit + 1)=maxLimit.y;

      *(zLimit)=minLimit.z;
      *(zLimit + 1)=maxLimit.z;

      //Assign output Variables

      //selected_points
      sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,num_points,3,selected_points);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //num_points
      intErr = createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+2,num_points);
      if(intErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //width
      intErr = createScalarInteger32(pvApiCtx,nbInputArgument(pvApiCtx)+3,width);
      if(intErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //height
      intErr = createScalarInteger32(pvApiCtx,nbInputArgument(pvApiCtx)+4,height);
      if(intErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //rgbValues
      sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+5,num_points,3,rgbValues);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //xLimit
      sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+6,1,2,xLimit);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //yLimit
      sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+7,1,2,yLimit);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //zLimit
      sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+8,1,2,zLimit);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      //Dense
      intErr = createScalarBoolean(pvApiCtx,nbInputArgument(pvApiCtx)+9,is_dense);
      if(intErr)
      {
        printError(&sciErr, 0);
        return 0;
      }

      for(int i=1;i<=9;i++)
      {
        AssignOutputVariable(pvApiCtx, i) = nbInputArgument(pvApiCtx) + i;
      }

      ReturnArguments(pvApiCtx);

    }
    catch(pcl::PCLException& e)
    {
      const char* err = e.what();
      Scierror(999,"%s",err);
    }

    return 0;
  }
}
