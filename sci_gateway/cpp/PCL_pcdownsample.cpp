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
#include <pcl/filters/random_sample.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/exceptions.h>
#include <pcl/common/common.h>

using namespace std;
extern "C"
{
  	#include "api_scilab.h"
  	#include "Scierror.h"
  	#include "BOOL.h"
  	#include <localization.h>
  	#include "sciprint.h"
  	int PCL_pcdownsample(char *fname, unsigned long fname_len)
  	{
    		SciErr sciErr;
    		int intErr = 0;
    		int *piAddr1 = NULL;    // Points
    		int *piAddr2 = NULL;    //Color
    		int *piAddr3 = NULL;    //Dense
    		int *piAddr4 = NULL;
    		int *piAddr5 = NULL;
   		int *piAddr6 = NULL;    //param
    		int iRows1 = 0;
    		int iCols1 = 0;
    		int iRows2 = 0;
    		int iCols2 = 0;
    		double *points = NULL;
   		double *color = NULL;
    		int dense = 0;
    		int H = 0;
    		int type = 0;
    		double param = 0;
    		CheckInputArgument(pvApiCtx,6,6);
    		CheckOutputArgument(pvApiCtx,9,9);
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
    		// get colors
    		sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
    		if(sciErr.iErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		sciErr = getMatrixOfDouble(pvApiCtx,piAddr2,&iRows2,&iCols2,&color);
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
    		intErr = getScalarBoolean(pvApiCtx,piAddr3,&dense);
    		if(intErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		// get height
    		sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
    		if(sciErr.iErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		intErr = getScalarInteger32(pvApiCtx,piAddr4,&H);
    		if(intErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		// get filter type
    		sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
    		if(sciErr.iErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		intErr = getScalarInteger32(pvApiCtx,piAddr5,&type);
    		if(intErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		// filter param
    		sciErr = getVarAddressFromPosition(pvApiCtx,6,&piAddr6);
    		if(sciErr.iErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		intErr = getScalarDouble(pvApiCtx,piAddr6,&param);
    		if(intErr)
    		{
      			printError(&sciErr,0);
      			return 0;
    		}
    		try
    		{
      			// Creating point cloud from input
      			pcl::PointCloud<pcl::PointXYZRGB> cloud;
      			cloud.width = iRows1;
      			cloud.height = H;
      			if(dense)
      			{
        			cloud.is_dense = true;
      			}
      			else
      			{
        			cloud.is_dense = false;
      			}
      			int size = iRows1 * H;
      			cloud.points.resize(size);
      			for(int i=0; i<size; i++)
      			{
        			cloud.points[i].x = *(points + i);
        			cloud.points[i].y = *(points + i + size);
        			cloud.points[i].z = *(points + i + 2*size);
        			cloud.points[i].r = *(color + i);
        			cloud.points[i].g = *(color + i + size);
        			cloud.points[i].b = *(color + i + 2*size);
      			}
      			pcl::PointCloud<pcl::PointXYZRGB>::Ptr output (new pcl::PointCloud<pcl::PointXYZRGB> ());
      			pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudptr (new pcl::PointCloud<pcl::PointXYZRGB> (cloud));
      			float x = (float)(param);
      			if(type == 1)
      			{
        			pcl::RandomSample<pcl::PointXYZRGB> rs;
        			rs.setInputCloud(cloudptr);
        			unsigned int output_points = (x*size)/100;
        			rs.setSample(output_points);
        			rs.filter(*output);
      			}
      			else if(type == 2)
      			{
        			pcl::VoxelGrid<pcl::PointXYZRGB> vg;
        			vg.setInputCloud(cloudptr);
        			vg.setLeafSize(x,x,x);
        			vg.filter(*output);
      			}
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
      			pcl::PointCloud<pcl::PointXYZRGB>::iterator it;
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
      			pcl::PointXYZRGB minLimit,maxLimit;
      			pcl::getMinMax3D(*output,minLimit,maxLimit);
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
			//Free Memory
			free(selected_points);
      			free(rgbValues);
      			free(xLimit);
      			free(yLimit);
      			free(zLimit);
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
