#if !defined(RLIST_H_INCLUDED)
#define RLIST_H_INCLUDED

// RList.h
#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\EraControls.h"
#include "..\Controls\HyperLink.h"
#include "..\Controls\TCToolBar\TCImageList.h"


#include "DialogEx.h"


#define RLIMAGE_ROOT            0
#define RLIMAGE_NOCOMMENT       1
#define RLIMAGE_NOCOMMENT_EXP   2
#define RLIMAGE_COMMENT         3
#define RLIMAGE_COMMENT_EXP     4
#define RLIMAGE_OUR             5
#define RLIMAGE_OUR_EXP         6

#define RLFLAG_USEFLAG  0x0010


class CRListRecord : public CObject {
public:
  CRListRecord();
  ~CRListRecord();
public:
  CPtrArray     m_array;
  long          m_ID;
  long          m_ParentID;
  long          m_Flags;
  CString       m_Fullname;
  CString       m_Address;
  CString       m_Phones;
  CString       m_Notice;
  HTREEITEM     m_hTreeItem;
public:
  int           GetChildCount();
  void          AddChild(CRListRecord* pChildRecord);
  void          Update();
  CRListRecord* InsertChild(const CString& szShortname, const CString& szAddress,
                            const CString& szPhones,  const CString& szNotice);
  void          Delete();
  int           GetImage();
  int           GetImage(CTreeCtrl& TreeCtrl);
};
class CRList {
public:
  CRList();
  ~CRList();
// Data members:
public:
  CMapPtrToPtr    m_map;
  CMapPtrToPtr    m_UserMap;
  CPtrArray       m_RootItems;
public:
  void  Clear();
  void  Sort(CPtrArray* pArray);
  void  Load(CProgressCtrl* pProgressCtrl=NULL, CStatic* pStatic=NULL);

  void  AddToUserMap(CRListRecord* pParent);
  void  RemoveFromUserMap(CRListRecord* pParent);
  void  SetParent(CRListRecord* pParent);
  void  FillRegCB(CComboBox& cb, const CString& sNewValue);

  BOOL  IsEmpty() { return (m_map.GetCount()==0); }
  void  Add(CRListRecord* pRecord);
  void  Delete(CRListRecord* pRecord);
  CRListRecord* Lookup(long ID);
  CRListRecord* LookupZeroParent(long ID);
  CRListRecord* Lookup(const CString& szName);
  HTREEITEM FillTreeCtrl(CTreeCtrl& tc, long ParentID, HTREEITEM hParentItem);
};


#define CRListViewBase CFormViewBG
/////////////////////////////////////////////////////////////////////////////
// CRListView dialog
class CRListView : public CRListViewBase {
  DECLARE_DYNCREATE(CRListView)
// Construction
protected:
  CRListView();

  virtual BOOL IsNeedSubclassForStaticBG(CWnd* pWnd);
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);

// Dialog Data
	//{{AFX_DATA(CRListView)
	enum { IDD = IDD_RLIST };
	CStatic	      m_Frame;
  CEraComboBox  m_Cases;
  CEraEdit      m_Fullname;
  CEraEdit      m_Shortname;
  CEraEdit      m_Address;
  CEraEdit      m_Phones;
  CEraEdit      m_Notice;
  CTreeCtrl     m_RTree;
  CListCtrl     m_RList;
  //CStatic	      m_EmailLabel;
  CHyperLink    m_EMailLink;
	//}}AFX_DATA
  HTREEITEM     m_hMinJust;
  CTCImageList  m_ImageList;
  BOOL          m_fCanSave;
  BOOL          m_fDoSave;
  BOOL          m_fPrintToWord;

  CRListRecord* m_pOurRecord;
  CRListRecord* m_pCurrentRecord;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRListView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual ~CRListView();

  void  UpdateTreeItem(CRListRecord* pRecord);
  void  UpdateListItem(CRListRecord* pRecord);
  void  DoSave();

  void  ShowHideEmail();
  void  FillFromRecord(CRListRecord* pRecord);
  void  FillListCtrl(CRListRecord* pParentRecord);
  void  FillParent(CRListRecord* pRecord, HTREEITEM hParent);
  void  Fill();
  void  OnPrintMenu();
  void  OnPrint(UINT nPrintID);
	// Generated message map functions
	//{{AFX_MSG(CRListView)
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
  afx_msg void OnAddToUseMap();
  afx_msg void OnUpdatePrintItem(CCmdUI* pCmdUI);
  afx_msg void OnPrintItem(UINT nID);
	afx_msg void OnUpdatePrint(CCmdUI* pCmdUI);
	afx_msg void OnPrint();
  afx_msg void OnWord();
  afx_msg void OnTemplates();
	afx_msg void OnClickRTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRClickRTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRClickChildList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSetOwner();
	afx_msg void OnSelendokCase();
	afx_msg void OnChangeShortname();
	//}}AFX_MSG
	afx_msg void OnHelp();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CRListAddDlg dialog
class CRListAddDlg : public CDialogEx {
// Construction
public:
	CRListAddDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRListAddDlg)
	enum { IDD = IDD_RLIST_ADD };
  CFrameBG    m_Frame1;
  CEraEdit    m_ChildOf;
  CXButtonXP	m_btnUp;
  CEraEdit    m_Shortname;
  CEraEdit    m_Address;
  CEraEdit    m_Phones;
  CEraEdit    m_Notice;
	//}}AFX_DATA

  CString     m_szShortname;
  CString     m_szAddress;
  CString     m_szPhones;
  CString     m_szNotice;

  CRListRecord* m_pSelectedRecord;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRListAddDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
  BOOL  CanAdd();

	// Generated message map functions
	//{{AFX_MSG(CRListAddDlg)
	virtual BOOL OnInitDialog();
  afx_msg void OnUp();
  afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CRListDelDlg dialog
class CRListDelDlg : public CDialogEx {
// Construction
public:
	CRListDelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRListDelDlg)
	enum { IDD = IDD_RLIST_DELETE };
  CEraEdit    m_Warning;
  CStaticBG   m_lblOr;
  CXButtonXP  m_RadioTree;
  CXButtonXP  m_RadioList;
	//}}AFX_DATA

  CTCImageList  m_RadioIL;
  CRListRecord* m_pRTreeRecord;
  CRListRecord* m_pRListRecord;
  CRListRecord* m_pRSelectedRecord;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRListDelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRListDelDlg)
	virtual BOOL OnInitDialog();
  afx_msg void OnRadioTree();
  afx_msg void OnRadioList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CRList theRList;

#endif // RLIST_H_INCLUDED
