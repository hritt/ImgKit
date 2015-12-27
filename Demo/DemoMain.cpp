/************************************************************************
*
*   Description: face detection
*
*   Author & Data: JY Liu, 2014/12/17
*
************************************************************************/

#include "../FaceDetection/FaceDetection.h"
#pragma comment(lib,"../Debug/FaceDetection.lib")

int main(int argc, char ** argv)
{
	const char * filename="lena.jpg";
	CvHaarClassifierCascade* cascade=LoadCascade();
	IplImage * image=cvLoadImage(filename,1);
	if(image && cascade){
		CvMemStorage *storage=cvCreateMemStorage(0);

		CvSeq * objects=DetectionFaceIplImage(image, cascade, storage);
		DrawDetectResult(image, objects, 1);

		cvReleaseMemStorage(&storage);//人脸位置序列objects中包含storage
		cvReleaseImage( &image );
	}

	return 0;
}