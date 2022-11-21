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

#ifndef _CRADIOGROUP_
#define _CRADIOGROUP_


///////////////////////////////////////////////////////////////////////
//	Class CRadioGroup -- control for establishing Radio hits
//
//	Thic class can be used to subclass a group box and gives direct
//	access to bounded radio buttons.
///////////////////////////////////////////////////////////////////////
class CRadioGroup :public CButton
{
enum{ cFirstIndex=1};	//1 based indexing. NB. Can change to 0 if required

public:
	CRadioGroup(){}
	virtual ~CRadioGroup(){}

	//Sets the active radio by index. The index is 1 based and the order  
	//is in the order they are created in the resource definition.
	void		SetRadio(int nRadio){ScanRadioGroup(FALSE,nRadio);}	
	//Return the 1 based index of the active radio.	
	int			GetRadio()const			{return ScanRadioGroup(TRUE);}		
	//Deselect all radios bounded by the groupbox		
	void		UnselectAll()				{ScanRadioGroup(FALSE);}

	DECLARE_MESSAGE_MAP()
private:
	//Helper methods to set/get radios bounded by the groupbox.
	bool		IsValidControl(CWnd* pWnd)const
					{return pWnd!=NULL && pWnd->GetParent()==GetParent();}

	long		ScanRadioGroup(BOOL bGetIndex,int nIndex=cFirstIndex-1)const;
};

#endif
