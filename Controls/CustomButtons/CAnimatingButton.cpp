//---------------------------------------------------------------------------
//	THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
//	THE AUTHOR DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR IMPLIED, 
//	INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
//	PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
//	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL, 
//	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, 
//
//	By John Curtis, Dec 1999.   
//---------------------------------------------------------------------------

#include "stdafx.h"

#ifndef _CANIMATINGBUTTON_
#include "CAnimatingButton.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAnimatingButton
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CAnimatingButton,CCustomTextButton)

BEGIN_MESSAGE_MAP(CAnimatingButton,CCustomTextButton)
	//{{AFX_MSG_MAP(CAnimatingButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//Override to adjust external button size
//
CRect	CAnimatingButton::GetBorderRect(CDC*,const CString&,const CRect& rClient)const
{
	return rClient;
}

//////////////////////////////////////////////////////////////////////
//
CRect	CAnimatingButton::GetTextRect(CDC* pDC,const CString& s,const CRect& rClient)const
{
	int nFrame=GetAnimationFrame();
	int nTotalFrames=GetNoOfAnimationFrames();

	//Get text size
	CSize		szText=GetTextSize(pDC,s)+CSize(1,1);	//Allow some slop

	//Move text from hidden in topleft corner to hidden in bottomright corner
	//So scan size == szText + rClient
	CSize		szScan=szText+rClient.Size();
	int			nNoPixelsPerFrame=max(szScan.cx,szScan.cy)/nTotalFrames;

	//Set the current location
	CPoint	pos=CPoint(	MulDiv(nFrame,szScan.cx,nTotalFrames*nNoPixelsPerFrame)-szText.cx,
											MulDiv(nFrame,szScan.cy,nTotalFrames*nNoPixelsPerFrame)-szText.cy);

	//Centre the text in the available client area
	return CRect(pos,szText);
}

/////////////////////////////////////////////////////////////////////////////

