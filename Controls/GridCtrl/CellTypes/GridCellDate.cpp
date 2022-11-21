///////////////////////////////////////////////////////////////////////////
//
// GridCellDate.cpp: implementation of the CGridCellDate class.
//
// Provides the implementation for a datetime picker cell type of the
// grid control.
//
// Written by Podsypalnikov Eugen 15 Mar 2001
// Modified:
//    31 May 2001  Fixed m_cTime bug (Chris Maunder)
//
// For use with CGridCtrl v2.22+
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../GridCtrl.h"
#include "../GridCell.h"
#include "GridCellDate.h"
#include "../../EraControls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CGridCellDate

IMPLEMENT_DYNCREATE(CGridCellDate, CGridCell)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCellDate::CGridCellDate() : CGridCell()
{
	m_dwStyle = 0;
	m_odt     = COleDateTime::GetCurrentTime();
}

CGridCellDate::CGridCellDate(DWORD dwStyle) : CGridCell()
{
	Init(dwStyle);
}

CGridCellDate::~CGridCellDate()
{
}

BOOL CGridCellDate::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, 
							 UINT nID, UINT nChar)
{
	m_bEditing = TRUE;

	// CInPlaceDate auto-deletes itself
	m_pEditWnd = new CEraDateEdit();
  m_pEditWnd->Create(_T("EDIT"), _T(""), WS_VISIBLE|WS_BORDER|WS_CHILD, rect, GetGrid(), nID);
/************************************** : by VK at 06.06.2004 10:26:51 **\
  GetGrid(), rect,
		m_dwStyle, nID, nRow, nCol, 
		GetTextClr(), GetBackClr(), GetTime(), nChar);
\************************************** : by VK at 06.06.2004 10:26:54 **/
	return TRUE;
}

CWnd* CGridCellDate::GetEditWnd() const
{
	return m_pEditWnd;
}

void CGridCellDate::EndEdit() {

//	if (m_pEditWnd) ((CEraDateEdit*)m_pEditWnd)->EndEdit();
  if ( m_pEditWnd )
    delete m_pEditWnd;
}

void CGridCellDate::Init(DWORD dwStyle) {
	m_odt   = COleDateTime::GetCurrentTime();
	m_dwStyle = dwStyle;

/************************************** : by VK at 06.06.2004 10:27:55 **\
	if (DTS_TIMEFORMAT == m_dwStyle) 
	{
		SetText(m_cTime.Format(_T("%H:%M:%S")));
	}
	else if (DTS_SHORTDATEFORMAT == m_dwStyle) 
	{
		SetText(m_cTime.Format(_T("%d:%m:%Y")));
	}
	SetFormat(DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);
\************************************** : by VK at 06.06.2004 10:27:58 **/
}


