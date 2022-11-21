// DialogEx.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "DialogEx.h"

#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgToolBar
BEGIN_MESSAGE_MAP(CDlgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDlgToolBar)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
                 
/////////////////////////////////////////////////////////////////////////////
// CDlgToolBar Construction/Destruction
CDlgToolBar::CDlgToolBar() {
}
CDlgToolBar::~CDlgToolBar() {
} 

/////////////////////////////////////////////////////////////////////////////
// CDlgToolBar::OnIdleUpdateCmdUI
//		OnIdleUpdateCmdUI handles the WM_IDLEUPDATECMDUI message, which is 
//      used to update the status of user-interface elements within the MFC 
//		framework.
//
// 		We have to get a little tricky here: CToolBar::OnUpdateCmdUI 
//      expects a CFrameWnd pointer as its first parameter.  However, it
//      doesn't do anything but pass the parameter on to another function
//      which only requires a CCmdTarget pointer.  We can get a CWnd pointer
//      to the parent window, which is a CCmdTarget, but may not be a 
//   	CFrameWnd.  So, to make CToolBar::OnUpdateCmdUI happy, we will call
//      our CWnd pointer a CFrameWnd pointer temporarily.  	
LRESULT CDlgToolBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM) {
	if (IsWindowVisible()) 
	{
		CFrameWnd *pParent = (CFrameWnd *)GetParent();
		if (pParent)
			OnUpdateCmdUI(pParent, (BOOL)wParam);
	}
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog
CDialogEx::CDialogEx(UINT nIDTemplate, CWnd* pParent/*=NULL*/)
	        :CDialogBG(nIDTemplate, pParent) {
	//{{AFX_DATA_INIT(CDialogEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fYes = m_fNo = FALSE;
}


void CDialogEx::DoDataExchange(CDataExchange* pDX) {
	CDialogBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDYES, m_btnOk);
	DDX_Control(pDX, IDNO, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogEx, CDialogBG)
	//{{AFX_MSG_MAP(CDialogEx)
	ON_COMMAND(IDYES, OnYes)
	ON_COMMAND(IDOK,  OnYes)
	ON_COMMAND(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEx message handlers
void CDialogEx::LoadBitmaps(){
  m_btnOk.SetIcon(IDI_YES);
  m_btnCancel.SetIcon(IDI_NO);
}

BOOL CDialogEx::OnInitDialog() {
  	
	// execute dialog RT_DLGINIT resource
	CDialogExBase::OnInitDialog();
	// execute dialog RT_DLGINIT resource
	BOOL bDlgInit;
	if (m_lpDialogInit != NULL)
		bDlgInit = ExecuteDlgInit(m_lpDialogInit);
	else
		bDlgInit = ExecuteDlgInit(m_lpszTemplateName);

	if (!bDlgInit) {
		TRACE0("Warning: ExecuteDlgInit failed during dialog init.\n");
		EndDialog(-1);
		return FALSE;
	}

	// transfer data into the dialog from member variables
	if (!UpdateData(FALSE)) {
		TRACE0("Warning: UpdateData failed during dialog init.\n");
		EndDialog(-1);
		return FALSE;
	}

  LoadBitmaps();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogEx::PumpMessages() {
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}
void CDialogEx::OnYes()
{
	UpdateData();
	CDialogEx::EndDialog(IDYES);
}
void CDialogEx::OnNo()
{
	CDialogEx::EndDialog(IDNO);
}

BOOL CDialogEx::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  if ( BN_CLICKED==HIWORD(wParam) ) {
    switch(LOWORD(wParam)) {
      case IDYES:
        if ( FALSE==m_fYes ) {
          m_fYes = TRUE;
          OnYes();
          m_fYes = FALSE;
        }
        return TRUE;
      case IDNO:
        if ( FALSE==m_fNo ) {
          m_fNo = TRUE;
          OnNo();
          m_fNo = FALSE;
        }
        return TRUE;
    }
  }
	return CDialogExBase::OnCommand(wParam, lParam);
}
