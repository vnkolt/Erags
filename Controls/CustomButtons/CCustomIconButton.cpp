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

#ifndef _CCUSTOMICONBUTTON_
#include "CCustomIconButton.h"
#endif

#include <MMSystem.h>

#ifdef _ERAGS
#include "..\..\Erags\resource.h"       // main ERAGS symbols
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCustomIconButton,CCustomButton)
BEGIN_MESSAGE_MAP(CCustomIconButton,CCustomButton)
	//{{AFX_MSG_MAP(CCustomIconButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const CSize cButtonMargin(10,10);		// number of pixels wider button is than icon

/////////////////////////////////////////////////////////////////////////////
//
bool CCustomIconButton::s_Hovering=false;

/////////////////////////////////////////////////////////////////////////////
//
static CRect GetBorderRect(const CRect& rButton,CSize sInflate)
{	
	CRect r=rButton;
	r.InflateRect(sInflate);
	return r;
}

/////////////////////////////////////////////////////////////////////////////
//Create an 'icon' from a toolbar bitmap
//
BOOL CCustomIconButton::LoadIcon(UINT nBitmapID,int nOffset,CSize sz)
{
	BOOL bLoadOK=FALSE;
	CBitmap bmToolbar;

	if(bmToolbar.LoadBitmap(nBitmapID))// load toolbar bitmap
		{
		if(m_Image.Create(sz.cx,sz.cy,ILC_MASK,0,10))//Create imagelist from bitmap
			{
			//Add bitmap to the image list. Use default button color as mask color
			m_Image.Add(&bmToolbar,GetSysColor(COLOR_3DFACE));//mask color
			m_Size=sz;
			
			nOffset--; //convert to 0 based

			//nOffset must be a valid offset
			ASSERT(nOffset>=0 && nOffset<m_Image.GetImageCount());

			if(nOffset>=0 && nOffset<m_Image.GetImageCount())
				{
				//Remove unneeded images
				for(int i=m_Image.GetImageCount()-1;i>=0;i--)
					{
					if(i!=nOffset)
						m_Image.Remove(i);	
					}
				}
			//Should be left with the one image
			ASSERT(m_Image.GetImageCount()==1);
			}
		}
	return bLoadOK;
}

/////////////////////////////////////////////////////////////////////////////
//Override to define extra hover behaviour
//
void	CCustomIconButton::OnHover(bool bEnteringButton)
{
	if(bEnteringButton)
		::PlaySound((LPCTSTR)IDR_WAVE2,AfxGetResourceHandle(),SND_RESOURCE | SND_ASYNC);
}

/////////////////////////////////////////////////////////////////////////////
//Override to define own hit testing
//
bool CCustomIconButton::ModifyHitRegion(const CRect& rClient,CHitRgn& hitRgn)
{
	hitRgn=GetBorderRect(GetIconRect(rClient),cButtonMargin);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
//Get visible button rect based on the buttons client rect
//
CRect	CCustomIconButton::GetIconRect(CRect rClient)const
{
CRect r=rClient;

if(m_Image.GetImageCount()==1)
	{
	CPoint centre=r.CenterPoint();

	//Centre the icon 
	r.left	=centre.x-m_Size.cx/2;
	r.right	=centre.x+m_Size.cx/2;
	r.top		=centre.y-m_Size.cy/2;
	r.bottom=centre.y+m_Size.cy/2;
	}
return r;
}

/////////////////////////////////////////////////////////////////////////////
//Draw the button based on the current state as defined in state.
//
void	CCustomIconButton::OnDraw(CDC* pDC,const CCustomButtonState& state)
{
const CSize cSelectionMargin(3,3);// number of pixels wider selection is than icon
const CSize cFocusMargin(5,5);		// number of pixels wider focus is than icon
const CSize cEdgeMargin(8,8);		// number of pixels wider focus is than icon

if(pDC!=NULL && m_Image.GetImageCount()==1)
	{
	CRect r=GetIconRect(state.m_rClient);
		
	//Draw button edge depending on if hilited or not, draw pushed-in or popped-out edge
	UINT nEdge=state.m_bHilited ? BDR_SUNKENOUTER:BDR_RAISEDINNER;
	pDC->DrawEdge(GetBorderRect(r,cEdgeMargin),nEdge,BF_RECT);
	
	//If enable draw selection and standard icon
	if(state.m_bEnabled) 
		{
		if(state.m_bSelected) 
			{
			if(state.m_bThreeState)
				pDC->FillSolidRect(GetBorderRect(r,cSelectionMargin),GetSysColor(COLOR_INACTIVEBORDER));
			else
				pDC->FillSolidRect(GetBorderRect(r,cSelectionMargin),GetSysColor(COLOR_BTNHIGHLIGHT));
			pDC->DrawEdge(GetBorderRect(r,cSelectionMargin),BDR_SUNKENOUTER,BF_RECT);
			}
		m_Image.Draw(pDC,0,r.TopLeft(),ILD_TRANSPARENT);//Use ImageList draw routine
		} 
	else //Draw disabled
		{
		HICON hIcon=m_Image.ExtractIcon(0);
		pDC->DrawState(r.TopLeft(),m_Size,hIcon,DSS_DISABLED,(HBRUSH)NULL);
		DestroyIcon(hIcon);
		}

	//Draw focus rect
	if(state.m_bFocused)
		{
		pDC->DrawFocusRect(GetBorderRect(r,cFocusMargin));
		}
	//Draw hover edge
	if(state.m_bHovering)
		{
		pDC->DrawEdge(GetBorderRect(r,cButtonMargin),EDGE_SUNKEN,BF_RECT);
		}
	} 
}



