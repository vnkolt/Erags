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

#ifndef _CCUSTOMBUTTON_
#include "CCustomButton.h"
#endif

#ifndef _CRADIOHELPERS_
#include "CRadioHelpers.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_ANIMATION_TIMER 503

///////////////////////////////////////////////////////////////////////
//	Class CHitRgn
//
//  Encapsulates a button hit region
//	You can either just use a rect region inwhich case the overhead of
//  a CRgn is unnecessary, or can set up a more complex region.
///////////////////////////////////////////////////////////////////////

//
// Set to a simple rect region in client coords
//
CHitRgn& CHitRgn::operator=(const CRect& r)	
{
	InitData();					//Remove current data
	m_rBox=r;						//Simple rect region
	m_rBox.NormalizeRect();//Just in case

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Is the pt (client coords) inside the region
//
int CHitRgn::GetRgnBox(LPRECT lpRect) const
{
	if(HaveCRgn())
		{
		return CRgn::GetRgnBox(lpRect);
		}
	else //Just get the stored rect
		{
		*lpRect=GetCachedBox();
		return SIMPLEREGION;	//Mark as valid
		}
}

/////////////////////////////////////////////////////////////////////////////
// Is the pt (client coords) inside the region
//
bool	CHitRgn::Inside(CPoint pt)const
{
	if(GetCachedBox().PtInRect(pt))//Must be in bounding box
		{
		if(HaveCRgn())	//If have a real region check inside it
			return PtInRegion(pt)!=FALSE;
		return true;
		}
	return false;
}

///////////////////////////////////////////////////////////////////////
//	Class CCustomButton
///////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CCustomButton,CButton)

BEGIN_MESSAGE_MAP(CCustomButton,CButton)
	//{{AFX_MSG_MAP(CCustomButton)
	ON_WM_PAINT()
	ON_WM_ENABLE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CAPTURECHANGED()

	//Used in animation	
	ON_WM_TIMER()
	ON_WM_DESTROY()

	ON_MESSAGE(BM_CLICK,OnBMClick)
	ON_MESSAGE(BM_SETCHECK,OnBMSetCheck)
	ON_MESSAGE(BM_SETSTATE,OnBMSetState)
	ON_MESSAGE(BM_GETCHECK,OnBMGetCheck)
	ON_MESSAGE(BM_GETSTATE,OnBMGetState)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//Helpers to determine the type of the button
//
bool	CCustomButton::StyleIsAuto()const
{
	UINT style=GetButtonStyle();
	return	(style==BS_AUTOCHECKBOX)	||
					(style==BS_AUTO3STATE) ||
					(style==BS_AUTORADIOBUTTON);
}

bool	CCustomButton::StyleIs3State()const
{
	UINT style=GetButtonStyle();
	return	(style==BS_3STATE)	||
					(style==BS_AUTO3STATE);
}

bool	CCustomButton::StyleIsCheck()const
{
	UINT style=GetButtonStyle();
	return	(style==BS_AUTOCHECKBOX)	||
					(style==BS_CHECKBOX) ||
					StyleIs3State();
}

bool	CCustomButton::StyleIsRadio()const
{
	UINT style=GetButtonStyle();
	return	(style==BS_AUTORADIOBUTTON)	||
					(style==BS_RADIOBUTTON);
}


/////////////////////////////////////////////////////////////////////////////
//	Setting the individual bits in the stored state of the button
//
void	CCustomButton::SetStateFlag(int bit,bool bSet)
{
	if(GetStateFlag(bit)!=bSet)
		{
		if(bSet)
			m_State|=bit;
		else
			m_State&=~bit;
		Update();//Refresh
		}
}

/////////////////////////////////////////////////////////////////////////////
// Sets up the CCustomButtonData flags object which defines the state of the
// button and then calls the overridden Draw() method. 
//
void	CCustomButton::DoDraw(const CRect& rClient,CDC* pDC)
{
	if(pDC)
		{
		//First fill in the client background
		pDC->FillSolidRect(rClient,::GetSysColor(COLOR_MENU));

		//Set up the drawing flags
		CCustomButtonState state;

		state.m_rClient=rClient;
		state.m_bSelected=GetSelectionState();
		state.m_bThreeState=IsThreeState();
		state.m_bHilited=GetHiliteState();
		state.m_bFocused=GetFocusState();
		state.m_bEnabled=IsWindowEnabled()!=FALSE;
		state.m_bHovering=Hovering();
		GetWindowText(state.m_sText);

		//Set animation state
		state.m_nNoOfFrames=m_Timer.GetNoOfFrames();
		state.m_nFrame=m_Timer.GetFrame();

		// Set parent dialog font
		CWnd* pParent=GetParent();		// parent window
		CFont* pOldFont=NULL;

		if(pParent!=NULL)
			pOldFont=pDC->SelectObject(pParent->GetFont());
		
		//Draw the button
		OnDraw(pDC,state);

		// Reset the font
		if(pParent!=NULL && pOldFont!=NULL)
			pDC->SelectObject(pOldFont);
		}
}


/////////////////////////////////////////////////////////////////////////////
//	Provides flicker free drawing of the button.
//	Calls the DoDraw() above, but also buffers the drawing to an offscreen bitmap.
//
bool	CCustomButton::DoBufferDraw(const CRect& r,CDC* pDC)
{
	bool bBufferOK=false;

	if(pDC)
		{
		const bool cCanBitBlt=(pDC->GetDeviceCaps(RASTERCAPS) & RC_BITBLT)!=0;
		CDC bufferDC;
		CBitmap bufferBitmap;

		if(cCanBitBlt && bufferDC.CreateCompatibleDC(pDC))
			{
			if(bufferBitmap.CreateCompatibleBitmap(pDC,r.Size().cx,r.Size().cy))
				{
				CBitmap* pOldBitmap=bufferDC.SelectObject(&bufferBitmap);
				if(pOldBitmap!=NULL)
					{
					CRect bufferRect(CPoint(0,0),r.Size());
					DoDraw(bufferRect,&bufferDC);					//Draw into offscreen buffer
					
					//Flush the buffer to the screen
					pDC->BitBlt(r.left,r.top,r.Width(),r.Height(),&bufferDC,0,0,SRCCOPY);
					bufferDC.SelectObject(pOldBitmap);		//unselect the bitmap
					bBufferOK=true;
					}
				}
			}
		else
			{
			TRACE("Failed to create a compatible DC");
			}
		}
	return bBufferOK;
}

/////////////////////////////////////////////////////////////////////////////
//	Called within the class whenever a redraw is needed.
//
void	CCustomButton::Update(CDC* pControlDC)
{
	CDC *pDC=pControlDC;

	CRect	r;
	GetClientRect(&r);//Get client rect

	if(pDC==NULL)//If controlDC is NULL call GetDC()
		pDC=CWnd::GetDC();

	if(pDC!=NULL)
		{
		if(!DoBufferDraw(r,pDC))
			DoDraw(r,pDC);	//If can't buffer then draw direct
			
		//Release DC if we own it
		if(pControlDC==NULL && pDC!=NULL)
			CWnd::ReleaseDC(pDC);
		}
}


/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnPaint() if not custom drawing otherwise Update()
//
void CCustomButton::OnPaint() 
{
	if(CustomDraw())
		{
		CPaintDC dc(this); // device context for painting
		Update(&dc);
		}
	else	//Call default
		{
		CButton::OnPaint();
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnEnable() if not custom drawing otherwise forces a redraw

void CCustomButton::OnEnable(BOOL bEnable) 
{
	if(CustomDraw())
		{
		Invalidate(false);
		}
	else	//Call default
		{
		CButton::OnEnable(bEnable);
		}
}


/////////////////////////////////////////////////////////////////////////////
// Hit Test Region
/////////////////////////////////////////////////////////////////////////////

bool CCustomButton::CallModifyHitRegion()
{
	//To stop reentry on call to MoveWindow() below
	static bool bLock=false;	
	if(bLock)
		return false;
	bLock=true;
	
	//Update the hit region to users definition
	//
	CRect rBox;
	CRect	rClient;
	bool bValid=true;

	GetClientRect(&rClient);

	//Default region to the client rect
	m_HitRegion=rClient;		

	// Allow the user to set the window region which defines the hit test area.
	if(ModifyHitRegion(rClient,m_HitRegion))
		{
		int	nType=m_HitRegion.GetRgnBox(&rBox);
		bValid=nType!=ERROR && nType!=NULLREGION;//Is it a valid region

		if(bValid)	
			{
			CWnd* pParent=GetParent();
			// Check the new bounding box is valid then resize the button. 
			//
			bValid=!rBox.IsRectNull() && !rBox.IsRectEmpty() && pParent!=NULL;

			if(bValid)
				{
				m_HitRegion.CacheRgnBox();//Cache the client bound for quick access
				
				//Modify button size if needed
				//
				if(rClient!=rBox)
					{
					ClientToScreen(rBox);
					pParent->ScreenToClient(rBox);
					MoveWindow(rBox.left,rBox.top,rBox.Width(),rBox.Height(),true);
					}
				}
			else//If not valid reset the default region to the client rect
				{
				m_HitRegion=rClient;	
				}
			}
		}
	bLock=false;
	return bValid;
}

/////////////////////////////////////////////////////////////////////////////
// Allow the user to set a custom  hit test area.
//
void CCustomButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	CallModifyHitRegion();
}

/////////////////////////////////////////////////////////////////////////////
//Need to handle so that the hit region can be adjusted when button resized
//
void CCustomButton::OnSize(UINT nType,int cx,int cy)
{
	CButton::OnSize(nType,cx,cy);
	CallModifyHitRegion();// Allow the user to reset a custom  hit test area.
}

/////////////////////////////////////////////////////////////////////////////
// Tracking
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//	is the mouse over the button
//
bool CCustomButton::OverButton()const
{
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	return OverButton(pt);
}

/////////////////////////////////////////////////////////////////////////////
// Return true if this button now has the capture
//
bool	CCustomButton::SetCapture()
{
	if(GetCapture()==NULL)
		{
		CWnd::SetCapture();
		return true;
		}
	return HaveCapture();//We may already have capture if hovering is active
}

/////////////////////////////////////////////////////////////////////////////
// Returns true if capture on this button was released
//
bool	CCustomButton::EndCapture()
{
	if(HaveCapture())
		{
		::ReleaseCapture();
		return true;
		}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
//	Called in OnLButtonDown() to track for a possible hit.
//
void	CCustomButton::StartTracking()
{
	if(SetCapture())
		{
		m_bHovering=false;	//Turn off hover tracking
		CWnd::SetFocus();
		SetHiliteState(true);
		Update();
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Called in OnLButtonUp() to register a hit. Otherwise to signify 
//	tracking no longer needed.
//
void	CCustomButton::EndTracking()
{
	//Now clean up the capture and update

	// First check if we go back to hovering, if so we will keep capture
	// so check the mouse is still in scope
	bool bStillHovering=GetHoverState() && 
											OverButton()		&& 
											HaveCapture();

	if(!bStillHovering)
		{
		SetHoverState(false);//Make sure hovering is off
		EndCapture();	//Turn off and end capture
		}
	SetHiliteState(false);//Make sure hiliting is off
}


/////////////////////////////////////////////////////////////////////////////
//	Update hovering status if needed
//
void CCustomButton::DoHover()
{
	//Support hovering only when NOT tracking
	//
	if(HoverEffects())	
		{
		//Check if we have crossed the button boundary...
		//
		if(OverButton()!=GetHoverState())	
			{
			SetHoverState(!GetHoverState());//Toggle the setting
			SetCaptureState(GetHoverState());
			// call user defined hover method....
			// The parameter indicates whether are we entering or leaving the button.
			// 
			Update();
			OnHover(GetHoverState());//If setting to true we are entering the button
			}
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnMouseMove() if not custom drawing otherwise continues
//	local tracking of the mouse.
//
void CCustomButton::OnMouseMove(UINT nFlags, CPoint pt) 
{
	if(CustomDraw())
		{
		if(Tracking())
			{
			bool bInButton=OverButton(pt);

			if(bInButton!=GetHiliteState())
				{
				SetHiliteState(bInButton);
				}
			}
		else	
			{
			DoHover();//Support hovering
			}
		}
	else	//Call default
		{
		CButton::OnMouseMove(nFlags,pt);
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnLButtonDown() if not custom drawing otherwise starts
//	local tracking of the mouse.
//
void CCustomButton::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	if(CustomDraw())
		{
		if(OverButton(pt))
			StartTracking();
		}
	else	//Call default
		{
		CButton::OnLButtonDown(nFlags,pt);
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnLButtonUp() if not custom drawing otherwise ends
//	local tracking of the mouse. Registers a hit by calling OnBMClick
//	if the mouse is in the button bounds.
//
void CCustomButton::OnLButtonUp(UINT nFlags, CPoint pt) 
{
	if(CustomDraw())
		{
		if(Tracking() && OverButton(pt))
			OnBMClick(0,0);
		EndTracking();
		}
	else	//Call default
		{
		CButton::OnLButtonUp(nFlags,pt);
		
		//If clicked in button let any encompassing groupboxes know.
		//Thus any ON_BN_CLICKED() message cracker defined will be called.
		//
		if(OverButton(pt))
			TellGroupClicked();		
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnLButtonDblClk() if not custom drawing otherwise OnLButtonDown()
//	which will start local tracking of the mouse.
//
void CCustomButton::OnLButtonDblClk(UINT nFlags, CPoint pt) 
{
	if(CustomDraw())
		{
		OnLButtonDown(nFlags,pt);
		}
	else	//Call default
		{
		CButton::OnLButtonDblClk(nFlags,pt);
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnSetFocus() if not custom drawing otherwise set
//	the cached focus state.
//
void CCustomButton::OnSetFocus(CWnd* pWnd)
{
	if(CustomDraw())
		{
		SetFocusState(true);
		}
	else	//Call default
		{
		CButton::OnSetFocus(pWnd);
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnKillFocus() if not custom drawing otherwise set
//	the cached focus state.
//
void CCustomButton::OnKillFocus(CWnd* pWnd) 
{
	if(CustomDraw())
		{
		EndTracking();	//eg. If key pressed while tracking
		SetFocusState(false);
		}
	else	//Call default
		{
		CButton::OnKillFocus(pWnd);
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls CButton::OnCaptureChanged() if not custom drawing otherwise handles
//	case when capture gets out of synch.
//	- this can happen if we go to a background App while hovering.
//
void CCustomButton::OnCaptureChanged(CWnd* pWnd) 
{
	if(CustomDraw())
		{
		// First check if hovering, if so we will keep capture
		if(GetHoverState())
			{
			SetHoverState(false);	//Turn off hovering
			Invalidate(false);		//force a redraw
			}
		}
	else	//Call default
		{
		CButton::OnCaptureChanged(pWnd);
		}
}

/////////////////////////////////////////////////////////////////////////////
//  Animation
/////////////////////////////////////////////////////////////////////////////
void CCustomButton::SetAnimation(bool bActive,int nNoOfFrames,int nMillisecsPerFrame)
{
if(bActive)
	{
	m_Timer.Start(GetSafeHwnd(),nMillisecsPerFrame,ID_ANIMATION_TIMER,nNoOfFrames);
	}
else
	{
	m_Timer.Stop();
	}
}

/////////////////////////////////////////////////////////////////////////////
//
void CCustomButton::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==ID_ANIMATION_TIMER)
		{
		m_Timer.IncrementFrame();
		Update();
		}
	CButton::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
//
void CCustomButton::OnDestroy() 
{
	m_Timer.Stop();	//If needed
	CButton::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
//	Send a BN_CLICKED message to any encompassing groupboxes.
//
void	CCustomButton::TellGroupClicked()
{
	if(StyleIsRadio())
		CRadioHelpers::TellGroupClicked(this);
}

/////////////////////////////////////////////////////////////////////////////
//	Calls Default() for the default window behaviour if not custom drawing 
//	otherwise handle the hit.
//
//	An application sends a BM_CLICK message to simulate the user clicking a button. 
//	This message causes the button to receive a WM_LBUTTONDOWN and a WM_LBUTTONUP 
//	message,and the button's parent window to receive a BN_CLICKED notification message.
//
LRESULT CCustomButton::OnBMClick(WPARAM,LPARAM)
{
	if(CustomDraw())
		{
		//Update selection state, based on the button style
		//
		if(StyleIsCheck())
			{
			if(StyleIs3State())//Allow 3 state behaviour 
				{
				bool b3State=IsThreeState();

				//If 3 state style is set 
				//On each click the selection state order is- 
				//		1. BST_UNCHECKED
				//		2. BST_CHECKED
				//		3. BST_CHECKED+BST_INDETERMINATE
				// then back to state 1.
				//
				SetThreeState(GetSelectionState() && !b3State);
				SetSelectionState(!GetSelectionState() || !b3State);
				}
			else
				{
				SetSelectionState(!GetSelectionState());
				}
			}
		else if(StyleIsRadio())
			{
			if(StyleIsAuto())
				{
				SetThreeState(false);
				if(!GetSelectionState())
					{
					SetSelectionState(true);
					CRadioHelpers::HitRadioItem(this);//Update the radio group
					}
				}
			TellGroupClicked();//Let any encompassing group box know we have been clicked
			}
		if(!GetFocusState())	//set focus if not already
			CWnd::SetFocus();

		CRadioHelpers::TellParentClicked(this);
		return 0;
		}
	else	//Call default
		{
		return CButton::Default();
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls Default() for the default window behaviour if not custom drawing 
//	otherwise sets the cached check state and updates.
//	Possible values for check state are:
//	BST_UNCHECKED      0x0000
//	BST_CHECKED        0x0001
//	BST_INDETERMINATE  0x0002	- 3rd state
//
LRESULT CCustomButton::OnBMSetCheck(WPARAM nCheckState,LPARAM)
{
	if(CustomDraw())
		{
		EndTracking();

		if(nCheckState==BST_INDETERMINATE)
			SetThreeState(true);
		else	//Only set the check state
			SetSelectionState(nCheckState!=BST_UNCHECKED);
		return 0;
		}
	else	//Call default
		{
		return CButton::Default();
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls Default() for the default window behaviour if not custom drawing 
//	otherwise gets the cached check state.
//
LRESULT CCustomButton::OnBMGetCheck(WPARAM,LPARAM)
{
	if(CustomDraw())
		{
		return m_State & 0x0003;	
		}
	else	//Call default
		{
		return CButton::Default();
		}
}

/////////////////////////////////////////////////////////////////////////////
//	Calls Default() for the default window behaviour if not custom drawing 
//	otherwise sets the cached state and updates.
//
LRESULT CCustomButton::OnBMSetState(WPARAM state,LPARAM)
{
	if(CustomDraw())
		{
		m_State=state;
		EndTracking();
		return 0;
		}
	else	//Call default
		{
		return CButton::Default();
		}
}


/////////////////////////////////////////////////////////////////////////////
//	Calls Default() for the default window behaviour if not custom drawing 
//	otherwise gets the cached state.
//
LRESULT CCustomButton::OnBMGetState(WPARAM,LPARAM)
{
	if(CustomDraw())
		{
		return m_State;
		}
	else	//Call default
		{
		return CButton::Default();
		}
}



/////////////////////////////////////////////////////////////////////////////
