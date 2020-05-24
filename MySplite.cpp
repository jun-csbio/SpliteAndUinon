// MySplite.cpp : implementation file
//

#include "stdafx.h"
#include "SpliteAndUinon.h"
#include "MySplite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySplite dialog


CMySplite::CMySplite(CWnd* pParent /*=NULL*/)
	: CDialog(CMySplite::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySplite)
	m_smallMB = 0;
	//}}AFX_DATA_INIT
}


void CMySplite::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySplite)
	DDX_Text(pDX, IDC_EDIT_SMALLMB, m_smallMB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMySplite, CDialog)
	//{{AFX_MSG_MAP(CMySplite)
	ON_BN_CLICKED(IDC_BTN_SCAN, OnBtnScan)
	ON_BN_CLICKED(IDC_BTN_SPLITE, OnBtnSplite)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySplite message handlers
BOOL isSpliteOK = FALSE;		//是否分割成功
UINT g_smallFileNum = 0;		//记录已经产生的小文件的个数
UINT g_smallFileMB = 0;			//记录每个文件已经转移的大小

//分割文件函数
UINT SpliteToNum(LPVOID pParam)
{
	BOOL Succ = TRUE;
	DWORD i = 1;

	DWORD dwBitsSize = 0;      //dwBitsSize是指定写入文件的字节数
	CFile filed;
	CString FileNum;   
	CString FileNTemp;

	//开辟数据缓冲区
	HANDLE filedate = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, PerSize);
	unsigned char *imgtemp = (unsigned char *)::GlobalLock((HGLOBAL)filedate);	
	
	//设置文件指针指向文件开始位置
	((CDoFileInfo *)pParam)->files.SeekToBegin();
	//分割文件,并写入磁盘
	while (Succ)
	{
		FileNum.Format("%d", i);		//分解后文件的编号
		i++;
		FileNTemp = ((CDoFileInfo *)pParam)->fileTitle + "_029" + "[" + FileNum + "]" + "." + ((CDoFileInfo *)pParam)->fileExt;
		filed.Open(FileNTemp, CFile::modeCreate|CFile::modeWrite, 0);
		//产生第i个小文件
		g_smallFileMB = 0;
		for (int j=0; j<(((CDoFileInfo *)pParam)->smallb)/PerSize; j++)
		{
			g_smallFileMB++;
			dwBitsSize = ((CDoFileInfo *)pParam)->files.ReadHuge(imgtemp, PerSize);  //<64K可以用Read函数	
			if (dwBitsSize <= 0)
			{
				i--;
				filed.Close();
				CFile::Remove(FileNTemp);
				g_smallFileNum = i - 1;			//同时返回产生的文件数目
				goto TAG; //return 0;
			}
			filed.WriteHuge(imgtemp, dwBitsSize);

			if (PerSize != dwBitsSize)
			{
				Succ = FALSE;
				break;
			}
		}//end_for_j
		filed.Close();
	} //while

	g_smallFileNum = i - 1;
	//解除邦定/释放内存
TAG:isSpliteOK = TRUE;
	::GlobalUnlock((HGLOBAL)imgtemp); 
	::GlobalFree(filedate);

	AfxMessageBox("文件分割完毕!");
	return 0;
}

void CMySplite::OnBtnScan()
{
	char Filter[] = "所有文件(*.*)|*.*||";		//打开的文件类型
	CFileDialog dlgOpen(TRUE, NULL, NULL,  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCSTR)Filter, NULL); //设置文件对话框模式
	if (IDOK == dlgOpen.DoModal())
	{
		fileInfo.filePath = dlgOpen.GetPathName();
		fileInfo.fileTitle = dlgOpen.GetFileTitle();
		fileInfo.fileExt = dlgOpen.GetFileExt();

		((CEdit *)GetDlgItem(IDC_EDIT_PATH))->SetWindowText(fileInfo.filePath);
	}	
}

void CMySplite::OnBtnSplite() 
{
	CFileException fe;
	if (!fileInfo.files.Open(fileInfo.filePath, CFile::modeRead|CFile::shareDenyWrite, &fe))
	{
		CString sMsg;
		sMsg.Format("读取%s文件时发生错误!", fileInfo.filePath);
		AfxMessageBox(sMsg, MB_OK, 0);
		return ;
	}

	//刷新m_smallMB的值
	UpdateData();
	if ((1>m_smallMB) || (800<m_smallMB))
	{
		AfxMessageBox("请输入一个数范围是（1--800）MB");
		fileInfo.files.Close();
		return ;
	}
	fileInfo.smallb = m_smallMB * PerSize;

	((CButton *)GetDlgItem(IDC_BTN_SPLITE))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BTN_EXIT))->EnableWindow(FALSE);

	SetTimer(1, 50, NULL);
	//产生线程来实现文件分割
	AfxBeginThread(SpliteToNum, &fileInfo);
}

void CMySplite::OnBtnExit() 
{
	OnCancel();	
}

void CMySplite::OnTimer(UINT nIDEvent) 
{
	if (isSpliteOK)
	{
		((CButton *)GetDlgItem(IDC_BTN_SPLITE))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BTN_EXIT))->EnableWindow(TRUE);
		fileInfo.files.Close();	
		isSpliteOK = FALSE;
		KillTimer(1);
	}

	//为什么没有及时的显示出来。需要互斥访问吗？
	CString str;
	str.Format("%d", g_smallFileNum);
	((CEdit *)GetDlgItem(IDC_EDIT_NUM))->SetWindowText(str);
	//进行进度条控制
	//.................

	CDialog::OnTimer(nIDEvent);
}
