
// ShowCameraDlg.h : ͷ�ļ�
//

#pragma once


#include <opencv2\opencv.hpp>


// CShowCameraDlg �Ի���
class CShowCameraDlg : public CDialogEx
{
// ����
public:
	CShowCameraDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOWCAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CvCapture * pCapture;
	IplImage * pFrame;

	afx_msg void OnBnClickedButtonShow();
	void DrawPicToHDC(IplImage * img, UINT ID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
