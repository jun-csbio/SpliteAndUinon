#if !defined(AFX_MYSPLITE_H__D9868B7E_CEC8_4E2A_9C6B_4E92833F42A2__INCLUDED_)
#define AFX_MYSPLITE_H__D9868B7E_CEC8_4E2A_9C6B_4E92833F42A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySplite.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySplite dialog
#include "DoFileInfo.h"

class CMySplite : public CDialog
{
// Construction
public:
	CDoFileInfo fileInfo;
	CMySplite(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMySplite)
	enum { IDD = IDD_SPLITE_DIALOG };
	UINT	m_smallMB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySplite)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMySplite)
	afx_msg void OnBtnScan();
	afx_msg void OnBtnSplite();
	afx_msg void OnBtnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPLITE_H__D9868B7E_CEC8_4E2A_9C6B_4E92833F42A2__INCLUDED_)
