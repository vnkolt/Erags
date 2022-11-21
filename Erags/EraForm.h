#if !defined(AFX_ERAFORM_H__38E9F519_C711_42C4_A4C3_4FC3BEA3A612__INCLUDED_)
#define AFX_ERAFORM_H__38E9F519_C711_42C4_A4C3_4FC3BEA3A612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraForm.h : header file
//
#include "..\Controls\EraControls.h"
#include "..\Controls\KMComboBox.h"
#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"

#pragma warning(disable : 4995)

#define NO_GEO_FIELDS_DIRTY     0
#define FATHER_GEO_FIELDS_DIRTY 1
#define MOTHER_GEO_FIELDS_DIRTY 2
#define ALL_FIELDS_DIRTY        3

class CChildFrame;
/////////////////////////////////////////////////////////////////////////////
// CEraForm DAO record view
class CEraForm : public CDaoRecordViewBG {
	DECLARE_DYNAMIC(CEraForm)
protected:
	CEraForm(UINT nIDTemplate);       // protected constructor used by dynamic creation
  int          GetFormID();

  virtual void ResetControls();
  virtual void SetFocusToFirstControl() = 0;
  virtual bool RecordNew();
  virtual void EmptyTable();
public:
  virtual void SetTooltips();
  virtual void ScrollToControl(CWnd* pWnd);

// Form Data
protected:
  CString    m_szPrintItem;
public:
  long       m_ID;
  UINT       m_idTemplate;
  bool       m_fEnableRelayEvent;
  WORD       m_ShownCtrlId;
	CPPToolTip m_tooltip;
  BOOL       m_fUpdateNavigateBars;
  CWnd*      m_pFocused;

// Attributes
public:
  CDaoRecordset* m_pSet;
  BOOL           m_bEnabled;
  int            m_nPrinPos;
  BOOL           m_fPrintToWord;
  CString        m_szFormName;
protected:
  WORD    m_LastCtrlId;
  BOOL    m_fNewRecord;

  CChildFrame*  m_pParentFrame;

// Operations
public:
  void    SetBookMarks();
  void    SetDefaultDateReg(UINT idForm);
  bool    SetDefaultNumber(short& Number);


  void    SetFont();
  void    EnableForm(BOOL bEnable);
  void    Refresh();

  virtual void Find(long lID);
  void         HideTooltip();
#ifndef FREE_LICENCE
  void         RegDlgCmd();
#endif

	static void OnSetfocusCountry(CEraNameComboBox& cmbCountry);
	static void OnSetfocusRegion(CEraNameComboBox& cmbCountry, CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbCity);
	static void OnSetfocusDistrict(CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbDistrict);
  static void OnSetfocusCity(CEraNameComboBox& cmbCountry, CEraNameComboBox& cmbRegion, CEraNameComboBox& cmbDistrict, CEraNameComboBox& cmbCity);
  void OnSetfocusPassportBy(CEraSeriaEdit& PassportSeria, CEraEdit& PassportNumber, CEraComboBox& cmbPassportBy);

#ifndef FREE_LICENCE
  virtual BOOL IsRDFFieldsDirty() = 0;
  virtual void SetRDFFields() = 0;
#endif // FREE_LICENCE
  virtual void OnPrint(UINT nPrintID) = 0;

  virtual void OnBlank(const CString& szTemplate, const CString& szOut){}
  virtual void OnBlankItem();

  //void  OnBlanksMenu(UINT nPrintID);
  void  OnPrintMenu();
  void  OnRTFShell(LPCTSTR szFilename);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraForm)
	public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual CDaoRecordset* OnGetRecordset();
	virtual BOOL OnMove(UINT nIDMoveCommand);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEraForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEraForm)
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnRecordFirst();
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdatePrint(CCmdUI* pCmdUI);
	afx_msg void OnPrint();
  afx_msg void OnWord();
  afx_msg void OnTemplates();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnUpdatePrintItem(CCmdUI* pCmdUI);
	afx_msg void OnPrintItem(UINT nID);
  afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
	//}}AFX_MSG
  afx_msg void OnHelp();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
  LRESULT OnHideTooltips(WPARAM, LPARAM);
  LRESULT OnShowTooltips(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

BOOL    CheckDateReg(CEraForm* pForm, CEraDateEdit* pDateEdit, BOOL fNewRecord);
BOOL    IsFocusChild(CWnd* pParentWnd);
void    SaveGeoValidation(const CString& szRegion, const CString& szDistrict, const CString& szCity, BOOL fWrite);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAFORM_H__38E9F519_C711_42C4_A4C3_4FC3BEA3A612__INCLUDED_)
