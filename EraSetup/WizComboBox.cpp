// WizComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "WizComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizComboBox

CWizComboBox::CWizComboBox()
{
}

CWizComboBox::~CWizComboBox()
{
}


BEGIN_MESSAGE_MAP(CWizComboBox, CComboBox)
	//{{AFX_MSG_MAP(CWizComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizComboBox message handlers

BOOL CWizComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN /*|| pMsg->wParam == VK_ESCAPE*/) {
    pMsg->wParam = VK_TAB;
  }
	return CComboBox::PreTranslateMessage(pMsg);
}
