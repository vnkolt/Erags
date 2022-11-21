// MainDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "MainDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlgBar dialog
CMainDlgBar::CMainDlgBar() {
	//{{AFX_DATA_INIT(CMainDlgBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CMainDlgBar::SetBkColor(BOOL bRepaint/*=TRUE*/) {
  CWnd* pWnd = GetWindow(GW_CHILD);
  while( pWnd ) {
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_IN, bRepaint);
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_BK_OUT, bRepaint);
    ((CButtonST*)pWnd)->SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, bRepaint);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}

BEGIN_MESSAGE_MAP(CMainDlgBar, CDialogBarBG)
	//{{AFX_MSG_MAP(CMainDlgBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlgBar message handlers
BOOL CMainDlgBar::Create(CWnd* pParentWnd) {
	// TODO: Add your specialized code here and/or call the base class
	if (!CDialogBarBG::Create(pParentWnd, IDTB_MAIN_TOOLBAR,  CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
		return FALSE;

  m_btnFolderTree.SubclassDlgItem(ID_FOLDER_TREE, this);
  m_btnFolderTree.SetBitmaps(IDB_BTN_FOLDER_TREE, RGB(255,0,255));
  m_btnFolderTree.SetTooltipText(_T("Показати/Сховати дерево папок БД ЕРАГС"));

  m_btnFileNew.SubclassDlgItem(ID_FILE_NEW, this);
  m_btnFileNew.SetBitmaps(IDB_BTN_FILE_NEW, RGB(255,0,255));
  m_btnFileNew.SetTooltipText(_T("Створити Новий Файл БД ЕРАГС"));

  m_btnFileOpen.SubclassDlgItem(ID_FILE_OPEN, this);
  m_btnFileOpen.SetBitmaps(IDB_FILE_OPEN, RGB(255,0,255), IDB_FILE_OPEN_OUT, RGB(255,0,255));
  m_btnFileOpen.SetTooltipText(_T("Відкрити Файл БД ЕРАГС"));

  m_btnFileRecent.SubclassDlgItem(ID_FILE_RECENT, this);
  m_btnFileRecent.SetBitmaps(IDB_BTN_RECENT, RGB(255,0,255));
  m_btnFileRecent.SetTooltipText(_T("Відкрити файл БД ЕРАГС із списку нещодавано вікриваємих"));

  m_btnFirst.SubclassDlgItem(ID_RECORD_FIRST, this);
  m_btnFirst.SetBitmaps(IDB_BTN_FIRST, RGB(255,0,255), IDB_BTN_FIRST_OUT, RGB(255,0,255));
  m_btnFirst.SetTooltipText(_T("Перший Запис"));

  m_btnPrev.SubclassDlgItem(ID_RECORD_PREV, this);
  m_btnPrev.SetBitmaps(IDB_BTN_PREV, RGB(255,0,255), IDB_BTN_PREV_OUT, RGB(255,0,255));
  m_btnPrev.SetTooltipText(_T("Попередній Запис"));

  m_btnNext.SubclassDlgItem(ID_RECORD_NEXT, this);
  m_btnNext.SetBitmaps(IDB_BTN_NEXT, RGB(255,0,255), IDB_BTN_NEXT_OUT, RGB(255,0,255));
  m_btnNext.SetTooltipText(_T("Наступний Запис"));

  m_btnLast.SubclassDlgItem(ID_RECORD_LAST, this);
  m_btnLast.SetBitmaps(IDB_BTN_LAST, RGB(255,0,255), IDB_BTN_LAST_OUT, RGB(255,0,255));
  m_btnLast.SetTooltipText(_T("Останній Запис"));

  m_btnNew.SubclassDlgItem(ID_RECORD_NEW, this);
  m_btnNew.SetBitmaps(IDB_BTN_RECORD_NEW, RGB(255,0,255), IDB_BTN_RECORD_NEW_OUT, RGB(255,0,255));
  m_btnNew.SetTooltipText(_T("Створити Новий Запис"));

  m_btnDelete.SubclassDlgItem(ID_RECORD_DELETE, this);
  m_btnDelete.SetBitmaps(IDB_BTN_RECORD_DELETE, RGB(255,0,255), IDB_BTN_RECORD_DELETE_OUT, RGB(255,0,255));
  m_btnDelete.SetTooltipText(_T("Видалити Поточний Запис або Позначені Записи"));

  m_btnHelp.SubclassDlgItem(ID_WHAT_IS_IT, this);
  m_btnHelp.SetBitmaps(IDB_BTN_HELP, RGB(255,0,255), IDB_BTN_HELP_OUT, RGB(255,0,255));
  m_btnHelp.SetTooltipText(_T("Помічник"));

  return TRUE;
}
