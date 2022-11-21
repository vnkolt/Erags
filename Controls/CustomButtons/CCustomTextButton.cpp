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

#ifndef _CCUSTOMTEXTBUTTON_
#include "CCustomTextButton.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const CSize cButtonMargin(12,10);	// number of pixels wider button is than text
const CSize cFocusMargin(5,5);	
const UINT cStdTextFormat=DT_TOP|DT_LEFT|DT_SINGLELINE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CCustomTextButton,CCustomButton)

BEGIN_MESSAGE_MAP(CCustomTextButton,CCustomButton)
	//{{AFX_MSG_MAP(CCustomTextButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
//
CRect CCustomTextButton::InflateRect(const CRect& rButton,CSize sInflate)const
{	
	CRect r=rButton;
	r.InflateRect(sInflate);
	return r;
}

//////////////////////////////////////////////////////////////////////
//
void CCustomTextButton::SetTextColor(COLORREF color)
{
	m_TextColor = color;
}

//////////////////////////////////////////////////////////////////////
//
CSize	CCustomTextButton::GetTextSize(CDC* pDC,const CString& s)const
{
	CWnd* pParent=GetParent();
	CFont* pOldFont=NULL;
	CSize szText(0,0);

	if(pDC!=NULL)
		{
		// Set parent dialog font
		if(pParent!=NULL)
			pOldFont=pDC->SelectObject(pParent->GetFont());

		//Get text size
		CRect rText(0,0,0,0);
		pDC->DrawText(s,rText,cStdTextFormat|DT_CALCRECT);
		szText=rText.Size();
		//szText=pDC->GetTextExtent(s);	

		//Reset the font
		if(pParent!=NULL && pOldFont!=NULL)
			pDC->SelectObject(pOldFont);
		}
	return szText;
}

//////////////////////////////////////////////////////////////////////
//
CRect	CCustomTextButton::GetTextRect(CDC* pDC,const CString& s,const CRect& rClient)const
{
	CRect rText=rClient;
	CPoint centre=rClient.CenterPoint();

	//Get text size
	CSize textSize=GetTextSize(pDC,s);

	//Centre the text in the available client area
	rText.left	=centre.x-textSize.cx/2;
	rText.right	=centre.x+textSize.cx/2+2;//Allow some slop for rounding due to /2
	rText.top		=centre.y-textSize.cy/2-1;
	rText.bottom=centre.y+textSize.cy/2+1;
	
	return rText;
}

//////////////////////////////////////////////////////////////////////
//Override to adjust external button size
//
CRect	CCustomTextButton::GetBorderRect(CDC* pDC,const CString& s,const CRect& rClient)const
{
	return InflateRect(GetTextRect(pDC,s,rClient),cButtonMargin);
}

//////////////////////////////////////////////////////////////////////
// CCustomButton Overridables 

//////////////////////////////////////////////////////////////////////
//Override to define own hit testing
//
bool CCustomTextButton::ModifyHitRegion(const CRect& rClient,CHitRgn& hitRgn)
{
	CWindowDC dc(NULL);
	CString s;
	GetWindowText(s);

	hitRgn=GetBorderRect(&dc,s,rClient);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
//Override to change drawing of text
//
void CCustomTextButton::DrawText(CDC* pDC,const CRect& rText,const CCustomButtonState& state)
{
if(pDC!=NULL)
	{
	bool bPressed=state.m_bSelected || state.m_bHilited;
	CString str=state.m_sText;
		
	CRect rDrawText=rText;
	if(bPressed) 
		rDrawText+=CPoint(1,1);

	//If enable draw selection and standard icon
	if(state.m_bEnabled) 
		{
		COLORREF color=pDC->SetTextColor(m_TextColor);
		pDC->DrawText(str,rDrawText,cStdTextFormat);
		pDC->SetTextColor(color);
		}
	else //Draw disabled
		{		
		// draw embossed text
		pDC->DrawState(rDrawText.TopLeft(),rDrawText.Size(),(LPCTSTR)str,
			DSS_DISABLED|DST_PREFIXTEXT,TRUE,str.GetLength(),(HBRUSH)NULL);
		}
	} 
}


/////////////////////////////////////////////////////////////////////////////
//Custom drawing of IconButton
//
void CCustomTextButton::OnDraw(CDC* pDC,const CCustomButtonState& state)
{
if(pDC!=NULL)
	{
	bool bPressed=state.m_bSelected || state.m_bHilited;
	CString str=state.m_sText;
	CRect rText=GetTextRect(pDC,str,state.m_rClient);
	CRect rBorder=GetBorderRect(pDC,str,state.m_rClient);
	
	//Draw button edge depending on if hilited or not, draw pushed-in or popped-out edge
	UINT nEdge=bPressed ? EDGE_SUNKEN:EDGE_RAISED;
	rBorder.DeflateRect(1,1);
	pDC->DrawEdge(rBorder,nEdge,BF_RECT);

	//Clip to internal border
	rBorder.DeflateRect(2,2);
	pDC->IntersectClipRect(	rBorder.left,rBorder.top,
													rBorder.right,rBorder.bottom);

	DrawText(pDC,rText,state);

	if(state.m_bFocused && state.m_bEnabled)//Draw focus rect
		pDC->DrawFocusRect(InflateRect(rText,cFocusMargin));
	
	pDC->SelectClipRgn(NULL);	//reset clip region
	} 
}

