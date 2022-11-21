// ETTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ETTest.h"
#include "ETTestDlg.h"
#include "Export.h"

#include "BasicExcelVC6.hpp"

#include <Atlconv.h>

using namespace YExcel;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_ROWS  10

/*
inline BSTR A2WBSTR(LPCSTR lp, int nLen = -1)
{
   USES_CONVERSION;
   BSTR str = NULL;
   int nConvertedLen = MultiByteToWideChar(_acp, 0, lp,
     nLen, NULL, NULL);
 
   // BUG FIX #1 (from Q241857): only subtract 1 from 
   // the length if the source data is nul-terminated
   if (nLen == -1)
      nConvertedLen--;
 
   str = ::SysAllocStringLen(NULL, nConvertedLen);
   if (str != NULL)
   {
     MultiByteToWideChar(_acp, 0, lp, nLen, str, nConvertedLen);
   }
   return str;
}
*/

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CETTestDlg dialog

CETTestDlg::CETTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CETTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CETTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CETTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CETTestDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CETTestDlg, CDialog)
	//{{AFX_MSG_MAP(CETTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CETTestDlg message handlers

BOOL CETTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
  m_List.InsertColumn(0, _T("Int"),  LVCFMT_LEFT, 64);
  m_List.InsertColumn(1, _T("Date"), LVCFMT_LEFT, 80);
  m_List.InsertColumn(2, _T("String"), LVCFMT_LEFT, 80);

  for( int i(0); i < MAX_ROWS; i++ ) {
    CString s;
    SYSTEMTIME st;
    GetLocalTime(&st);
    m_List.InsertItem(i, _T(""));

    s.Format(_T("%d"), i);
    m_List.SetItemText(i, 0, s);

    s.Format(_T("%02d.%02d.%04d"), st.wDay, st.wMonth, st.wYear);
    m_List.SetItemText(i, 1, s);

    s.Format(_T("Строка %d"), i);
    m_List.SetItemText(i, 2, s);

  }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CETTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CETTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CETTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CETTestDlg::OnOK() {
	// TODO: Add extra validation here
	CDialog::OnOK();
  YExcel::BasicExcel e;

  CExportTable et(3);
  et.SetColumn(0, VT_I4,   _T("INT"),  _T("Целое"));
  et.SetColumn(1, VT_DATE, _T("DATE"), _T("Дата"));
  et.SetColumn(2, VT_BSTR, _T("BSTR"), _T("Строка"));

  YExcel::BasicExcelWorksheet* sheet = e.AddWorksheet(A2WBSTR("Лист1"), 0);

  int nRow = 0;
  while (nRow < MAX_ROWS) {
    nRow = et.AddRow();
    for( int nCol(0); nCol < 3; nCol++ ) {
      COleVariant var;
      CString s = m_List.GetItemText(nRow, nCol);
      switch( nCol ) {
        case 0: // INT
          var = COleVariant((long)atoi(s), VT_I4);
          break;
        case 1: // DATE
          var = s;
          break;
        case 2: // BSTR
          var = s;
          break;
      }
      et.SetData(nCol, nRow, var);
    }
  }

  for( int r = 0; r < et.GetRowCount(); r++ ) {
    for( int c = 0; c < et.GetColumnCount(); c++ ) {
      COleVariant var = et.GetCellData(c, r);
      BSTR bStr = NULL;
      switch( var.vt ) {
        case VT_R8    : sheet->Cell(r,c)->SetDouble (var.dblVal);     break;
        case VT_BOOL  : sheet->Cell(r,c)->SetInteger(var.boolVal);    break;
        case VT_I4    : sheet->Cell(r,c)->SetInteger(var.lVal);       break;
        //case VT_DATE  : sheet->Cell(r,c)->
//        case VT_BSTR  : sheet->Cell(r,c)->SetWString(var.bstrVal);    break;
//        case VT_BSTRT : sheet->Cell(r,c)->SetString (V_BSTRT(&var));  break;

        case VT_BSTR  :
        case VT_BSTRT :
          bStr = A2WBSTR( CString(var.bstrVal) );
          sheet->Cell(r,c)->SetWString ( bStr);  break;
      }
      if ( bStr ) {
        ::SysFreeString(bStr);
      }
    }
  }

  e.SaveAs("example.xls");

}
