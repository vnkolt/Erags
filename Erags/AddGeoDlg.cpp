// AddGeoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "AddGeoDlg.h"
#include "Geography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
держава
край
м≥сто
область
район
село
селище
смт
станиц€
станц≥€
хут≥р
*/
CString CompactGeoType(const CString& szType) {
  CString s;
  if ( szType==_T("село") ) {
    s = _T("с.");
  }
  else if ( szType==_T("селище") ) {
    s = _T("с-ще");
  }
  else if ( szType==_T("м≥сто") ) {
    s = _T("м.");
  }
  else if ( szType==_T("район") ) {
    s = _T("р-н");
  }
  else
    s = szType;
  return s;
}
/////////////////////////////////////////////////////////////////////////////
// CAddGeoDlg dialog
CAddGeoDlg::CAddGeoDlg(CWnd* pParent, ERAGSGEOTYPE geotype)
           :CDialogEx(CAddGeoDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CAddGeoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_GeoType = geotype;
  m_pParentGeoRecord = m_pRecord = NULL;
  m_fOk = false;
}


void CAddGeoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddGeoDlg)
  DDX_Control(pDX, IDC_LBLTYPE, m_lblType);
  DDX_Control(pDX, IDC_LBLNAME, m_lblName);
  DDX_Control(pDX, IDC_LBLFULLNAME, m_lblFullName);
	DDX_Control(pDX, IDC_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_NAME, m_edtName);
	DDX_Control(pDX, IDC_FULLNAME, m_edtFullName);
  DDX_Control(pDX, IDC_BTN_UP, m_btnUp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddGeoDlg, CDialogEx)
	//{{AFX_MSG_MAP(CAddGeoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddGeoDlg message handlers

BOOL CAddGeoDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  LPCTSTR szTypes[] = { "держава",
                        "край",
                        "м≥сто",
                        "область",
                        "район",
                        "село",
                        "селище",
                        "смт",
                        "станиц€",
                        "станц≥€",
                        "хут≥р",
                        NULL
                      };

  for( int i(0); szTypes[i]; i++ ) {
    m_cmbType.AddString(szTypes[i]);
  }

	switch ( m_GeoType ) {
    case GT_COUNTRY :
      m_cmbType.SelectString(-1, _T("держава"));
      break;
    case GT_REGION  :
      m_cmbType.SelectString(-1, _T("область"));
      break;
    case GT_DISTRICT:
      m_cmbType.SelectString(-1, _T("район"));
      break;
    case GT_CITY    :
      m_cmbType.SelectString(-1, _T("село"));
      break;
  }
  if ( m_pParentGeoRecord ) {
    GetDlgItem(IDC_GEOPATH)->SetWindowText( GetGeoPath(m_pParentGeoRecord) );
  }
  m_btnUp.SetIcon(IDI_UP);
  m_btnOk.EnableWindow(FALSE);

  if ( !m_sName.IsEmpty() ) {
    m_edtName.SetWindowText(m_sName);
  }
/*
  int nCount = m_cmbType.GetCount();
  CString s;
  for( int i(0); i < nCount; i++ ) {
    m_cmbType.GetLBText(i, s);
  }
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddGeoDlg::OnYes() {
	// TODO: Add extra validation here
  m_edtName.GetWindowText(m_sName);
  m_edtFullName.GetWindowText(m_sFullName);
  m_cmbType.GetWindowText(m_sType);
  if ( m_pParentGeoRecord ) {
    m_pRecord = new CGeoRecord();
    m_pRecord->m_pParent  = m_pParentGeoRecord;
    m_pRecord->m_ParentID = m_pParentGeoRecord->m_ID;
    m_pRecord->m_Name     = m_sName;
    m_pRecord->m_AltName  = m_sFullName;
    m_pRecord->m_Type     = CompactGeoType(m_sType);
    if ( m_pRecord->Insert() ) {
      m_pParentGeoRecord->m_array.Add( m_pRecord );
      m_fOk = true;
    }
    else {
      delete m_pRecord;
      m_pRecord = NULL;
    }
  }
  else {  // Add for country only
    m_pRecord = new CGeoRecord();
    m_pRecord->m_pParent  = NULL;
    m_pRecord->m_ParentID = 0;
    m_pRecord->m_Name     = m_sName;
    m_pRecord->m_AltName  = m_sFullName;
    m_pRecord->m_Type     = CompactGeoType(m_sType);
    if ( m_pRecord->Insert() ) {
      if ( m_pParentGeoRecord )
        m_pParentGeoRecord->m_array.Add( m_pRecord );
      else
        theGeoCache.m_array.Add( m_pRecord );
      m_fOk = true;
    }
    else {
      delete m_pRecord;
      m_pRecord = NULL;
    }
  }
  EndDialog(IDYES);
}

void CAddGeoDlg::OnUp() {
  if ( m_pParentGeoRecord ) {
    m_pParentGeoRecord = m_pParentGeoRecord->m_pParent;
    GetDlgItem(IDC_GEOPATH)->SetWindowText( GetGeoPath(m_pParentGeoRecord) );
  }
}

BOOL CAddGeoDlg::CanAdd() {
  return (FALSE==m_edtName.GetText().IsEmpty());
}

BOOL CAddGeoDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  switch( LOWORD(wParam) ) {
    case IDC_BTN_UP:
      if ( BN_CLICKED==HIWORD(wParam) ) {
        OnUp();
        return true;
      }
      break;
    case IDC_NAME:
      if ( EN_CHANGE==HIWORD(wParam) ) {
        m_btnOk.EnableWindow( CanAdd() );
      }
      break;
  }
  return CDialogEx::OnCommand(wParam, lParam);
}
