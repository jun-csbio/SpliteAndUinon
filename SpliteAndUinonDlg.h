// SpliteAndUinonDlg.h : header file
//

#if !defined(AFX_SPLITEANDUINONDLG_H__D2EB744C_150C_4FCB_A889_92F8038DF84C__INCLUDED_)
#define AFX_SPLITEANDUINONDLG_H__D2EB744C_150C_4FCB_A889_92F8038DF84C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpliteAndUinonDlg dialog

class CSpliteAndUinonDlg : public CDialog
{
// Construction
public:
	CSpliteAndUinonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpliteAndUinonDlg)
	enum { IDD = IDD_SPLITEANDUINON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpliteAndUinonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpliteAndUinonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSplite();
	afx_msg void OnBtnUnion();
	afx_msg void OnBtnExname();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITEANDUINONDLG_H__D2EB744C_150C_4FCB_A889_92F8038DF84C__INCLUDED_)
