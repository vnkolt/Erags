// DBGridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\Erags\Erags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DBGridDlg.h"
#include <afxpriv.h>

#include "..\Controls\EraControls.h"

// CDBGridToolBar
BEGIN_MESSAGE_MAP(CDBGridToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDBGridToolBar)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
                 
/////////////////////////////////////////////////////////////////////////////
// CDlgToolBar Construction/Destruction
CDBGridToolBar::CDBGridToolBar() {
}
CDBGridToolBar::~CDBGridToolBar() {
} 

/////////////////////////////////////////////////////////////////////////////
// CDBGridToolBar::OnIdleUpdateCmdUI
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
LRESULT CDBGridToolBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM) {
	if (IsWindowVisible()) 
	{
		CFrameWnd *pParent = (CFrameWnd *)GetParent();
		if (pParent)
			OnUpdateCmdUI(pParent, (BOOL)wParam);
	}
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CDBGridDlg dialog


CDBGridDlg::CDBGridDlg(CWnd* pParent /*=NULL*/, UINT id/*=IDD_DBGRID*/)
	         :CDialogBG(id, pParent) {
	//{{AFX_DATA_INIT(CDBGridDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDBGridDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogBG::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBGridDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
  DDX_GridControl(pDX, IDC_GRID, m_Grid);
}

BEGIN_MESSAGE_MAP(CDBGridDlg, CDialogBG)
	//{{AFX_MSG_MAP(CDBGridDlg)
	ON_UPDATE_COMMAND_UI(ID_RECORD_EDIT, OnUpdateRecordEdit)
	ON_COMMAND(ID_RECORD_EDIT, OnRecordEdit)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
	ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBGridDlg message handlers
BOOL CDBGridDlg::OnInitDialog() {
	CDialogBG::OnInitDialog();
	
	// TODO: Add extra initialization here
//  m_Grid.SetDBGridMode(TRUE);

	// Create toolbar at the top of the dialog window
	if (m_toolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLYBY | TBSTYLE_FLAT))	{
    UINT IDArray[] = {ID_RECORD_EDIT, ID_RECORD_NEW, ID_RECORD_DELETE};
	  m_toolBar.LoadBitmap(IDR_DATAGRID);
	  m_toolBar.SetButtons(IDArray, 3);
	}

	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);
	
	// Now move all the controls so they are in the same relative
	// position within the remaining client area as they would be
	// with no control bars.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top); 

	CRect  rcChild;					
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)	{                               
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}

	// Adjust the dialog window dimensions
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	
	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
		
	// Finally, center the dialog on the screen
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBGridDlg::OnUpdateRecordEdit(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
}

void CDBGridDlg::OnRecordEdit() {
	// TODO: Add your command handler code here
  CCellID cell = m_Grid.GetFocusCell();
  if ( m_Grid.IsValid(cell) ) {
    SendKeys(VK_F2, 0);
  }
}

void CDBGridDlg::OnUpdateRecordNew(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
}

void CDBGridDlg::OnRecordNew() {
  if ( m_Grid.GetRowCount()==m_Grid.GetFixedRowCount() ) {
    m_Grid.InsertRow(_T(""));
    m_Grid.AddRow(1);
    m_Grid.SetFocusCell(1,1);
    m_Grid.EnsureVisible(1, 1);
  }
  if ( m_Grid.GetEditRow() != -1 ) {
    SendKeys(VK_RETURN, 0);
  }
  SendKeys(VK_END, VK_CONTROL);
  SendKeys(VK_DOWN, 0);
  OnRecordEdit();
}

void CDBGridDlg::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
}

void CDBGridDlg::OnRecordDelete() {
	// TODO: Add your command handler code here
  int nRow = m_Grid.GetEditRow();
  if ( nRow != -1 ) {
    SendKeys(VK_RETURN, 0);
    CCellID cell;
    m_Grid.SelectRows( CCellID(nRow, 0), TRUE, TRUE );
  }
  SendKeys(VK_DELETE, 0);
}
