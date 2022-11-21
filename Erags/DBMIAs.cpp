// DBMIAs.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBMIAs.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBMIAs dialog
BEGIN_MESSAGE_MAP(CDBMIAs, CDBGridDlg)
	//{{AFX_MSG_MAP(CDBMIAs)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBMIAs::CDBMIAs(CWnd* pParent /*=NULL*/):CDBGridDlg(pParent) {
	//{{AFX_DATA_INIT(CDBMIAs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDBMIAs::DoDataExchange(CDataExchange* pDX) {
	CDBGridDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBMIAs)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBMIAs message handlers
BOOL CDBMIAs::OnInitDialog() {
	CDBGridDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
  
  m_Grid.m_pDB = &theDataManager.m_dbLists;
  m_Grid.m_InsertSQL = _T("INSERT INTO MIA (NAME) VALUES (Null)");
  m_Grid.m_TableName = _T("MIA");
  m_Grid.SetRowCount(1);
  m_Grid.SetColumnCount(2);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetFixedRowCount(1);

  m_Grid.SetItemData(0, 0, (LPARAM)_T("ID") );
  m_Grid.SetItemData(0, 1, (LPARAM)_T("NAME") );

  m_Grid.m_FieldTypes.SetSize(2);
  m_Grid.m_FieldTypes.SetAt(0, dbLong);
  m_Grid.m_FieldTypes.SetAt(1, dbText);

  m_Grid.SetItemText(0, 1, _T("Назва відділу ВС в орудному відмінку") );
  m_Grid.SetColumnWidth(0, 16);
  m_Grid.SetColumnWidth(1, 500);
  m_Grid.Load();
  SetWindowText(_T("Органи внутрішніх справ"));
  m_Grid.SortItems(pfnDBGridCompare, 1, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDBMIAs::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#MIA"));
  return TRUE;
}