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

#ifndef _CCUSTOMTEXTBUTTON_
#define _CCUSTOMTEXTBUTTON_


#ifndef _CCUSTOMBUTTON_
#include "CCustomButton.h"
#endif

///////////////////////////////////////////////////////////////////////
//	Class CCustomTextButton
//
//	This class demonstrates the use of CCustomButton.
//	CCustomIconButton is derived from CCustomButton and draw the button text
//	in a customised way.	
//	
///////////////////////////////////////////////////////////////////////

class CCustomTextButton :public CCustomButton  
{
	DECLARE_DYNAMIC(CCustomTextButton)

public:
	CCustomTextButton(){m_TextColor=RGB(0,0,0);}
	virtual ~CCustomTextButton(){}

	void SetTextColor(COLORREF color);

	//CCustomButton Overridables 
	virtual	bool	CustomDraw()const{return true;}	//Return TRUE so Draw() is called
	virtual	void	OnDraw(CDC* pDC,const CCustomButtonState& state);//Custom drawing of IconButton
	virtual	bool	ModifyHitRegion(const CRect& rClient,CHitRgn&);	//Override to define own hit testing
	DECLARE_MESSAGE_MAP()


protected:		
	COLORREF m_TextColor;

	CSize	GetTextSize(CDC* pDC,const CString& s)const;
	CRect	InflateRect(const CRect& rButton,CSize sInflate)const;
	void	DrawText(CDC* pDC,const CRect& rText,const CCustomButtonState& state);	//Override to change drawing of text

	virtual	CRect	GetTextRect(CDC* pDC,const CString& s,const CRect& rClient)const;
	virtual	CRect	GetBorderRect(CDC* pDC,const CString& s,const CRect& rClient)const;	//Override to adjust external button size
};

#endif
