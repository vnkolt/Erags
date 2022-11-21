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

#ifndef _CRADIOHELPERS_
#define _CRADIOHELPERS_

///////////////////////////////////////////////////////////////////////
//	Class CRadioHelpers -- namespace for generic radio button helpers
///////////////////////////////////////////////////////////////////////

class CRadioHelpers
{
public:
	static bool		IsGroupBox(CWnd* pButton)				{return TestStyle(pButton,BS_GROUPBOX);}
	static bool		IsAutoRadio(CWnd* pButton)			{return TestStyle(pButton,BS_AUTORADIOBUTTON);}
	static bool		IsRadioGroup(CWnd* pButton)			{return IsRadio(pButton) && TestStyle(pButton,WS_GROUP);}

	static void		HitRadioItem(CWnd* pButton);
	static void		TellParentClicked(CWnd* pButton);
	static void		TellGroupClicked(CWnd* pButton);

private:
	static bool		IsRadio(CWnd* pButton);
	static UINT		GetStyle(CWnd* pButton);
	static bool		TestStyle(CWnd* pButton,UINT nStyle){return (GetStyle(pButton) & nStyle)!=0;}
	static CWnd*	FindStartOfRadioGroup(CWnd* pButton);
};

#endif
