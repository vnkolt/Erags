#include "stdafx.h"
#include "mso8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace mso08 {

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
};