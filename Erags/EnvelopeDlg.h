#if !defined(AFX_ENVELOPEDLG_H__8E511584_5970_4335_8E9F_A3551735035E__INCLUDED_)
#define AFX_ENVELOPEDLG_H__8E511584_5970_4335_8E9F_A3551735035E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnvelopeDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\EraControls.h"

class CRListRecord;

struct TransRecord {
  CString szUkr;
  CString szRus;
  long    lType;  // TRANSF_WORD, TRANSF_BOS, TRANSF_EOS, TRANSF_SUBS
};

class CTransList {
public:
  CTransList();
  ~CTransList();
private:
  void  Clear(CPtrArray& array);
  void  Sort(CPtrArray& array);
public:
  BOOL    Load();
  void    FillTokenArray(const char* szSrc, CStringArray& tokens);
  void    Translate(CEraEdit* pEdit);
public:
  CPtrArray m_Words;
  CPtrArray m_Begins;
  CPtrArray m_Ends;
  CPtrArray m_Subs;
};

/////////////////////////////////////////////////////////////////////////////
// CEnvelopeDlg dialog

class CEnvelopeDlg : public CDialogEx
{
// Construction
public:
	CEnvelopeDlg(UINT nPrintID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnvelopeDlg)
	enum { IDD = IDD_ENVELOPE };
  CFrameBG  m_Frame1;
  CFrameBG  m_Frame2;
	CEraEdit	m_Sender_Coutry;
	CEraEdit	m_Sender_Region;
	CEraEdit	m_Sender_City;
	CEraEdit	m_Sender_Address;
	CEraEdit	m_Sender_Index;
	CEraEdit	m_Sender;
	CEraEdit	m_Addressee;
	CEraEdit	m_Addressee_Coutry;
	CEraEdit	m_Addressee_Region;
	CEraEdit	m_Addressee_City;
	CEraEdit	m_Addressee_Address;
	CEraEdit	m_Addressee_Index;
	//}}AFX_DATA

  CRListRecord* m_pRecord;
  CTransList    m_TransList;
  BOOL          m_fTranslate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnvelopeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnvelopeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENVELOPEDLG_H__8E511584_5970_4335_8E9F_A3551735035E__INCLUDED_)
