#if !defined(AFX_EXNAME_H__FAA97E0B_9A3A_4D20_ABAA_40541A771B8D__INCLUDED_)
#define AFX_EXNAME_H__FAA97E0B_9A3A_4D20_ABAA_40541A771B8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExName dialog
#include "DoFileInfo.h"

class CExName : public CDialog
{
// Construction
public:
	CDoFileInfo fileInfo;
	CString strExt;
public: 
	void SearchAllFiles();
	CExName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExName)
	enum { IDD = IDD_EXNAME_DIALOG };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExName)
	afx_msg void OnBtnScan();
	afx_msg void OnBtnExext();
	afx_msg void OnBtnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXNAME_H__FAA97E0B_9A3A_4D20_ABAA_40541A771B8D__INCLUDED_)
