// ABCDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "ABCDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CABCDlgBar dialog


CABCDlgBar::CABCDlgBar() {
	//{{AFX_DATA_INIT(CABCDlgBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CABCDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CABCDlgBar)
	DDX_Control(pDX, ID_FILE_NEW, m_btnFileNew);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CABCDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CABCDlgBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CABCDlgBar message handlers
BOOL CABCDlgBar::Create(CWnd* pParentWnd) {
	if (!CDialogBar::Create(pParentWnd, IDR_MAINFRAME,  CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
		return FALSE;

  //m_btnFileNew.Attach( GetDlgItem(ID_FILE_NEW)->m_hWnd );
  m_btnFileNew.SubclassDlgItem(ID_FILE_NEW, this);
  m_btnFileNew.SetIcon(IDI_FILE_NEW, IDI_FILE_NEW_GRAY);
  //m_btnFileNew.DrawBorder(FALSE);

  m_btnFileOpen.SubclassDlgItem(ID_FILE_OPEN, this);
  m_btnFileOpen.SetIcon(IDI_FILE_OPEN, IDI_FILE_OPEN_GRAY);
  //m_btnFileOpen.DrawBorder(FALSE);

  m_btnBirth.SubclassDlgItem(ID_BIRTH, this);
  m_btnBirth.SetIcon(IDI_BIRTH, IDI_BIRTH_GRAY);

  m_btnMarriage.SubclassDlgItem(ID_MARRIAGE, this);
  m_btnMarriage.SetIcon(IDI_MARRIAGE, IDI_MARRIAGE_GRAY);

  m_btnDivorce.SubclassDlgItem(ID_DIVORCE, this);
  m_btnDivorce.SetIcon(IDI_DIVORCE, IDI_DIVORCE_GRAY);

  m_btnChange.SubclassDlgItem(ID_CHANGE, this);
  m_btnChange.SetIcon(IDI_CHANGE, IDI_CHANGE_GRAY);

  m_btnDeath.SubclassDlgItem(ID_DEATH, this);
  m_btnDeath.SetIcon(IDI_DEATH, IDI_DEATH_GRAY);

  return TRUE;
}