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

#ifndef _CRADIOGROUP_
#include "CRadioGroup.h"
#endif

#ifndef _CRADIOHELPERS_
#include "CRadioHelpers.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////
//	Class CRadioGroup -- control for establishing Radio hits
///////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CRadioGroup,CButton)
//{{AFX_MSG_MAP(CRadioGroup)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////
//Helper method to set/get radios bounded by the groupbox.
//
//	bGetIndex:	getting or setting radio
//	nIndex:			index of the radio button (only used if bGetIndex==FALSE)
//
long CRadioGroup::ScanRadioGroup(BOOL bGetIndex,int nIndex)const
{
	long nRadioNo=cFirstIndex-1;//-1;	//1 based indexing
	CRect rBounds;
	GetWindowRect(&rBounds);//bounds of the groupbox

	if(GetParent()!=NULL)
		{
		BOOL bContinue=TRUE;

		// walk all children in group
		for(CWnd* pWnd=GetParent()->GetWindow(GW_CHILD);bContinue && IsValidControl(pWnd);pWnd=pWnd->GetNextWindow())	
			{
			CRect rRadio;
			pWnd->GetWindowRect(&rRadio);

			//Count auto radio buttons, that are encompassed by the group box. 
			//Exclude the group box itself.
			//
			if(rRadio.IntersectRect(rRadio,rBounds) && pWnd->GetSafeHwnd()!=GetSafeHwnd())
				{
				if(CRadioHelpers::IsAutoRadio(pWnd))
					{
					nRadioNo++;	//Increment index of radio

					if(bGetIndex)		// thus get active
						{
						if(pWnd->SendMessage(BM_GETCHECK,0,0L)!=0)//Have the active button
							bContinue=FALSE;	
						}
					else						// set the radio
						{
						pWnd->SendMessage(BM_SETCHECK,nRadioNo==nIndex,0L);
						}
					}
				}
			} 
		if(bContinue && bGetIndex)//Didn't find set radio
			{
			nRadioNo=-1;
			TRACE("CRadioGroup::DoRadioGroup: Didn't find set radio in group.");
			}
		}
	return nRadioNo;
}

///////////////////////////////////////////////////////////////////////




