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

/*加载Classifier Cascade
  输出：CvHaarClassifierCascade
       NULL 加载失败（文件不存在）  */
CvHaarClassifierCascade * LoadCascade(const char * cascadeName="../data/haarcascade_frontalface_alt2.xml");

/*在IplImage格式原图中检测人脸，函数中会对图片按scale进行缩放
  注意：需先加载CvHaarClassifierCascade
  输出：检测到的人脸位置序列 */
CvSeq * DetectionFaceIplImage(IplImage * image, CvHaarClassifierCascade * cascade, CvMemStorage* storage);

/*根据人脸位置序列，将图片中人脸标记出来
  输入：flags 1-矩形框，2-圆形框
  输出：true   成功
        false  输入有误，image为空或flags取值不为1或2 */
bool DrawDetectResult(IplImage * image, CvSeq * objects, int flags=1);