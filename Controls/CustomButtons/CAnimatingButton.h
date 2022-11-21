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

#ifndef _CANIMATINGBUTTON_
#define _CANIMATINGBUTTON_


#ifndef _CCUSTOMTEXTBUTTON_
#include "CCustomTextButton.h"
#endif

///////////////////////////////////////////////////////////////////////
//	Class CAnimatingButton
///////////////////////////////////////////////////////////////////////
class CAnimatingButton : public CCustomTextButton
{
	DECLARE_DYNAMIC(CAnimatingButton)
public:
	CAnimatingButton(){}
	virtual ~CAnimatingButton(){}

	virtual	bool	ModifyHitRegion(const CRect&,CHitRgn&){return false;}//Use client rect
	DECLARE_MESSAGE_MAP()

protected:		
	virtual	CRect	GetBorderRect(CDC* pDC,const CString& s,const CRect& rClient)const;	//Override to adjust external button size
	virtual	CRect	GetTextRect(CDC* pDC,const CString& s,const CRect& rClient)const;
};

///////////////////////////////////////////////////////////////////////

#endif
