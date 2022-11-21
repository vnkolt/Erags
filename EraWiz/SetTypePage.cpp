// SetTypePage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "SetTypePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTypePage dialog


CSetTypePage::CSetTypePage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CSetTypePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTypePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetTypePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTypePage)
	DDX_Control(pDX, IDC_TYPELIST, m_TypeList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTypePage, CDialog)
	//{{AFX_MSG_MAP(CSetTypePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTypePage message handlers

BOOL CSetTypePage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here

  m_TypeList.AddString(_T("ВВРАЦС Київського МУЮ"));
  m_TypeList.AddString(_T("ВРАЦС Севастопольського МУЮ"));
  m_TypeList.AddString(_T("Управління РАЦС ГУЮ Міністерства юстиції України в АР Крим"));
  m_TypeList.AddString(_T("ВРАЦС областного управління юстиції"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
