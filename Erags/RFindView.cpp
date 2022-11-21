// RFindView.cpp : implementation of the CRFindView class
//

#include "stdafx.h"
#include "Erags.h"
#include <Shlwapi.h>
#include <locale.h>

#include "MainFrm.h"
#include "EraForm.h"

#include "RFindDoc.h"
#include "RFindView.h"
#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Controls\MyFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FW_COLS 5
#define NUM_BITMAPS  5
#define	LARGE_BITMAP_WIDTH	32
#define	LARGE_BITMAP_HEIGHT	32
#define	SMALL_BITMAP_WIDTH	16
#define	SMALL_BITMAP_HEIGHT	16

#define FLC_TYPE      0
#define FLC_NUMBER    1
#define FLC_DATE      2
#define FLC_FULLNAME  3

/////////////////////////////////////////////////////////////////////////////
// CRFindView

IMPLEMENT_DYNCREATE(CRFindView, CListView)

BEGIN_MESSAGE_MAP(CRFindView, CListView)
  //{{AFX_MSG_MAP(CRFindView)
  ON_WM_CREATE()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRFindView construction/destruction
int CompareDateString(const CString& sDateA, const CString& sDateB) {
  int iY[2], iM[2], iD[2];
  // dd.mm.yyyy
  if ( sDateA.GetLength() < 10 || sDateB.GetLength() < 10 ) {
    return (sDateA.GetLength()-sDateB.GetLength());
  }
  iY[0] = atoi(sDateA.Right(4));
  iY[1] = atoi(sDateB.Right(4));
  iM[0] = atoi(sDateA.Mid(3, 2));
  iM[1] = atoi(sDateB.Mid(3, 2));
  iD[0] = atoi(sDateA.Left(2));
  iD[1] = atoi(sDateB.Left(2));

  CString sDA, sDB;
  sDA.Format(_T("%04d%02d%02d"), iY[0], iM[0], iD[0]);
  sDB.Format(_T("%04d%02d%02d"), iY[1], iM[1], iD[1]);

  return sDA.Compare(sDB);
}

int CALLBACK RFindSortResults(LPARAM lParam1,
                              LPARAM lParam2,
                              LPARAM lParamSort) {
  CRFoundOb* pFound1 = (CRFoundOb*)lParam1;
  CRFoundOb* pFound2 = (CRFoundOb*)lParam2;
  switch(lParamSort) {
    case FLC_NUMBER:
      return atoi(pFound1->m_sNumber) - atoi(pFound2->m_sNumber);
    case FLC_DATE:
      return CompareDateString(pFound1->m_sDateReg,pFound2->m_sDateReg);
    case FLC_FULLNAME:
      return CyrCompare(pFound1->m_sFullName, pFound2->m_sFullName);
  }
  return 0;
}


CRFindView::CRFindView() {
  m_pPrinterFont = NULL;
}

CRFindView::~CRFindView() {
}

void CRFindView::Clear() {
  GetListCtrl().DeleteAllItems();
}
void CRFindView::AddToList(int imlIndex,
                           long lID, const CString& sNumber, const CString& sDateReg,
                           const CString& sFullName, const CString& sPath) {
  CListCtrl& list = GetListCtrl();
  int nItem = list.InsertItem(list.GetItemCount(), _T(""), imlIndex);
  int nActType = 0;
  LPTSTR szAZ = _T("");
  switch(imlIndex) {
    case IML_BIRTH_W:   case IML_BIRTH_M:
    case IML_FATHER:    case IML_MOTHER:
      nActType = 1;
      szAZ = _T("Н  ");
      break;
    case IML_MARRIAGE:
      nActType = 2;
      szAZ = _T("О  ");
      break;
    case IML_DIVORCE_W: case IML_DIVORCE_M:
      nActType = 3;
      szAZ = _T("РШ ");
      break;
    case IML_CHANGE_W: case IML_CHANGE_M:
      nActType = 4;
      szAZ = _T("П  ");
      break;
    case IML_DEATH_W: case IML_DEATH_M:
      nActType = 5;
      szAZ = _T("С");
      break;
    case IML_FATHER_W:  case IML_FATHER_M:
      nActType = 6;
      szAZ = _T("ВБ ");
      break;
  }
//  LPTSTR szFileName = PathFindFileName(sPath);
  list.SetItemText(nItem, 0, szAZ);
  list.SetItemText(nItem, 1, sNumber);
  list.SetItemText(nItem, 2, sDateReg);
  list.SetItemText(nItem, 3, sFullName);
  list.SetItemText(nItem, 4, sPath);

  list.SetItemData(nItem, (DWORD)(new CRFoundOb(imlIndex, lID, nActType, szAZ, sNumber, sDateReg, sFullName)) );
}

BOOL CRFindView::PreCreateWindow(CREATESTRUCT& cs) {
  cs.style = WS_CHILDWINDOW|WS_VISIBLE|LVS_REPORT;
  return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRFindView drawing
void CRFindView::OnDraw(CDC* pDC) {
/*
  CRFindDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  CListCtrl& refCtrl = GetListCtrl();
  refCtrl.InsertItem(0, "Item!");
*/
  // TODO: add draw code for native data here
}

int CRFindView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CListView::OnCreate(lpCreateStruct) == -1)
    return -1;
//  SetDlgCtrlID(ID_FOUND_LIST);
  return 0;
}
void CRFindView::OnInitialUpdate() {
  CListView::OnInitialUpdate();
  CListCtrl& list = GetListCtrl();

  LV_COLUMN lvC;          // list view column structure
  char *szColumns[FW_COLS] = {_T("АЗ") , _T(" № "), _T("Дата р-ції"), _T("Прізвище - ім'я - по батькові"), _T("Файл")};
  int   iaColumns[FW_COLS] = {32, 32, 72, 172, 200};


  CString strTitle;
  strTitle.Format(_T("Маршрут пошуку: %s"), GetFilePath(theApp.GetHelperMDB()) );

  if ( NULL==m_ImageList.m_hImageList ) {
    m_ImageList.Create(IDB_IMLIST, 16, 11, RGB(0xFF,0,0xFF) );
	  // Associate the image lists with the list view control.
  	list.SetImageList(&m_ImageList, LVSIL_SMALL);

  	// Now initialize the columns you will need.
	  // Initialize the LV_COLUMN structure.
  	// The mask specifies that the fmt, width, pszText, and subitem members
	  // of the structure are valid.
  	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	  lvC.fmt = LVCFMT_LEFT;  // left-align column

  	// Add the columns.
	  for(int i(0); i < FW_COLS; i++){
  		lvC.iSubItem = i;
	  	lvC.pszText = szColumns[i];
      lvC.cx = iaColumns[i];
  		if (list.InsertColumn(i, &lvC) == -1)
	  		return;
  	}
    list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
  }

}

/////////////////////////////////////////////////////////////////////////////
// CRFindView printing

void CRFindView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
  pDC->SetMapMode(MM_TWIPS);
  int nHorzSize =pDC->GetDeviceCaps(LOGPIXELSX);
  int nVertSize =pDC->GetDeviceCaps(LOGPIXELSY);
  
  CListView::OnPrepareDC(pDC, pInfo);
}

void CRFindView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {
  CPrintDialog dlg(FALSE);
  if (!dlg.GetDefaults()) {
    AfxMessageBox(_T("Прінтер не встановлено!"));
    return;
  }    

  CFont* pFont = GetListCtrl().GetFont();
  if (NULL==pFont) {
    return;
  }

  LOGFONT lf;
  pFont->GetLogFont(&lf);
  
  m_pPrinterFont = new CFont();
  m_pPrinterFont->CreateFont(lf.lfHeight *20 ,0,0,0,400,FALSE,FALSE,0,
                  RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,
                  CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, lf.lfFaceName
                  );

  CFont* pOldFont = (CFont*) pDC->SelectObject(m_pPrinterFont);
  pDC->SetMapMode(MM_TWIPS);

  m_nPageHeight = pDC->GetDeviceCaps(VERTRES) ; // 3075
  m_nPageWidth  = pDC->GetDeviceCaps(HORZRES); //

  CSize sz(m_nPageWidth,m_nPageHeight);
  pDC->DPtoLP(&sz);

  m_nPageHeight = sz.cy - m_margins.top -m_margins.bottom;
  m_nPageWidth  = sz.cx;

  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm); // in logical units

  m_nRowWidth = m_nPageWidth - m_margins.left -m_margins.right;
  m_nRowHeight = (tm.tmHeight + tm.tmExternalLeading) *9/8;

  pDC->SelectObject(pOldFont);

  UINT pos=0;
  m_total_bands =0;
  m_band[0] = m_total_bands;
  for (int i=0; i<m_nColumns; i++) {
    pos+= (m_column_size[i].cy - m_column_size[i].cx);
    if (pos>m_nRowWidth *(m_total_bands+1)) {
      m_total_bands++;
    }
    m_band[i] = m_total_bands;
  }
  m_total_bands++;

  m_nLinesPerPage = m_nPageHeight / m_nRowHeight -3; // header, column header, footer
  int nLinesCount = GetListCtrl().GetItemCount();
  m_nPagesPerBand = (nLinesCount + m_nLinesPerPage - 1) / m_nLinesPerPage;
  int nMaxPage = m_total_bands * m_nPagesPerBand;
  pInfo->SetMaxPage(nMaxPage);
  pInfo->m_nCurPage = 1;  // start previewing at page# 1

}

void CRFindView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
  if (m_pPrinterFont) {
    delete m_pPrinterFont;
  }
}

void CRFindView::PrintPageHeader(CDC* pDC) {
  if (m_nCurrentBand==m_total_bands-1) {
    CString szWindowName, str;
    GetParentFrame()->GetWindowText(szWindowName);

    str = szWindowName;
    CPoint point(0,-m_margins.top);
    CSize size = pDC->GetTextExtent(str);
    point.x = m_nPageWidth - size.cx - m_margins.right;
    pDC->TextOut(point.x,point.y,str);
    pDC->TextOut(point.x+2,point.y+2,str);
  }
  LV_COLUMN lvc;
  TCHAR ColumnText[64];

  lvc.mask = LVCF_TEXT;
  lvc.pszText = ColumnText;
  lvc.cchTextMax =64;

  // find the first column that belongs to the current band
  int nFirstColumn = -1;
  for (int i=0; i<m_nColumns; i++) {
    if (m_band[i]==m_nCurrentBand) {
      nFirstColumn =i;
      break;
    }
  }
  int LeftMargin = 0;
  if (nFirstColumn==-1) {
    return;
  }
  LeftMargin = m_column_size[nFirstColumn].cx;
  CListCtrl& list = GetListCtrl();

  CBrush bBrush;
  COLORREF back_color = RGB(0,255,0); //GetSysColor(COLOR_BTNFACE);
  VERIFY(bBrush.CreateSolidBrush(back_color));    

  CRect rectHeader(m_margins.left -3,
                   -m_margins.top-m_nRowHeight +3,
                   m_nRowWidth + m_margins.right,
                   -m_margins.top-2*m_nRowHeight -10);
  // pDC->Rectangle(&rectHeader);
  pDC->MoveTo(rectHeader.left ,rectHeader.bottom);
  pDC->LineTo(rectHeader.right,rectHeader.bottom);

  // CBrush* pOldBrush = pDC->SelectObject(&bBrush);

  for (int index=0; index<m_nColumns; index++) {
    int nColumnNo = m_column_order_array[index];
    if (list.GetColumn(nColumnNo,&lvc)) {
      if (m_band[index]==m_nCurrentBand) {
        CString szText(ColumnText);
        CRect rcItem;
        rcItem.top     = -m_nRowHeight - m_margins.top;
        rcItem.bottom  = -2*m_nRowHeight - m_margins.top;
        rcItem.left = m_column_size[index].cx - LeftMargin + m_margins.left;
        rcItem.right= m_column_size[index].cy - LeftMargin + m_margins.left;

        pDC->DrawText(szText,-1,rcItem,m_justify[index]| DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP /*| DT_RIGHT */);
      }
    }
  }

  // pDC->SelectObject(pOldBrush);

}

void CRFindView::PrintPageFooter(CPoint point, CDC* pDC, CPrintInfo* pInfo) {
  CString str;
  str.Format(_T("Page %d-%d"), m_nPage,m_nCurrentBand+1);
  CSize size = pDC->GetTextExtent(str);
  point.x = m_nPageWidth - size.cx - m_margins.right;
  pDC->TextOut(point.x, point.y, str);
}

#define OFFSET_OTHER  6

void CRFindView::OnPrintLine(CDC* pDC, int nItem, int cy) {
  CListCtrl& list = GetListCtrl();
  pDC->SetMapMode(MM_TWIPS);

  LV_COLUMN lvc;
  lvc.mask=LVCF_FMT | LVCF_WIDTH;

  // find the first column that belongs to the current band
  int nFirstColumn = -1;
  for (int i=0; i<m_nColumns; i++) {
    if (m_band[i]==m_nCurrentBand) {
      nFirstColumn =i;
      break;
    }
  }
  int LeftMargin = 0;
  if (nFirstColumn==-1) {
    return;
  }
  LeftMargin = m_column_size[nFirstColumn].cx;

  for (int index=0; index<m_nColumns; index++) {
    int nColumnNo = m_column_order_array[index];
    if (list.GetColumn(nColumnNo,&lvc)) {
      if (m_band[index]!=m_nCurrentBand) {
        continue;
      }
      CString szText = list.GetItemText(nItem,nColumnNo);

      CRect rcItem;
      rcItem.top = cy;
      rcItem.left  = m_column_size[index].cx - LeftMargin + m_margins.left;
      rcItem.right = m_column_size[index].cy - LeftMargin + m_margins.left;

      pDC->DrawText(szText,-1,rcItem,m_justify[index] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP /*| DT_RIGHT */);
    }
  }
}

void CRFindView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
  CFont* pOldFont = (CFont*) pDC->SelectObject(m_pPrinterFont);

  m_nPage        = (pInfo->m_nCurPage-1) % m_nPagesPerBand +1;
  m_nCurrentBand = (pInfo->m_nCurPage-1) / m_nPagesPerBand;
  
  int nStart;
  int nEnd;
  CPoint point(0,-2* m_nRowHeight - m_margins.top);
 
  nStart= (m_nPage-1) * m_nLinesPerPage;
  nEnd  = nStart + m_nLinesPerPage;

  PrintPageHeader(pDC);

  CListCtrl& list = GetListCtrl();
  for (int i=nStart; i<nEnd; i++) {
    if (i>=list.GetItemCount()) {
      break;
    }
    point.y -= m_nRowHeight;
    OnPrintLine(pDC,i,point.y);
  } 

  point.y -=m_nRowHeight;
  PrintPageFooter(point,pDC,pInfo);
  pDC->SelectObject(pOldFont);
}

BOOL CRFindView::OnPreparePrinting(CPrintInfo* pInfo) {
  TCHAR ColumnText[64];
  LV_COLUMN lvc;
  lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
  lvc.pszText = ColumnText;
  lvc.cchTextMax =64;

  CListCtrl& list = GetListCtrl();

  m_margins = CRect(1440,1440/2,1440/2,1440/2); // 1 TWIP = 1/1440 of an inch

  CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();
  m_nColumns = pHeaderCtrl->GetItemCount();
  list.GetColumnOrderArray(m_column_order_array,m_nColumns);

  if (list.GetItemCount()>0)  {
    for (int index=0; index<m_nColumns; index++) {
      int nColumnNo = m_column_order_array[index];
      if (list.GetColumn(nColumnNo,&lvc)) {
        CString szText(ColumnText);
        CRect rcItem;
        list.GetSubItemRect(0,nColumnNo,LVIR_LABEL,rcItem);
        m_column_size[index] = CSize(rcItem.left*20,rcItem.right*20); // 20 because of TWIPS
        m_justify[index]=DT_LEFT;
        switch(lvc.fmt & LVCFMT_JUSTIFYMASK) {
          case LVCFMT_RIGHT:
            m_justify[index]=DT_RIGHT;
            break;
          case LVCFMT_LEFT :
            m_justify[index]=DT_LEFT;
            break;  
          case LVCFMT_CENTER:
            m_justify[index]=DT_CENTER;
            break;
          default:
            break;
        }
      }
    }
  }else{
    int pos =0;
    for (int index=0; index<m_nColumns; index++) {
      int nColumnNo = m_column_order_array[index];
      if (list.GetColumn(nColumnNo,&lvc)) {
        CString szText(ColumnText);
        int width = list.GetColumnWidth(nColumnNo);
        m_column_size[index] = CSize(pos*20,width*20); // 20 because of TWIPS
        pos+=width;
        m_justify[index]=DT_LEFT;
      }
    }
  }
  int nMaxPage = m_total_bands * m_nPagesPerBand;
  pInfo->SetMaxPage(nMaxPage);
  return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CRFindView diagnostics

#ifdef _DEBUG
void CRFindView::AssertValid() const {
  CListView::AssertValid();
}
void CRFindView::Dump(CDumpContext& dc) const {
  CListView::Dump(dc);
}

CRFindDoc* CRFindView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRFindDoc)));
  return (CRFindDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRFindView message handlers
void CRFindView::WriteCSVHeader(CFile* pFile) {
  CListCtrl& list = GetListCtrl();

  CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();
  int nColumns = pHeaderCtrl->GetItemCount();
	list.GetColumnOrderArray(m_column_order_array,nColumns);

	TCHAR ColumnText[64];
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvc.pszText = ColumnText;
	lvc.cchTextMax =64;

  CString header;
  for (int index=0; index<nColumns; index++) {
    int nColumnNo = m_column_order_array[index];
	  if (list.GetColumn(nColumnNo,&lvc)) {
      CString szText(ColumnText);
      header+= szText;
      header+= _T(",");
    }
  }
  header+= _T("\r\n");
 
  pFile->Write((LPCTSTR)header,header.GetLength()); 
}

void CRFindView::WriteCSVBody(CFile* pFile) {
  CListCtrl& list = GetListCtrl();

  CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();
  int nColumns = pHeaderCtrl->GetItemCount();
	list.GetColumnOrderArray(m_column_order_array,nColumns);

  for (int row=0; row<list.GetItemCount(); row++) {
    CString szRow;
    for (int column=0; column<nColumns; column++) {
      int nColumnNo = m_column_order_array[column];
      CString szText = list.GetItemText(row,nColumnNo);
      szRow+= szText;
      szRow+= _T(",");
    }
    szRow+= _T("\r\n");
    pFile->Write((LPCTSTR)szRow,szRow.GetLength()); 
  }
}

void CRFindView::ExportToCSV() {
  CMyFileDialog sfd(FALSE, "csv", "*.csv");
  sfd.m_fEnableTemplate = FALSE;
  sfd.SetTitle(0, _T("Записати результат пушуку для EXEL"));
  if (sfd.DoModal()!=IDOK) {
    return;
  }
  CFile file;
  CString szPathName = sfd.GetPathName();
  VERIFY(file.Open(szPathName, CFile::modeCreate | CFile::modeWrite));
  WriteCSVHeader(&file);
  WriteCSVBody(&file);
  file.Close();
} 

void CRFindView::OnFileSave() {
	ExportToCSV();
}
void CRFindView::OnFilePrintPreview() {
  CListView::OnFilePrintPreview();
}

void CRFindView::OnFilePrint() {
  CListView::OnFilePrint(); 
}

void CRFindView::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) {
  // setlocale(LC_ALL, _T("ukrainian") );
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  switch(pNMListView->iSubItem) {
    case FLC_NUMBER:
    case FLC_DATE:
    case FLC_FULLNAME:
      GetListCtrl().SortItems(RFindSortResults, (DWORD)pNMListView->iSubItem);
  }
	*pResult = 0;
}

void CRFindView::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

  CRFoundOb* pFoundOb = (CRFoundOb*)GetListCtrl().GetItemData(pNMListView->iItem);
  if ( pFoundOb )
	  delete pFoundOb;
	*pResult = 0;
}

void CRFindView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) {
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	if ( pLVKeyDown->wVKey==VK_DELETE ) {
    int nItem;
    do {
      nItem = GetListCtrl().GetNextItem(-1, LVNI_SELECTED);
      if ( -1 != nItem )
        GetListCtrl().DeleteItem(nItem);
    } while( -1 != nItem );
  }
	*pResult = 0;
}

