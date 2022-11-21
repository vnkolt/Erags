// RepairDlg.cpp : implementation file
//

#include "stdafx.h"
#include "era2era3.h"
#include "RepairDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepairDlg dialog


CRepairDlg::CRepairDlg(LPCTSTR szFieldName, LPCTSTR szActName,
                       int nAct, COleDateTime DateReg,
                       LPCTSTR szNameOf, CWnd* pParent /*=NULL*/)
	         :CDialogBG(CRepairDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CRepairDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_szFieldName = szFieldName;
  m_szActName   = szActName;
  m_nAct        = nAct;
  m_DateReg     = DateReg;
  m_NameOf      = szNameOf;
}


void CRepairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRepairDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRepairDlg, CDialogBG)
	//{{AFX_MSG_MAP(CRepairDlg)
	ON_EN_CHANGE(IDC_WHAT, OnChangeWhat)
	ON_BN_CLICKED(IDC_NOMORE, OnNomore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepairDlg message handlers

BOOL CRepairDlg::OnInitDialog() {
	CDialogBG::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString s;
  s.Format(_T("  В поле \"%s\" було введене значення, яке потім видалили зі списку.\r\n")
           _T("Підніміть актовий запис про %s № %d від %02d.%02d.%04d ")
           _T("та введіть %s в актовому записі.\r\n")
           _T("  В конвертованому файлі БД буде внесене це значення.\r\n\r\n")
           _T("  Натисніть \"Скасувати\" щоб залишити це поле пустим."),
           m_szFieldName, m_szActName, m_nAct, m_DateReg.GetDay(), m_DateReg.GetMonth(), m_DateReg.GetYear(),
           m_NameOf);
  GetDlgItem(IDC_RAPAIR)->SetWindowText(s);
  GetDlgItem(IDC_LBL_WHAT)->SetWindowText(m_szFieldName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRepairDlg::OnChangeWhat() {
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogBG::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
  GetDlgItem(IDC_WHAT)->GetWindowText(m_szFieldValue);
	GetDlgItem(IDOK)->EnableWindow(!m_szFieldValue.IsEmpty());
}

void CRepairDlg::OnNomore() 
{
	// TODO: Add your control notification handler code here
  g_fNoAskMore = IsDlgButtonChecked(IDC_NOMORE);
}
