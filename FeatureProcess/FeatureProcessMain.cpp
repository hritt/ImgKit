#include "FeatureProcess.h"

int main(int argc ,char *argv[])
{
	IplImage * src=cvLoadImage("Aaron_Eckhart_0001.jpg");
	if(!src){
		cerr<<"Fail to load picture!"<<endl;
		exit(1);
	}
	IplImage * gray=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage * dst=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);

	cvSmooth(src,src,CV_MEDIAN,3);//CV_MEDIAN:中值滤波,核大小为size1*size1
	cvCvtColor(src,gray,CV_BGR2GRAY);
	cvSmooth(gray,gray,CV_MEDIAN,7);

	cvReleaseImage(&src);

	cvNamedWindow("gray");
	cvShowImage("gray",gray);
	cvWaitKey(0);
	cvDestroyWindow("gray");
	cvReleaseImage(&gray);

	return 0;
}