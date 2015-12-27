#include "FaceDetection.h"

//http://www.cnblogs.com/mengdd/archive/2012/08/01/2619043.html
//�������ӵ������ǣ��õ�һ��ͼ�����Ƚ������ţ�scale=1.2����Ϊһ��Сͼ�񣩣�Ȼ�������ź��Сͼ���ϼ��������������ȽϿ�
double scale=1.2;

CvHaarClassifierCascade * LoadCascade(const char * cascadeName)
{
	//cascadeNameĬ��Ϊhaarcascade_frontalface_alt2.xml
	CvHaarClassifierCascade * cascade=(CvHaarClassifierCascade*)cvLoad(cascadeName,0,0,0);//���ط�����
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
	cvCvtColor(image,gray,CV_BGR2GRAY);//��ɫ�ռ�ת������������ʵ��RGB��ɫ��HSV,HSI����ɫ�ռ��ת����Ҳ����ת��Ϊ�Ҷ�ͼ��
	cvResize(gray, smallImg, CV_INTER_LINEAR);
	cvEqualizeHist(smallImg,smallImg);//�Ҷ�ͼ��ֱ��ͼ���⻯

	cvClearMemStorage(storage);//����ڴ�����ͷ�

	double tstart=(double)cvGetTickCount();
	//CvSeq:�ɶ�̬����Ԫ������
	CvSeq * objects=cvHaarDetectObjects(smallImg,cascade,storage,
		1.1,//��ǰ��������̵�ɨ���У��������ڵı���ϵ��������1.1ָ������������������10%
		2,  //���ɼ��Ŀ������ھ��ε���С����
		0,  //������ʽ,��������Canny��Ե��������ų�һЩ��Ե���ٻ��ߺܶ��ͼ������
		cvSize(30,30)//��ⴰ�ڵ���С�ߴ�
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

	static CvScalar colors[] = { //��������Ŀ����ɫ��������������Ϳ���ʹ�ò�ͬ��ɫ���
		{0,0,255},{0,128,255},{0,255,255},{0,255,0},
		{255,128,0},{255,255,0},{255,0,0},{255,0,255}
	};

	if(flags==1){//���ο�
		for(int i=0;i<(objects?objects->total:0);i++){
			CvRect * r=(CvRect *)cvGetSeqElem(objects,i);
			cvRectangle(image,cvPoint(r->x*scale,r->y*scale),cvPoint((r->x+r->width)*scale,(r->y+r->height)*scale),colors[i%8]);
		}
	}else if(flags==2){//Բ�ο�
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
