// SpliteAndUinonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpliteAndUinon.h"
#include "SpliteAndUinonDlg.h"
#include "MySplite.h"
#include "MyUnion.h"
#include "ExName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpliteAndUinonDlg dialog

CSpliteAndUinonDlg::CSpliteAndUinonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpliteAndUinonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpliteAndUinonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpliteAndUinonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpliteAndUinonDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpliteAndUinonDlg, CDialog)
	//{{AFX_MSG_MAP(CSpliteAndUinonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SPLITE, OnBtnSplite)
	ON_BN_CLICKED(IDC_BTN_UNION, OnBtnUnion)
	ON_BN_CLICKED(IDC_BTN_EXNAME, OnBtnExname)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpliteAndUinonDlg message handlers

BOOL CSpliteAndUinonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(3, 500, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpliteAndUinonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CPaintDC dc(this); // device context for painting
		CString str;
		str = "海量文件与微小文件之间的转换";
		 
		CFont fontLogo;
		fontLogo.CreateFont(32, 0, 0, 0, 55, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "Arial");

		dc.SetBkMode(TRANSPARENT);
		CRect rectText;
		GetClientRect(&rectText);
		CFont *oldFont = (CFont *)dc.SelectObject(&fontLogo);
		//在DC上输出文字
		COLORREF oldColor = dc.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		dc.DrawText(str, rectText, DT_SINGLELINE|DT_LEFT|DT_CENTER);
		dc.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		dc.DrawText(str, rectText, DT_SINGLELINE|DT_LEFT|DT_CENTER);

		//先保存原来的字体颜色
		dc.SetTextColor(oldColor);
		dc.SelectObject(oldFont);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpliteAndUinonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpliteAndUinonDlg::OnBtnSplite() 
{
	CMySplite spliteDlg;
	spliteDlg.DoModal();
}

void CSpliteAndUinonDlg::OnBtnUnion() 
{
	CMyUnion unionDlg;
	unionDlg.DoModal();
}

void CSpliteAndUinonDlg::OnBtnExname() 
{
	CExName exnameDlg;
	exnameDlg.DoModal();
}

void CSpliteAndUinonDlg::OnTimer(UINT nIDEvent) 
{
	CRect spliteRect;
	CRect changeRect;
	CRect unionRect;
	CPoint curPos;
	CString str;

	
	GetCursorPos(&curPos);
	((CButton *)GetDlgItem(IDC_BTN_SPLITE))->GetWindowRect(&spliteRect);
	((CButton *)GetDlgItem(IDC_BTN_UNION))->GetWindowRect(&unionRect);
	((CButton *)GetDlgItem(IDC_BTN_EXNAME))->GetWindowRect(&changeRect);

	if (unionRect.PtInRect(curPos))
	{
		str = "   按下此键可以实现被分割后的微小文件合并成为一个大文件";
		str += "\n\n甚至海量文件。当然合并成较大的文件时需要一定时间，在\n\n这段时间里，你可以浏览一下网页，看看新闻。";
	}
	else if (changeRect.PtInRect(curPos))
	{
		str = "   按下此键可以实现被分割后的微小文件统一更改扩展名。";
		str += "\n\n你可以通过更改扩展名来迷惑使用者，使他认为这是\n\n一个别的文件甚至是一个不可运行的文件。";
	}
	else if (spliteRect.PtInRect(curPos))
	{
		str = "   按下此键可以实现存储空间较大的文件甚至是海量文件";
		str += "\n\n分割成占有指定大小的微小存储空间的小文件。这样做\n\n可以有助于大文件用小容量的存储器转移。";
	}
	else
	{
		str = "   此程序主要是为了实现但文件转换成小文件转移后再合并，";
		str += "\n\n当然在分割与合并的时候需要一定的时间，请您耐心等候。";
		str += "\n\n此外，此小程序还提供了文件分割后的统一更改扩展名的功";
		str += "\n\n能。 ";
		str += "\n\n                                        制作者：胡俊";
		str += "\n                                        安徽师范大学";
		str += "\n                                        QQ:919269426";
		str += "\n                                        日期:2011/2/1";
	}
	
	((CStatic *)GetDlgItem(IDC_MINDER))->SetWindowText(str);
	
	CDialog::OnTimer(nIDEvent);
}
