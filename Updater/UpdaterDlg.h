
// UpdaterDlg.h : header file
//

#pragma once
#include "afxcmn.h"

struct SFileInfo {
  CString   szFilename;
  FILETIME  ft;
  DWORD     dwFilesize;
  CString   szMD5;
  int       nItem;
  
  SFileInfo() {
    ft.dwLowDateTime = ft.dwHighDateTime = 0;
    dwFilesize = nItem = 0;
  }
};
typedef CArray<SFileInfo, SFileInfo&> FIArray;

// CUpdaterDlg dialog
class CUpdaterDlg : public CDialog
{
// Construction
public:
	CUpdaterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UPDATER_DIALOG };
  BOOL          m_fEnableClose;
  CListCtrl     m_FileList;
  CProgressCtrl m_Progress;

  DWORD   m_dwTotalSize;
  FIArray m_Files;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
  void  FillList();
  void  Unpack(LPCTSTR szFilename);
  void  ReplaceTable(CDaoDatabase& dbOld, CDaoDatabase& dbNew, LPCTSTR szTableName);
  void  UpdateHelpers(LPCTSTR szFilename);
  void  Copy(LPCTSTR szFilename, FILETIME& ft);
  void  Update();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
