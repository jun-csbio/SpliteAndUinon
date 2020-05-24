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
BOOL	isUnionOK = FALSE; //����ǲ��Ǻϲ����

UINT UnionToOneFile(LPVOID pParam)
{
	if (0 == g_fileNum)
	{
		AfxMessageBox("����û��ѡ���ļ�... ��ѡ����Ӧ�ļ�!");
		return 0;
	}

//	((CButton *)GetDlgItem(IDC_BTN_HEBING))->EnableWindow(FALSE);

	DWORD dwBitsSize = 0;
	//�������ݻ���������СΪһ�����̵Ĵ�С
	HANDLE filedate = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, PerSize);
	unsigned char *imgtemp = (unsigned char *)::GlobalLock((HGLOBAL)filedate);	//�ڴ�

	///////////////////////////////////////////////////////////////////////////////////////
	CString tempPath;

	CFile tempFile;
	CFile endFile;

	tempPath =g_strHalfPath + "." + ((CDoFileInfo *)pParam)->fileExt; 
	endFile.Open(tempPath, CFile::modeCreate|CFile::modeWrite, 0);	//����Ҫ���ɵ��ļ�

	CString str;
	CFileException fe;	
	for (DWORD i=1; i<=g_fileNum; i++)
	{
		str.Format("[%d].", i);
		tempPath = g_strHalfPath + str + ((CDoFileInfo *)pParam)->fileExt; 
		if (!tempFile.Open(tempPath, CFile::modeRead|CFile::shareDenyWrite, &fe))
		{	
			CString sMsg;
			sMsg.Format("��ȡ%s�ļ�ʱ��������!", tempPath);
			AfxMessageBox(sMsg, MB_OK, 0);

			CString StrPath = endFile.GetFilePath();
			endFile.Close();				//������ʱ�ļ�
			CFile::Remove(StrPath);			//ɾ���м��ļ��ļ�
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

	//����/�ͷ��ڴ�
	::GlobalUnlock((HGLOBAL)imgtemp); 
	::GlobalFree(filedate);

	//�ƺ���
	endFile.Close();
	isUnionOK = TRUE;
	AfxMessageBox("΢�ļ��ϲ��ɹ�����");
	return 0;
}

// CMyUnion message handlers

void CMyUnion::OnBtnScan() 
{
	char Filter[] = "�����ļ�(*.*)|*.*||";		//�򿪵��ļ�����
	CFileDialog dlgOpen(TRUE, NULL, NULL,  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCSTR)Filter, NULL); //�����ļ��Ի���ģʽ
	if (IDOK == dlgOpen.DoModal())
	{
		fileInfo.filePath = dlgOpen.GetPathName();
		fileInfo.fileTitle = dlgOpen.GetFileTitle();
		fileInfo.fileExt = dlgOpen.GetFileExt();

		((CEdit *)GetDlgItem(IDC_EDIT_PATH))->SetWindowText(fileInfo.filePath);
		
		m_list.ResetContent();  //���List���������
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
	//�����߳�ȥ�ϲ�
	AfxBeginThread(UnionToOneFile, &fileInfo);
}

void CMyUnion::SearchAllFiles()
{
	CFileFind finder;
	CString tempStr, tempTitle;
	CString FileTitleTemp = fileInfo.fileTitle;
	int tempPos;

	if (3 < FileTitleTemp.GetLength())   //���ָ����ļ�title�ĳ�������Ϊ4//[x]
	{
		tempPos = FileTitleTemp.ReverseFind('['); //�Ӻ��濪ʼ����'['
		if (tempPos >= 1)				//���û�ҵ����߲�����Ҫ����ʲô������
		{
			FileTitleTemp = FileTitleTemp.Left(tempPos);			
		}
		else
		{
			AfxMessageBox("�Բ�����ѡ����ļ����ܲ���Ҫ�ϲ����ļ��������ļ�����...�밴�¡��������ѡ��");
			return ;
		}
	}
	else
	{
		AfxMessageBox("�Բ�����ѡ����ļ����ܲ���Ҫ�ϲ����ļ��������ļ�����...�밴�¡��������ѡ��");
		return ;
	}

	g_fileNum = 0;  //?????
	BOOL bWorking = finder.FindFile("*.*");
	while(bWorking)
	{
		bWorking = finder.FindNextFile(); //find next file

		tempStr = finder.GetFileName();
		tempTitle = finder.GetFileTitle();

		if (3 < tempTitle.GetLength())   //���ָ����ļ�title�ĳ�������Ϊ4//[x]
		{
			tempPos = tempTitle.ReverseFind('['); //�Ӻ��濪ʼ����'['
			if (tempPos >= 1)			//���û�ҵ����߲�����Ҫ����ʲô������
			{
				tempTitle = tempTitle.Left(tempPos);
				if (tempTitle == FileTitleTemp)   //�����ȥһ�����ʺ���ѡ���Title - [x]һ��
				{
					g_fileNum++;						//��¼Ҫ�ϲ��ļ�����Ŀ
					m_list.AddString((LPCTSTR)tempStr); //�����б��	
				}	
			}
		}		
	}//while
}

//��õ�һ���ļ��Ĵ�С
DWORD CMyUnion::GetSingleLength()
{	
	CString tempPath;
	CString FileTitleTemp = fileInfo.fileTitle; //FileTitle;

	CFile tempFile;
	DWORD SingleLen = 0; //��һ���ļ��ĳ���

	CString str;
	CFileException fe;
	CString sMsg;
	str.Format("[1].");
	tempPath = fileInfo.filePath.Left(fileInfo.filePath.GetLength()-fileInfo.fileTitle.GetLength()-fileInfo.fileExt.GetLength()-1);
	tempPath += FileTitleTemp.Left(FileTitleTemp.ReverseFind('['));
	g_strHalfPath = tempPath;   //�����м����
	tempPath += str + fileInfo.fileExt; 
	if (!tempFile.Open(tempPath, CFile::modeRead|CFile::shareDenyWrite, &fe))
	{	
		sMsg.Format("��ȡ%s�ļ�ʱ��������!", tempPath);
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
	//���н���������
	//.................

	CDialog::OnTimer(nIDEvent);
}
