// DoFileInfo.h: interface for the CDoFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOFILEINFO_H__7C3E6FA4_E68C_45E3_B2B8_8F275CC320BB__INCLUDED_)
#define AFX_DOFILEINFO_H__7C3E6FA4_E68C_45E3_B2B8_8F275CC320BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDoFileInfo  
{
public:
	CDoFileInfo();
	virtual ~CDoFileInfo();
public:
	CFile	files;
	CString filePath;
	CString fileTitle;
	CString fileExt;
	DWORD	smallb;
};

#endif // !defined(AFX_DOFILEINFO_H__7C3E6FA4_E68C_45E3_B2B8_8F275CC320BB__INCLUDED_)
