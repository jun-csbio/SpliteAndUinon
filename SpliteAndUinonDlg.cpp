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
		str = "�����ļ���΢С�ļ�֮���ת��";
		 
		CFont fontLogo;
		fontLogo.CreateFont(32, 0, 0, 0, 55, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "Arial");

		dc.SetBkMode(TRANSPARENT);
		CRect rectText;
		GetClientRect(&rectText);
		CFont *oldFont = (CFont *)dc.SelectObject(&fontLogo);
		//��DC���������
		COLORREF oldColor = dc.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		dc.DrawText(str, rectText, DT_SINGLELINE|DT_LEFT|DT_CENTER);
		dc.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		dc.DrawText(str, rectText, DT_SINGLELINE|DT_LEFT|DT_CENTER);

		//�ȱ���ԭ����������ɫ
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
		str = "   ���´˼�����ʵ�ֱ��ָ���΢С�ļ��ϲ���Ϊһ�����ļ�";
		str += "\n\n���������ļ�����Ȼ�ϲ��ɽϴ���ļ�ʱ��Ҫһ��ʱ�䣬��\n\n���ʱ�����������һ����ҳ���������š�";
	}
	else if (changeRect.PtInRect(curPos))
	{
		str = "   ���´˼�����ʵ�ֱ��ָ���΢С�ļ�ͳһ������չ����";
		str += "\n\n�����ͨ��������չ�����Ի�ʹ���ߣ�ʹ����Ϊ����\n\nһ������ļ�������һ���������е��ļ���";
	}
	else if (spliteRect.PtInRect(curPos))
	{
		str = "   ���´˼�����ʵ�ִ洢�ռ�ϴ���ļ������Ǻ����ļ�";
		str += "\n\n�ָ��ռ��ָ����С��΢С�洢�ռ��С�ļ���������\n\n���������ڴ��ļ���С�����Ĵ洢��ת�ơ�";
	}
	else
	{
		str = "   �˳�����Ҫ��Ϊ��ʵ�ֵ��ļ�ת����С�ļ�ת�ƺ��ٺϲ���";
		str += "\n\n��Ȼ�ڷָ���ϲ���ʱ����Ҫһ����ʱ�䣬�������ĵȺ�";
		str += "\n\n���⣬��С�����ṩ���ļ��ָ���ͳһ������չ���Ĺ�";
		str += "\n\n�ܡ� ";
		str += "\n\n                                        �����ߣ�����";
		str += "\n                                        ����ʦ����ѧ";
		str += "\n                                        QQ:919269426";
		str += "\n                                        ����:2011/2/1";
	}
	
	((CStatic *)GetDlgItem(IDC_MINDER))->SetWindowText(str);
	
	CDialog::OnTimer(nIDEvent);
}
