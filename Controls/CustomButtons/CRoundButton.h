//---------------------------------------------------------------------------
//	THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
//	THE AUTHOR DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR IMPLIED, 
//	INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
//	PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
//	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL, 
//	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, 
//
//	Written by Chris Maunder (chrismaunder@codeguru.com)
//	Copyright (c) 1998.
//	Adapted to work with CCustomButton as a base class.
//
//---------------------------------------------------------------------------

#ifndef _CROUNDBUTTON_
#define _CROUNDBUTTON_


#ifndef _CCUSTOMBUTTON_
#include "CCustomButton.h"
#endif

///////////////////////////////////////////////////////////////////////
//	Class CRoundButton
///////////////////////////////////////////////////////////////////////

class CRoundButton : public CCustomButton
{
	DECLARE_DYNAMIC(CRoundButton)

public:
	CRoundButton(){}
	virtual ~CRoundButton(){}

	virtual	bool	CustomDraw()const{return true;}	//Return true so OnDraw() is called
	virtual	void	OnDraw(CDC* pDC,const CCustomButtonState& state);//Custom drawing
	virtual	bool	ModifyHitRegion(const CRect& Client,CHitRgn& hitRgn);//Override to define own hit testing
	virtual	bool	HoverEffects()const{return s_Hovering;}
	virtual	void	OnHover(bool bEnteringButton);	
	DECLARE_MESSAGE_MAP()

protected:
	int    GetRadius(const CRect& rClient)const{return rClient.bottom/2-1;}

	//Drawing helpers
	static COLORREF GetColour(double dAngle,COLORREF crBright,COLORREF crDark);
	static void DrawCircle(CDC* pDC,CPoint p,LONG lRadius,COLORREF crColour,BOOL bDashed=FALSE);
	static void DrawCircle(CDC* pDC,CPoint p,LONG lRadius,COLORREF crBright,COLORREF crDark);

public:
	static bool	s_Hovering;
};

#endif
