// WizEdit.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "WizEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizEdit

CWizEdit::CWizEdit()
{
}

CWizEdit::~CWizEdit()
{
}


BEGIN_MESSAGE_MAP(CWizEdit, CEdit)
	//{{AFX_MSG_MAP(CWizEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizEdit message handlers

BOOL CWizEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN /*|| pMsg->wParam == VK_ESCAPE*/) {
    pMsg->wParam = VK_TAB;
  }
	
	return CEdit::PreTranslateMessage(pMsg);
}
