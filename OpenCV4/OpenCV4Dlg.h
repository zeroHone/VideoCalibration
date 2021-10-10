
// OpenCV4Dlg.h : header file
//

#pragma once
#include <opencv2/core.hpp>

// COpenCV4Dlg dialog
class COpenCV4Dlg : public CDialogEx
{
// Construction
public:
	COpenCV4Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDisp();
	void DisplayImage(cv::Mat & img, int IDC);
	CString TminVal,TmaxVal;
	bool mShowImage;
	afx_msg void OnBnClickedStop();
	afx_msg void OnOptionsCalibrate();
	cv::Mat mOriginalFrame, imageOption;
	static void mouseEvent(int Event, int x, int y, int flags, void * param);

	
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	

	void AsyncHandler(int Event, int x, int y, int flags);
	cv::Point startPoint;
	cv::Point endPoint;
	bool drawRect;
	cv::Mat ROI;
	CSliderCtrl m_Tmin;
	CSliderCtrl m_Tmax;

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int threshValue;
	CString m_areaValue;
	CString m_refVal;
	int numberOfPoints;
	double threshold1;
	double threshold2;
	int kernelSize;
	afx_msg void OnCbnSelchangeCombo1();
	CString m_comboBox;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CComboBox m_ctrlCombo;
	afx_msg void OnBnClickedRadioOriginal();
	afx_msg void OnBnClickedRadioEdges();
	int m_imageType;
	afx_msg void OnBnClickedButtonCalculate();
	
	double m_pixelValue;
	CString m_tVal;
	int thresholdValue;
	CSliderCtrl m_thresholdValue;
	afx_msg void OnBnClickedRadioThreshold();
	int circleMove;
	bool showCircle;
	afx_msg void OnBnClickedRadioCircle();
	afx_msg void OnOptionsShowcircle();
	afx_msg void OnOptionsHidecircles();
	afx_msg void OnOptionsExit();
};
