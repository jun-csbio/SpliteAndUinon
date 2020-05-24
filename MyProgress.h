#if !defined(AFX_MYPROGRESS_H__D491D8D4_CA77_4990_9B4F_7AA3CF4B9DCA__INCLUDED_)
#define AFX_MYPROGRESS_H__D491D8D4_CA77_4990_9B4F_7AA3CF4B9DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyProgress dialog

class CMyProgress : public CDialog
{
// Construction
public:
	CMyProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyProgress)
	enum { IDD = IDD_PROGRESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyProgress)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESS_H__D491D8D4_CA77_4990_9B4F_7AA3CF4B9DCA__INCLUDED_)
