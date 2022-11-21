// DBStreets.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBStreets.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBStreets dialog
BEGIN_MESSAGE_MAP(CDBStreets, CDBGridDlg)
	//{{AFX_MSG_MAP(CDBStreets)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBStreets::CDBStreets(CWnd* pParent /*=NULL*/):CDBGridDlg(pParent) {
	//{{AFX_DATA_INIT(CDBStreets)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDBStreets::DoDataExchange(CDataExchange* pDX) {
	CDBGridDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBStreets)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBStreets message handlers
BOOL CDBStreets::OnInitDialog() {
	CDBGridDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
  
  m_Grid.m_pDB = &theDataManager.m_dbLists;
  m_Grid.m_InsertSQL = _T("INSERT INTO Streets (STREET) VALUES (Null)");
  m_Grid.m_TableName = _T("Streets");
  m_Grid.SetRowCount(1);
  m_Grid.SetColumnCount(2);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetFixedRowCount(1);

  m_Grid.SetItemData(0, 0, (LPARAM)_T("ID") );
  m_Grid.SetItemData(0, 1, (LPARAM)_T("STREET") );

  m_Grid.m_FieldTypes.SetSize(2);
  m_Grid.m_FieldTypes.SetAt(0, dbLong);
  m_Grid.m_FieldTypes.SetAt(1, dbText);

  m_Grid.SetItemText(0, 1, _T("¬ул€ц€") );
  m_Grid.SetColumnWidth(0, 16);
  m_Grid.SetColumnWidth(1, 200);
  m_Grid.Load();
  SetWindowText(_T("¬улиц≥"));
  m_Grid.SortItems(pfnDBGridCompare, 1, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDBStreets::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#Streets"));
  return TRUE;
}