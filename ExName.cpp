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

UINT g_fileSl = 0; //��¼С�ļ�����Ŀ

// CExName message handlers

void CExName::OnBtnScan() 
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

void CExName::SearchAllFiles()
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
			AfxMessageBox("�Բ�����ѡ����ļ����ܲ���Ҫ�������ļ��������ļ�����...�밴�¡��������ѡ��");
			return ;
		}
	}
	else
	{
		AfxMessageBox("�Բ�����ѡ����ļ����ܲ���Ҫ�������ļ��������ļ�����...�밴�¡��������ѡ��");
		return ;
	}

	g_fileSl = 0;  //?????
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
					g_fileSl++;						//��¼Ҫ�ϲ��ļ�����Ŀ
					m_list.AddString((LPCTSTR)tempStr); //�����б��	
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

	//����û��������չ��	
	((CEdit *)GetDlgItem(IDC_EDIT_EXT))->GetWindowText(strExt);
	if ('.' != strExt.GetAt(0))
	{
		AfxMessageBox("����û��������Ч����չ��...");
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
	
	//û�����ĸ��ļ�����ʧ����ô����
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

	AfxMessageBox("������չ���ɹ�!!");
}

void CExName::OnBtnShow() 
{
	m_list.ResetContent();  //���List���������
	SearchAllFiles();
}
