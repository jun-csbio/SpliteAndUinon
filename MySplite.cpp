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
BOOL isSpliteOK = FALSE;		//�Ƿ�ָ�ɹ�
UINT g_smallFileNum = 0;		//��¼�Ѿ�������С�ļ��ĸ���
UINT g_smallFileMB = 0;			//��¼ÿ���ļ��Ѿ�ת�ƵĴ�С

//�ָ��ļ�����
UINT SpliteToNum(LPVOID pParam)
{
	BOOL Succ = TRUE;
	DWORD i = 1;

	DWORD dwBitsSize = 0;      //dwBitsSize��ָ��д���ļ����ֽ���
	CFile filed;
	CString FileNum;   
	CString FileNTemp;

	//�������ݻ�����
	HANDLE filedate = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, PerSize);
	unsigned char *imgtemp = (unsigned char *)::GlobalLock((HGLOBAL)filedate);	
	
	//�����ļ�ָ��ָ���ļ���ʼλ��
	((CDoFileInfo *)pParam)->files.SeekToBegin();
	//�ָ��ļ�,��д�����
	while (Succ)
	{
		FileNum.Format("%d", i);		//�ֽ���ļ��ı��
		i++;
		FileNTemp = ((CDoFileInfo *)pParam)->fileTitle + "_029" + "[" + FileNum + "]" + "." + ((CDoFileInfo *)pParam)->fileExt;
		filed.Open(FileNTemp, CFile::modeCreate|CFile::modeWrite, 0);
		//������i��С�ļ�
		g_smallFileMB = 0;
		for (int j=0; j<(((CDoFileInfo *)pParam)->smallb)/PerSize; j++)
		{
			g_smallFileMB++;
			dwBitsSize = ((CDoFileInfo *)pParam)->files.ReadHuge(imgtemp, PerSize);  //<64K������Read����	
			if (dwBitsSize <= 0)
			{
				i--;
				filed.Close();
				CFile::Remove(FileNTemp);
				g_smallFileNum = i - 1;			//ͬʱ���ز������ļ���Ŀ
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
	//����/�ͷ��ڴ�
TAG:isSpliteOK = TRUE;
	::GlobalUnlock((HGLOBAL)imgtemp); 
	::GlobalFree(filedate);

	AfxMessageBox("�ļ��ָ����!");
	return 0;
}

void CMySplite::OnBtnScan()
{
	char Filter[] = "�����ļ�(*.*)|*.*||";		//�򿪵��ļ�����
	CFileDialog dlgOpen(TRUE, NULL, NULL,  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCSTR)Filter, NULL); //�����ļ��Ի���ģʽ
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
		sMsg.Format("��ȡ%s�ļ�ʱ��������!", fileInfo.filePath);
		AfxMessageBox(sMsg, MB_OK, 0);
		return ;
	}

	//ˢ��m_smallMB��ֵ
	UpdateData();
	if ((1>m_smallMB) || (800<m_smallMB))
	{
		AfxMessageBox("������һ������Χ�ǣ�1--800��MB");
		fileInfo.files.Close();
		return ;
	}
	fileInfo.smallb = m_smallMB * PerSize;

	((CButton *)GetDlgItem(IDC_BTN_SPLITE))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BTN_EXIT))->EnableWindow(FALSE);

	SetTimer(1, 50, NULL);
	//�����߳���ʵ���ļ��ָ�
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

	//Ϊʲôû�м�ʱ����ʾ��������Ҫ���������
	CString str;
	str.Format("%d", g_smallFileNum);
	((CEdit *)GetDlgItem(IDC_EDIT_NUM))->SetWindowText(str);
	//���н���������
	//.................

	CDialog::OnTimer(nIDEvent);
}
