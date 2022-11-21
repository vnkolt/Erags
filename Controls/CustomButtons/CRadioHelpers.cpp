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

#ifndef _CRADIOHELPERS_
#include "CRadioHelpers.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////
//	Class CRadioHelpers -- namespace for generic radio button helpers
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//Is this CWnd a radio button

bool CRadioHelpers::IsRadio(CWnd* pButton)
	{
		return	pButton!=NULL && 
						(pButton->SendMessage(WM_GETDLGCODE,0,0L) & DLGC_RADIOBUTTON)!=0;
	}

///////////////////////////////////////////////////////////////////////
//Get the button style
//
UINT	CRadioHelpers::GetStyle(CWnd* pButton)
{
	if(pButton!=NULL)
		return (UINT)::GetWindowLong(pButton->GetSafeHwnd(),GWL_STYLE);
	return 0;
}

///////////////////////////////////////////////////////////////////////
//Either find an auto radio group or the first non radio control
//
CWnd* CRadioHelpers::FindStartOfRadioGroup(CWnd* pStartRadio)
{
	CWnd* pRadio		=NULL;
	CWnd* pNextRadio=NULL;

	if(pStartRadio!=NULL)
		{
		CWnd* pDialog=pStartRadio->GetParent();

		if(pDialog!=NULL)
			{
			for(pRadio=pStartRadio;pRadio!=NULL && !IsRadioGroup(pRadio);)	// walk back till find start of group
				{
				pNextRadio=pDialog->GetNextDlgGroupItem(pRadio,TRUE);//Get previous
				
				if(!IsRadio(pNextRadio))
					{
					break;
					}

				if(pNextRadio==pRadio || pNextRadio==pStartRadio)
					{
					TRACE("FindStartOfRadioGroup : Empty group\n");
					pRadio=NULL;
					}
				else
					{
					pRadio=pNextRadio;
					}
				}
			}
		}
	return pRadio;
}


///////////////////////////////////////////////////////////////////////
//Correct behaviour in response to a click in a radio button
//
void CRadioHelpers::HitRadioItem(CWnd* pHitRadio)
{
	CWnd* pStartRadio =FindStartOfRadioGroup(pHitRadio);

	if(pHitRadio!=NULL && pStartRadio!=NULL)
		{
		CWnd* pDialog=pHitRadio->GetParent();

		if(pDialog!=NULL)
			{
			for(CWnd* pRadio=pStartRadio;pRadio!=NULL && IsRadio(pRadio);)	// walk back till find start of group
				{
				if(IsRadio(pRadio))
					{
					if(pRadio==pHitRadio && IsAutoRadio(pRadio))
						{
						pRadio->SendMessage(BM_SETCHECK,1,0L);
						}
					else
						{
						pRadio->SendMessage(BM_SETCHECK,0,0L);	//turn off others
						}
					}
				pRadio=pDialog->GetNextDlgGroupItem(pRadio);
				if(pRadio==pStartRadio || !IsRadio(pRadio))
					break;
				}
			}
		}
}

///////////////////////////////////////////////////////////////////////
//Send a BN_CLICKED message to the button's parent
//
void CRadioHelpers::TellParentClicked(CWnd* pButton) 
{
	if(pButton!=NULL)
		{
		CWnd* pParent	=pButton->GetParent();
		int nControlID=pButton->GetDlgCtrlID();
		HWND hWnd			=pButton->GetSafeHwnd();

		if(pParent!=NULL && hWnd!=0)
			pParent->SendMessage(WM_COMMAND,MAKEWPARAM(nControlID,BN_CLICKED),(LPARAM)hWnd);
		}
}


///////////////////////////////////////////////////////////////////////
//Send a BN_CLICKED message to all encompassing groupbox's
//	
void CRadioHelpers::TellGroupClicked(CWnd* pButton) 
{
	if(pButton!=NULL)
		{
		CRect rButton;
		pButton->GetWindowRect(rButton);

		CWnd* pFirstItem=pButton->GetWindow(GW_HWNDFIRST);//Get first sibling
		CWnd* pLastItem	=pButton->GetWindow(GW_HWNDLAST);	//Get last sibling

		if(pFirstItem && pLastItem)// walk through the items to find groupbox's
			{
			for(CWnd* pItem=pFirstItem;pItem!=NULL;pItem=pItem->GetWindow(GW_HWNDNEXT))	
				{				
				if(IsGroupBox(pItem))
					{
					CRect rGroupBox;
					pItem->GetWindowRect(rGroupBox);
					if(rGroupBox.IntersectRect(rGroupBox,rButton))
						{
						TellParentClicked(pItem);
						}
					}
				if(pItem==pLastItem)
					break;
				}
			}
		}
}

///////////////////////////////////////////////////////////////////////
