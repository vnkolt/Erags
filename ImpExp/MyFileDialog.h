#if !defined(AFX_MYFILEDIALOG_H__940B1C47_4EC3_4565_B62E_EF048817169A__INCLUDED_)
#define AFX_MYFILEDIALOG_H__940B1C47_4EC3_4565_B62E_EF048817169A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog dialog

class CMyFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMyFileDialog)

public:
	CMyFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	virtual int  DoModal();
	virtual void OnInitDone();

// Data members:
private:
  CString         m_sFileName;

  CSpinButtonCtrl m_Spin;
  int     m_ResourseID;
  CString m_szFileTitle;
// Operations:
public:
    void  SetTitle(int ResourseID, LPCTSTR szTitle) {
      m_ResourseID = ResourseID;
      m_szFileTitle = szTitle;
    }

	// for dialog data exchange and validation
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//{{AFX_MSG(CMyFileDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILEDIALOG_H__940B1C47_4EC3_4565_B62E_EF048817169A__INCLUDED_)
