// DBNames.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "DBNames.h"
#include "..\Common\DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBNames dialog
BEGIN_MESSAGE_MAP(CDBNames, CDBGridDlg)
	//{{AFX_MSG_MAP(CDBNames)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBNames::CDBNames(CWnd* pParent /*=NULL*/)
	            :CDBGridDlg(pParent, IDD_DBNAMES) {
	//{{AFX_DATA_INIT(CDBNames)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDBNames::DoDataExchange(CDataExchange* pDX) {
	CDBGridDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBNames)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDBNames::Load(LPCTSTR szTableName, LPCTSTR szField) {
  m_Grid.SetRowCount(1);

  CString sql;
  sql.Format(_T("SELECT ID,%s,SEX FROM %s ORDER BY %s"), szField, szTableName, szField);

  CDaoQueryDef qd(&theDataManager.m_dbLists);
  CDaoRecordset rs(&theDataManager.m_dbLists);

  int iRow = 0;
  try {
    qd.Create(NULL,sql);
    rs.Open(&qd);

    int nColumns = m_Grid.GetColumnCount();

    m_Grid.m_FieldTypes.SetSize(nColumns);
    m_Grid.m_FieldNames.SetSize(nColumns);

    for( int col(0); col < m_Grid.GetColumnCount(); col++ ) {
      LPCTSTR szField = (LPCTSTR)m_Grid.GetItemData(0, col);
      CDaoFieldInfo fi;
      rs.GetFieldInfo(szField, fi);
      m_Grid.m_FieldTypes.SetAt(col, fi.m_nType);
      m_Grid.m_FieldNames.SetAt(col, fi.m_strName);
    }

    while ( !rs.IsEOF() ) {
      long lID = iDBLongField(rs, 0);
      CString sName   = iDBStringField(rs, 1);
      bool fMale      = iDBBoolField(rs, 2);

      iRow++;
      m_Grid.InsertRow(_T(""));
      m_Grid.SetItemData(iRow, 0, (LPARAM)lID);
      m_Grid.SetItemText(iRow, 1, sName);
      m_Grid.SetItemText(iRow, 2, fMale ? _T("Ч") : _T("Ж") );

      rs.MoveNext();
    }
    rs.Close();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return FALSE;
	}
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CDBNames message handlers
BOOL CDBNames::OnInitDialog() {
	CDBGridDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
  
  m_Grid.m_pDB = &theDataManager.m_dbLists;

/************************************** : by VK at 26.02.2004 19:00:19 **\
  m_Grid.m_InsertSQL = _T("INSERT INTO Streets (STREET) VALUES (Null)");
  m_Grid.m_TableName = _T("Streets");
\************************************** : by VK at 26.02.2004 19:00:22 **/
  m_Grid.SetRowCount(1);
  m_Grid.SetColumnCount(3);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetFixedRowCount(1);

  m_Grid.SetItemData(0, 0, (LPARAM)_T("ID") );
  m_Grid.SetItemData(0, 1, (LPARAM)m_szFieldName );
  m_Grid.SetItemData(0, 2, (LPARAM)_T("SEX") );

  m_Grid.m_FieldTypes.SetSize(3);
  m_Grid.m_FieldTypes.SetAt(0, dbLong);
  m_Grid.m_FieldTypes.SetAt(1, dbText);
  m_Grid.m_FieldTypes.SetAt(2, dbBoolean);

  m_Grid.SetItemText(0, 1, m_szColumnName );
  m_Grid.SetItemText(0, 2, _T("Стать") );
  m_Grid.SetColumnWidth(0, 16);
  m_Grid.SetColumnWidth(1, 140);
  m_Grid.SetColumnWidth(2, 60);
  Load(m_Grid.m_TableName, m_szFieldName);
  SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDBNames::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#Names"));
  return TRUE;
}