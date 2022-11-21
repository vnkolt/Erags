// CantOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "CantOpenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************** : by VK at 24.01.2007 18:54:01 **\
CString MakeRTFString(LPCTSTR szRTFKey) {
  CString s;
  while ( *szRTFKey ) {
    if ( (unsigned char)*szRTFKey > 128 ) {
      CString sChar;
      sChar.Format(_T("\\\'%02x"), (unsigned char)*szRTFKey );
      s += sChar;
      szRTFKey++;
      continue;
    }
    s += *szRTFKey++;
  }
  return s;
}
\************************************** : by VK at 24.01.2007 18:54:04 **/
/////////////////////////////////////////////////////////////////////////////
// CCantOpenDlg dialog
CCantOpenDlg::CCantOpenDlg(CWnd* pParent /*=NULL*/)
             :CDialogEx(CCantOpenDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CCantOpenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CCantOpenDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCantOpenDlg)
	//DDX_Control(pDX, IDC_INFO, m_InfoText);
  DDX_Control(pDX, IDC_RADIO1, m_Radio1);
  DDX_Control(pDX, IDC_RADIO2, m_Radio2);
  DDX_Control(pDX, IDC_RADIO3, m_Radio3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCantOpenDlg, CDialogEx)
	//{{AFX_MSG_MAP(CCantOpenDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCantOpenDlg message handlers
BOOL CCantOpenDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here

	// TODO: Add extra initialization here
  HRSRC hrsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_TXT1), "TXT");
  if ( NULL==hrsrc )
    return FALSE;
  
  HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hrsrc);
  LPVOID pData = ::LockResource(hGlobal);
  if ( NULL==pData )
    return FALSE;
  
  CString s = (LPCTSTR)pData;
  //m_szFilename.Replace(_T("\\"), _T("\\\\"));
  //m_szFilename = DecodeRTFKey(m_szFilename);
/************************************** : by VK at 24.01.2007 18:54:33 **\
  m_szFilename = MakeRTFString(m_szFilename);
\************************************** : by VK at 24.01.2007 18:54:36 **/
  s.Replace(_T("Filename"), m_szFilename);
  //m_InfoText.SetRTF( s );

  GetDlgItem(IDC_INFO)->SetWindowText(s);

  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_Radio1.SetRadioImageList(&m_RadioIL);  m_Radio1.SetRadio(IDC_RADIO1, IDC_RADIO3);
    m_Radio2.SetRadioImageList(&m_RadioIL);  m_Radio2.SetRadio(IDC_RADIO1, IDC_RADIO3);
    m_Radio3.SetRadioImageList(&m_RadioIL);  m_Radio3.SetRadio(IDC_RADIO1, IDC_RADIO3);
  }

  CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO3);
  m_idCheckedButton = IDC_RADIO3;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCantOpenDlg::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_idCheckedButton = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);
	CDialogEx::OnYes();
}
