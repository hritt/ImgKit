/************************************************************************
*
*   Description: face detection
*
*   Author & Data: JY Liu, 2014/12/16
*
************************************************************************/

#pragma once

#include <iostream>
using namespace std;

#include "cv.h"
#include "highgui.h"

/*����Classifier Cascade
  �����CvHaarClassifierCascade
       NULL ����ʧ�ܣ��ļ������ڣ�  */
CvHaarClassifierCascade * LoadCascade(const char * cascadeName="../data/haarcascade_frontalface_alt2.xml");

/*��IplImage��ʽԭͼ�м�������������л��ͼƬ��scale��������
  ע�⣺���ȼ���CvHaarClassifierCascade
  �������⵽������λ������ */
CvSeq * DetectionFaceIplImage(IplImage * image, CvHaarClassifierCascade * cascade, CvMemStorage* storage);

/*��������λ�����У���ͼƬ��������ǳ���
  ���룺flags 1-���ο�2-Բ�ο�
  �����true   �ɹ�
        false  ��������imageΪ�ջ�flagsȡֵ��Ϊ1��2 */
bool DrawDetectResult(IplImage * image, CvSeq * objects, int flags=1);