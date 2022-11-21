#if !defined(AFX_WORDCNTRITEM_H__DD5EC833_9F1E_4F7B_B727_BDE6C1CE0231__INCLUDED_)
#define AFX_WORDCNTRITEM_H__DD5EC833_9F1E_4F7B_B727_BDE6C1CE0231__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordCntrItem.h : header file
//

#include <afxole.h>
#include <comdef.h>

class CWordDocument;
class CWordView;

/////////////////////////////////////////////////////////////////////////////
// CWordCntrItem document

class CWordCntrItem : public COleDocObjectItem
{
  DECLARE_SERIAL(CWordCntrItem)

// Constructors
public:
  CWordCntrItem(CWordDocument* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	IDispatchPtr m_disp;

  CWordDocument* GetDocument()
    { return (CWordDocument*)COleDocObjectItem::GetDocument(); }
  CWordView* GetActiveView()
    { return (CWordView*)COleDocObjectItem::GetActiveView(); }

  void AttachDisp();
  void CloseDisp();
	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWordCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
  virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);
	//}}AFX_VIRTUAL

// Implementation
public:
  ~CWordCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDCNTRITEM_H__DD5EC833_9F1E_4F7B_B727_BDE6C1CE0231__INCLUDED_)
