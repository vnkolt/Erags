// era2era3Dlg.h : header file
//

#if !defined(AFX_ERA2ERA3DLG_H__8018F847_6424_4DCA_9785_EC46212A2023__INCLUDED_)
#define AFX_ERA2ERA3DLG_H__8018F847_6424_4DCA_9785_EC46212A2023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CSexRecord : public CObject {
public:
  CString m_Name;
  bool    m_fSex;
  CSexRecord(LPCTSTR szName, bool fSex) {
    m_Name = szName;
    m_fSex = fSex;
  }
};

class C2FieldRecord : public CObject {
public:
  CString m_Value1;
  CString m_Value2;
  C2FieldRecord(LPCTSTR szValue1, LPCTSTR szValue2) {
    m_Value1 = szValue1;
    m_Value2 = szValue2;
  }
};

typedef CTypedPtrMap<CMapStringToOb,CString,CSexRecord*>    SEXMap;
typedef CTypedPtrMap<CMapStringToOb,CString,C2FieldRecord*> RECORDMap;

void  FreeSexMap(SEXMap& map);
void  Free2FieldMap(RECORDMap& map);

/////////////////////////////////////////////////////////////////////////////
// CEra2era3Dlg dialog

class CEra2era3Dlg : public CDialog
{
// Construction
public:
	CEra2era3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEra2era3Dlg)
	enum { IDD = IDD_ERA2ERA3_DIALOG };
	CProgressCtrl	m_ProgressTotal;
	CProgressCtrl	m_ProgressFile;
	CListCtrl	m_oldFileList;
	CListCtrl	m_newFileList;
	//}}AFX_DATA

  CStringArray        m_SourceFiles;
  CDWordArray         m_RecArray;
  long                m_TotalRecs;
  long                m_FilePos;
  long                m_TotalPos;

// maps
  SEXMap              m_Names;
  SEXMap              m_Patronymics;
  CMapStringToString  m_Banks;
  RECORDMap           m_Cities;
  CMapStringToString  m_Regions;
  CMapStringToString  m_Districts;
  RECORDMap           m_Countries;
  CMapStringToString  m_Streets;
  RECORDMap           m_Nations;
  CMapStringToString  m_RAGSes;
  CMapStringToString  m_ROVDs;
  CMapStringToString  m_MHospitals;
  CMapStringToString  m_Hospitals;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEra2era3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

  void  SetName(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName, LPCTSTR szWhat=NULL);
  void  SetPatronymic(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName, LPCTSTR szWhat=NULL);

  void  SetCountry(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

  void  SetCitizen(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

  void  SetNation(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, BOOL fSex, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName, BOOL fToMemo=FALSE);
  void  SetNationToMemo(CDaoRecordset& rsNew, CDaoRecordset& rsOld, int NAZ, COleDateTime& DateReg, BOOL fSex, COleVariant var, LPCTSTR szMemoFld, LPCTSTR szFieldDesc, LPCTSTR szActName);

  void  SetDistrict(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
  void  SetRegion(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
  void  SetCity(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

  void  SetStreet(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);

  void  SetROVD(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
  void  SetRAGS(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
  void  SetBank(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var, LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName);
  void  SetMemo(CDaoRecordset& rsNew, LPCTSTR szMemoNew, COleVariant& varMemoOld);
  void  AddToMemo(CDaoRecordset& rsNew, LPCTSTR szMemoFld, LPCTSTR szWhat, const CString& sValue);


  void  FillFileList();
  void  FillSexMap(SEXMap& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField);
  void  Fill2FieldMap(RECORDMap& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szField1, LPCTSTR szField2);
  void  FillStringMap(CMapStringToString& map, CDaoDatabase& db, LPCTSTR szTableName, LPCTSTR szKeyField, LPCTSTR szValueField);
  void  CopyDeath(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut);
  void  CopyBirth(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut);
  void  CopyMarriage(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut);
  void  CopyDivorce(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut);
  void  CopyChange(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut);
  long  GetRecs(int nIndex);
  bool  IsTablePresent(CDaoDatabase& dbIn, LPCTSTR szTable);
  void  Convert(int nIndex);

	// Generated message map functions
	//{{AFX_MSG(CEra2era3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChooseOld();
	afx_msg void OnChooseNew();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERA2ERA3DLG_H__8018F847_6424_4DCA_9785_EC46212A2023__INCLUDED_)
