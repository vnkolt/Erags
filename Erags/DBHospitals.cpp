// DBHospitals.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBHospitals.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDBHospitals dialog
BEGIN_MESSAGE_MAP(CDBHospitals, CDBGridDlg)
	//{{AFX_MSG_MAP(CDBHospitals)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBHospitals::CDBHospitals(CWnd* pParent /*=NULL*/):CDBGridDlg(pParent) {
	//{{AFX_DATA_INIT(CDBHospitals)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDBHospitals::DoDataExchange(CDataExchange* pDX) {
	CDBGridDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBHospitals)
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBHospitals message handlers

BOOL CDBHospitals::OnInitDialog() {
	CDBGridDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
  
  m_Grid.m_pDB = &theDataManager.m_dbLists;
  m_Grid.m_InsertSQL = _T("INSERT INTO Hospitals (PSEUDO, HOSPITAL) VALUES (Null,Null)");
  m_Grid.m_TableName = _T("Hospitals");
  m_Grid.SetRowCount(1);
  m_Grid.SetColumnCount(3);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetFixedRowCount(1);

  m_Grid.SetItemData(0, 0, (LPARAM)_T("ID") );
  m_Grid.SetItemData(0, 1, (LPARAM)_T("PSEUDO") );
  m_Grid.SetItemData(0, 2, (LPARAM)_T("HOSPITAL") );

  m_Grid.m_FieldTypes.SetSize(3);
  m_Grid.m_FieldTypes.SetAt(0, dbLong);
  m_Grid.m_FieldTypes.SetAt(1, dbText);
  m_Grid.m_FieldTypes.SetAt(2, dbText);

  m_Grid.SetItemText(0, 1, _T("Псевдонім") );
  m_Grid.SetItemText(0, 2, _T("Назва") );
  m_Grid.SetColumnWidth(0, 16);
  m_Grid.SetColumnWidth(1, 80);
  m_Grid.SetColumnWidth(2, 400);
  m_Grid.Load();
  SetWindowText(_T("Пологові будинки та лікарні"));
  m_Grid.SortItems(pfnDBGridCompare, 1, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
BOOL CDBHospitals::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	// TODO: Add your specialized code here and/or call the base class
  NMHDR* pNMHDR = (NMHDR*)lParam;
  GV_DISPINFO *pgvDispInfo = (GV_DISPINFO *)pNMHDR;
  GV_ITEM     *pgvItem = &pgvDispInfo->item;

  if ( GVN_ENDLABELEDIT==pgvDispInfo->hdr.code ) {
    CWnd* pWnd = (CWnd*)CWnd::FromHandle(pgvDispInfo->hdr.hwndFrom);
    if ( pWnd->IsKindOf( RUNTIME_CLASS(CEdit) ) ) {
      CEdit* pEdit = (CEdit*)pWnd;
      if ( pEdit->GetModify() ) {
        int i(0);
        i++;
      }
    }
  }
	return CDBGridDlg::OnNotify(wParam, lParam, pResult);
}
*/

BOOL CDBHospitals::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#Hospitals"));
  return TRUE;
}