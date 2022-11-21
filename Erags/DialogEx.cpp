// DialogEx.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
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
	        :CDialogExBase(nIDTemplate, pParent) {
	//{{AFX_DATA_INIT(CDialogEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fYes = m_fNo = FALSE;
}


void CDialogEx::DoDataExchange(CDataExchange* pDX) {
	CDialogExBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDYES, m_btnOk);
	DDX_Control(pDX, IDNO, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogEx, CDialogExBase)
	//{{AFX_MSG_MAP(CDialogEx)
//  ON_BN_CLICKED(IDYES, OnYes)
//  ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEx message handlers
void CDialogEx::LoadBitmaps(){
  m_btnOk.SetIcon(IDI_YES);
  m_btnCancel.SetIcon(IDI_NO);
/************************************** : by VK at 22.05.2005 9:51:05 **\
  m_btnOk.SetBitmaps(IDB_YESFOCUS256, RGB(255,0,255), IDB_YES256, RGB(255,0,255));
  m_btnOk.SizeToContent();
  m_btnOk.DrawBorder(FALSE);
  m_btnOk.DrawFlatFocus(TRUE);
  m_btnOk.m_bShowDisabledBitmap = FALSE;

  m_btnCancel.SetBitmaps(IDB_NOFOCUS256, RGB(255,0,255), IDB_NO256, RGB(255,0,255));
  m_btnCancel.SizeToContent();
  m_btnCancel.DrawBorder(FALSE);
  m_btnCancel.DrawFlatFocus(TRUE);
  m_btnCancel.m_bShowDisabledBitmap = FALSE;
\************************************** : by VK at 22.05.2005 9:51:09 **/
}

BOOL CDialogEx::OnInitDialog() {
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

/************************************** : by VK at 20.01.2004 2:13:52 **\
	// TODO: Add extra initialization here
	CWnd* pItemWnd = GetWindow(GW_CHILD);
  if(pItemWnd){
    LOGFONT lf;
		CFont* pFont = pItemWnd->GetFont();
		if(pFont && pFont->GetLogFont(&lf)){
			lf.lfWeight =  FW_BOLD;
			lf.lfHeight = -14;
			strcpy(lf.lfFaceName, _T("Times New Roman Cyr"));
			m_Font.CreateFontIndirect(&lf);
			while(pItemWnd ) {
				pItemWnd->SetFont(&m_Font);
				pItemWnd = pItemWnd->GetWindow(GW_HWNDNEXT);
			}
    }
	}
\************************************** : by VK at 20.01.2004 2:13:55 **/

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
