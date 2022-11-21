#if !defined(AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_)
#define AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RepairDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CRepairDlg dialog
class CRepairDlg : public CDialog {
// Construction
public:
	CRepairDlg(LPCTSTR szFieldName, LPCTSTR szActName,
             int nAct, COleDateTime DateReg,
             LPCTSTR szNameOf, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRepairDlg)
	enum { IDD = IDD_REPAIR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  CString       m_szFieldName, m_szActName;
  int           m_nAct;
  COleDateTime  m_DateReg;
  CString       m_NameOf;
  CString       m_szFieldValue; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepairDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRepairDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeWhat();
	afx_msg void OnNomore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


void AddToMemo(CDaoRecordset& rsNew, LPCTSTR szMemoFld, LPCTSTR szWhat, const CString& sValue);
void SetName(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName, LPCTSTR szWhat=NULL);
void SetPatronymic(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                   LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
                   LPCTSTR szWhat=NULL);

void SetCountry(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
void SetRegion(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

void SetCity(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
void SetDistrict(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                 LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
void SetStreet(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

void SetCitizen(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName );


void SetNation(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, BOOL fSex, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
               BOOL fToMemo=FALSE);
void SetNationToMemo(CDaoRecordset& rsNew, CDaoRecordset& rsOld,
                     int NAZ, COleDateTime& DateReg, BOOL fSex,
                     COleVariant var, LPCTSTR szMemoFld, LPCTSTR szFieldDesc, LPCTSTR szActName);

void SetRAGS(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
void SetROVD(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);


void SetBank(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPAIRDLG_H__E1569767_EEFE_43C1_B4A9_E4895F8F42BD__INCLUDED_)
