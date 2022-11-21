#if !defined(AFX_LOGINDLG_H__2A0CDF4D_56B1_4A58_B554_B5C6AABB2CAC__INCLUDED_)
#define AFX_LOGINDLG_H__2A0CDF4D_56B1_4A58_B554_B5C6AABB2CAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

#define MAX_USERS 50

struct UserInfo {
  CString szUser;
  CString szPost;
  CString szPassword;
};

typedef CArray<UserInfo, UserInfo&> UserArray;

class CUsers {
public:
  CUsers();
  ~CUsers();
public:
  UserArray m_Users;
  int       m_FreeIndex;
public:
  void      Load();
  int       GetCount()   { return m_Users.GetSize(); }
  UserInfo  GetAt(int i) { return m_Users.GetAt(i);  }
  void      Add(LPCTSTR szUser, LPCTSTR szPost, LPCTSTR szPassword);
  void      Delete(LPCTSTR szUser);
};
extern CUsers theUsers;

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
class CLoginDlg : public CDialog {
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN };
	CListCtrl m_lstLogin;
  CString   m_szPassword;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnShowPassword();
	virtual void OnOK();
	afx_msg void OnEditchangeLogin();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__2A0CDF4D_56B1_4A58_B554_B5C6AABB2CAC__INCLUDED_)
