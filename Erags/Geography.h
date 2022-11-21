#if !defined(GEOGRAPHY_H_INCLUDED)
#define GEOGRAPHY_H_INCLUDED


#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\EraControls.h"

//class CGeoRecord;
//typedef CTypedPtrMap<CMapStringToOb, CString, CGeoRecord*> GeoMap;

#define GEO_MENU_TYPE_NONE  0
#define GEO_MENU_TYPE_TREE  1
#define GEO_MENU_TYPE_LIST  2

#define GRF_UPDATED   0x0001

class CGeoRecord : public CObject {
public:
  CGeoRecord();
  ~CGeoRecord();
// data members:
public:
  CPtrArray   m_array;
  CGeoRecord* m_pParent;
  long        m_ID;
  long        m_ParentID;
  CString     m_Name;
  CString     m_AltName;
  CString     m_Type;
  CString     m_ZipCode;
  CString     m_PhoneCode;
  CString     m_Directory;
  //bool        m_fLoaded;
  DWORD       m_dwFlags;
  HTREEITEM   m_hItem;

  BOOL        Updated() { return (m_dwFlags & GRF_UPDATED); }

  int         GetCount() { return m_array.GetSize(); }
  bool        IsCountry() const;
  bool        IsRegion() const;
  bool        IsCity() const;
  bool        IsMainCity() const;
  bool        IsVillage(CString* pDest=NULL) const;
  bool        IsDistrict() const;
  int         GetGeoTypeWeight();
  CString     GetTypeName();
  CString     GetShortTypeName();

  CString     GetName();
  CString     GetAltName();
  CString     GetNameWithAltName();
  bool        HasChildren();
  bool        Insert();
  bool        Update();
  bool        RemoveRecord();
  void        RemoveRecordFromArray(CGeoRecord* pRecord);
};

CString GetGeoPath(CGeoRecord* pRecord);

class CGeoCache : public CObject {
public:
  CGeoCache();
  ~CGeoCache();
// data members:
public:
  CPtrArray   m_array;
// operations:
  void Clear();
  void Sort(CPtrArray* pArray);
  BOOL Load(CDaoDatabase& db, CProgressCtrl* pProgressCtrl, CStatic* pStatic);

  int         GetIndex(CGeoRecord* pRecord, CPtrArray*& pArray);
  CGeoRecord* GetFirstRecord();
  CGeoRecord* GetPrevRecord(CGeoRecord* pRecord);
  CGeoRecord* GetNextRecord(CGeoRecord* pRecord);
  CGeoRecord* GetLastRecord(CPtrArray& array);


  CGeoRecord* GetCountry(CPtrArray* pArray, const CString& s);
  CGeoRecord* GetCountry(const CString& s);
  CGeoRecord* GetRegion(CPtrArray* pArray, const CString& s);
  #ifdef _GEO
  CGeoRecord* GetCity(CPtrArray* pArray, const CString& s, char typeLetter=0);
  #else
  CGeoRecord* GetCity(CPtrArray* pArray, const CString& s);
  #endif
  CGeoRecord* GetDistrict(CPtrArray* pArray, const CString& s);

  void SelectCBDefault(CEraComboBox& cb);
  void FillCountryCB(CEraComboBox& cb, CPtrArray* pArray);
  void FillCountryCB(CEraComboBox& cb, const CString& sNewValue);
  void FillRegionCB(CEraComboBox& cb, CEraComboBox& cbCountry, const CString& sNewValue);
  void FillDistrictCB(CEraComboBox& cb, CEraComboBox& cbRegion, const CString& sNewValue);
  void FillCityCB(CEraComboBox& cb, CEraComboBox& cbRegion, CEraComboBox& cbDistrict, const CString& sNewValue);
  void FillCityCBByCountryCities(CEraComboBox& cb, CEraComboBox& cbCountry, const CString& sNewValue);

  CString FindFullCountry(const CString& sCountry);
  void RemoveRecordFromArray(CGeoRecord* pRecord);
};

#define CGeoListViewBase CFormViewBG

/************************************** : by VK at 27.01.2008 10:58:48 **\

/////////////////////////////////////////////////////////////////////////////
// CGeoListView dialog
class CGeoListView : public CGeoListViewBase {
  DECLARE_DYNCREATE(CGeoListView)
// Construction
protected:
  CGeoListView();

  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);

// Dialog Data
	//{{AFX_DATA(CGeoListView)
	enum { IDD = IDD_GEOGRAPHY };
	CTreeCtrl	    m_GeoTree;
	CListCtrl     m_GeoList;
	//}}AFX_DATA
  CImageList    m_ImageList;
  int           m_MenuType;

  int   GetImageIndex(const CGeoRecord* pRecord);
  void  Load(CPtrArray* pArray, HTREEITEM hParent);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoListView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual ~CGeoListView();

  void        RedrawListItem(int nItem, CGeoRecord* pRecord);
  void        FillGeoList(CGeoRecord* pParentRecord);
  HTREEITEM   FindRecordOnTree(CGeoRecord* pRecord, HTREEITEM hItem=NULL);
  int         FindRecordInList(CGeoRecord* pRecord);

  CGeoRecord* GetSelectedTreeRecord();
  CGeoRecord* GetSelectedListRecord();
  CGeoRecord* GetSelectedRecord();

  void        SetType(LPCTSTR szType);
  void        TrackGeoAddMenu(CPoint& p);

  void        AddToTreeAndList(CGeoRecord* m_pRecord);

	// Generated message map functions
	//{{AFX_MSG(CGeoListView)
	virtual void OnInitialUpdate();
  afx_msg void OnDestroy();
	afx_msg void OnSelchangedGeoTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickGeotree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickGeoTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickGeoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddCountry();
	afx_msg void OnAddDistrict();
	afx_msg void OnAddRegion();
	afx_msg void OnAddCity();
	afx_msg void OnRename();
	afx_msg void OnSetCountry();
	afx_msg void OnSetRegion();
	afx_msg void OnSetTerritory();
	afx_msg void OnSetDistrict();
	afx_msg void OnSetCity();
	afx_msg void OnSetMainCity();
	afx_msg void OnSetSMT();
	afx_msg void OnSetHamlet();
	afx_msg void OnSetVillage();
	afx_msg void OnDelete();
	afx_msg void OnKeydownGeoTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnReturnGeotree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditGeoTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditGeoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	//}}AFX_MSG
	afx_msg void OnHelp();
	DECLARE_MESSAGE_MAP()
};

\************************************** : by VK at 27.01.2008 10:58:55 **/


extern CGeoCache theGeoCache;

#endif // GEOGRAPHY_H_INCLUDED