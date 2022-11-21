// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "mso97.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IAccessible properties

/////////////////////////////////////////////////////////////////////////////
// IAccessible operations


/////////////////////////////////////////////////////////////////////////////
// _IMsoDispObj properties

/////////////////////////////////////////////////////////////////////////////
// _IMsoDispObj operations

LPDISPATCH _IMsoDispObj::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _IMsoDispObj::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _IMsoOleAccDispObj properties

/////////////////////////////////////////////////////////////////////////////
// _IMsoOleAccDispObj operations

LPDISPATCH _IMsoOleAccDispObj::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _IMsoOleAccDispObj::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBars properties

/////////////////////////////////////////////////////////////////////////////
// CommandBars operations

LPDISPATCH CommandBars::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBars::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::GetActionControl()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::GetActiveMenuBar()
{
	LPDISPATCH result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::Add(const VARIANT& Name, const VARIANT& Position, const VARIANT& MenuBar, const VARIANT& Temporary)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Position, &MenuBar, &Temporary);
	return result;
}

long CommandBars::GetCount()
{
	long result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBars::GetDisplayTooltips()
{
	BOOL result;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBars::SetDisplayTooltips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBars::GetDisplayKeysInTooltips()
{
	BOOL result;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBars::SetDisplayKeysInTooltips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH CommandBars::FindControl(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Id, &Tag, &Visible);
	return result;
}

LPDISPATCH CommandBars::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

BOOL CommandBars::GetLargeButtons()
{
	BOOL result;
	InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBars::SetLargeButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBars::GetMenuAnimationStyle()
{
	long result;
	InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBars::SetMenuAnimationStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPUNKNOWN CommandBars::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CommandBars::ReleaseFocus()
{
	InvokeHelper(0x60030010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBar properties

/////////////////////////////////////////////////////////////////////////////
// CommandBar operations

LPDISPATCH CommandBar::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBar::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBar::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CommandBar::GetContext()
{
	CString result;
	InvokeHelper(0x60040001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBar::SetContext(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBar::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CommandBar::Delete()
{
	InvokeHelper(0x60040004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CommandBar::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH CommandBar::FindControl(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible, const VARIANT& Recursive)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Id, &Tag, &Visible, &Recursive);
	return result;
}

long CommandBar::GetHeight()
{
	long result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBar::GetIndex()
{
	long result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBar::GetLeft()
{
	long result;
	InvokeHelper(0x6004000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBar::GetName()
{
	CString result;
	InvokeHelper(0x6004000e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBar::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CommandBar::GetNameLocal()
{
	CString result;
	InvokeHelper(0x60040010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBar::SetNameLocal(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBar::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60040012, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBar::GetPosition()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBar::GetRowIndex()
{
	long result;
	InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetRowIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBar::GetProtection()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetProtection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBar::Reset()
{
	InvokeHelper(0x60040019, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBar::ShowPopup(const VARIANT& x, const VARIANT& y)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6004001a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &x, &y);
}

long CommandBar::GetTop()
{
	long result;
	InvokeHelper(0x6004001b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBar::GetType()
{
	long result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBar::GetVisible()
{
	BOOL result;
	InvokeHelper(0x6004001e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBar::GetWidth()
{
	long result;
	InvokeHelper(0x60040020, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040020, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarControls properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarControls operations

LPDISPATCH CommandBarControls::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarControls::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarControls::Add(const VARIANT& Type, const VARIANT& Id, const VARIANT& Parameter, const VARIANT& Before, const VARIANT& Temporary)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Id, &Parameter, &Before, &Temporary);
	return result;
}

long CommandBarControls::GetCount()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarControls::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN CommandBarControls::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarControls::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarControl properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarControl operations

LPDISPATCH CommandBarControl::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarControl::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBarControl::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CommandBarControl::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarControl::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void CommandBarControl::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString CommandBarControl::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CommandBarControl::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CommandBarControl::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarControl::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarControl::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarControl::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarControl::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarControl::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long CommandBarControl::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarControl::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarControl::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString CommandBarControl::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarControl::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarControl::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarControl::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CommandBarControl::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CommandBarControl::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarControl::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarControl::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBarControl::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarButton properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarButton operations

LPDISPATCH CommandBarButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarButton::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBarButton::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CommandBarButton::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarButton::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void CommandBarButton::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString CommandBarButton::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CommandBarButton::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CommandBarButton::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarButton::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarButton::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarButton::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarButton::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long CommandBarButton::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarButton::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString CommandBarButton::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarButton::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarButton::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CommandBarButton::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CommandBarButton::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarButton::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarButton::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBarButton::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CommandBarButton::GetBuiltInFace()
{
	BOOL result;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBuiltInFace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CommandBarButton::CopyFace()
{
	InvokeHelper(0x60050002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarButton::GetFaceId()
{
	long result;
	InvokeHelper(0x60050003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetFaceId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarButton::PasteFace()
{
	InvokeHelper(0x60050005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CommandBarButton::GetShortcutText()
{
	CString result;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetShortcutText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarButton::GetState()
{
	long result;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetStyle()
{
	long result;
	InvokeHelper(0x6005000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup operations

LPDISPATCH CommandBarPopup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarPopup::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBarPopup::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CommandBarPopup::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarPopup::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void CommandBarPopup::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString CommandBarPopup::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CommandBarPopup::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CommandBarPopup::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarPopup::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarPopup::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarPopup::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarPopup::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarPopup::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long CommandBarPopup::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarPopup::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarPopup::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString CommandBarPopup::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarPopup::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarPopup::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CommandBarPopup::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CommandBarPopup::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarPopup::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarPopup::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBarPopup::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH CommandBarPopup::GetCommandBar()
{
	LPDISPATCH result;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarPopup::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x60050001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetOLEMenuGroup()
{
	long result;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetOLEMenuGroup(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarComboBox properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarComboBox operations

LPDISPATCH CommandBarComboBox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarComboBox::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarComboBox::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBarComboBox::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CommandBarComboBox::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarComboBox::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void CommandBarComboBox::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString CommandBarComboBox::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CommandBarComboBox::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CommandBarComboBox::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarComboBox::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarComboBox::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarComboBox::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarComboBox::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarComboBox::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarComboBox::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long CommandBarComboBox::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarComboBox::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarComboBox::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarComboBox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString CommandBarComboBox::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarComboBox::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarComboBox::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarComboBox::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CommandBarComboBox::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CommandBarComboBox::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBarComboBox::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarComboBox::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CommandBarComboBox::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CommandBarComboBox::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarComboBox::AddItem(LPCTSTR Text, const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60050000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text, &Index);
}

void CommandBarComboBox::Clear()
{
	InvokeHelper(0x60050001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarComboBox::GetDropDownLines()
{
	long result;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetDropDownLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarComboBox::GetDropDownWidth()
{
	long result;
	InvokeHelper(0x60050004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetDropDownWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarComboBox::GetList(long Index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Index);
	return result;
}

void CommandBarComboBox::SetList(long Index, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, lpszNewValue);
}

long CommandBarComboBox::GetListCount()
{
	long result;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarComboBox::GetListHeaderCount()
{
	long result;
	InvokeHelper(0x60050009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetListHeaderCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarComboBox::GetListIndex()
{
	long result;
	InvokeHelper(0x6005000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetListIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarComboBox::RemoveItem(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

long CommandBarComboBox::GetStyle()
{
	long result;
	InvokeHelper(0x6005000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarComboBox::GetText()
{
	CString result;
	InvokeHelper(0x60050010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarComboBox::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Adjustments properties

/////////////////////////////////////////////////////////////////////////////
// Adjustments operations

LPDISPATCH Adjustments::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Adjustments::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Adjustments::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Adjustments::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float Adjustments::GetItem(long Index)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		Index);
	return result;
}

void Adjustments::SetItem(long Index, float newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_R4;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CalloutFormat properties

/////////////////////////////////////////////////////////////////////////////
// CalloutFormat operations

LPDISPATCH CalloutFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CalloutFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CalloutFormat::AutomaticLength()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CalloutFormat::CustomDrop(float Drop)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Drop);
}

void CalloutFormat::CustomLength(float Length)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Length);
}

void CalloutFormat::PresetDrop(long DropType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DropType);
}

long CalloutFormat::GetAccent()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAccent(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAngle()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAngle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAutoAttach()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetAutoAttach(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CalloutFormat::GetAutoLength()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetBorder()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetBorder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float CalloutFormat::GetDrop()
{
	float result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetDropType()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float CalloutFormat::GetGap()
{
	float result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetGap(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CalloutFormat::GetLength()
{
	float result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long CalloutFormat::GetType()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CalloutFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ColorFormat properties

/////////////////////////////////////////////////////////////////////////////
// ColorFormat operations

LPDISPATCH ColorFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ColorFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ColorFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ColorFormat::GetRgb()
{
	long result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ColorFormat::SetRgb(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ColorFormat::GetSchemeColor()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ColorFormat::SetSchemeColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ColorFormat::GetType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat properties

/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat operations

LPDISPATCH ConnectorFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ConnectorFormat::BeginConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectedShape, ConnectionSite);
}

void ConnectorFormat::BeginDisconnect()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ConnectorFormat::EndConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ConnectedShape, ConnectionSite);
}

void ConnectorFormat::EndDisconnect()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long ConnectorFormat::GetBeginConnected()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetBeginConnectedShape()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetBeginConnectionSite()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetEndConnected()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ConnectorFormat::GetEndConnectedShape()
{
	LPDISPATCH result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetEndConnectionSite()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ConnectorFormat::GetType()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ConnectorFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// FillFormat properties

/////////////////////////////////////////////////////////////////////////////
// FillFormat operations

LPDISPATCH FillFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FillFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FillFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::Background()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FillFormat::OneColorGradient(long Style, long Variant, float Degree)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant, Degree);
}

void FillFormat::Patterned(long Pattern)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Pattern);
}

void FillFormat::PresetGradient(long Style, long Variant, long PresetGradientType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant, PresetGradientType);
}

void FillFormat::PresetTextured(long PresetTexture)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetTexture);
}

void FillFormat::Solid()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FillFormat::TwoColorGradient(long Style, long Variant)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Style, Variant);
}

void FillFormat::UserPicture(LPCTSTR PictureFile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PictureFile);
}

void FillFormat::UserTextured(LPCTSTR TextureFile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 TextureFile);
}

LPDISPATCH FillFormat::GetBackColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::SetBackColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH FillFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FillFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long FillFormat::GetGradientColorType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float FillFormat::GetGradientDegree()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetGradientStyle()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetGradientVariant()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPattern()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPresetGradientType()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetPresetTexture()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString FillFormat::GetTextureName()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long FillFormat::GetTextureType()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float FillFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void FillFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long FillFormat::GetType()
{
	long result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long FillFormat::GetVisible()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FillFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder properties

/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder operations

LPDISPATCH FreeformBuilder::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FreeformBuilder::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FreeformBuilder::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FreeformBuilder::AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
}

LPDISPATCH FreeformBuilder::ConvertToShape()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// GroupShapes properties

/////////////////////////////////////////////////////////////////////////////
// GroupShapes operations

LPDISPATCH GroupShapes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GroupShapes::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GroupShapes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GroupShapes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GroupShapes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN GroupShapes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// LineFormat properties

/////////////////////////////////////////////////////////////////////////////
// LineFormat operations

LPDISPATCH LineFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long LineFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH LineFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH LineFormat::GetBackColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBackColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetBeginArrowheadLength()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetBeginArrowheadStyle()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetBeginArrowheadWidth()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetBeginArrowheadWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetDashStyle()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetDashStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadLength()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadStyle()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetEndArrowheadWidth()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetEndArrowheadWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH LineFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void LineFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetPattern()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetPattern(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long LineFormat::GetStyle()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float LineFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long LineFormat::GetVisible()
{
	long result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float LineFormat::GetWeight()
{
	float result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void LineFormat::SetWeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// ShapeNode properties

/////////////////////////////////////////////////////////////////////////////
// ShapeNode operations

LPDISPATCH ShapeNode::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNode::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetEditingType()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT ShapeNode::GetPoints()
{
	VARIANT result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long ShapeNode::GetSegmentType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ShapeNodes properties

/////////////////////////////////////////////////////////////////////////////
// ShapeNodes operations

LPDISPATCH ShapeNodes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNodes::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNodes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeNodes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeNodes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN ShapeNodes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void ShapeNodes::Delete(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void ShapeNodes::Insert(long Index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
}

void ShapeNodes::SetEditingType(long Index, long EditingType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, EditingType);
}

void ShapeNodes::SetPosition(long Index, float X1, float Y1)
{
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, X1, Y1);
}

void ShapeNodes::SetSegmentType(long Index, long SegmentType)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, SegmentType);
}


/////////////////////////////////////////////////////////////////////////////
// PictureFormat properties

/////////////////////////////////////////////////////////////////////////////
// PictureFormat operations

LPDISPATCH PictureFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PictureFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PictureFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void PictureFormat::IncrementBrightness(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void PictureFormat::IncrementContrast(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

float PictureFormat::GetBrightness()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetBrightness(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long PictureFormat::GetColorType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetColorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float PictureFormat::GetContrast()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetContrast(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropBottom()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropBottom(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropLeft()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropRight()
{
	float result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropRight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float PictureFormat::GetCropTop()
{
	float result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetCropTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long PictureFormat::GetTransparencyColor()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetTransparencyColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long PictureFormat::GetTransparentBackground()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PictureFormat::SetTransparentBackground(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ShadowFormat properties

/////////////////////////////////////////////////////////////////////////////
// ShadowFormat operations

LPDISPATCH ShadowFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShadowFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShadowFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShadowFormat::IncrementOffsetX(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShadowFormat::IncrementOffsetY(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

LPDISPATCH ShadowFormat::GetForeColor()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetForeColor(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShadowFormat::GetObscured()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetObscured(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float ShadowFormat::GetOffsetX()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetOffsetX(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ShadowFormat::GetOffsetY()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetOffsetY(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ShadowFormat::GetTransparency()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetTransparency(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShadowFormat::GetType()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ShadowFormat::GetVisible()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShadowFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Shape properties

/////////////////////////////////////////////////////////////////////////////
// Shape operations

LPDISPATCH Shape::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::Apply()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::Delete()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shape::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::Flip(long FlipCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FlipCmd);
}

void Shape::IncrementLeft(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::IncrementRotation(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::IncrementTop(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void Shape::PickUp()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::RerouteConnections()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Shape::ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void Shape::ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void Shape::Select(const VARIANT& Replace)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Replace);
}

void Shape::SetShapesDefaultProperties()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shape::Ungroup()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Shape::ZOrder(long ZOrderCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ZOrderCmd);
}

LPDISPATCH Shape::GetAdjustments()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetAutoShapeType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetAutoShapeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Shape::GetBlackWhiteMode()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetBlackWhiteMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH Shape::GetCallout()
{
	LPDISPATCH result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetConnectionSiteCount()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Shape::GetConnector()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetConnectorFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetFill()
{
	LPDISPATCH result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetGroupItems()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetHeight()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetHorizontalFlip()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float Shape::GetLeft()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Shape::GetLine()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shape::GetLockAspectRatio()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetLockAspectRatio(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Shape::GetName()
{
	CString result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Shape::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH Shape::GetNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetRotation()
{
	float result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetRotation(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH Shape::GetPictureFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetShadow()
{
	LPDISPATCH result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTextEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetTextFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shape::GetThreeD()
{
	LPDISPATCH result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float Shape::GetTop()
{
	float result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetType()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Shape::GetVerticalFlip()
{
	long result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Shape::GetVertices()
{
	VARIANT result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long Shape::GetVisible()
{
	long result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Shape::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float Shape::GetWidth()
{
	float result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void Shape::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Shape::GetZOrderPosition()
{
	long result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ShapeRange properties

/////////////////////////////////////////////////////////////////////////////
// ShapeRange operations

LPDISPATCH ShapeRange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN ShapeRange::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void ShapeRange::Align(long AlignCmd, long RelativeTo)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AlignCmd, RelativeTo);
}

void ShapeRange::Apply()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Delete()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::Distribute(long DistributeCmd, long RelativeTo)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DistributeCmd, RelativeTo);
}

LPDISPATCH ShapeRange::Duplicate()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::Flip(long FlipCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FlipCmd);
}

void ShapeRange::IncrementLeft(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShapeRange::IncrementRotation(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ShapeRange::IncrementTop(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

LPDISPATCH ShapeRange::Group()
{
	LPDISPATCH result;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::PickUp()
{
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH ShapeRange::Regroup()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::RerouteConnections()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ShapeRange::ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void ShapeRange::ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
{
	static BYTE parms[] =
		VTS_R4 VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Factor, RelativeToOriginalSize, fScale);
}

void ShapeRange::Select(const VARIANT& Replace)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Replace);
}

void ShapeRange::SetShapesDefaultProperties()
{
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH ShapeRange::Ungroup()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ShapeRange::ZOrder(long ZOrderCmd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ZOrderCmd);
}

LPDISPATCH ShapeRange::GetAdjustments()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetAutoShapeType()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetAutoShapeType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ShapeRange::GetBlackWhiteMode()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetBlackWhiteMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH ShapeRange::GetCallout()
{
	LPDISPATCH result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetConnectionSiteCount()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetConnector()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetConnectorFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetFill()
{
	LPDISPATCH result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetGroupItems()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetHeight()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetHorizontalFlip()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetLeft()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ShapeRange::GetLine()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetLockAspectRatio()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetLockAspectRatio(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString ShapeRange::GetName()
{
	CString result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH ShapeRange::GetNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetRotation()
{
	float result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetRotation(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ShapeRange::GetPictureFormat()
{
	LPDISPATCH result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetShadow()
{
	LPDISPATCH result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTextEffect()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetTextFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ShapeRange::GetThreeD()
{
	LPDISPATCH result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float ShapeRange::GetTop()
{
	float result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetType()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetVerticalFlip()
{
	long result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT ShapeRange::GetVertices()
{
	VARIANT result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long ShapeRange::GetVisible()
{
	long result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float ShapeRange::GetWidth()
{
	float result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ShapeRange::SetWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ShapeRange::GetZOrderPosition()
{
	long result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Shapes properties

/////////////////////////////////////////////////////////////////////////////
// Shapes operations

LPDISPATCH Shapes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shapes::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Shapes::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN Shapes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::AddCallout(long Type, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, BeginX, BeginY, EndX, EndY);
	return result;
}

LPDISPATCH Shapes::AddCurve(const VARIANT& SafeArrayOfPoints)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SafeArrayOfPoints);
	return result;
}

LPDISPATCH Shapes::AddLabel(long Orientation, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Orientation, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddLine(float BeginX, float BeginY, float EndX, float EndY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		BeginX, BeginY, EndX, EndY);
	return result;
}

LPDISPATCH Shapes::AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddPolyline(const VARIANT& SafeArrayOfPoints)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SafeArrayOfPoints);
	return result;
}

LPDISPATCH Shapes::AddShape(long Type, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
	return result;
}

LPDISPATCH Shapes::AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Orientation, Left, Top, Width, Height);
	return result;
}

LPDISPATCH Shapes::BuildFreeform(long EditingType, float X1, float Y1)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_R4 VTS_R4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		EditingType, X1, Y1);
	return result;
}

LPDISPATCH Shapes::Range(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Shapes::SelectAll()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shapes::GetBackground()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Shapes::GetDefault()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat properties

/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat operations

LPDISPATCH TextEffectFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextEffectFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextEffectFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::ToggleVerticalText()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long TextEffectFormat::GetAlignment()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetFontBold()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontBold(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetFontItalic()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontItalic(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString TextEffectFormat::GetFontName()
{
	CString result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float TextEffectFormat::GetFontSize()
{
	float result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetFontSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long TextEffectFormat::GetKernedPairs()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetKernedPairs(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetNormalizedHeight()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetNormalizedHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetPresetShape()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetPresetShape(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetPresetTextEffect()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetPresetTextEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long TextEffectFormat::GetRotatedChars()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetRotatedChars(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString TextEffectFormat::GetText()
{
	CString result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float TextEffectFormat::GetTracking()
{
	float result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextEffectFormat::SetTracking(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// TextFrame properties

/////////////////////////////////////////////////////////////////////////////
// TextFrame operations

LPDISPATCH TextFrame::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long TextFrame::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH TextFrame::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

float TextFrame::GetMarginBottom()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginBottom(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginLeft()
{
	float result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginLeft(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginRight()
{
	float result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginRight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float TextFrame::GetMarginTop()
{
	float result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetMarginTop(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long TextFrame::GetOrientation()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void TextFrame::SetOrientation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat properties

/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat operations

LPDISPATCH ThreeDFormat::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ThreeDFormat::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::IncrementRotationX(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ThreeDFormat::IncrementRotationY(float Increment)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Increment);
}

void ThreeDFormat::ResetRotation()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ThreeDFormat::SetThreeDFormat(long PresetThreeDFormat)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetThreeDFormat);
}

void ThreeDFormat::SetExtrusionDirection(long PresetExtrusionDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PresetExtrusionDirection);
}

float ThreeDFormat::GetDepth()
{
	float result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetDepth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH ThreeDFormat::GetExtrusionColor()
{
	LPDISPATCH result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetExtrusionColorType()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetExtrusionColorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPerspective()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPerspective(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetExtrusionDirection()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ThreeDFormat::GetPresetLightingDirection()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetLightingDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetLightingSoftness()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetLightingSoftness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetMaterial()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetPresetMaterial(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long ThreeDFormat::GetPresetThreeDFormat()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float ThreeDFormat::GetRotationX()
{
	float result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetRotationX(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float ThreeDFormat::GetRotationY()
{
	float result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetRotationY(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long ThreeDFormat::GetVisible()
{
	long result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ThreeDFormat::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Assistant properties

/////////////////////////////////////////////////////////////////////////////
// Assistant operations

LPDISPATCH Assistant::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Assistant::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Assistant::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Assistant::Move(long xLeft, long yTop)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 xLeft, yTop);
}

void Assistant::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Assistant::GetTop()
{
	long result;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Assistant::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Assistant::GetLeft()
{
	long result;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Assistant::Help()
{
	InvokeHelper(0x60030006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Assistant::StartWizard(BOOL On, LPCTSTR Callback, long PrivateX, const VARIANT& Animation, const VARIANT& CustomTeaser, const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right)
{
	long result;
	static BYTE parms[] =
		VTS_BOOL VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030007, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		On, Callback, PrivateX, &Animation, &CustomTeaser, &Top, &Left, &Bottom, &Right);
	return result;
}

void Assistant::EndWizard(long WizardID, BOOL varfSuccess, const VARIANT& Animation)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL VTS_VARIANT;
	InvokeHelper(0x60030008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 WizardID, varfSuccess, &Animation);
}

void Assistant::ActivateWizard(long WizardID, long act, const VARIANT& Animation)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x60030009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 WizardID, act, &Animation);
}

void Assistant::ResetTips()
{
	InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Assistant::GetNewBalloon()
{
	LPDISPATCH result;
	InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Assistant::GetBalloonError()
{
	long result;
	InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL Assistant::GetVisible()
{
	BOOL result;
	InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long Assistant::GetAnimation()
{
	long result;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Assistant::SetAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Assistant::GetReduced()
{
	BOOL result;
	InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetReduced(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void Assistant::SetAssistWithHelp(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetAssistWithHelp()
{
	BOOL result;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetAssistWithWizards(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetAssistWithWizards()
{
	BOOL result;
	InvokeHelper(0x60030015, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetAssistWithAlerts(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetAssistWithAlerts()
{
	BOOL result;
	InvokeHelper(0x60030017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetMoveWhenInTheWay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetMoveWhenInTheWay()
{
	BOOL result;
	InvokeHelper(0x60030019, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetSounds(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetSounds()
{
	BOOL result;
	InvokeHelper(0x6003001b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetFeatureTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetFeatureTips()
{
	BOOL result;
	InvokeHelper(0x6003001d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetMouseTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetMouseTips()
{
	BOOL result;
	InvokeHelper(0x6003001f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetKeyboardShortcutTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetKeyboardShortcutTips()
{
	BOOL result;
	InvokeHelper(0x60030021, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetHighPriorityTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetHighPriorityTips()
{
	BOOL result;
	InvokeHelper(0x60030023, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetTipOfDay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetTipOfDay()
{
	BOOL result;
	InvokeHelper(0x60030025, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetGuessHelp(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetGuessHelp()
{
	BOOL result;
	InvokeHelper(0x60030027, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Assistant::SetSearchWhenProgramming(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Assistant::GetSearchWhenProgramming()
{
	BOOL result;
	InvokeHelper(0x60030029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString Assistant::GetItem()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString Assistant::GetFileName()
{
	CString result;
	InvokeHelper(0x6003002c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Assistant::SetFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6003002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Assistant::GetName()
{
	CString result;
	InvokeHelper(0x6003002e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Balloon properties

/////////////////////////////////////////////////////////////////////////////
// Balloon operations

LPDISPATCH Balloon::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Balloon::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Balloon::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Balloon::GetCheckboxes()
{
	LPDISPATCH result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Balloon::GetLabels()
{
	LPDISPATCH result;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Balloon::SetBalloonType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetBalloonType()
{
	long result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetIcon(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetIcon()
{
	long result;
	InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetHeading(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Balloon::GetHeading()
{
	CString result;
	InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Balloon::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Balloon::GetText()
{
	CString result;
	InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Balloon::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetMode()
{
	long result;
	InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetAnimation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetAnimation()
{
	long result;
	InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetButton(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetButton()
{
	long result;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetCallback(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Balloon::GetCallback()
{
	CString result;
	InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Balloon::SetPrivate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Balloon::GetPrivate()
{
	long result;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::SetAvoidRectangle(long Left, long Top, long Right, long Bottom)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x60030015, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Left, Top, Right, Bottom);
}

CString Balloon::GetName()
{
	CString result;
	InvokeHelper(0x60030016, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Balloon::Show()
{
	long result;
	InvokeHelper(0x60030017, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void Balloon::Close()
{
	InvokeHelper(0x60030018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// BalloonCheckboxes properties

/////////////////////////////////////////////////////////////////////////////
// BalloonCheckboxes operations

LPDISPATCH BalloonCheckboxes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BalloonCheckboxes::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString BalloonCheckboxes::GetName()
{
	CString result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonCheckboxes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonCheckboxes::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

long BalloonCheckboxes::GetCount()
{
	long result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BalloonCheckboxes::SetCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPUNKNOWN BalloonCheckboxes::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// BalloonCheckbox properties

/////////////////////////////////////////////////////////////////////////////
// BalloonCheckbox operations

LPDISPATCH BalloonCheckbox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BalloonCheckbox::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString BalloonCheckbox::GetItem()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString BalloonCheckbox::GetName()
{
	CString result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonCheckbox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void BalloonCheckbox::SetChecked(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL BalloonCheckbox::GetChecked()
{
	BOOL result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void BalloonCheckbox::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString BalloonCheckbox::GetText()
{
	CString result;
	InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// BalloonLabels properties

/////////////////////////////////////////////////////////////////////////////
// BalloonLabels operations

LPDISPATCH BalloonLabels::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BalloonLabels::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString BalloonLabels::GetName()
{
	CString result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonLabels::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonLabels::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

long BalloonLabels::GetCount()
{
	long result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void BalloonLabels::SetCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPUNKNOWN BalloonLabels::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// BalloonLabel properties

/////////////////////////////////////////////////////////////////////////////
// BalloonLabel operations

LPDISPATCH BalloonLabel::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long BalloonLabel::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString BalloonLabel::GetItem()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString BalloonLabel::GetName()
{
	CString result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH BalloonLabel::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void BalloonLabel::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString BalloonLabel::GetText()
{
	CString result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IFoundFiles properties

/////////////////////////////////////////////////////////////////////////////
// IFoundFiles operations

CString IFoundFiles::GetItem(long Index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Index);
	return result;
}

long IFoundFiles::GetCount()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IFind properties

/////////////////////////////////////////////////////////////////////////////
// IFind operations

CString IFind::GetSearchPath()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IFind::GetName()
{
	CString result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IFind::GetSubDir()
{
	BOOL result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IFind::GetTitle()
{
	CString result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IFind::GetAuthor()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IFind::GetKeywords()
{
	CString result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IFind::GetSubject()
{
	CString result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IFind::GetOptions()
{
	long result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IFind::GetMatchCase()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IFind::GetText()
{
	CString result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IFind::GetPatternMatch()
{
	BOOL result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT IFind::GetDateSavedFrom()
{
	VARIANT result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IFind::GetDateSavedTo()
{
	VARIANT result;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

CString IFind::GetSavedBy()
{
	CString result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IFind::GetDateCreatedFrom()
{
	VARIANT result;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IFind::GetDateCreatedTo()
{
	VARIANT result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long IFind::GetView()
{
	long result;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IFind::GetSortBy()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IFind::GetListBy()
{
	long result;
	InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IFind::GetSelectedFile()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IFind::GetResults()
{
	LPDISPATCH result;
	InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IFind::Show()
{
	long result;
	InvokeHelper(0x60020015, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void IFind::SetSearchPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetSubDir(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IFind::SetTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetAuthor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetKeywords(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IFind::SetMatchCase(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IFind::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetPatternMatch(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IFind::SetDateSavedFrom(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IFind::SetDateSavedTo(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IFind::SetSavedBy(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IFind::SetDateCreatedFrom(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IFind::SetDateCreatedTo(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IFind::SetView(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IFind::SetSortBy(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IFind::SetListBy(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IFind::SetSelectedFile(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IFind::Execute()
{
	InvokeHelper(0x6002002a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IFind::Load(LPCTSTR bstrQueryName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrQueryName);
}

void IFind::Save(LPCTSTR bstrQueryName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrQueryName);
}

void IFind::Delete(LPCTSTR bstrQueryName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrQueryName);
}

long IFind::GetFileType()
{
	long result;
	InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IFind::SetFileType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// FoundFiles properties

/////////////////////////////////////////////////////////////////////////////
// FoundFiles operations

LPDISPATCH FoundFiles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FoundFiles::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString FoundFiles::GetItem(long Index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Index);
	return result;
}

long FoundFiles::GetCount()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN FoundFiles::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PropertyTest properties

/////////////////////////////////////////////////////////////////////////////
// PropertyTest operations

LPDISPATCH PropertyTest::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PropertyTest::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString PropertyTest::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long PropertyTest::GetCondition()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT PropertyTest::GetValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT PropertyTest::GetSecondValue()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long PropertyTest::GetConnector()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// PropertyTests properties

/////////////////////////////////////////////////////////////////////////////
// PropertyTests operations

LPDISPATCH PropertyTests::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PropertyTests::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyTests::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

long PropertyTests::GetCount()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void PropertyTests::Add(LPCTSTR Name, long Condition, const VARIANT& Value, const VARIANT& SecondValue, long Connector)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, Condition, &Value, &SecondValue, Connector);
}

void PropertyTests::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

LPUNKNOWN PropertyTests::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileSearch properties

/////////////////////////////////////////////////////////////////////////////
// FileSearch operations

LPDISPATCH FileSearch::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FileSearch::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL FileSearch::GetSearchSubFolders()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FileSearch::SetSearchSubFolders(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL FileSearch::GetMatchTextExactly()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FileSearch::SetMatchTextExactly(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL FileSearch::GetMatchAllWordForms()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FileSearch::SetMatchAllWordForms(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString FileSearch::GetFileName()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileSearch::SetFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long FileSearch::GetFileType()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileSearch::SetFileType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long FileSearch::GetLastModified()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void FileSearch::SetLastModified(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString FileSearch::GetTextOrProperty()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileSearch::SetTextOrProperty(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FileSearch::GetLookIn()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FileSearch::SetLookIn(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long FileSearch::Execute(long SortBy, long SortOrder, BOOL AlwaysAccurate)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		SortBy, SortOrder, AlwaysAccurate);
	return result;
}

void FileSearch::NewSearch()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH FileSearch::GetFoundFiles()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FileSearch::GetPropertyTests()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
