// DBCitizenships.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBCitizenships.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDBCitizenships dialog
BEGIN_MESSAGE_MAP(CDBCitizenships, CDBGridDlg)
	//{{AFX_MSG_MAP(CDBCitizenships)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBCitizenships::CDBCitizenships(CWnd* pParent /*=NULL*/) 
                :CDBGridDlg(pParent) {
	//{{AFX_DATA_INIT(CDBCitizenships)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDBCitizenships::DoDataExchange(CDataExchange* pDX) {
	CDBGridDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBCitizenships)
	//}}AFX_DATA_MAP
}

////////////////////////////////////////////////////////////////////////////
// CDBCitizenships message handlers
BOOL CDBCitizenships::OnInitDialog() {
	CDBGridDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
  
  m_Grid.m_pDB = &theDataManager.m_dbLists;
  m_Grid.m_InsertSQL = _T("INSERT INTO Citizenships (CITIZENSHIP, FULLCITIZENSHIP) VALUES (Null,Null)");
  m_Grid.m_TableName = _T("Citizenships");
  m_Grid.SetRowCount(1);
  m_Grid.SetColumnCount(3);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetFixedRowCount(1);

  m_Grid.SetItemData(0, 0, (LPARAM)_T("ID") );
  m_Grid.SetItemData(0, 1, (LPARAM)_T("CITIZENSHIP") );
  m_Grid.SetItemData(0, 2, (LPARAM)_T("FULLCITIZENSHIP") );

  m_Grid.m_FieldTypes.SetSize(3);
  m_Grid.m_FieldTypes.SetAt(0, dbLong);
  m_Grid.m_FieldTypes.SetAt(1, dbText);
  m_Grid.m_FieldTypes.SetAt(2, dbText);

  m_Grid.SetItemText(0, 1, _T("Коротка Назва") );
  m_Grid.SetItemText(0, 2, _T("Довга Назва") );
  m_Grid.SetColumnWidth(0, 16);
  m_Grid.SetColumnWidth(1, 120);
  m_Grid.SetColumnWidth(2, 400);
  m_Grid.Load();
  SetWindowText(_T("Громадянтсва"));
  m_Grid.SortItems(pfnDBGridCompare, 1, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
BOOL CDBCitizenships::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
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
BOOL CDBCitizenships::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#Citizenships"));
  return TRUE;
}