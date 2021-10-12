
// OpenCV4Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "OpenCV4.h"
#include "OpenCV4Dlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <regex>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// COpenCV4Dlg dialog



COpenCV4Dlg::COpenCV4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCV4_DIALOG, pParent)
	, TminVal(_T(""))
	, TmaxVal(_T(""))
	, m_areaValue(_T(""))
	, m_refVal(_T(""))
	, m_comboBox(_T(""))
	, m_imageType(0)
	
	, m_tVal(_T(""))
	, m_fileLoad(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void COpenCV4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DEBUG, TminVal);
	DDX_Text(pDX, IDC_DEBUG2, TmaxVal);

	DDX_Control(pDX, IDC_TMIN, m_Tmin);
	DDX_Control(pDX, IDC_TMAX, m_Tmax);

	DDX_Text(pDX, IDC_AREA, m_areaValue);
	DDX_Text(pDX, IDC_EDIT1, m_refVal);
	DDX_CBString(pDX, IDC_KERNEL, m_comboBox);
	DDX_Control(pDX, IDC_KERNEL, m_ctrlCombo);
	DDX_Radio(pDX, IDC_RADIO1, m_imageType);

	DDX_Text(pDX, IDC_TVAL, m_tVal);
	DDX_Control(pDX, IDC_THRESH, m_thresholdValue);
	DDX_Text(pDX, IDC_LOAD, m_fileLoad);
}

BEGIN_MESSAGE_MAP(COpenCV4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON1, &COpenCV4Dlg::OnBnClickedStop)
	ON_COMMAND(ID_OPTIONS_CALIBRATE, &COpenCV4Dlg::OnOptionsCalibrate)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_KERNEL, &COpenCV4Dlg::OnCbnSelchangeCombo1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, &COpenCV4Dlg::OnBnClickedRadioOriginal)
	ON_BN_CLICKED(IDC_RADIO2, &COpenCV4Dlg::OnBnClickedRadioEdges)
	ON_BN_CLICKED(IDC_BUTTON2, &COpenCV4Dlg::OnBnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_RADIO3, &COpenCV4Dlg::OnBnClickedRadioThreshold)
	ON_COMMAND(ID_OPTIONS_SHOWCIRCLE, &COpenCV4Dlg::OnOptionsShowcircle)
	ON_COMMAND(ID_OPTIONS_HIDECIRCLES, &COpenCV4Dlg::OnOptionsHidecircles)
	ON_COMMAND(ID_OPTIONS_EXIT, &COpenCV4Dlg::OnOptionsExit)
	ON_BN_CLICKED(IDC_BUTTON3, &COpenCV4Dlg::OnBnClickedLoadVideo)
	ON_BN_CLICKED(IDC_BUTTON5, &COpenCV4Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &COpenCV4Dlg::OnBnClickedStopVideo)
	ON_BN_CLICKED(IDC_BUTTON4, &COpenCV4Dlg::OnBnClickedButtonFit)
	ON_WM_CLOSE()
//	ON_WM_MOVE()
//	ON_WM_MOVING()
//	ON_WM_WINDOWPOSCHANGED()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// COpenCV4Dlg message handlers

BOOL COpenCV4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//MessageBox( "Hosein", "Habibifar", MB_OK);

	drawRect = false;
	m_Tmin.SetRange(0, 255, TRUE);
	m_Tmin.SetPos(50);
	TminVal.Format("%d", 50);


	m_Tmax.SetRange(0, 255, TRUE);
	m_Tmax.SetPos(180);
	TmaxVal.Format("%d", 180);

	m_thresholdValue.SetRange(0, 255, TRUE);
	m_thresholdValue.SetPos(120);
	m_tVal.Format("%d", 120);



	threshold1 = 50;
	threshold2 = 180;
	kernelSize = 3;
	m_refVal = "20.0";
	
	threshValue = 0;
	numberOfPoints = 0;
	m_ctrlCombo.AddString("3");
	m_ctrlCombo.AddString("5");
	m_ctrlCombo.AddString("7");
	m_ctrlCombo.AddString("9");
	m_ctrlCombo.SetCurSel(0);
	m_areaValue = "-";
	circleMove = 0;
	m_fileLoad = "---";

	UpdateData(false);
	showCircle = false;
	m_startThread = 1;
	AfxBeginThread(threadProc, LPVOID(this));
	//SetTimer(1234, 333, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenCV4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenCV4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		if (~lastFrame.empty()) {
			//cv::imshow("Image", frame);
			//cv::waitKey(5);
			DisplayImage(lastFrame, 1023);
		}
		CDialogEx::OnPaint();
	}
	//if (~lastFrame.empty() && showVideo) {
	//	cv::imshow("Image", lastFrame);
	//	cv::waitKey(20);
	//}
	//ssageBox("OnPaint", "OnPaint", MB_OK);

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenCV4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCV4Dlg::OnBnClickedDisp()
{

	

		
}


void COpenCV4Dlg::DisplayImage(cv::Mat& img, int IDC)
{
	// TODO: Add your implementation code here.
		// TODO: Add your control notification handler code here
	CDC* pDC = GetDlgItem(IDC)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	
	using namespace cv;
	

	IplImage* image = &cvIplImage(img);
	CRect rect;
	CvvImage imgP;
	imgP.CopyOf(image);

	GetDlgItem(IDC)->GetClientRect(&rect);
	imgP.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
	imgP.Destroy();
}





void COpenCV4Dlg::OnBnClickedStop()
{
	//cv::Mat frame, temp1,temp2;
	//uchar* ptr;
	//CString message;
	//UpdateData(true);
	////mOriginalFrame.copyTo(imageOption);

	//if (!mOriginalFrame.empty()) {
	//if (m_imageType == 1) {
	//	cv::Canny(mOriginalFrame, frame, threshold1, threshold2, kernelSize);
	//	cv::cvtColor(frame, imageOption, CV_GRAY2BGR);
	//	
	//	
	//	//		cv::threshold(frame, outPut, threshold2, 255, CV_THRESH_BINARY);
	//	
	//}
	//else if(m_imageType == 2){
	//
	//	cv::cvtColor(mOriginalFrame, temp1, CV_BGR2GRAY);
	//	cv::threshold(temp1, temp2, thresholdValue, 255, cv::THRESH_BINARY);
	//	cv::cvtColor(temp2, imageOption, CV_GRAY2BGR);
	//	

	//	
	//}
	//else {
	//	mOriginalFrame.copyTo(imageOption);

	//}
	///* 
	//int x1 = startPoint.x;
	//int y1 = startPoint.y;
	//int x2 = endPoint.x;
	//int y2 = endPoint.y;
	//cv::Mat cannyEdge;
	//cv::Canny(mOriginalFrame, cannyEdge, threshold1, threshold2, kernelSize);
	//if (x1 < x2) {
	//	for (int x = x1; x <= x2; x++) {




	//	}
	//}
	//else if (x2 > x1) {
	//	for (int x = x1; x <= x2; x++) {




	//	}
	//}
	//else {
	//
	//
	//
	//
	//}*/
	//
	//}

	//imageOption.copyTo(temp1);

	//if (showCircle) {
	//	cv::circle(temp1, cv::Point(startPoint.x, startPoint.y), 5, cv::Scalar(0, 255, 0), 2);
	//	cv::line(temp1, cv::Point(startPoint.x, startPoint.y), cv::Point(endPoint.x, endPoint.y), cv::Scalar(0, 0, 255), 2);
	//	cv::circle(temp1, cv::Point(endPoint.x, endPoint.y), 5, cv::Scalar(0, 255, 0), 2);

	//}else
	//cv::line(temp1, cv::Point(startPoint.x, startPoint.y), cv::Point(endPoint.x, endPoint.y), cv::Scalar(0, 0, 255),2);

	//imshow("Image", temp1);
	}





void COpenCV4Dlg::OnOptionsCalibrate()
{
	// TODO: Add your command handler code here
		//cv::putText(mOriginalFrame, PathOfFile, cv::Point(50, 50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 0), 2, false);
	cv::Mat temp;

	CFileDialog m_ldFile(true);

	if (m_ldFile.DoModal() == IDOK) {

		CString filePath = m_ldFile.GetPathName();
		std::string PathOfFile((char*)filePath.GetBuffer(), filePath.GetLength());

		//temp = cv::imread(PathOfFile);
		//cv::cvtColor(temp, mOriginalFrame, cv::COLOR_GRAY2BGR);
		mOriginalFrame = cv::imread(PathOfFile);
		mOriginalFrame.copyTo(imageOption);
		mOriginalFrame.copyTo(temp);
		startPoint.x = round(mOriginalFrame.cols / 2 - 50);
		endPoint.x = round(mOriginalFrame.cols / 2 + 50);
		startPoint.y = round(mOriginalFrame.rows / 2);
		endPoint.y = startPoint.y;

		cv::line(temp, cv::Point(startPoint.x, startPoint.y), cv::Point(endPoint.x, endPoint.y), cv::Scalar(0, 0, 255), 2);
		if(showCircle) {
			
			cv::circle(temp, cv::Point(startPoint.x, startPoint.y), 5, cv::Scalar(0, 255, 0), 2);

			cv::circle(temp, cv::Point(endPoint.x, endPoint.y), 5, cv::Scalar(0, 255, 0), 2);
		}
		
		cv::namedWindow("Image");

		cv::imshow("Image", temp);

		cv::setMouseCallback("Image", mouseEvent, this);

		cv::waitKey(50);
	}

}




void COpenCV4Dlg::mouseEvent(int Event, int x, int y, int flags, void * params)
{


	// TODO: Add your implementation code here.
	COpenCV4Dlg* myClass = reinterpret_cast<COpenCV4Dlg*>(params);


		myClass->AsyncHandler(Event, x, y, flags);
		
	

}




void COpenCV4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	//m_fileLoad.Format("Value is %d", m_test);
	//UpdateData(false);


	CDialogEx::OnTimer(nIDEvent);
}




void COpenCV4Dlg::AsyncHandler(int Event, int x , int y, int flags)
{
	//// TODO: Add your implementation code here.
	
	
	
	cv::Mat frame,frameCanny;
	imageOption.copyTo(frame);
	int width, height;

	//if (Event == CV_EVENT_LBUTTONUP) {

	//	if (numberOfPoints % 2 == 0) {
	//			startPoint.x = x;
	//startPoint.y = y;
	//numberOfPoints = 1;
	//
	//			}
	//	else if (numberOfPoints % 2 == 1)
	//	{
	//		endPoint.x = x;
	//		endPoint.y = y;
	//		numberOfPoints = 0;
	//		cv::line(frame, startPoint, endPoint, cv::Scalar(0, 0, 255), 2);
	//		cv::circle(imageOption, cv::Point(startPoint.x, startPoint.y), 5, cv::Scalar(0, 255, 0), 2);
	//		cv::circle(imageOption, cv::Point(endPoint.x, endPoint.y), 5, cv::Scalar(0, 255, 0), 2);
	//	}
	//	imshow("Image", frame);
	//}


	//if (Event == CV_EVENT_LBUTTONUP) {
	//	m_areaValue = "Left Button UP";
	//		if(abs(startPoint.x-x) < 5.0 && abs(startPoint.y - y) < 5.0){
	//			circleMove = 1;
	//				}
	//		else if (abs(endPoint.x - x) < 5.0 && abs(endPoint.y - y) < 5.0) {
	//			circleMove = 2;
	//			}

	//}
	//else if (Event = CV_EVENT_MOUSEMOVE) {
	//	m_areaValue = "Mouse Move";
	//	
	//	switch (circleMove) {
	//	
	//	case 1:
	//		startPoint.x = x;
	//		startPoint.y = y;
	//		break;
	//	case 2:
	//		endPoint.x = x;
	//		endPoint.y = y;
	//		break;
	//	default:
	//		break;
	//
	//	
	//	}
	//	
	//}
	//else if (Event == CV_EVENT_LBUTTONDOWN) {
	//	m_areaValue = "Left Button DOWN";
	//	circleMove = 0;
	//}


	if (Event == CV_EVENT_LBUTTONDOWN) {
		if (abs(startPoint.x - x) < 5.0 && abs(startPoint.y - y) < 5.0) {
						circleMove = 1;
							}
		else if (abs(endPoint.x - x) < 5.0 && abs(endPoint.y - y) < 5.0) {
						circleMove = 2;
						}
	
	}

	else if (Event == CV_EVENT_LBUTTONUP) {
		circleMove = 0;
	}

	else if (Event == CV_EVENT_MOUSEMOVE) {
			switch (circleMove) {
		
		case 1:
			startPoint.x = x;
			startPoint.y = y;
			break;
		case 2:
			endPoint.x = x;
			endPoint.y = y;
			break;
		default:
			break;
	
		
		}
	
	}
	

	UpdateData(false);
	if (circleMove) {

		cv::line(frame, startPoint, endPoint, cv::Scalar(0, 0, 255), 2);
		if (showCircle) {
			cv::circle(frame, cv::Point(startPoint.x, startPoint.y), 5, cv::Scalar(0, 255, 0), 2);

			cv::circle(frame, cv::Point(endPoint.x, endPoint.y), 5, cv::Scalar(0, 255, 0), 2);
		}
		


		imshow("Image", frame);
	}


}


void COpenCV4Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

//	else {
	//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	//}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void COpenCV4Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here


	m_ctrlCombo.GetLBText(m_ctrlCombo.GetCurSel(), m_comboBox);
	if (m_comboBox == "3" || m_comboBox == "5" || m_comboBox == "7" || m_comboBox == "9") {
		kernelSize = atoi(m_comboBox);
	
	}
}


void COpenCV4Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	cv::Mat frameCanny;
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar*)&m_Tmin) {
		threshold1 =  m_Tmin.GetPos();
		TminVal.Format(_T("%.1f"), round(threshold1));

	}
	else if (pScrollBar == (CScrollBar*)&m_Tmax) {
		threshold2 =  m_Tmax.GetPos();
		TmaxVal.Format(_T("%.1f"), round(threshold2));

	}
	else if (pScrollBar == (CScrollBar*)&m_thresholdValue) {
	
		thresholdValue = m_thresholdValue.GetPos();
		m_tVal.Format(_T("%d"), thresholdValue);
	
	
	}

	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void COpenCV4Dlg::OnBnClickedRadioOriginal()
{
	// TODO: Add your control notification handler code here

	
	UpdateData(true);

}


void COpenCV4Dlg::OnBnClickedRadioEdges()
{
	// TODO: Add your control notification handler code here

	UpdateData(true);


}


void COpenCV4Dlg::OnBnClickedButtonCalculate()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	double  refVal;
	CString str1;
	std::string inpStr(m_refVal.GetBuffer(), m_refVal.GetLength());
	double lengthLine = 0;
	std::regex number("[1-9][0-9]*.[0-9]*");

	if (std::regex_match(inpStr, number)) {
	
	lengthLine = sqrt(pow((startPoint.x - endPoint.x), 2.0) + pow((startPoint.y - endPoint.y), 2.0));// pixels
	refVal = atof(m_refVal);
	m_pixelValue = (floor((refVal / lengthLine)*100.0))/100;
	m_areaValue.Format("%.2f", m_pixelValue);
	UpdateData(false);

	
	}




}


void COpenCV4Dlg::OnBnClickedRadioThreshold()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}


void COpenCV4Dlg::OnBnClickedRadioCircle()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

}


void COpenCV4Dlg::OnOptionsShowcircle()
{
	// TODO: Add your command handler code here
	//cv::Mat frame;
	//imageOption.copyTo(frame);
	//cv::line(frame, startPoint, endPoint, cv::Scalar(0, 0, 255), 2);
	//cv::circle(frame, cv::Point(startPoint.x, startPoint.y), 5, cv::Scalar(0, 255, 0), 2);
	//cv::circle(frame, cv::Point(endPoint.x, endPoint.y), 5, cv::Scalar(0, 255, 0), 2);
	showCircle = true;
	//imshow("Image", frame);

}


void COpenCV4Dlg::OnOptionsHidecircles()
{
	// TODO: Add your command handler code here

	showCircle = false;
	//cv::Mat frame;
	//imageOption.copyTo(frame);
	//cv::line(frame, startPoint, endPoint, cv::Scalar(0, 0, 255), 2);
	//
	//
	////imshow("Image", frame);


}


void COpenCV4Dlg::OnOptionsExit()
{
	// TODO: Add your command handler code here
	OnClose();
	OnOK();
}


void COpenCV4Dlg::OnBnClickedLoadVideo()
{
	CFileDialog m_ldFile(true);
	int key;
	cv::Mat frame;

	if (m_ldFile.DoModal() == IDOK) {
		// TODO: Add your control notification handler code here
		CString filePath = m_ldFile.GetPathName();
		std::string PathOfFile((char*)filePath.GetBuffer(), filePath.GetLength());

		//temp = cv::imread(PathOfFile);
		//cv::cvtColor(temp, mOriginalFrame, cv::COLOR_GRAY2BGR);
		cap.open(PathOfFile);
		if (cap.isOpened()) {
			cap >> frame;
		startPoint.x = round(frame.cols / 2 - 50);
		endPoint.x = round(frame.cols / 2 + 50);
		startPoint.y = round(frame.rows / 2);
		endPoint.y = startPoint.y;
		}
	}
	m_fileLoad.Format("File Loaded");
	UpdateData(false);


}







void COpenCV4Dlg::OnBnClickedButton5()// Start
{
	// TODO: Add your control notification handler code here
	showVideo = 1;

	//obj->cap >> frame;
	//cv::imshow("Image", frame);
	
	

}


void COpenCV4Dlg::OnBnClickedStopVideo()
{
	// TODO: Add your control notification handler code here
	showVideo = 0;

}


UINT COpenCV4Dlg::threadProc(LPVOID param)
{
	// TODO: Add your implementation code here.
	COpenCV4Dlg* obj = (COpenCV4Dlg*)param;
	

	cv::Mat frame, temp1, temp2;

			while (obj->m_startThread) {
				if (obj->cap.isOpened() && obj->showVideo) {
					obj->cap >> frame;
					frame.copyTo(obj->lastFrame);
				
					if (~frame.empty()) {
	
						
							if (obj->m_imageType == 1) {
								cv::Canny(obj->lastFrame,temp1, obj->threshold1, obj->threshold2, obj->kernelSize);
								cv::cvtColor(temp1, obj->imageOption, CV_GRAY2BGR);


								//		cv::threshold(frame, outPut, threshold2, 255, CV_THRESH_BINARY);

							}
							else if (obj->m_imageType == 2) {

								cv::cvtColor(obj->lastFrame, temp1, CV_BGR2GRAY);
								cv::threshold(temp1, temp2, obj->thresholdValue, 255, cv::THRESH_BINARY);
								cv::cvtColor(temp2, obj->imageOption, CV_GRAY2BGR);



							}
							else {
								obj->lastFrame.copyTo(obj->imageOption);

							}


				

						obj->imageOption.copyTo(temp1);

						if (obj->showCircle) {
							cv::circle(temp1, cv::Point(obj->startPoint.x, obj->startPoint.y), 5, cv::Scalar(0, 255, 0), 2);
							cv::line(temp1, cv::Point(obj->startPoint.x, obj->startPoint.y), cv::Point(obj->endPoint.x, obj->endPoint.y), cv::Scalar(0, 0, 255), 2);
							cv::circle(temp1, cv::Point(obj->endPoint.x, obj->endPoint.y), 5, cv::Scalar(0, 255, 0), 2);

						}
						else
							cv::line(temp1, cv::Point(obj->startPoint.x, obj->startPoint.y), cv::Point(obj->endPoint.x, obj->endPoint.y), cv::Scalar(0, 0, 255), 2);

						
						//**************************************
					}
				}
			//obj->cap >> frame;
			//cv::imshow("Image", frame);
				obj->DisplayImage(temp1, 1023);
			Sleep(50);
			
			
			

			}
	
	return TRUE;
	}



void COpenCV4Dlg::OnBnClickedButtonFit()
{
	// TODO: Add your control notification handler code here


}



void COpenCV4Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	showVideo = 0;
	cap.release();
	
	m_startThread = 0;
	
	CDialogEx::OnClose();
}











void COpenCV4Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	int newX, newY;
	CRect rect, rectParent;
	CPoint p1;
	CWnd* parent = GetDlgItem(IDC_IMG)->GetParent();
	parent->GetWindowRect(&rectParent);
	
	p1.x = point.x;
	p1.y = point.y;
	
	ClientToScreen(&p1);
	
	GetDlgItem(IDC_IMG)->GetWindowRect(&rect);
	//GetDlgItem(1023)->
	

	//m_fileLoad.Format("newX=%d, newY=%d, p1.x=%d, p1.y=%d, point.x=%d, point.y=%d",newX, newY, p1.x, p1.y, point.x, point.y);
	if ((p1.x >= rect.left) && (p1.x <= rect.right) && (p1.y <= rect.bottom) && (p1.y >= rect.top)) 
		
		m_fileLoad.Format("Inside rect.left=%d < X=%d < rect.right=%d | rect.top=%d < Y=%d < rect.bottom=%d", rect.left, p1.x, rect.right, rect.top, p1.y,   rect.bottom );
	else	
		m_fileLoad.Format("Outside rect.left=%d < X=%d < rect.right=%d | rect.top=%d < Y=%d < rect.bottom=%d", rect.left, p1.x, rect.right, rect.top, p1.y, rect.bottom);
	//}
//	else {
	//	m_fileLoad = "Outside";

	//}
	

	//m_fileLoad.Format("Parent.left = %d , rect.left = %d, Parent.right = %d , rect.right = %d", rectParent.left, rect.left, rectParent.right,  rect.right);
	UpdateData(false);


	CDialogEx::OnLButtonDblClk(nFlags, point);
}
