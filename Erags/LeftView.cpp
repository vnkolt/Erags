// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Erags.h"

#include "RFindDoc.h"
#include "LeftView.h"

#include "..\Common\CyrString.h"
#include "..\Controls\GridCtrl\GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

BEGIN_MESSAGE_MAP(CLeftView, CView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView() {
  m_pGridCtrl = NULL;
}

CLeftView::~CLeftView() {
	if (m_pGridCtrl)
		delete m_pGridCtrl;
}

void CLeftView::CreateFindArray() {
  m_Surnames.RemoveAll();
  m_Names.RemoveAll();
  m_Patronymics.RemoveAll();
  if ( m_pGridCtrl->GetRowCount() > 1 ) {
    for( int i(1); i < m_pGridCtrl->GetRowCount(); i++ ) {
      CString s1 = Trim(m_pGridCtrl->GetItemText(i, 1)); // Surname
      CString s2 = Trim(m_pGridCtrl->GetItemText(i, 2)); // Name
      CString s3 = Trim(m_pGridCtrl->GetItemText(i, 3)); // Patronymic
      if ( FALSE==s1.IsEmpty() || FALSE==s2.IsEmpty() || FALSE==s3.IsEmpty()) {
        s1 = UpperString(s1);
        s2 = UpperString(s2);
        s3 = UpperString(s3);
        m_Surnames.Add(s1);
        m_Names.Add(s2);
        m_Patronymics.Add(s3);
      }
    }
  }
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
  cs.style = WS_VISIBLE | WS_CHILD;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
/*
	CRFindDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
*/
	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing
BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo) {
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	if (m_pGridCtrl == NULL) 	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->Create(rect, this, ID_SEARCH_LIST);

		// fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
    m_pGridCtrl->SetColumnResize(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);
    m_pGridCtrl->SetTrackFocusCell(FALSE);

		try {
			m_pGridCtrl->SetRowCount(100);
			m_pGridCtrl->SetColumnCount(4);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)	{
			e->ReportError();
			e->Delete();
			return;
		}

    m_pGridCtrl->SetRowHeight(0,17);
		m_pGridCtrl->SetItemText(0, 0, _T("N/N") );
    m_pGridCtrl->SetItemText(0, 1, _T("Прізвище") );    m_pGridCtrl->SetColumnWidth(1,62);
    m_pGridCtrl->SetItemText(0, 2, _T("Ім'я") );        m_pGridCtrl->SetColumnWidth(2,72);
    m_pGridCtrl->SetItemText(0, 3, _T("По батькові") ); m_pGridCtrl->SetColumnWidth(3,72);
    // fill rows/cols with text
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++) {
      m_pGridCtrl->SetItemTextFmt(row, 0, _T("%d"), row);
      m_pGridCtrl->SetRowHeight(row,17);
    }
    #ifdef _DEBUG
      m_pGridCtrl->SetItemText(1, 1, _T("Ткач") );
      m_pGridCtrl->SetItemText(2, 1, _T("Іванов") );
      m_pGridCtrl->SetItemText(3, 1, _T("Ткаченко") );
      m_pGridCtrl->SetItemText(4, 1, _T("Волков") );
    #endif
		//m_pGridCtrl->AutoSize();
    m_pGridCtrl->SetColumnWidth(0, 30);
    m_pGridCtrl->SetColumnWidth(1, 84);
    //m_pGridCtrl->SetDefCellHeight(14);
    //m_pGridCtrl->SetRowHeight(0,14);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics
#ifdef _DEBUG
void CLeftView::AssertValid() const {
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

CRFindDoc* CLeftView::GetDocument() { // non-debug version is inline

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRFindDoc)));
	return (CRFindDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

BOOL CLeftView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
	// TODO: Add your specialized code here and/or call the base class
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
void CLeftView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {
	if (m_pGridCtrl)
		m_pGridCtrl->OnBeginPrinting(pDC, pInfo);
}

void CLeftView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
	if (m_pGridCtrl)
		m_pGridCtrl->OnPrint(pDC, pInfo);
}

void CLeftView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {
	if (m_pGridCtrl)
		m_pGridCtrl->OnEndPrinting(pDC, pInfo);
}

BOOL CLeftView::OnEraseBkgnd(CDC* pDC) {
	return TRUE;
}

void CLeftView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	if (m_pGridCtrl->GetSafeHwnd()) {
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}
