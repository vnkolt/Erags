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

#ifndef _CCUSTOMICONBUTTON_
#define _CCUSTOMICONBUTTON_

#ifndef _CCUSTOMBUTTON_
#include "CCustomButton.h"
#endif

///////////////////////////////////////////////////////////////////////
//	Class CCustomIconButton
//
//	This class demonstrates the use of CCustomButton.
//	CCustomIconButton is derived from CCustomButton and draw a custom
//	button based on an indexed bitmap taken from a toolbar style strip bitmap.	
//	
///////////////////////////////////////////////////////////////////////

class CCustomIconButton :public CCustomButton
{
	DECLARE_DYNAMIC(CCustomIconButton)

public:
	CCustomIconButton(){}
	virtual ~CCustomIconButton(){}

	//Loads the image from a toolbar-style strip bitmap. 
	//nOffset is the 1 based offset of the icon.
	BOOL LoadIcon(UINT nBitMapID,int nOffset,CSize sz=CSize(16,15));
	BOOL LoadIcon(UINT nBitMapID,CSize sz=CSize(16,15)){return LoadIcon(nBitMapID,1,sz);}

protected:
	virtual	bool	CustomDraw()const{return true;}	//Return TRUE so Draw() is called
	virtual	void	OnDraw(CDC* pDC,const CCustomButtonState& state);//Custom drawing of IconButton
	virtual	bool	ModifyHitRegion(const CRect& Client,CHitRgn& hitRgn);//Override to define own hit testing
	virtual	bool	HoverEffects()const{return s_Hovering;}
	virtual	void	OnHover(bool bEnteringButton);	
	DECLARE_MESSAGE_MAP()

protected:
	CImageList	m_Image;	//Store the image in an image list for convenience
	CSize				m_Size;		//Cache the size of the bitmap.

	CRect				GetIconRect(CRect rClient)const;

public:
	static bool	s_Hovering;
};

#endif
