// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "mso9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace mso09 {

/////////////////////////////////////////////////////////////////////////////
// _CommandBars properties

/////////////////////////////////////////////////////////////////////////////
// _CommandBars operations

LPDISPATCH _CommandBars::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _CommandBars::GetCreator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBars::GetActionControl()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBars::GetActiveMenuBar()
{
	LPDISPATCH result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBars::Add(const VARIANT& Name, const VARIANT& Position, const VARIANT& MenuBar, const VARIANT& Temporary)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Position, &MenuBar, &Temporary);
	return result;
}

long _CommandBars::GetCount()
{
	long result;
	InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBars::GetDisplayTooltips()
{
	BOOL result;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetDisplayTooltips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _CommandBars::GetDisplayKeysInTooltips()
{
	BOOL result;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetDisplayKeysInTooltips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _CommandBars::FindControl(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Id, &Tag, &Visible);
	return result;
}

LPDISPATCH _CommandBars::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

BOOL _CommandBars::GetLargeButtons()
{
	BOOL result;
	InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetLargeButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6003000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _CommandBars::GetMenuAnimationStyle()
{
	long result;
	InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetMenuAnimationStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPUNKNOWN _CommandBars::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBars::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _CommandBars::ReleaseFocus()
{
	InvokeHelper(0x60030010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _CommandBars::GetAdaptiveMenus()
{
	BOOL result;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetAdaptiveMenus(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _CommandBars::FindControls(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60030015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Id, &Tag, &Visible);
	return result;
}

BOOL _CommandBars::GetDisplayFonts()
{
	BOOL result;
	InvokeHelper(0x60030017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBars::SetDisplayFonts(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60030017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBar::GetAdaptiveMenu()
{
	BOOL result;
	InvokeHelper(0x60040022, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetAdaptiveMenu(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarControl::GetIsPriorityDropped()
{
	BOOL result;
	InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _CommandBarButton properties

/////////////////////////////////////////////////////////////////////////////
// _CommandBarButton operations

LPDISPATCH _CommandBarButton::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _CommandBarButton::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarButton::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _CommandBarButton::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _CommandBarButton::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarButton::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void _CommandBarButton::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString _CommandBarButton::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _CommandBarButton::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _CommandBarButton::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CommandBarButton::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarButton::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarButton::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarButton::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarButton::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBarButton::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long _CommandBarButton::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarButton::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarButton::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarButton::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _CommandBarButton::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarButton::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _CommandBarButton::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _CommandBarButton::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _CommandBarButton::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _CommandBarButton::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarButton::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarButton::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarButton::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _CommandBarButton::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _CommandBarButton::GetIsPriorityDropped()
{
	BOOL result;
	InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarButton::GetBuiltInFace()
{
	BOOL result;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetBuiltInFace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _CommandBarButton::CopyFace()
{
	InvokeHelper(0x60050002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CommandBarButton::GetFaceId()
{
	long result;
	InvokeHelper(0x60050003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetFaceId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _CommandBarButton::PasteFace()
{
	InvokeHelper(0x60050005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _CommandBarButton::GetShortcutText()
{
	CString result;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetShortcutText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarButton::GetState()
{
	long result;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarButton::GetStyle()
{
	long result;
	InvokeHelper(0x6005000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarButton::GetHyperlinkType()
{
	long result;
	InvokeHelper(0x6005000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarButton::SetHyperlinkType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
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

BOOL CommandBarPopup::GetIsPriorityDropped()
{
	BOOL result;
	InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
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
// _CommandBarComboBox properties

/////////////////////////////////////////////////////////////////////////////
// _CommandBarComboBox operations

LPDISPATCH _CommandBarComboBox::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _CommandBarComboBox::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarComboBox::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _CommandBarComboBox::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _CommandBarComboBox::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarComboBox::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void _CommandBarComboBox::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString _CommandBarComboBox::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _CommandBarComboBox::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _CommandBarComboBox::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CommandBarComboBox::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarComboBox::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarComboBox::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarComboBox::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarComboBox::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBarComboBox::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long _CommandBarComboBox::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarComboBox::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarComboBox::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarComboBox::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _CommandBarComboBox::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarComboBox::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _CommandBarComboBox::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _CommandBarComboBox::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _CommandBarComboBox::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _CommandBarComboBox::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarComboBox::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarComboBox::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarComboBox::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _CommandBarComboBox::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _CommandBarComboBox::GetIsPriorityDropped()
{
	BOOL result;
	InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::AddItem(LPCTSTR Text, const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60050000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text, &Index);
}

void _CommandBarComboBox::Clear()
{
	InvokeHelper(0x60050001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CommandBarComboBox::GetDropDownLines()
{
	long result;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetDropDownLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarComboBox::GetDropDownWidth()
{
	long result;
	InvokeHelper(0x60050004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetDropDownWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarComboBox::GetList(long Index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Index);
	return result;
}

void _CommandBarComboBox::SetList(long Index, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, lpszNewValue);
}

long _CommandBarComboBox::GetListCount()
{
	long result;
	InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarComboBox::GetListHeaderCount()
{
	long result;
	InvokeHelper(0x60050009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetListHeaderCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60050009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarComboBox::GetListIndex()
{
	long result;
	InvokeHelper(0x6005000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetListIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _CommandBarComboBox::RemoveItem(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

long _CommandBarComboBox::GetStyle()
{
	long result;
	InvokeHelper(0x6005000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6005000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarComboBox::GetText()
{
	CString result;
	InvokeHelper(0x60050010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarComboBox::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _CommandBarActiveX properties

/////////////////////////////////////////////////////////////////////////////
// _CommandBarActiveX operations

LPDISPATCH _CommandBarActiveX::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _CommandBarActiveX::GetCreator()
{
	long result;
	InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarActiveX::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _CommandBarActiveX::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _CommandBarActiveX::GetCaption()
{
	CString result;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarActiveX::Copy(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

void _CommandBarActiveX::Delete(const VARIANT& Temporary)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Temporary);
}

CString _CommandBarActiveX::GetDescriptionText()
{
	CString result;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetDescriptionText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _CommandBarActiveX::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _CommandBarActiveX::Execute()
{
	InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CommandBarActiveX::GetHeight()
{
	long result;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CommandBarActiveX::GetHelpContextId()
{
	long result;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetHelpContextId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarActiveX::GetHelpFile()
{
	CString result;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarActiveX::GetId()
{
	long result;
	InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarActiveX::GetIndex()
{
	long result;
	InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CommandBarActiveX::Move(const VARIANT& Bar, const VARIANT& Before)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Bar, &Before);
	return result;
}

long _CommandBarActiveX::GetLeft()
{
	long result;
	InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarActiveX::GetOLEUsage()
{
	long result;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetOLEUsage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _CommandBarActiveX::GetOnAction()
{
	CString result;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetOnAction(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _CommandBarActiveX::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _CommandBarActiveX::GetParameter()
{
	CString result;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetParameter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarActiveX::GetPriority()
{
	long result;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _CommandBarActiveX::Reset()
{
	InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _CommandBarActiveX::SetFocus()
{
	InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _CommandBarActiveX::GetTag()
{
	CString result;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetTag(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _CommandBarActiveX::GetTooltipText()
{
	CString result;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetTooltipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _CommandBarActiveX::GetTop()
{
	long result;
	InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CommandBarActiveX::GetType()
{
	long result;
	InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _CommandBarActiveX::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _CommandBarActiveX::GetWidth()
{
	long result;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _CommandBarActiveX::GetIsPriorityDropped()
{
	BOOL result;
	InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _CommandBarActiveX::GetControlCLSID()
{
	CString result;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _CommandBarActiveX::SetControlCLSID(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPUNKNOWN _CommandBarActiveX::GetQueryControlInterface(LPCTSTR bstrIid)
{
	LPUNKNOWN result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, parms,
		bstrIid);
	return result;
}

void _CommandBarActiveX::SetInnerObjectFactory(LPUNKNOWN pUnk)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x60050003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pUnk);
}

void _CommandBarActiveX::EnsureControl()
{
	InvokeHelper(0x60050004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _CommandBarActiveX::SetInitWith(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x60050005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}
}