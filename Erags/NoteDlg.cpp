// NoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "NoteDlg.h"

#include "Menu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog


CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	       :CDialogEx(CNoteDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CNoteDlg)
	m_sNote = _T("");
	//}}AFX_DATA_INIT
  m_nPos = 0;
  m_fMale = false;
  m_pD1 = m_pD2 = NULL;
}


void CNoteDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoteDlg)
	DDX_Text(pDX, IDC_NOTEFLD, m_sNote);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialogEx)
	//{{AFX_MSG_MAP(CNoteDlg)
	ON_BN_CLICKED(IDC_NOTEMENU, OnNoteMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg message handlers
void CNoteDlg::OnNoteMenu()  {
  CString sMemo, s;
  UINT nPos = m_nPos;
  GetDlgItem(IDC_NOTEFLD)->GetWindowText(sMemo);
  s = ContextMenu(GetParent()->m_hWnd/*m_hWnd*/, nPos, m_fMale, m_d, sMemo, true, m_pD1, m_pD2);
  if ( s!=sMemo) {
    GetDlgItem(IDC_NOTEFLD)->SetWindowText(s);
  }
}
