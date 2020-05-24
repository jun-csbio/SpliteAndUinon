// ExName.cpp : implementation file
//

#include "stdafx.h"
#include "SpliteAndUinon.h"
#include "ExName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExName dialog


CExName::CExName(CWnd* pParent /*=NULL*/)
	: CDialog(CExName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExName)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExName, CDialog)
	//{{AFX_MSG_MAP(CExName)
	ON_BN_CLICKED(IDC_BTN_SCAN, OnBtnScan)
	ON_BN_CLICKED(IDC_BTN_EXEXT, OnBtnExext)
	ON_BN_CLICKED(IDC_BTN_SHOW, OnBtnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

UINT g_fileSl = 0; //记录小文件的数目

// CExName message handlers

void CExName::OnBtnScan() 
{
	char Filter[] = "所有文件(*.*)|*.*||";		//打开的文件类型
	CFileDialog dlgOpen(TRUE, NULL, NULL,  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCSTR)Filter, NULL); //设置文件对话框模式
	if (IDOK == dlgOpen.DoModal())
	{
		fileInfo.filePath = dlgOpen.GetPathName();
		fileInfo.fileTitle = dlgOpen.GetFileTitle();
		fileInfo.fileExt = dlgOpen.GetFileExt();

		((CEdit *)GetDlgItem(IDC_EDIT_PATH))->SetWindowText(fileInfo.filePath);
		
		m_list.ResetContent();  //清空List里面的内容
		SearchAllFiles();
	}	
}

void CExName::SearchAllFiles()
{
	CFileFind finder;
	CString tempStr, tempTitle;
	CString FileTitleTemp = fileInfo.fileTitle;
	int tempPos;

	if (3 < FileTitleTemp.GetLength())   //被分割后的文件title的长度至少为4//[x]
	{
		tempPos = FileTitleTemp.ReverseFind('['); //从后面开始搜索'['
		if (tempPos >= 1)				//如果没找到或者不符合要求则什么都不作
		{
			FileTitleTemp = FileTitleTemp.Left(tempPos);			
		}
		else
		{
			AfxMessageBox("对不起，您选择的文件可能不是要操作的文件，或者文件被损坏...请按下“浏览”在选择");
			return ;
		}
	}
	else
	{
		AfxMessageBox("对不起，您选择的文件可能不是要操作的文件，或者文件被损坏...请按下“浏览”在选择");
		return ;
	}

	g_fileSl = 0;  //?????
	BOOL bWorking = finder.FindFile("*.*");
	while(bWorking)
	{
		bWorking = finder.FindNextFile(); //find next file

		tempStr = finder.GetFileName();
		tempTitle = finder.GetFileTitle();

		if (3 < tempTitle.GetLength())   //被分割后的文件title的长度至少为4//[x]
		{
			tempPos = tempTitle.ReverseFind('['); //从后面开始搜索'['
			if (tempPos >= 1)			//如果没找到或者不符合要求则什么都不作
			{
				tempTitle = tempTitle.Left(tempPos);
				if (tempTitle == FileTitleTemp)   //如果除去一切杂质后与选择的Title - [x]一样
				{
					g_fileSl++;						//记录要合并文件的数目
					m_list.AddString((LPCTSTR)tempStr); //加入列表框	
				}	
			}
		}		
	}//while
}

void CExName::OnBtnExext() 
{
	CString fileHalfPath;
	CString FileTitleTemp = fileInfo.fileTitle;
	fileHalfPath = fileInfo.filePath.Left(fileInfo.filePath.GetLength()-fileInfo.fileTitle.GetLength()-fileInfo.fileExt.GetLength()-1);
	fileHalfPath += FileTitleTemp.Left(FileTitleTemp.ReverseFind('['));

	//获得用户输入的扩展名	
	((CEdit *)GetDlgItem(IDC_EDIT_EXT))->GetWindowText(strExt);
	if ('.' != strExt.GetAt(0))
	{
		AfxMessageBox("您还没有输入有效的扩展名...");
		((CEdit *)GetDlgItem(IDC_EDIT_EXT))->GetCapture(); //???????
		return ;
	}
	else
	{
		strExt = strExt.Right(strExt.GetLength()-1);
	}
	CString tempPath;
	CString oldPath;
	CString str;
	CFileException fe;
	
	//没能做哪个文件被丢失后怎么处理
	for (DWORD i=1; i<=g_fileSl; i++)
	{
		str.Format("[%d].", i);
		oldPath = fileHalfPath + str + fileInfo.fileExt;
		tempPath = fileHalfPath + str + strExt;
		CFile::Rename(oldPath, tempPath);
	}//for
	
	//????????
	fileInfo.fileExt = strExt;
	fileInfo.filePath = fileHalfPath + "[1]." + strExt;

	AfxMessageBox("更改扩展名成功!!");
}

void CExName::OnBtnShow() 
{
	m_list.ResetContent();  //清空List里面的内容
	SearchAllFiles();
}
