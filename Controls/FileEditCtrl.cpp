// FileEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "FileEditCtrl.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileEditCtrl

CFileEditCtrl::CFileEditCtrl()
{
	m_bFindFolder = FALSE;		
	m_button = new CFEButton();
	m_edit = new CEdit();
	m_pbi = NULL;
	m_pcfd = NULL;
}

CFileEditCtrl::~CFileEditCtrl()
{
	if (m_button) delete m_button;
	if (m_edit) delete m_edit;
	if (m_pbi) delete m_pbi;
	if (m_pcfd) delete m_pcfd;
}


BEGIN_MESSAGE_MAP(CFileEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CFileEditCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED (2, OnBrowse)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileEditCtrl message handlers

int CFileEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Get the edit control styles and create the edit control
	DWORD style = lpCreateStruct->style & 0x1800009BL; // WS_VISIBLE | WS_DISABLED | permitted edit control styles
	if (!m_edit->Create(WS_CHILD | WS_CLIPSIBLINGS | style, CRect (0,0,1,1), this, 1))
		return -1;

	// Get the button styles and create the button
	style = lpCreateStruct->style & 0x18000000L; // WS_VISIBLE | WS_DISABLED
	if (!m_button->Create("", WS_CHILD | WS_CLIPSIBLINGS | BS_OWNERDRAW | style, CRect (0,0,1,1), this, 2))
		return -1;
	
	// determine if control will find folders or files
	m_bFindFolder = lpCreateStruct->style & FES_FOLDER;

	if (m_bFindFolder)
	{
		// set up the browseinfo structure used by SHBrowseForFolder()
		m_pbi = new BROWSEINFO();
		::ZeroMemory(m_pbi, sizeof(BROWSEINFO));
		m_pbi->hwndOwner = GetSafeHwnd();
		m_pbi->pszDisplayName = m_buffer;
		m_pbi->lpszTitle = "Browse for Folder";
		m_pbi->ulFlags = BIF_RETURNONLYFSDIRS;
	}
	else
	{
		// create the CFileDialog
		m_pcfd = new CFileDialog(TRUE);
		m_pcfd->m_ofn.hwndOwner = GetSafeHwnd();
	}
	return 0;
}

void CFileEditCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// set the control sizes
	m_edit->MoveWindow(0, 0, cx - cy, cy);
	m_button->MoveWindow(cx-cy, 0, cy, cy);
}

void CFileEditCtrl::OnBrowse()
{
	if (m_bFindFolder)
		FECBrowseForFolder();
	else
		FECOpenFile();
}

// This is the default callback procedure for the SHBrowseForFolder function.
// It will set the current selection to the directory specified in the edit control
int CALLBACK FECCallBackProc(HWND hWnd, UINT Msg, LPARAM unused, LPARAM lpData)
{
    if (Msg == BFFM_INITIALIZED)
        ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);
    return 0;
}

BOOL CFileEditCtrl::FECBrowseForFolder()
{
	BOOL Proc = TRUE;	// assume user of this class has set a callback procedure
	CString Path;
	LPARAM oldLP = m_pbi->lParam;
	if (!m_pbi->lpfn)	// user has not set a callback procedure
	{					// flag it, and use the default procedure
		Proc = FALSE;
		m_edit->GetWindowText(Path);	// get the path in the edit control
		if (!PathFileExists(Path))		// make sure it exists
			Path = "";
		m_pbi->lpfn = FECCallBackProc;	// set the callback procedure
		m_pbi->lParam = (LPARAM)(LPCTSTR)Path; // set lParam to point to path
	}
	ITEMIDLIST *idl = SHBrowseForFolder (m_pbi);
	if (!Proc)			// reset m_pbi to clear the default callback proc.
	{
		m_pbi->lpfn = NULL;
		m_pbi->lParam = oldLP;
	}
	if (idl)
	{
		SHGetPathFromIDList (idl, m_buffer);	// get path string from ITEMIDLIST
		m_edit->SetWindowText(m_buffer);		// update edit control
		LPMALLOC lpm;
		if (SHGetMalloc (&lpm) == NOERROR)
			lpm->Free(idl);    // free memory returned by SHBrowseForFolder
    GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());  // by VK
		return TRUE;
	}
	return FALSE;
}

BOOL CFileEditCtrl::FECOpenFile()
{
	// Start the CFileDialog
	if (m_pcfd->DoModal() == IDOK)
	{
		CString Path = "";
		POSITION pos = m_pcfd->GetStartPosition();
		Path += m_pcfd->GetNextPathName(pos);
		while (pos)
			Path += "; " + m_pcfd->GetNextPathName(pos);
		m_edit->SetWindowText (Path);
    GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());  // by VK
	}
	return TRUE;
}

void CFileEditCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	// make sure the edit control has the input focus
	CWnd::OnSetFocus(pOldWnd);
	
	m_edit->SetFocus();
}

void CFileEditCtrl::OnEnable(BOOL bEnable) 
{
	CWnd::OnEnable(bEnable);
	
	// enable or disable the edit and button controls
	m_button->EnableWindow(bEnable);
	m_edit->EnableWindow(bEnable);

}

void CFileEditCtrl::SetFont(CFont *pFont, BOOL bRedraw)
{
	m_edit->SetFont(pFont,bRedraw);
}

void CFileEditCtrl::SetWindowText(LPCTSTR text)
{
 	m_edit->SetWindowText(text);
}

void CFileEditCtrl::GetWindowText(CString &text) const
{
	m_edit->GetWindowText(text);
}

int CFileEditCtrl::GetWindowText(LPTSTR buffer, int max) const
{
	return m_edit->GetWindowText(buffer, max);
}

int CFileEditCtrl::GetWindowTextLength() const
{
	return m_edit->GetWindowTextLength();
}

BROWSEINFO* CFileEditCtrl::GetBrowseInfo() const
{
	// returns a pointer to the BROWSEINFO structure
	// so the user of this control can set their own
	// parameters for SHBrowseForFolder
	return m_pbi;
}

CEdit* CFileEditCtrl::GetEditControl() const
{
	// returns a pointer to the edit control so the
	// user can modify it (background colour, transparency, ect.)
	return m_edit;
}

OPENFILENAME* CFileEditCtrl::GetOpenFileName() const
{
	// returns a pointer to the OPENFILENAME structure so the
	// user can modify the Open File dialog
	if (m_pcfd)
		return (&m_pcfd->m_ofn);
	return NULL;
}


POSITION CFileEditCtrl::GetStartPosition() const
{
	if (m_pcfd)
		return m_pcfd->GetStartPosition();
	return NULL;
}

CString CFileEditCtrl::GetNextPathName(POSITION &pos) const
{
	if (m_pcfd)
		return m_pcfd->GetNextPathName(pos);
	return "";
}
