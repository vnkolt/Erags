
// DownloaderDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CDownloaderDlg dialog
class CDownloaderDlg : public CDialog {
// Construction
public:
	CDownloaderDlg(FIArray* pFIArray, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
  FIArray*      m_pFIArray;
  DWORD         m_DownloadSize;
  DWORD         m_cbDownloaded;
  CProgressCtrl m_Progress;
	enum { IDD = IDD_DOWNLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

private:
  BOOL Download(LPCTSTR szServer, LPCTSTR szUrl, LPCTSTR szTarget, FILETIME& ft, DWORD dwFilesize);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  CListCtrl m_FileList;
  afx_msg void OnBnClickedOk();
};
