// MyProgress.cpp : implementation file
//

#include "stdafx.h"
#include "SpliteAndUinon.h"
#include "MyProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyProgress dialog


CMyProgress::CMyProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CMyProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyProgress)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyProgress, CDialog)
	//{{AFX_MSG_MAP(CMyProgress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyProgress message handlers
