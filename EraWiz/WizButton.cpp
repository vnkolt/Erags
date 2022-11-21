// WizButton.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "WizButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizButton

CWizButton::CWizButton()
{
}

CWizButton::~CWizButton()
{
}


BEGIN_MESSAGE_MAP(CWizButton, CButton)
	//{{AFX_MSG_MAP(CWizButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizButton message handlers

BOOL CWizButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN ) {
    pMsg->wParam = VK_TAB;
  }
	
	return CButton::PreTranslateMessage(pMsg);
}
