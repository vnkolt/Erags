//
// ExportDlgs.cpp
//
#include "stdafx.h"
#include "ImpExp.h"
#include "ExportDlgs.h"

#include "..\Common\Export.h"
#include "..\Common\FHelpers.h"
#include "..\Common\DaoErr.h"
#include "..\Common\MDB.h"

#pragma warning (disable : 4786)
#include "..\Common\BasicExcelVC6.hpp"

#include <Atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct EFieldName {
  LPCTSTR szDBName;
  LPCTSTR szAltName;
};

#define BIRTH_G10         0x0001   // Const �_�10 = 1  ' ����� 10 {�10: }
#define BIRTH_RENEW       0x0002   // Const �_��� = 2  ' ���������� ��
#define BIRTH_LONGTERM    0x0004   // Const �_��� = 4  ' � ��������� ������
#define BIRTH_NOINLIST    0x0008   // Const �_��� = 8  ' �� � ������ ��������������
#define BIRTH_DECL20      0x0010

#define BIRTH_TYPE_ACT          0 // ��� ��� ���������
#define BIRTH_TYPE_MOTHER       1 // ����� �����
#define BIRTH_TYPE_PARENTS      2 // ����� ������
#define BIRTH_TYPE_APPL         3 // �����
#define BIRTH_TYPE_APPLNUM      4 // ����� �
#define BIRTH_TYPE_AFFILIATION1 5 // ����� ��� �������� ����������
#define BIRTH_TYPE_AFFILIATION2 6 // ������ ����� ��� �������� ����������

LPCTSTR GetFatherSource(BYTE b) {
  switch(b) {
    case BIRTH_TYPE_ACT         : return "�� ��� ����";
    case BIRTH_TYPE_MOTHER      : return "����� �����";
    case BIRTH_TYPE_PARENTS     : return "����� ������";
    case BIRTH_TYPE_APPL        : return "�����";
    case BIRTH_TYPE_APPLNUM     : return "����� �";
    case BIRTH_TYPE_AFFILIATION1: return "����� ������ ��� ��";
    case BIRTH_TYPE_AFFILIATION2: return "������ ����� ������ ��� ��";
  }
  return "";
}

void SetCell(YExcel::BasicExcelCell* pCell, COleVariant& var) {
  CString s;
  BSTR bStr = NULL;
  switch(var.vt) {
    case VT_I2:
    case VT_UI2:
      //pCell->Set(var.iVal);
      s.Format(_T("%d"), var.iVal);
      break;
    case VT_UI4:
    case VT_UINT:
      //pCell->Set((int)var.uintVal);
      s.Format(_T("%d"), var.uintVal);
      break;
    case VT_INT:
      //pCell->Set(var.intVal);
      s.Format(_T("%d"), var.intVal);
      break;
    case VT_I1:
    case VT_UI1:
      s.Format(_T("%c"), var.bVal);
      bStr = A2WBSTR(s);
      //pCell->Set(s);
      break;
    case VT_BSTR:
      s = V_BSTRT(&var);
      bStr = A2WBSTR(s);
      break;
    case VT_DATE:
      {
        COleDateTime d(var);
        if (d.GetStatus() == COleDateTime::valid) {
          s.Format(_T("%02d.%02d.%04d"), d.GetDay(), d.GetMonth(), d.GetYear());
          //pCell->Set(s);
        }
      }
      break;
  }
  if ( bStr != NULL ) {
    pCell->Set(bStr);
    ::SysFreeString(bStr);
  }
  else if ( false==s.IsEmpty() ) {
    pCell->Set(s);
  }
}

int FindAltFieldName(EFieldName* pFields, int nCount, LPCTSTR szDBName) {
  for( int i(0); i < nCount; i++ ) {
    if ( 0==strcmp(pFields[i].szDBName, szDBName) )
      return i;
  }
  return -1;
}
EFieldName  efBirth[] = { { "NUMBER"		       ,         "� ��"                                },
                          { "SEX"		           ,         "�����"                               },
                          { "DATEREG"		       ,         "���� �-���"                          },
                          { "RENEW"            ,         "���������"                           },
                          { "SURNAME"          ,         "�������"                            },
                          { "NAME"             ,         "��'�"                                },
                          { "PATRONYMIC"       ,         "�� �������"                         },
                          { "BIRTH_DATE"       ,         "���� ����������"                     },
                          { "BP_COUNTRY"       ,         "��: �������"                         },
                          { "BP_REGION"        ,         "��: �������"                         },
                          { "BP_CITY"          ,         "��: ̳��� (����, ������)"            },
                          { "BP_DISTRICT"      ,         "��: �����"                           },
                          { "NKIDS"            ,         "���������� ����"                    },
                          { "BYCOUNT"          ,         "��� �� �������� ������ � �����"     },
                          { "ALIVE_FLAG"       ,         "�������������/���������������"       },
                          { "SOURCE_TYPE"      ,         "ϳ������ (�� ��� ����, �����)"       },
                          { "SOURCE_NDOC"      ,         "����� �� ��� ���� (����� �����, ����� ������, ����)" },
                          { "SOURCE_DATE"      ,         "���� �� ��� ���� (����� �����, ����� ������, ����)" },
                          { "SOURCE_BY"        ,         "��� �������� �� ��� ����"            },
                          { "MEDICAL_CERTIFICATE_NUMBER","� ��������� ��-�� ��� ����������"    },
                          { "MEDICAL_CERTIFICATE_DATE",  "���� ��������� ��-�� ��� ����������" },
                          { "MEDICAL_CERTIFICATE_BY",    "��� ������ ������� ��-�� ��� ����������" },
                          { "FATHER_SURNAME"   ,         "������� ������"                     },
                          { "FATHER_NAME"      ,         "��'� ������"                         },
                          { "FATHER_PATRONYMIC",         "�� ������� ������"                  },
                          { "FATHER_BIRTH_DATE",         "�� ������"                           },
                          { "FATHER_CITIZENSHIP",        "������������ ������"                 },
                          { "FATHER_COUNTRY"   ,         "�� ������: �������"                  },
                          { "FATHER_REGION"    ,         "�� ������: �������"                  },
                          { "FATHER_CITY"      ,         "�� ������: ̳��� (����, ������)"     },
                          { "FATHER_DISTRICT"  ,         "�� ������: �����"                    },
                          { "FATHER_STREET"    ,         "�� ������: ������"                   },
                          { "FATHER_HOUSE"     ,         "�� ������: �������"                  },
                          { "FATHER_FLAT"      ,         "�� ������: ��������"                 },
                          { "MOTHER_SURNAME"   ,         "������� �����"                     },
                          { "MOTHER_NAME"      ,         "��'� �����"                         },
                          { "MOTHER_PATRONYMIC",         "�� ������� �����"                  },
                          { "MOTHER_BIRTH_DATE",         "�� �����"                           },
                          { "MOTHER_CITIZENSHIP",        "������������ �����"                 },
                          { "MOTHER_COUNTRY"   ,         "�� �����: �������"                  },
                          { "MOTHER_REGION"    ,         "�� �����: �������"                  },
                          { "MOTHER_CITY"      ,         "�� �����: ̳��� (����, ������)"     },
                          { "MOTHER_DISTRICT"  ,         "�� �����: �����"                    },
                          { "MOTHER_STREET"    ,         "�� �����: ������"                   },
                          { "MOTHER_HOUSE"     ,         "�� �����: �������"                  },
                          { "MOTHER_FLAT"      ,         "�� �����: ��������"                 },
                          { "DECLARANT_NAME"   ,         "ϲ� �������� (��������)"            },
                          { "DECLARANT_ADDRESS",         "������ �������� (��������)"         },
                          { "DECLARANT_PASSPORT_TYPE",   "�������� ��������"                   },
                          { "DECLARANT_PASSPORT_SERIA",  "���� ��������� ��������"            },
                          { "DECLARANT_PASSPORT_NUMBER", "����� ��������� ��������"            },
                          { "DECLARANT_PASSPORT_DATE",   "���� ������ ��������� ��������"      },
                          { "DECLARANT_PASSPORT_BY",     "��� ������ �������� ��������"        },
                          { "CERTIFICATE_SERIA" ,        "���� ��������"                     },
                          { "CERTIFICATE_NUMBER",        "����� ��������"                     },
                          { "NOTICE"            ,        "������"                             },
                       };
CPtrArray  g_BithFields;
/////////////////////////////////////////////////////////////////////////////
// CExpTypesPage dialog
CExpTypesPage::CExpTypesPage(CWnd* pParent /*=NULL*/)
            	:CNewWizPage(CExpTypesPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpTypesPage)
	m_XLS = true;
	m_RTF = false;
	m_HTM = false;
	m_Birth = true;
	m_Marriage = true;
	m_Divorce = true;
	m_Change = true;
	m_Death = true;
	//}}AFX_DATA_INIT
}

void CExpTypesPage::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpTypesPage)
	DDX_Check(pDX, IDC_CHECK_XLS, m_XLS);
	DDX_Check(pDX, IDC_CHECK_RTF, m_RTF);
	DDX_Check(pDX, IDC_CHECK_HTM, m_HTM);
	DDX_Check(pDX, IDC_CHECK_BIRH, m_Birth);
	DDX_Check(pDX, IDC_CHECK_MARRIAGE, m_Marriage);
	DDX_Check(pDX, IDC_CHECK_DIVORCE, m_Divorce);
	DDX_Check(pDX, IDC_CHECK_CHANGE, m_Change);
	DDX_Check(pDX, IDC_CHECK_DEATH, m_Death);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpTypesPage, CNewWizPage)
	//{{AFX_MSG_MAP(CExpTypesPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpTypesPage message handlers


/////////////////////////////////////////////////////////////////////////////
// CExpBirth dialog
CExpBirth::CExpBirth(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CExpBirth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpBirth)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CExpBirth::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpBirth)
	DDX_Control(pDX, IDC_NO_EXPORT, m_NoList);
	DDX_Control(pDX, IDC_DO_EXPORT, m_DoList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpBirth, CNewWizPage)
	//{{AFX_MSG_MAP(CExpBirth)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_NO_EXPORT, OnItemchangedNoExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DO_EXPORT, OnItemchangedDoExport)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SUB, OnSub)
	ON_BN_CLICKED(IDC_SUB_ALL, OnSubAll)
	ON_BN_CLICKED(IDC_ADD_ALL, OnAddAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SORT_SPIN, OnDeltaposSortSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpBirth message handlers
BOOL CExpBirth::OnInitDialog() {
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here
  //m_NoList.ModifyStyle(0, WS_CAPTION);
  //m_DoList.ModifyStyle(0, WS_CAPTION);

  m_NoList.InsertColumn(0, _T("����� ����"), LVCFMT_LEFT, 180);
  m_NoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	
  m_DoList.InsertColumn(0, _T("����� ����"), LVCFMT_LEFT, 180);
  m_DoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);

  for( int i(0); i < sizeof(efBirth)/sizeof(efBirth[0]); i++ ) {
    m_NoList.InsertItem(i, efBirth[i].szAltName);
    m_NoList.SetItemData(i, (DWORD)&efBirth[i]);
  }
  GetDlgItem(IDC_ADD)->EnableWindow(false);
  GetDlgItem(IDC_SUB)->EnableWindow(false);
  GetDlgItem(IDC_SUB_ALL)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CExpBirth::OnItemchangedNoExport(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  BOOL fEnableAdd    = (m_NoList.GetFirstSelectedItemPosition() != NULL);
  BOOL fEnableAddAll = (m_NoList.GetItemCount() > 0);
  GetDlgItem(IDC_ADD)->EnableWindow(fEnableAdd);
  GetDlgItem(IDC_ADD_ALL)->EnableWindow(fEnableAddAll);
	*pResult = 0;
}
void CExpBirth::OnItemchangedDoExport(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  BOOL fEnableSub    = (m_DoList.GetFirstSelectedItemPosition() != NULL);
  BOOL fEnableSubAll = (m_DoList.GetItemCount() > 0);
  GetDlgItem(IDC_SUB)->EnableWindow(fEnableSub);
  GetDlgItem(IDC_SUB_ALL)->EnableWindow(fEnableSubAll);
	*pResult = 0;
}

void CExpBirth::OnAdd() {
	// TODO: Add your control notification handler code here
  int nItem;
  POSITION pos = m_NoList.GetFirstSelectedItemPosition();
  while ( pos ) {
    nItem = m_NoList.GetNextSelectedItem(pos);
    if ( nItem >= 0 ) {
      EFieldName* p = (EFieldName*)m_NoList.GetItemData(nItem);
      int iDoItem = m_DoList.GetItemCount();
      m_DoList.InsertItem(iDoItem, p->szAltName);
      m_DoList.SetItemData(iDoItem, (DWORD)p);
    }
  }
  while ( (nItem = m_NoList.GetNextItem(-1, LVNI_SELECTED)) >=0 ) {
    m_NoList.DeleteItem(nItem);
  }
}
void CExpBirth::OnAddAll() {
  int nCount = m_NoList.GetItemCount();
  for( int i(0); i < nCount; i++ ) {
    EFieldName* p = (EFieldName*)m_NoList.GetItemData(i);
    int iDoItem = m_DoList.GetItemCount();
    m_DoList.InsertItem(iDoItem, p->szAltName);
    m_DoList.SetItemData(iDoItem, (DWORD)p);
  }
  m_NoList.DeleteAllItems();
}

void CExpBirth::OnSub() {
  int nItem;
  POSITION pos = m_DoList.GetFirstSelectedItemPosition();
  while ( pos ) {
    nItem = m_DoList.GetNextSelectedItem(pos);
    if ( nItem >= 0 ) {
      EFieldName* p = (EFieldName*)m_DoList.GetItemData(nItem);
      int iNoItem = m_NoList.GetItemCount();
      m_NoList.InsertItem(iNoItem, p->szAltName);
      m_NoList.SetItemData(iNoItem, (DWORD)p);
    }
  }
  while ( (nItem = m_DoList.GetNextItem(-1, LVNI_SELECTED)) >=0 ) {
    m_DoList.DeleteItem(nItem);
  }
}

void CExpBirth::OnSubAll() {
  int nCount = m_DoList.GetItemCount();
  for( int i(0); i < nCount; i++ ) {
    EFieldName* p = (EFieldName*)m_DoList.GetItemData(i);
    int iNoItem = m_NoList.GetItemCount();
    m_NoList.InsertItem(iNoItem, p->szAltName);
    m_NoList.SetItemData(iNoItem, (DWORD)p);
  }
  m_DoList.DeleteAllItems();
}

void CExpBirth::OnDeltaposSortSpin(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int nItem = m_DoList.GetNextItem(-1, LVNI_SELECTED);
  if ( nItem >= 0 ) {
    EFieldName* p = (EFieldName*)m_DoList.GetItemData(nItem);
    m_DoList.DeleteItem(nItem);
    nItem += pNMUpDown->iDelta;
    if ( nItem < 0 )
      nItem = 0;
    if ( nItem > m_DoList.GetItemCount() )
      nItem = m_DoList.GetItemCount();
    m_DoList.InsertItem(nItem, p->szAltName);
    m_DoList.SetItemData(nItem, (DWORD)p);
    m_DoList.SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
    m_DoList.EnsureVisible(nItem, FALSE);
  } 
	*pResult = 0;
}

LRESULT CExpBirth::OnWizardNext() {
  g_BithFields.RemoveAll();
  int nCount = m_DoList.GetItemCount();
  for( int i(0); i < nCount; i++ ) {
    EFieldName* p = (EFieldName*)m_DoList.GetItemData(i);
    g_BithFields.Add(p);
  }
  return CNewWizPage::OnWizardNext();
}

/////////////////////////////////////////////////////////////////////////////
// CExpProgressDlg dialog
CExpProgressDlg::CExpProgressDlg(CWnd* pParent /*=NULL*/)
              	:CNewWizPage(CExpProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CExpProgressDlg::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpProgressDlg, CNewWizPage)
	//{{AFX_MSG_MAP(CExpProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpProgressDlg message handlers
BOOL CExpProgressDlg::OnInitDialog() {
	CNewWizPage::OnInitDialog();

  CString szXLSName;
  szXLSName.Format(_T("%s\\%s.xls"), GetFilePath(g_SourceDB.GetName()), GetFileName(g_SourceDB.GetName()));

  long lTotalRecords = 0;
  if ( g_BithFields.GetSize() ) {
    lTotalRecords += GetRecordCount(g_SourceDB, _T("BIRTHES"));
  }
  m_Progress.SetRange32(0, lTotalRecords);


  YExcel::BasicExcel e;
	
	// TODO: Add extra initialization here
  if ( g_BithFields.GetSize()) {
    CDaoRecordset rs(&g_SourceDB);
    try {
      rs.Open(dbOpenTable, _T("BIRTHES"), dbReadOnly);
      rs.SetCurrentIndex(_T("NUMBER"));
      int nFields = rs.GetFieldCount();
      CExportTable et(nFields);
      for( int i(0); i < nFields; i++ ) {
        CDaoFieldInfo fi;
        rs.GetFieldInfo(i, fi);
        VARTYPE vt = 0;
        switch( fi.m_nType ) {
          case dbBoolean :  vt = VT_BOOL; break;
          case dbByte    :  vt = VT_UI1;  break;
          case dbInteger :  vt = VT_I2;   break;
          case dbLong    :  vt = VT_I4;   break;
          case dbCurrency:  vt = VT_CY;   break;
          case dbSingle  :  vt = VT_R4;   break;
          case dbDouble  :  vt = VT_R8;   break;
          case dbDate    :  vt = VT_DATE; break;
          case dbText    :  vt = VT_BSTR; break;
          case dbMemo    :  vt = VT_BSTR; break;
        }
        int AltIndex = FindAltFieldName(efBirth, sizeof(efBirth)/sizeof(efBirth[0]), fi.m_strName);
        if ( -1==AltIndex ) {
          et.SetColumn(i, vt, fi.m_strName, fi.m_strName);
        }
        else {
          et.SetColumn(i, vt, fi.m_strName, efBirth[AltIndex].szAltName);
        }
      }
      int nRow = 0;
      while ( !rs.IsEOF() ) {
        CString szSurname = GetFieldString(&rs, _T("SURNAME"));
        if ( false==szSurname.IsEmpty() ) {
          nRow = et.AddRow();
          for( int i(0); i < nFields; i++ ) {
            COleVariant var;
            rs.GetFieldValue(i, var);
            CString szColumnName = et.GetColumnName(i);
            if ( szColumnName==_T("SEX") ) {
              if ( var.boolVal ) { et.SetData(i, nRow, COleVariant((BYTE)'�')); }
              else               { et.SetData(i, nRow, COleVariant((BYTE)'�')); }
            }
            else if ( szColumnName==_T("RENEW") ) {
              CString s;
              if ( var.lVal && BIRTH_RENEW    ) { s = _T("���");   }
              if ( var.lVal && BIRTH_LONGTERM ) { s += _T(", ���"); }
              s.TrimLeft(); s.TrimRight();
              et.SetData(i, nRow, COleVariant(s));
            }
            else if ( szColumnName==_T("SOURCE_TYPE") ) {
              et.SetData(i, nRow, COleVariant(GetFatherSource(var.bVal), VT_BSTRT));
            }
            else if ( szColumnName==_T("NKIDS") || szColumnName==_T("BYCOUNT") ) {
              et.SetData(i, nRow, COleVariant((short)var.bVal));
            }
            else if ( szColumnName==_T("ALIVE_FLAG") ) {
              if ( var.boolVal ) { et.SetData(i, nRow, COleVariant((BYTE)'�')); }
              else               { et.SetData(i, nRow, COleVariant((BYTE)'�')); }
            }
            else {
              et.SetData(i, nRow, var);
            }
          }
        }
        rs.MoveNext();
      }
      BSTR bStr = A2WBSTR("������ ��� ������");
      YExcel::BasicExcelWorksheet* sheet = e.AddWorksheet(bStr, 0);
      if ( bStr ) {
        ::SysFreeString(bStr);
      }
      et.DeleteColumn(_T("ID"));
      et.DeleteColumn(_T("BP_FLAG"));
      et.DeleteColumn(_T("DECLARANT_TYPE"));
      et.DeleteColumn(_T("EXTNOTES"));
      for( int c = 0; c < et.GetColumnCount(); c++ ) {
        bStr = A2WBSTR(et.GetColumnAltName(c));
        if ( bStr ) {
          sheet->Cell(0,c)->SetWString(bStr);
          ::SysFreeString(bStr);
        }
      }
      for( int r = 0; r < et.GetRowCount(); r++ ) {
        for( c = 0; c < et.GetColumnCount(); c++ ) {
          COleVariant var = et.GetCellData(c, r);
          CString s = et.GetColumnName(c);
          SetCell(sheet->Cell(r+1,c), var);
        }
      }
    }
    catch(CDaoException* e) {
      OnMessage(MT_ERROR, FormatDaoError(e));
      e->Delete();
    }
  }
  e.SaveAs(szXLSName);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CExportWizardDlg dialog
CExportWizardDlg::CExportWizardDlg(CWnd* pParent /*=NULL*/)
                 :CNewWizDialog(CExportWizardDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CExportWizardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CExportWizardDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportWizardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportWizardDlg, CNewWizDialog)
	//{{AFX_MSG_MAP(CExportWizardDlg)
	ON_WM_CTLCOLOR()
  ON_WM_DESTROY()
  ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg message handlers
BOOL CExportWizardDlg::OnInitDialog() {

	SetPlaceholderID(IDC_SHEETRECT);

	CNewWizDialog::OnInitDialog();

	m_Brush.CreateSolidBrush(CLR_BK);

  GetDlgItem(ID_HELP)->ShowWindow(SW_SHOW);
/*
  HICON hIcon = theApp.LoadIcon(IDR_MAINFRAME);
  SetIcon(hIcon, TRUE);
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CExportWizardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	switch (nCtlColor) {	   
		case CTLCOLOR_STATIC:
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
		case CTLCOLOR_SCROLLBAR:
		case CTLCOLOR_BTN:
		case CTLCOLOR_DLG:	    
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(CLR_BK);
			return m_Brush;
	}	
	// TODO: Return a different brush if the default is not desired
	return m_Brush;
}

void CExportWizardDlg::OnDestroy() {
  CNewWizDialog::OnDestroy();

/*
  if ( g_fSuccessful ) {
    CFinishPage FinishPage;
    FinishPage.DoModal();
  }
*/
}

void CExportWizardDlg::OnHelp() {
}

void ExportWizard(LPCTSTR szSrcDB) {
  CExportWizardDlg dlg;
  CExpTypesPage    TypesPage;
  CExpBirth        BirthPage;
  CExpProgressDlg  ProgressPage;

  dlg.AddPage(&TypesPage,    CExpTypesPage::IDD);
  dlg.AddPage(&BirthPage,    CExpBirth::IDD);
  dlg.AddPage(&ProgressPage, CExpProgressDlg::IDD);

  dlg.DoModal();
}

