// WordDocument.cpp : implementation file
//
#include "stdafx.h"
#include "Erags.h"
#include "WordDocument.h"

#include "WordView.h"
#include "WordCntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordDocument

IMPLEMENT_DYNCREATE(CWordDocument, COleDocument)

CWordDocument::CWordDocument()
              :m_ctrl(0), m_pView(NULL) {
}

BOOL CWordDocument::OnNewDocument() {
	if (!COleDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CWordDocument::~CWordDocument() {
}


BEGIN_MESSAGE_MAP(CWordDocument, COleDocument)
	//{{AFX_MSG_MAP(CWordDocument)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateEnabledCmd)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateEnabledCmd)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_PAGE_SETUP, OnUpdateEnabledCmd)
	ON_COMMAND(ID_PAGE_SETUP, OnFilePageSetup)
	ON_UPDATE_COMMAND_UI(ID_RETURN, OnUpdateEnabledCmd)
	ON_COMMAND(ID_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordDocument diagnostics

#ifdef _DEBUG
void CWordDocument::AssertValid() const
{
	COleDocument::AssertValid();
}

void CWordDocument::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWordDocument serialization
void CWordDocument::Serialize(CArchive& ar) {
/************************************** : by VK at 24.08.2004 23:12:58 **\
	if (ar.IsStoring()) {
		ar << m_template;
	} else {
		ar >> m_template;
	}
\************************************** : by VK at 24.08.2004 23:13:01 **/
}

/////////////////////////////////////////////////////////////////////////////
// CWordDocument commands
BOOL CWordDocument::OnOpenDocument(LPCTSTR lpszPathName) {
	if (!COleDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
  CWordCntrItem* pItem = NULL;

  POSITION pos = GetFirstViewPosition();
  m_pView = (CWordView*)GetNextView(pos);
	ASSERT(m_pView != NULL);

	m_pView->BeginWaitCursor();

	TRY
	{
		// Create new item connected to this document.
    const int max_try = 5;
    for( int i(0); i < max_try; i++ ) { // А что делать, если не всегда с первого раза получается?
                                        // Warning: constructing COleException, scode = E_ABORT ($80004004).
                                        // First-chance exception in Erags.exe (KERNEL32.DLL): 0xE06D7363: Microsoft C++ Exception.
  		pItem = new CWordCntrItem(this);
	  	ASSERT_VALID(pItem);

      if ( pItem->CreateFromFile(lpszPathName) ) {
			  break; // Получилось!
		  }
      else {
			  delete pItem; // Не получилось с первого (второго, третьего...) раза.
        pItem = NULL;
        Sleep(100);   // Сколько надо Ворду, чтобы освободить свои потроха?
      }
    }

    if ( NULL==pItem ) { // Всё равно не получилось?
      return FALSE;      // Ну это просто свинство!
    }

		ASSERT_VALID(pItem);
    m_ctrl = pItem;

		// make sure we deactivate any active items first.
		COleClientItem* pActiveItem = GetInPlaceActiveItem(m_pView);
		if (pActiveItem != NULL)
			pActiveItem->Deactivate();

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		pItem->Activate(OLEIVERB_SHOW, m_pView);
		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		// set selection to last inserted item
		m_pView->m_pSelection = (CWordCntrItem*) pItem;
		UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		// AfxMessageBox(IDP_FAILED_TO_CREATE);
    e->ReportError(MB_OK);
	}
	END_CATCH

	return TRUE;
}

void CWordDocument::OnCloseDocument() {
  // TODO: Add your specialized code here and/or call the base class
  try {
    if ( m_pView )
      m_pView->DoWordCommand(WMC_QUIT);
    if (m_ctrl) {
      m_ctrl->CloseDisp();
    }
  }
  catch(...) {
  }
	COleDocument::OnCloseDocument();
}

BOOL CWordDocument::OnSaveDocument(LPCTSTR lpszPathName) {
	// TODO: Add your specialized code here and/or call the base class
	
	return COleDocument::OnSaveDocument(lpszPathName);
}

BOOL CWordDocument::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
  return TRUE;
//	return COleDocument::SaveModified();
}

void CWordDocument::OnUpdateEnabledCmd(CCmdUI* pCmdUI)  {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CWordDocument::OnFileSaveAs() {
	// TODO: Add your command handler code here
  m_pView->DoWordCommand(WMC_SAVE_AS);
}

void CWordDocument::OnFilePrint() {
	// TODO: Add your command handler code here
  m_pView->DoWordCommand(WMC_PRINT);
}
void CWordDocument::OnFilePageSetup() {
  m_pView->DoWordCommand(WMC_PAGE_SETUP);
}

void CWordDocument::OnReturn() {
	// TODO: Add your command handler code here
  OnCloseDocument();
/************************************** : by VK at 28.08.2004 11:19:14 **\
  m_ctrl->Deactivate();
  m_pView->GetParentFrame()->DestroyWindow();
\************************************** : by VK at 28.08.2004 11:19:18 **/
}

BOOL CWordDocument::ReportError(SCODE sc) const {
  return FALSE;
}
