/*Author-Ebey Abraham*/

#include <numeric>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sciprint.h>
#include <sys/stat.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
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
  	int PCL_removeInvalidPoints(char *fname, unsigned long fname_len)
  	{
    		SciErr sciErr;
    		int intErr = 0;
    		int *piAddr1 = NULL;    // Points
    		int *piAddr2 = NULL;    //Color
    		int *piAddr3 = NULL;    //Dense
    		int *piAddr4 = NULL;
    		int iRows1 = 0;
    		int iCols1 = 0;
    		int iRows2 = 0;
    		int iCols2 = 0;
    		double *points = NULL;
    		double *color = NULL;
    		int dense = 0;
    		int H = 0;
    		double *indices = NULL;
    		CheckInputArgument(pvApiCtx,4,4);
    		CheckOutputArgument(pvApiCtx,10,10);
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
      			// create PointCloud from input
      			PointCloud<PointXYZRGB>::Ptr cloud (new PointCloud<PointXYZRGB> ());
      			if(dense)
      			{
        			cloud->is_dense = true;
      			}
      			else
      			{
        			cloud->is_dense = false;
      			}
      			PointXYZRGB p;
      			for(int i=0; i<iRows1*H; i++)
      			{
        			p.x = *(points + i);
        			p.y = *(points + i + iRows1*H);
        			p.z = *(points + i + 2*iRows1*H);
        			p.r = *(color + i);
        			p.g = *(color + i + iRows2*H);
        			p.b = *(color + i + 2*iRows2*H);
        			cloud->push_back(p);
      			}
      			// Remove invalid points from input point cloud
      			vector<int> indices;
      			PointCloud<PointXYZRGB>::Ptr output(new PointCloud<PointXYZRGB> ());
      			removeNaNFromPointCloud(*cloud, *output, indices);
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
      			// Convert vetor of valid points to an array
      			// Also convert 0-based to 1-based indexing
      			double validIndices[num_points];
      			for(int i=0; i<num_points;i++)
      			{
        			validIndices[i] = indices[i] + 1;
      			}
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
      			//validIndices
      			sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+10,num_points,1,validIndices);
      			if(sciErr.iErr)
      			{
        			printError(&sciErr, 0);
        			return 0;
      			}
      			for(int i=1;i<=10;i++)
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
