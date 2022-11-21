// WordCntrItem.cpp : implementation file
//
#include "stdafx.h"
#include "Erags.h"
#include "WordCntrItem.h"
#include "WordDocument.h"

#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordCntrItem implementation

IMPLEMENT_SERIAL(CWordCntrItem, COleDocObjectItem, 0)

CWordCntrItem::CWordCntrItem(CWordDocument* pContainer)
	: COleDocObjectItem(pContainer)
{
	((CEragsApp*)AfxGetApp())->m_pWordActive = pContainer;
}

CWordCntrItem::~CWordCntrItem()
{
	if (((CEragsApp*)AfxGetApp())->m_pWordActive == GetDocument())
	    ((CEragsApp*)AfxGetApp())->m_pWordActive = 0;
}

void CWordCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	BOOL modified = m_pDocument->IsModified();
	COleDocObjectItem::OnChange(nCode, dwParam);
	m_pDocument->SetModifiedFlag(modified);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

BOOL CWordCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

  // During in-place activation CWordCntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleDocObjectItem::SetItemRects to move the item
	//  to the new position.

	if (!COleDocObjectItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: update any cache you may have of the item's rectangle/extent

	return TRUE;
}

BOOL CWordCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow) {
  BOOL bResult = COleDocObjectItem::OnShowControlBars(pFrameWnd, TRUE/*bShow*/);
	if(pFrameWnd->m_nIdleFlags & CFrameWnd::idleLayout)
		pFrameWnd->RecalcLayout();

	return bResult;
}

void CWordCntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);
	m_pView->GetClientRect(rPosition);
  rPosition.top += 20; // toolbar
}

void CWordCntrItem::AttachDisp() {
/************************************** : by VK at 25.08.2004 2:28:38 **\
	LPDISPATCH  lpDispatch = GetIDispatch();
	if (lpDispatch != 0) {
		m_disp.Attach(lpDispatch,false);
	}
  else {
		m_disp = GetObject(L"Word.Application");
	}
\************************************** : by VK at 25.08.2004 2:28:43 **/
}

void CWordCntrItem::CloseDisp() {
	m_disp = 0;
}


void CWordCntrItem::OnActivate()
{
	((CEragsApp*)AfxGetApp())->m_pWordActive = GetDocument();
  POSITION pos = ((CEragsApp*)AfxGetApp())->m_pWordActive->GetFirstViewPosition();
  CView* pView = ((CEragsApp*)AfxGetApp())->m_pWordActive->GetNextView(pos);

/************************************** : by VK at 25.08.2004 0:35:40 **\
   CFrameWnd* pFrame = DYNAMIC_DOWNCAST(CFrameWnd, AfxGetApp()->m_pMainWnd);
   ASSERT(pFrame != NULL);

   CWnd* pView = pFrame->GetActiveView();
   ASSERT(pView != NULL);
\************************************** : by VK at 25.08.2004 0:35:43 **/
   COleDocObjectItem* pItem =
	  (COleDocObjectItem*) GetDocument()->GetInPlaceActiveItem(pView);

   // if this isn't the item being activated, deactivate it.
   if (pItem != NULL && pItem != this)
	  pItem->Deactivate();

   COleDocObjectItem::OnActivate();

//  CFrameWnd* pFrame = pView->GetParentFrame();
}

void CWordCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	if (((CEragsApp*)AfxGetApp())->m_pWordActive == GetDocument())
		((CEragsApp*)AfxGetApp())->m_pWordActive = 0;
	
	COleDocObjectItem::OnDeactivateUI(bUndoable);

    // Hide the object if it is not an outside-in object
    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
  if ( theApp.m_pWordView ) {
    ((CView*)theApp.m_pWordView)->GetParentFrame()->PostMessage(WM_CLOSE);
  }
}

void CWordCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleDocObjectItem data.
	// Since this sets up the m_pDocument pointer returned from
  //  CWordCntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleDocObjectItem::Serialize(ar);

  // now store/retrieve data specific to CWordCntrItem
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWordCntrItem diagnostics

#ifdef _DEBUG
void CWordCntrItem::AssertValid() const
{
	COleDocObjectItem::AssertValid();
}

void CWordCntrItem::Dump(CDumpContext& dc) const
{
	COleDocObjectItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
