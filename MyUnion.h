#if !defined(AFX_MYUNION_H__C9FD7BC6_3E75_4391_9EAD_70C5184F4561__INCLUDED_)
#define AFX_MYUNION_H__C9FD7BC6_3E75_4391_9EAD_70C5184F4561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyUnion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyUnion dialog
#include "DoFileInfo.h"

class CMyUnion : public CDialog
{
// Construction
public:
	CDoFileInfo fileInfo;
public:
	DWORD GetSingleLength();
	void SearchAllFiles();
	CMyUnion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyUnion)
	enum { IDD = IDD_UNION_DIALOG };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyUnion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyUnion)
	afx_msg void OnBtnScan();
	afx_msg void OnBtnHebing();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYUNION_H__C9FD7BC6_3E75_4391_9EAD_70C5184F4561__INCLUDED_)
