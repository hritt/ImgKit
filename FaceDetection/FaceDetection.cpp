#include "FaceDetection.h"

//http://www.cnblogs.com/mengdd/archive/2012/08/01/2619043.html
//缩放因子的作用是：拿到一个图像，首先将它缩放（scale=1.2即变为一个小图像），然后在缩放后的小图像上检测人脸，这样会比较快
double scale=1.2;

CvHaarClassifierCascade * LoadCascade(const char * cascadeName)
{
	//cascadeName默认为haarcascade_frontalface_alt2.xml
	CvHaarClassifierCascade * cascade=(CvHaarClassifierCascade*)cvLoad(cascadeName,0,0,0);//加载分类器
	if(!cascade){
		cerr<<"ERROR:Could not load classifier cascade"<<endl;
		return NULL;
	}
	return cascade;
}

CvSeq * DetectionFaceIplImage(IplImage * image, CvHaarClassifierCascade * cascade, CvMemStorage* storage)
{
	IplImage * gray=cvCreateImage(cvSize(image->width,image->height),8,1);
	IplImage * smallImg=cvCreateImage(cvSize(cvRound(image->width/scale),cvRound(image->height/scale)),8,1);
	cvCvtColor(image,gray,CV_BGR2GRAY);//颜色空间转换函数，可以实现RGB颜色向HSV,HSI等颜色空间的转换，也可以转换为灰度图像
	cvResize(gray, smallImg, CV_INTER_LINEAR);
	cvEqualizeHist(smallImg,smallImg);//灰度图象直方图均衡化

	cvClearMemStorage(storage);//清空内存而不释放

	double tstart=(double)cvGetTickCount();
	//CvSeq:可动态增长元素序列
	CvSeq * objects=cvHaarDetectObjects(smallImg,cascade,storage,
		1.1,//在前后两次相继的扫描中，搜索窗口的比例系数。例如1.1指将搜索窗口依次扩大10%
		2,  //构成检测目标的相邻矩形的最小个数
		0,  //操作方式,可以利用Canny边缘检测器来排除一些边缘很少或者很多的图像区域
		cvSize(30,30)//检测窗口的最小尺寸
		);
	double tend=(double)cvGetTickCount();
	cout<<"Detect face use "<<(tend-tstart)/cvGetTickFrequency()/1000<<"ms"<<endl;

	cvReleaseImage(&gray);
	cvReleaseImage(&smallImg);

	return objects;
}

bool DrawDetectResult(IplImage * image, CvSeq * objects, int flags)
{
	if(image==NULL)
		return false;

	static CvScalar colors[] = { //标记人脸的框的颜色，这样多个人脸就可以使用不同颜色标记
		{0,0,255},{0,128,255},{0,255,255},{0,255,0},
		{255,128,0},{255,255,0},{255,0,0},{255,0,255}
	};

	if(flags==1){//矩形框
		for(int i=0;i<(objects?objects->total:0);i++){
			CvRect * r=(CvRect *)cvGetSeqElem(objects,i);
			cvRectangle(image,cvPoint(r->x*scale,r->y*scale),cvPoint((r->x+r->width)*scale,(r->y+r->height)*scale),colors[i%8]);
		}
	}else if(flags==2){//圆形框
		for(int i=0;i<(objects?objects->total:0);i++){
			CvRect* r = (CvRect*)cvGetSeqElem( objects, i );
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle( image, center, radius, colors[i%8], 3, 8, 0 );
		}
	}else
		return false;

	cvNamedWindow("result",1);
	cvShowImage("result",image);
	cvWaitKey(0);
	cvDestroyWindow("result");

	return true;
}
