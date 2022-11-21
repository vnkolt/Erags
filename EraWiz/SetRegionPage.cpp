// SetRegionPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "SetRegionPage.h"

#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRegionPage dialog


CSetRegionPage::CSetRegionPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CSetRegionPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRegionPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetRegionPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRegionPage)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	DDX_Control(pDX, IDC_REGLIST, m_Regions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRegionPage, CDialog)
	//{{AFX_MSG_MAP(CSetRegionPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REGLIST, OnItemchangedReglist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRegionPage message handlers
int CSetRegionPage::GetImage(const CString& sType) {
  if ( sType.IsEmpty() ) {
    return 6;
  }
  TCHAR type = sType.GetAt(0);
  switch(type) {
    case TCHAR('д'):                  return 0;
    case TCHAR('о'): case TCHAR('к'): return 1;
    case TCHAR('м'):                  return 2;
    case TCHAR('р'):                  return 3;
  }
  return 6;
}
LPCTSTR CSetRegionPage::GetTypeName(const CString& sType) {
  if ( sType.IsEmpty() ) {
  return _T("");
  }
  TCHAR type = sType.GetAt(0);
  switch(type) {
    case TCHAR('д'): return _T("держава");
    case TCHAR('о'): return _T("облаcть");
    case TCHAR('к'): return _T("край");
    case TCHAR('м'): return _T("місто");
    case TCHAR('р'): return _T("район");
  }
  return _T("");
}

BOOL CSetRegionPage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);
  GetParent()->GetDlgItem(ID_WIZNEXT)->EnableWindow(FALSE);

  m_Regions.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
  m_ImageList.Create(IDIL_GEOTREE, 16, 1, RGB(255, 0, 255) );

  m_Regions.InsertColumn(0, _T("Назва"), LVCFMT_LEFT, 140);
  m_Regions.InsertColumn(1, _T("Тип"), LVCFMT_LEFT, 80);
  m_Regions.SetImageList(&m_ImageList, LVSIL_SMALL);

  try {
    CDaoRecordset rs(&theDatabase);
    rs.Open(dbOpenDynaset, _T("SELECT ID,TYPE,NAME FROM Geography WHERE PARENT=1"));
    int nItem = 0;
    while ( !rs.IsEOF() ) {
      long      ID      = iDBLongField(rs, 0);
      CString   sType   = iDBStringField(rs,1);
      CString   sRegion = iDBStringField(rs,2);
      m_Regions.InsertItem(nItem, sRegion, GetImage(sType));
      m_Regions.SetItemText(nItem, 1, GetTypeName(sType));
      rs.MoveNext();
      nItem++;
    }
  }
  catch(...) {
    return FALSE;
  }

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetRegionPage::OnItemchangedReglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  GetParent()->GetDlgItem(ID_WIZNEXT)->EnableWindow(TRUE);
	*pResult = 0;
}

