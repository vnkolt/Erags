// ABCList.h : interface of the CABCList class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABCLIST_H__BC8461B1_B192_44C9_B3B0_3CB585E8BF58__INCLUDED_)
#define AFX_ABCLIST_H__BC8461B1_B192_44C9_B3B0_3CB585E8BF58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Controls\ListViewCtrlEx.h"
#include "..\Controls\FlatHeaderCtrl.h"

#define SO_NONE    0
#define SO_ASC     1
#define SO_DESC    2

#define IML_MALE   0
#define IML_FEMALE 1


#define IMI_NO         -1

#define IMI_ASCENDING   0
#define IMI_DESCENDING  1

#define IMI_MAN         2
#define IMI_MAN_ASC     3
#define IMI_MAN_DESC    4

#define IMI_MMARRIAGE       5
#define IMI_MMARRIAGE_ASC   6
#define IMI_MMARRIAGE_DESC  7

#define IMI_WOMAN       8
#define IMI_WOMAN_ASC   9
#define IMI_WOMAN_DESC 10

#define IMI_WMARRIAGE       11
#define IMI_WMARRIAGE_ASC   12
#define IMI_WMARRIAGE_DESC  13


#define BC_SEX        0
#define BC_NUMBER     1
#define BC_DATEREG    2
#define BC_SURNAME    3
#define BC_NAME       4
#define BC_PATRONYMIC 5
#define BC_TOTAL      6

#define CC_SEX             0
#define CC_NUMBER          1
#define CC_DATEREG         2
#define CC_OLDSURNAME      3
#define CC_NEWSURNAME      4
#define CC_OLDNAME         5
#define CC_NEWNAME         6
#define CC_OLDPATRONYMIC   7
#define CC_NEWPATRONYMIC   8
#define CC_TOTAL           9

#define MC_NUMBER          0
#define MC_DATEREG         1
#define MC_MOLD_SURNAME    2
#define MC_MNEW_SURNAME    3
#define MC_MNAME           4
#define MC_MPATRONYMIC     5
#define MC_WOLD_SURNAME    6
#define MC_WNEW_SURNAME    7
#define MC_WNAME           8
#define MC_WPATRONYMIC     9
#define MC_TOTAL          10

#define DIVC_NUMBER          0
#define DIVC_DATEREG         1
#define DIVC_MOLD_SURNAME    2
#define DIVC_MNEW_SURNAME    3
#define DIVC_MNAME           4
#define DIVC_MPATRONYMIC     5
#define DIVC_WOLD_SURNAME    6
#define DIVC_WNEW_SURNAME    7
#define DIVC_WNAME           8
#define DIVC_WPATRONYMIC     9
#define DIVC_TOTAL          10

#define DC_SEX        0
#define DC_NUMBER     1
#define DC_DATEREG    2
#define DC_SURNAME    3
#define DC_NAME       4
#define DC_PATRONYMIC 5
#define DC_TOTAL      6

class CFormABC;
class CEraABCDoc;

BOOL  MoveFirst(CDaoRecordset* pSet);
BOOL  MoveLast(CDaoRecordset* pSet);

int CALLBACK CompareABCProc(LPARAM, LPARAM, LPARAM);

class ABCItemData {
public:
  long          m_ID;
  short         m_Number;
  COleDateTime  m_DateReg;
  BOOL          m_fDeleted;

  void Reset(long ID, short Number, COleDateTime DateReg) {
    m_ID        = ID;
    m_Number    = Number;
    m_DateReg   = DateReg;
    m_fDeleted  = FALSE;
  }

  virtual ~ABCItemData(){}
};

class ABCItemDataBirth : public ABCItemData {
public:
  BOOL    m_fMale;
  CString m_Surname;
  CString m_Name;
  CString m_Patronymic;
  void Reset(long ID, short Number, COleDateTime DateReg, BOOL fMale, LPCTSTR Surname, LPCTSTR Name, LPCTSTR Patronymic) {
    ABCItemData::Reset(ID, Number, DateReg);
    m_fMale       = fMale;
    m_Surname     = Surname;
    m_Name        = Name;
    m_Patronymic  = Patronymic;
  }
  ABCItemDataBirth(long ID, short Number, COleDateTime DateReg, BOOL fMale, LPCTSTR Surname, LPCTSTR Name, LPCTSTR Patronymic) {
    Reset(ID, Number, DateReg, fMale, Surname, Name, Patronymic);
  }
  virtual ~ABCItemDataBirth(){}
};

class ABCItemDataMarriage : public ABCItemData {
public:
  CString m_MOldSurname;
  CString m_MNewSurname;
  CString m_MName;
  CString m_MPatronymic;
  CString m_WOldSurname;
  CString m_WNewSurname;
  CString m_WName;
  CString m_WPatronymic;

  void Reset(long ID, short Number, COleDateTime DateReg,
             LPCTSTR MOldSurname, LPCTSTR MNewSurname, LPCTSTR MName, LPCTSTR MPatronymic,
             LPCTSTR WOldSurname, LPCTSTR WNewSurname, LPCTSTR WName, LPCTSTR WPatronymic) {
    ABCItemData::Reset(ID, Number, DateReg);
    m_MOldSurname = MOldSurname;
    m_MNewSurname = MNewSurname;
    m_MName       = MName;
    m_MPatronymic = MPatronymic;

    m_WOldSurname = WOldSurname;
    m_WNewSurname = WNewSurname;
    m_WName       = WName;
    m_WPatronymic = WPatronymic;
  }

  ABCItemDataMarriage(long ID, short Number, COleDateTime DateReg,
                     LPCTSTR MOldSurname, LPCTSTR MNewSurname, LPCTSTR MName, LPCTSTR MPatronymic,
                     LPCTSTR WOldSurname, LPCTSTR WNewSurname, LPCTSTR WName, LPCTSTR WPatronymic) {
    Reset(ID, Number, DateReg, MOldSurname, MNewSurname, MName, MPatronymic, WOldSurname, WNewSurname, WName, WPatronymic);
  }
  virtual ~ABCItemDataMarriage(){}
};

class ABCItemDataDivorce : public ABCItemData {
public:
  CString m_MOldSurname;
  CString m_MNewSurname;
  CString m_MName;
  CString m_MPatronymic;
  CString m_WOldSurname;
  CString m_WNewSurname;
  CString m_WName;
  CString m_WPatronymic;

  void Reset(long ID, short Number, COleDateTime DateReg,
             LPCTSTR MOldSurname, LPCTSTR MNewSurname, LPCTSTR MName, LPCTSTR MPatronymic,
             LPCTSTR WOldSurname, LPCTSTR WNewSurname, LPCTSTR WName, LPCTSTR WPatronymic) {
    ABCItemData::Reset(ID, Number, DateReg);
    m_MOldSurname = MOldSurname;
    m_MNewSurname = MNewSurname;
    m_MName       = MName;
    m_MPatronymic = MPatronymic;

    m_WOldSurname = WOldSurname;
    m_WNewSurname = WNewSurname;
    m_WName       = WName;
    m_WPatronymic = WPatronymic;
  }
  ABCItemDataDivorce(long ID, short Number, COleDateTime DateReg,
                     LPCTSTR MOldSurname, LPCTSTR MNewSurname, LPCTSTR MName, LPCTSTR MPatronymic,
                     LPCTSTR WOldSurname, LPCTSTR WNewSurname, LPCTSTR WName, LPCTSTR WPatronymic) {
    Reset(ID, Number, DateReg, MOldSurname, MNewSurname, MName, MPatronymic, WOldSurname, WNewSurname, WName, WPatronymic);
  }
  virtual ~ABCItemDataDivorce(){}
};

class ABCItemDataChange : public ABCItemData {
public:
  BOOL    m_fMale;
  CString m_OldSurname;
  CString m_OldName;
  CString m_OldPatronymic;
  CString m_NewSurname;
  CString m_NewName;
  CString m_NewPatronymic;

  void Reset(long ID, short Number, COleDateTime DateReg, BOOL fMale,
             LPCTSTR OldSurname,    LPCTSTR NewSurname,
             LPCTSTR OldName,       LPCTSTR NewName,
             LPCTSTR OldPatronymic, LPCTSTR NewPatronymic) {
    ABCItemData::Reset(ID, Number, DateReg);
    m_fMale         = fMale;
    m_OldSurname    = OldSurname;
    m_NewSurname    = NewSurname;
    m_OldName       = OldName;
    m_NewName       = NewName;
    m_OldPatronymic = OldPatronymic;
    m_NewPatronymic = NewPatronymic;
  }

  ABCItemDataChange(long ID, short Number, COleDateTime DateReg, BOOL fMale,
                    LPCTSTR OldSurname,    LPCTSTR NewSurname,
                    LPCTSTR OldName,       LPCTSTR NewName,
                    LPCTSTR OldPatronymic, LPCTSTR NewPatronymic) {
    Reset(ID, Number, DateReg, fMale, OldSurname, NewSurname, OldName, NewName, OldPatronymic, NewPatronymic);
  }
  virtual ~ABCItemDataChange(){}
};

class ABCItemDataDeath : public ABCItemData {
public:
  BOOL    m_fMale;
  CString m_Surname;
  CString m_Name;
  CString m_Patronymic;

  void  Reset(long ID, short Number, COleDateTime DateReg, BOOL fMale, LPCTSTR Surname, LPCTSTR Name, LPCTSTR Patronymic) {
    ABCItemData::Reset(ID, Number, DateReg);
    m_fMale       = fMale;
    m_Surname     = Surname;
    m_Name        = Name;
    m_Patronymic  = Patronymic;
  }

  ABCItemDataDeath(long ID, short Number, COleDateTime DateReg, BOOL fMale, LPCTSTR Surname, LPCTSTR Name, LPCTSTR Patronymic) {
    Reset(ID, Number, DateReg, fMale, Surname, Name, Patronymic);
  }
  virtual ~ABCItemDataDeath(){}
};

//typedef CMap<long, long, ABCItemData*, ABCItemData*> ABCMap;
typedef CMap<long, long, ABCItemData*,ABCItemData*&> ABCMap;

#define CABCListBase CListView
class CABCList : public CABCListBase {
protected: // create from serialization only
	CABCList();
	DECLARE_DYNCREATE(CABCList)

// Attributes
public:
  int             m_SortColumn;
  CWordArray      m_SortOrder;
protected:
  CImageList      m_SexImageList;
  ABCMap          m_Items;
  int             m_FocusedItem;
  long            m_FocusedID;
  BOOL            m_fInitialized;
  CFlatHeaderCtrl m_wndHeader;
// Operations
public:
  CFormABC*    GetABCForm();
  virtual void FillRow(int nItem){}
  virtual void Fill();
  void         ClearSelection();
  int          UpdateData(long ID);
  void         GoTo(long lID);
/************************************** : by VK at 21.12.2004 2:03:13 **\
	CEraABCDoc*  GetDocument();
\************************************** : by VK at 21.12.2004 2:03:15 **/
  int          GetItemCount();

  BOOL         CanGoToPrev();
  BOOL         CanGoToNext();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CABCList)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CABCList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CABCList)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
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
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  friend class CFormABC;
  friend int CALLBACK CompareABCProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

/************************************** : by VK at 21.12.2004 2:03:17 **\
#ifndef _DEBUG  // debug version in ABCList.cpp
inline CEraABCDoc* CABCList::GetDocument()
   { return (CEraABCDoc*)m_pDocument; }
#endif
\************************************** : by VK at 21.12.2004 2:03:21 **/

/////////////////////////////////////////////////////////////////////////////
// CBirthList
class CBirthList : public CABCList {
protected: // create from serialization only
	DECLARE_DYNCREATE(CBirthList)

// Operations
public:
  void FillRow(int nItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirthList)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBirthList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMarriageList
class CMarriageList : public CABCList {
protected: // create from serialization only
	DECLARE_DYNCREATE(CMarriageList)

// Operations
public:
  void FillRow(int nItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarriageList)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMarriageList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDivorceList
class CDivorceList : public CABCList {
protected: // create from serialization only
	DECLARE_DYNCREATE(CDivorceList)

// Operations
public:
  void FillRow(int nItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDivorceList)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDivorceList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CChangeList
class CChangeList : public CABCList {
protected: // create from serialization only
	DECLARE_DYNCREATE(CChangeList)

// Operations
public:
  void FillRow(int nItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeList)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChangeList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDeathList
class CDeathList : public CABCList {
protected: // create from serialization only
	DECLARE_DYNCREATE(CDeathList)

// Operations
public:
  void FillRow(int nItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeathList)
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDeathList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABCLIST_H__BC8461B1_B192_44C9_B3B0_3CB585E8BF58__INCLUDED_)
