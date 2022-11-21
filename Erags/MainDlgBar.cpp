// MainDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
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

void CMainDlgBar::SetOfficeButtons() {
  if ( MS_OFFICE==theApp.GetOffice() ) {
    m_btnWord.SetBitmaps(IDB_BTN_WORD, RGB(255,0,255), IDB_BTN_WORD_OUT, RGB(255,0,255));
  }
  else {
    m_btnWord.SetBitmaps(IDB_BTN_SWRITER, RGB(255,0,255), IDB_BTN_SWRITER_OUT, RGB(255,0,255));
  }
}
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
  m_btnFileNew.SetTooltipText(_T("Будувати Новий Файл БД ЕРАГС (Ctrl + N(укр. Т))"));

  m_btnFileOpen.SubclassDlgItem(ID_FILE_OPEN, this);
  m_btnFileOpen.SetBitmaps(IDB_FILE_OPEN, RGB(255,0,255), IDB_FILE_OPEN_OUT, RGB(255,0,255));
  m_btnFileOpen.SetTooltipText(_T("Відкрити Файл БД ЕРАГС (Ctrl + O(укр. Щ))"));

  m_btnFileRecent.SubclassDlgItem(ID_FILE_RECENT, this);
  m_btnFileRecent.SetBitmaps(IDB_BTN_RECENT, RGB(255,0,255));
  m_btnFileRecent.SetTooltipText(_T("Відкрити файл БД ЕРАГС зі списку файлів, які недавно вікривалися"));

  m_btnBirth.SubclassDlgItem(ID_BIRTH, this);
  m_btnBirth.SetBitmaps(IDB_BTN_BIRTH, RGB(255,0,255), IDB_BTN_BIRTH_OUT, RGB(255,0,255));
  m_btnBirth.SetTooltipText(_T("Реєстрація Народження (Ctrl + 1)"));

  m_btnMarriage.SubclassDlgItem(ID_MARRIAGE, this);
  m_btnMarriage.SetBitmaps(IDB_BTN_MARRIAGE, RGB(255,0,255), IDB_BTN_MARRIAGE_OUT, RGB(255,0,255));
  m_btnMarriage.SetTooltipText(_T("Реєстрація Шлюбу (Ctrl + 2)"));

  m_btnDivorce.SubclassDlgItem(ID_DIVORCE, this);
  m_btnDivorce.SetBitmaps(IDB_BTN_DIVORCE, RGB(255,0,255), IDB_BTN_DIVORCE_OUT, RGB(255,0,255));
  m_btnDivorce.SetTooltipText(_T("Реєстрація Розірвання Шлюбу (Ctrl + 3)"));

  m_btnChange.SubclassDlgItem(ID_CHANGE, this);
  m_btnChange.SetBitmaps(IDB_BTN_CHANGE, RGB(255,0,255), IDB_BTN_CHANGE_OUT, RGB(255,0,255));
  m_btnChange.SetTooltipText(_T("Реєстрація Зміни Імені (Ctrl + 4)"));

  m_btnDeath.SubclassDlgItem(ID_DEATH, this);
  m_btnDeath.SetBitmaps(IDB_BTN_DEATH, RGB(255,0,255), IDB_BTN_DEATH_OUT, RGB(255,0,255));
  m_btnDeath.SetTooltipText(_T("Реєстрація Смерті (Ctrl + 5)"));

  m_btnExtNotes.SubclassDlgItem(ID_EXTNOTES, this);
  m_btnExtNotes.SetBitmaps(IDB_BTN_EXTNOTES, RGB(255,0,255), IDB_BTN_EXTNOTES_OUT, RGB(255,0,255));
  m_btnExtNotes.SetTooltipText(_T("Зміни та доповнення до АЗ про Народження"));

/*
  m_btnLaws.SubclassDlgItem(ID_LAWS, this);
  m_btnLaws.SetBitmaps(IDB_BTN_LAWS, RGB(255,0,255), IDB_BTN_LAWS_OUT, RGB(255,0,255));
  m_btnLaws.SetTooltipText(_T("Юридичний Довідник"));
*/
  m_btnGeography.SubclassDlgItem(ID_GEOGRAPHY, this);
  m_btnGeography.SetBitmaps(IDB_BTN_GEOGRAPHY, RGB(255,0,255), IDB_BTN_GEOGRAPHY_OUT, RGB(255,0,255));
  m_btnGeography.SetTooltipText(_T("Географчні Назви (Ctrl+U (укр. Г))"));

  m_btnRedCross.SubclassDlgItem(ID_MEDICS, this);
  m_btnRedCross.SetBitmaps(IDB_BTN_RED_CROSS, RGB(255,0,255), IDB_BTN_RED_CROSS_OUT, RGB(255,0,255));
  m_btnRedCross.SetTooltipText(_T("Пологові Будинки, Лікарні, Морги"));

  m_btnCityHall.SubclassDlgItem(ID_REGISTRARS, this);
  m_btnCityHall.SetBitmaps(IDB_BTN_CITY_HALL, RGB(255,0,255), IDB_BTN_CITY_HALL_OUT, RGB(255,0,255));
  m_btnCityHall.SetTooltipText(_T("Органи Реєстрації (Ctrl+H (укр. Р))"));

  m_btnUkraine.SubclassDlgItem(ID_POLICE, this);
  m_btnUkraine.SetBitmaps(IDB_BTN_UKRAINE, RGB(255,0,255), IDB_BTN_UKRAINE_OUT, RGB(255,0,255));
  m_btnUkraine.SetTooltipText(_T("Органи Внутрішніх Справ"));

  m_btnUAH.SubclassDlgItem(ID_BANK, this);
  m_btnUAH.SetBitmaps(IDB_BTN_UAH, RGB(255,0,255), IDB_BTN_UAH_OUT, RGB(255,0,255));
  m_btnUAH.SetTooltipText(_T("Фінансові Установи"));

  m_btnFirst.SubclassDlgItem(ID_RECORD_FIRST, this);
  m_btnFirst.SetBitmaps(IDB_BTN_FIRST, RGB(255,0,255), IDB_BTN_FIRST_OUT, RGB(255,0,255));
  m_btnFirst.SetTooltipText(_T("Перший Запис (Alt + Home)"));

  m_btnPrev.SubclassDlgItem(ID_RECORD_PREV, this);
  m_btnPrev.SetBitmaps(IDB_BTN_PREV, RGB(255,0,255), IDB_BTN_PREV_OUT, RGB(255,0,255));
  m_btnPrev.SetTooltipText(_T("Попередній Запис (Alt + <-)"));

  m_btnNext.SubclassDlgItem(ID_RECORD_NEXT, this);
  m_btnNext.SetBitmaps(IDB_BTN_NEXT, RGB(255,0,255), IDB_BTN_NEXT_OUT, RGB(255,0,255));
  m_btnNext.SetTooltipText(_T("Наступний Запис (Alt + ->)"));

  m_btnLast.SubclassDlgItem(ID_RECORD_LAST, this);
  m_btnLast.SetBitmaps(IDB_BTN_LAST, RGB(255,0,255), IDB_BTN_LAST_OUT, RGB(255,0,255));
  m_btnLast.SetTooltipText(_T("Останній Запис (Alt + End)"));

  m_btnNew.SubclassDlgItem(ID_RECORD_NEW, this);
  m_btnNew.SetBitmaps(IDB_BTN_RECORD_NEW, RGB(255,0,255), IDB_BTN_RECORD_NEW_OUT, RGB(255,0,255));
  m_btnNew.SetTooltipText(_T("Створити Новий Запис (Alt + Insert)"));

  m_btnDelete.SubclassDlgItem(ID_RECORD_DELETE, this);
  m_btnDelete.SetBitmaps(IDB_BTN_RECORD_DELETE, RGB(255,0,255), IDB_BTN_RECORD_DELETE_OUT, RGB(255,0,255));
  m_btnDelete.SetTooltipText(_T("Видалити Поточний Запис (Alt + Delete)"));

  m_btnFindIn.SubclassDlgItem(ID_FINDIN, this);
  m_btnFindIn.SetBitmaps(IDB_BTN_FINDIN, RGB(255,0,255));
  m_btnFindIn.SetTooltipText(_T("Пошук АЗ за номером або прізвищем"));

  m_btnFindOut.SubclassDlgItem(ID_FIND, this);
  m_btnFindOut.SetBitmaps(IDB_BTN_FINDOUT, RGB(255,0,255), IDB_BTN_FINDOUT_OUT, RGB(255,0,255));
  m_btnFindOut.SetTooltipText(_T("Пошук по всій Базі Даних"));


  m_btnPrint.SubclassDlgItem(ID_PRINT, this);
  m_btnPrint.SetBitmaps(IDB_BTN_PRINT, RGB(255,0,255), IDB_BTN_PRINT_OUT, RGB(255,0,255));
  m_btnPrint.SetTooltipText(_T("Перегляд/Друк (Ctrl + P(укр. З))"));

  if ( MS_OFFICE==theApp.GetOffice() ) {
    m_btnWord.SubclassDlgItem(ID_WORD, this);
  }
  else {
    m_btnWord.SubclassDlgItem(ID_WORD, this);
  }
  SetOfficeButtons();
  m_btnWord.SetTooltipText(_T("Експорт документа (Ctrl + E(укр. У))"));

  
  m_btnTemplates.SubclassDlgItem(ID_TEMPLATES, this);
  m_btnTemplates.SetBitmaps(IDB_BTN_TEMPLATES, RGB(255,0,255), IDB_BTN_TEMPLATES_OUT, RGB(255,0,255));
  m_btnTemplates.SetTooltipText(_T("Операції із Шаблонами"));

  m_btnHelp.SubclassDlgItem(ID_WHAT_IS_IT, this);
  m_btnHelp.SetBitmaps(IDB_BTN_HELP, RGB(255,0,255), IDB_BTN_HELP_OUT, RGB(255,0,255));
  m_btnHelp.SetTooltipText(_T("Помічник"));

  return TRUE;
}
