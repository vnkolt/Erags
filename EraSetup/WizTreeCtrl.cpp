// WizTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "WizTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizTreeCtrl

CWizTreeCtrl::CWizTreeCtrl()
{
}

CWizTreeCtrl::~CWizTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CWizTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CWizTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizTreeCtrl message handlers

BOOL CWizTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN /*|| pMsg->wParam == VK_ESCAPE*/) {
    pMsg->wParam = VK_TAB;
  }
	return CTreeCtrl::PreTranslateMessage(pMsg);
}
