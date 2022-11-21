// OODocument.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "OODocument.h"
#include "OOView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COODocument

IMPLEMENT_DYNCREATE(COODocument, COleDocument)

COODocument::COODocument():m_pView(NULL) {
}

BOOL COODocument::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

COODocument::~COODocument()
{
}


BEGIN_MESSAGE_MAP(COODocument, COleDocument)
	//{{AFX_MSG_MAP(COODocument)
  ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_RETURN, OnUpdateEnabledCmd)
	ON_COMMAND(ID_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COODocument diagnostics

#ifdef _DEBUG
void COODocument::AssertValid() const
{
	COleDocument::AssertValid();
}

void COODocument::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COODocument serialization
void COODocument::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	}
	else {
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COODocument commands
BOOL COODocument::OnOpenDocument(LPCTSTR lpszPathName) {
	if (!COleDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
  POSITION pos = GetFirstViewPosition();
  m_pView = (COOView*)GetNextView(pos);
	ASSERT(m_pView != NULL);

	return TRUE;
}
void COODocument::OnUpdateEnabledCmd(CCmdUI* pCmdUI)  {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);
}
void COODocument::OnReturn() {
	// TODO: Add your command handler code here
  OnCloseDocument();
}


void COODocument::OnUpdateFileSaveAs(CCmdUI* pCmdUI)  {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);
}

void COODocument::OnFileSaveAs() {
	// TODO: Add your command handler code here
  m_pView->OnFileSaveAs();
}

