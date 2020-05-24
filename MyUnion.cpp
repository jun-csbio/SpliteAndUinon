// MyUnion.cpp : implementation file
//

#include "stdafx.h"
#include "SpliteAndUinon.h"
#include "MyUnion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyUnion dialog


CMyUnion::CMyUnion(CWnd* pParent /*=NULL*/)
	: CDialog(CMyUnion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyUnion)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyUnion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyUnion)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyUnion, CDialog)
	//{{AFX_MSG_MAP(CMyUnion)
	ON_BN_CLICKED(IDC_BTN_SCAN, OnBtnScan)
	ON_BN_CLICKED(IDC_BTN_HEBING, OnBtnHebing)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
UINT	g_fileNum = 0;
DWORD	g_smallFileLong = 0;
CString g_strHalfPath;  //eg:G:\Vadio\gils
BOOL	isUnionOK = FALSE; //标记是不是合并完毕

UINT UnionToOneFile(LPVOID pParam)
{
	if (0 == g_fileNum)
	{
		AfxMessageBox("您还没有选择文件... 请选择相应文件!");
		return 0;
	}

//	((CButton *)GetDlgItem(IDC_BTN_HEBING))->EnableWindow(FALSE);

	DWORD dwBitsSize = 0;
	//开辟数据缓冲区，大小为一张软盘的大小
	HANDLE filedate = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, PerSize);
	unsigned char *imgtemp = (unsigned char *)::GlobalLock((HGLOBAL)filedate);	//内存邦定

	///////////////////////////////////////////////////////////////////////////////////////
	CString tempPath;

	CFile tempFile;
	CFile endFile;

	tempPath =g_strHalfPath + "." + ((CDoFileInfo *)pParam)->fileExt; 
	endFile.Open(tempPath, CFile::modeCreate|CFile::modeWrite, 0);	//创建要生成的文件

	CString str;
	CFileException fe;	
	for (DWORD i=1; i<=g_fileNum; i++)
	{
		str.Format("[%d].", i);
		tempPath = g_strHalfPath + str + ((CDoFileInfo *)pParam)->fileExt; 
		if (!tempFile.Open(tempPath, CFile::modeRead|CFile::shareDenyWrite, &fe))
		{	
			CString sMsg;
			sMsg.Format("读取%s文件时发生错误!", tempPath);
			AfxMessageBox(sMsg, MB_OK, 0);

			CString StrPath = endFile.GetFilePath();
			endFile.Close();				//产生临时文件
			CFile::Remove(StrPath);			//删除中间文件文件
			isUnionOK = TRUE;
			return 0;
		}

		for (int j=0; j<g_smallFileLong/PerSize; j++)
		{
			dwBitsSize = tempFile.ReadHuge(imgtemp, PerSize);
			endFile.WriteHuge(imgtemp, dwBitsSize);
			if (dwBitsSize < PerSize)
			{
				break;
			}
		}//end_for_j
		
		tempFile.Close();
	}//for i

	//解除邦定/释放内存
	::GlobalUnlock((HGLOBAL)imgtemp); 
	::GlobalFree(filedate);

	//善后处理
	endFile.Close();
	isUnionOK = TRUE;
	AfxMessageBox("微文件合并成功！！");
	return 0;
}

// CMyUnion message handlers

void CMyUnion::OnBtnScan() 
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

void CMyUnion::OnBtnHebing() 
{
	g_smallFileLong = GetSingleLength();
	
	((CButton *)GetDlgItem(IDC_BTN_HEBING))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BTN_ADD))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(FALSE);

	SetTimer(2, 50, NULL);
	//产生线程去合并
	AfxBeginThread(UnionToOneFile, &fileInfo);
}

void CMyUnion::SearchAllFiles()
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
			AfxMessageBox("对不起，您选择的文件可能不是要合并的文件，或者文件被损坏...请按下“浏览”在选择");
			return ;
		}
	}
	else
	{
		AfxMessageBox("对不起，您选择的文件可能不是要合并的文件，或者文件被损坏...请按下“浏览”在选择");
		return ;
	}

	g_fileNum = 0;  //?????
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
					g_fileNum++;						//记录要合并文件的数目
					m_list.AddString((LPCTSTR)tempStr); //加入列表框	
				}	
			}
		}		
	}//while
}

//获得第一个文件的大小
DWORD CMyUnion::GetSingleLength()
{	
	CString tempPath;
	CString FileTitleTemp = fileInfo.fileTitle; //FileTitle;

	CFile tempFile;
	DWORD SingleLen = 0; //第一个文件的长度

	CString str;
	CFileException fe;
	CString sMsg;
	str.Format("[1].");
	tempPath = fileInfo.filePath.Left(fileInfo.filePath.GetLength()-fileInfo.fileTitle.GetLength()-fileInfo.fileExt.GetLength()-1);
	tempPath += FileTitleTemp.Left(FileTitleTemp.ReverseFind('['));
	g_strHalfPath = tempPath;   //储存中间情况
	tempPath += str + fileInfo.fileExt; 
	if (!tempFile.Open(tempPath, CFile::modeRead|CFile::shareDenyWrite, &fe))
	{	
		sMsg.Format("读取%s文件时发生错误!", tempPath);
		AfxMessageBox(sMsg, MB_OK, 0);
		return 0;
	}
		
	SingleLen = tempFile.GetLength();
	tempFile.Close();
	return SingleLen;
}

void CMyUnion::OnTimer(UINT nIDEvent) 
{
	if (isUnionOK)	
	{
		((CButton *)GetDlgItem(IDC_BTN_HEBING))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BTN_ADD))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(TRUE);

		isUnionOK = FALSE;
		KillTimer(2);
	}
	//进行进度条控制
	//.................

	CDialog::OnTimer(nIDEvent);
}
