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

#ifndef _CCUSTOMBUTTON_
#define _CCUSTOMBUTTON_

#ifndef _CANIMATIONTIMER_
#include "CAnimationTimer.h"
#endif

///////////////////////////////////////////////////////////////////////
//	Class CHitRgn
//
//  Encapsulates a button hit region
//	You can either just use a rect region in which case the overhead of
//  a CRgn is unnecessary, or can set up a more complex CRgn region.
///////////////////////////////////////////////////////////////////////

class CHitRgn: public CRgn
{
public:
	CHitRgn():m_rBox(0,0,0,0){}
	~CHitRgn(){FreeCRgn();}	//Clean up

	int				GetRgnBox(LPRECT lpRect) const;	// Overload CRgn:: version to allow for simple rects
	CHitRgn&	operator=(const CRect&);				// Set hit zone to a simple rect region in client coords
	bool			Inside(CPoint pt)const;					// test if pt in client coords is in the hit region

private:
	CRect			m_rBox;	//Simple hit box bounds in client coords

	void			InitData()					{ FreeCRgn(); m_rBox=CRect(0,0,0,0);}
	bool			HaveCRgn()const			{ return GetSafeHandle()!=NULL;}	
	void			FreeCRgn()					{ if(HaveCRgn())DeleteObject();}	// Free GDI object if active

	void			CacheRgnBox()				{ if(HaveCRgn()) GetRgnBox(m_rBox);}//Copy the CRgn bounds to m_rBox
	CRect			GetCachedBox()const	{return m_rBox;}//Get cached box

	friend class CCustomButton;
};


///////////////////////////////////////////////////////////////////////
//	Class CCustomButtonState
//
//  Contains the state data required to draw the button
//	This class is passed to the CCustomButton virtual method Draw()
///////////////////////////////////////////////////////////////////////
class CCustomButtonState
{
public:
	CCustomButtonState()
	:	m_bSelected(false),m_bThreeState(false),m_bHilited(false),
		m_bFocused(false),m_bEnabled(false),m_bHovering(false),
		m_nNoOfFrames(0),m_nFrame(0){}

	CRect		m_rClient;
	CString m_sText;
	bool		m_bSelected;
	bool		m_bThreeState;
	bool		m_bHilited;
	bool		m_bFocused;
	bool		m_bEnabled;

	//Support for hover effect
	bool		m_bHovering;		//Is the mouse hovering over this button

	//Support for animation
	int			m_nNoOfFrames;	//Total number of frames in a sequence
	int			m_nFrame;				//Which animation frame is this
	};

///////////////////////////////////////////////////////////////////////
//	Class CCustomButton
//	
//	Contains a class for generic custom drawing of a button
//	To custom draw a button:
//					1.	override CustomDraw() to returns true
//					2.	override OnDraw() to do the drawing
//	To add hovering effects:
//					1.	override HoverEffects() to returns true
//					2.	override OnHover() to provide non-drawing effects
//	To add animation:
//					1.	call SetAnimation()
//
///////////////////////////////////////////////////////////////////////
class CCustomButton :public CButton
{
	DECLARE_DYNAMIC(CCustomButton)
public:
	CCustomButton():m_State(0),m_bHovering(false){}
	virtual ~CCustomButton(){}

	//Turn on/off animation. 
	//The drawing code OnDraw() will be called every 'nMillisecsPerFrame' with 
	//the frame variable 'CCustomButtonState::m_nFrame' incremented each time.
	void	SetAnimation(bool bActive,int nNoOfFrames=0,int nMillisecsPerFrame=10);

	//Overridables

protected:
	// Override and return 'true' to get custom behaviour
	virtual	bool	CustomDraw()const{return false;}
	// Override to provide custom drawing. Called if CustomDraw() return true.
	virtual	void	OnDraw(CDC*,const CCustomButtonState&){}

	// Override and return 'true' to define your own hit testing region 
	// the default is the client rect.
	virtual	bool	ModifyHitRegion(const CRect& /*rClient*/,CHitRgn& /*hitRgn*/){return false;}

	// Override and return 'true' to get hovering effects:
	// 1. The Draw routine will be called with data.m_bHovering
	//		set true, as the mouse passes over the button.
	// 2. OnHover() will be called as the mouse crosses the hit region
	virtual	bool	HoverEffects()const{return false;}

	// Override OnHover() to provide non-drawing effect such as sounds.
	// The parameter 'bEnteringButton' specifies if entering or leaving 
	// the buttons hit region.
	virtual	void	OnHover(bool /*bEnteringButton*/){}	

protected:
	//{{AFX_MSG(CCustomButton)
	//All these methods/messages need to be overridden/subclassed to
	//avoid any drawing by the underlying window object. 
	virtual void	PreSubclassWindow();
	afx_msg void	OnPaint();
	afx_msg void	OnEnable(BOOL bEnable);
	afx_msg void	OnSize(UINT nType,int cx,int cy);

	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void	OnSetFocus(CWnd* pOldWnd);
	afx_msg void	OnKillFocus(CWnd* pNewWnd);
	afx_msg void	OnCaptureChanged(CWnd* pNewWnd);

	//Used in animation
	afx_msg void	OnTimer(UINT nIDEvent);
	afx_msg void	OnDestroy();

	//Handle button messages
	LRESULT				OnBMClick(WPARAM,LPARAM);
	LRESULT				OnBMSetCheck(WPARAM wParam,LPARAM lParam);
	LRESULT				OnBMSetState(WPARAM wParam,LPARAM lParam);
	LRESULT				OnBMGetCheck(WPARAM,LPARAM);
	LRESULT				OnBMGetState(WPARAM,LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	//Access to button state
	bool	GetStateFlag(int bit)const			{return (m_State & bit)!=0;}
	bool	GetSelectionState()const				{return GetStateFlag(BST_CHECKED);}
	bool	IsThreeState()const							{return GetStateFlag(BST_INDETERMINATE);}
	bool	GetHiliteState()const						{return GetStateFlag(BST_PUSHED);}
	bool	GetFocusState()const						{return	GetStateFlag(BST_FOCUS);}

	//Modifying the button state
	void	SetStateFlag(int bit,bool bSet);
	void	SetSelectionState(bool bSel)		{SetStateFlag(BST_CHECKED,bSel);}
	void	SetThreeState(bool bThreeState)	{SetStateFlag(BST_INDETERMINATE,bThreeState);}
	void	SetHiliteState(bool bHilite)		{SetStateFlag(BST_PUSHED,bHilite);}
	void	SetFocusState(bool bFocus)			{SetStateFlag(BST_FOCUS,bFocus);}

	//Send a BN_CLICKED to any Groupbox that contains this button
	void	TellGroupClicked();	

	//Drawing
	void	Update(CDC* pDC=NULL);				
	void	DoDraw(const CRect& rClient,CDC* pDC=NULL);				//Call the overridden virtual method Draw()
	bool	DoBufferDraw(const CRect& rClient,CDC* pDC=NULL);	//Buffered call to DoDraw()

	//Style access
	bool	StyleIsAuto()const;
	bool	StyleIsCheck()const;
	bool	StyleIsRadio()const;
	bool	StyleIs3State()const;

	//Support for mouse capture
	bool	SetCapture();	//Set capture to this button if free
	bool	EndCapture();
	bool	SetCaptureState(bool bState){return bState ? SetCapture():EndCapture();}
	bool	HaveCapture()const{return static_cast<const CWnd*>(this)==CWnd::GetCapture();}

	//Support for Hit tracking
	bool	OverButton(CPoint pt)const{return m_HitRegion.Inside(pt);}		
	bool	OverButton()const;				//is the mouse over the button
	void	StartTracking();					//Begin tracking on a MouseDown.
	void	EndTracking();						//End tracking on MouseUp or Other external event
	//Are we tracking a button press
	bool	Tracking()const{return HaveCapture() && !GetHoverState();}	


	//Hovering support
	//Only set hover state if effect flag is active
	void	DoHover();										//called to handle hovering 
	void	SetHoverState(bool bHovering)	{m_bHovering=bHovering;}
	bool	GetHoverState()const					{return m_bHovering;}
	bool	Hovering()const								{return OverButton() && GetHoverState();}

	//Support for animation
	bool	Animating()const							{return m_Timer.IsTiming();}
	int		GetAnimationFrame() const			{return m_Timer.GetFrame();}
	int		GetNoOfAnimationFrames()const	{return m_Timer.GetNoOfFrames();}

	//Support for a user defined hit region
	bool	CallModifyHitRegion();

private:
	int							m_State;			//Current button state
	CHitRgn					m_HitRegion;	//Default is the client rect

	bool						m_bHovering;	//Mark if over the button, last time OnHover() called
																//ONLY used if HoverEffects() returns true.

	CAnimationTimer	m_Timer;			//Animation timer
};

#endif
