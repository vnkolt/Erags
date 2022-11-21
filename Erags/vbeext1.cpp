// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "vbeext1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace VBEEXT1 {

/////////////////////////////////////////////////////////////////////////////
// Application properties

/////////////////////////////////////////////////////////////////////////////
// Application operations

CString Application::GetVersion()
{
	CString result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// VBE properties

/////////////////////////////////////////////////////////////////////////////
// VBE operations

CString VBE::GetVersion()
{
	CString result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetVBProjects()
{
	LPDISPATCH result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetCodePanes()
{
	LPDISPATCH result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetEvents()
{
	LPDISPATCH result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetActiveVBProject()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void VBE::SetRefActiveVBProject(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH VBE::GetSelectedVBComponent()
{
	LPDISPATCH result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetMainWindow()
{
	LPDISPATCH result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetActiveWindow()
{
	LPDISPATCH result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH VBE::GetActiveCodePane()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void VBE::SetRefActiveCodePane(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// Window properties

/////////////////////////////////////////////////////////////////////////////
// Window operations

LPDISPATCH Window::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Window::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Window::Close()
{
	InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Window::GetCaption()
{
	CString result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL Window::GetVisible()
{
	BOOL result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Window::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long Window::GetLeft()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Window::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Window::GetTop()
{
	long result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Window::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Window::GetWidth()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Window::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Window::GetHeight()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Window::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Window::GetWindowState()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Window::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Window::SetFocus()
{
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Window::GetType()
{
	long result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Window::GetLinkedWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Window::GetLinkedWindowFrame()
{
	LPDISPATCH result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Windows properties

/////////////////////////////////////////////////////////////////////////////
// _Windows operations

LPDISPATCH _Windows::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Windows::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Windows::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long _Windows::GetCount()
{
	long result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _LinkedWindows properties

/////////////////////////////////////////////////////////////////////////////
// _LinkedWindows operations

LPDISPATCH _LinkedWindows::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _LinkedWindows::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long _LinkedWindows::GetCount()
{
	long result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _LinkedWindows::Remove(LPDISPATCH Window)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Window);
}

void _LinkedWindows::Add(LPDISPATCH Window)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Window);
}


/////////////////////////////////////////////////////////////////////////////
// Events properties

/////////////////////////////////////////////////////////////////////////////
// Events operations

LPUNKNOWN Events::GetReferencesEvents(LPDISPATCH VBProject)
{
	LPUNKNOWN result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, parms,
		VBProject);
	return result;
}

LPUNKNOWN Events::GetCommandBarEvents(LPDISPATCH CommandBarControl)
{
	LPUNKNOWN result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, parms,
		CommandBarControl);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _dispVBProjectsEvents properties

/////////////////////////////////////////////////////////////////////////////
// _dispVBProjectsEvents operations

void _dispVBProjectsEvents::ItemAdded(LPDISPATCH VBProject)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBProject);
}

void _dispVBProjectsEvents::ItemRemoved(LPDISPATCH VBProject)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBProject);
}

void _dispVBProjectsEvents::ItemRenamed(LPDISPATCH VBProject, LPCTSTR OldName)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBProject, OldName);
}

void _dispVBProjectsEvents::ItemActivated(LPDISPATCH VBProject)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBProject);
}


/////////////////////////////////////////////////////////////////////////////
// _dispVBComponentsEvents properties

/////////////////////////////////////////////////////////////////////////////
// _dispVBComponentsEvents operations

void _dispVBComponentsEvents::ItemAdded(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}

void _dispVBComponentsEvents::ItemRemoved(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}

void _dispVBComponentsEvents::ItemRenamed(LPDISPATCH VBComponent, LPCTSTR OldName)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent, OldName);
}

void _dispVBComponentsEvents::ItemSelected(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}

void _dispVBComponentsEvents::ItemActivated(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}

void _dispVBComponentsEvents::ItemReloaded(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}


/////////////////////////////////////////////////////////////////////////////
// _dispReferencesEvents properties

/////////////////////////////////////////////////////////////////////////////
// _dispReferencesEvents operations

void _dispReferencesEvents::ItemAdded(LPDISPATCH Reference)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Reference);
}

void _dispReferencesEvents::ItemRemoved(LPDISPATCH Reference)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Reference);
}


/////////////////////////////////////////////////////////////////////////////
// _dispCommandBarControlEvents properties

/////////////////////////////////////////////////////////////////////////////
// _dispCommandBarControlEvents operations

void _dispCommandBarControlEvents::Click(LPDISPATCH CommandBarControl, BOOL* handled, BOOL* CancelDefault)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL VTS_PBOOL;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CommandBarControl, handled, CancelDefault);
}


/////////////////////////////////////////////////////////////////////////////
// _ProjectTemplate properties

/////////////////////////////////////////////////////////////////////////////
// _ProjectTemplate operations


/////////////////////////////////////////////////////////////////////////////
// _VBProject properties

/////////////////////////////////////////////////////////////////////////////
// _VBProject operations

CString _VBProject::GetHelpFile()
{
	CString result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _VBProject::SetHelpFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _VBProject::GetHelpContextID()
{
	long result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _VBProject::SetHelpContextID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _VBProject::GetDescription()
{
	CString result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _VBProject::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _VBProject::GetMode()
{
	long result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBProject::GetReferences()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _VBProject::GetName()
{
	CString result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _VBProject::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _VBProject::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBProject::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _VBProject::GetProtection()
{
	long result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL _VBProject::GetSaved()
{
	BOOL result;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBProject::GetVBComponents()
{
	LPDISPATCH result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _VBProjects properties

/////////////////////////////////////////////////////////////////////////////
// _VBProjects operations

LPDISPATCH _VBProjects::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH _VBProjects::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBProjects::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _VBProjects::GetCount()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// SelectedComponents properties

/////////////////////////////////////////////////////////////////////////////
// SelectedComponents operations

LPDISPATCH SelectedComponents::Item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH SelectedComponents::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SelectedComponents::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SelectedComponents::GetCount()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Components properties

/////////////////////////////////////////////////////////////////////////////
// _Components operations

LPDISPATCH _Components::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Components::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Components::GetCount()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Components::Remove(LPDISPATCH Component)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Component);
}

LPDISPATCH _Components::Add(long ComponentType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ComponentType);
	return result;
}

LPDISPATCH _Components::Import(LPCTSTR FileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName);
	return result;
}

LPDISPATCH _Components::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _VBComponents properties

/////////////////////////////////////////////////////////////////////////////
// _VBComponents operations

LPDISPATCH _VBComponents::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH _VBComponents::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _VBComponents::GetCount()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _VBComponents::Remove(LPDISPATCH VBComponent)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 VBComponent);
}

LPDISPATCH _VBComponents::Add(long ComponentType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ComponentType);
	return result;
}

LPDISPATCH _VBComponents::Import(LPCTSTR FileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName);
	return result;
}

LPDISPATCH _VBComponents::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Component properties

/////////////////////////////////////////////////////////////////////////////
// _Component operations

BOOL _Component::GetIsDirty()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Component::SetIsDirty(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _Component::GetName()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Component::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _VBComponent properties

/////////////////////////////////////////////////////////////////////////////
// _VBComponent operations

BOOL _VBComponent::GetSaved()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _VBComponent::GetName()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _VBComponent::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _VBComponent::GetDesigner()
{
	LPDISPATCH result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBComponent::GetCodeModule()
{
	LPDISPATCH result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _VBComponent::GetType()
{
	long result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _VBComponent::Export(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

LPDISPATCH _VBComponent::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBComponent::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _VBComponent::GetHasOpenDesigner()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBComponent::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _VBComponent::DesignerWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _VBComponent::Activate()
{
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Property properties

/////////////////////////////////////////////////////////////////////////////
// Property operations

VARIANT Property::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Property::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT Property::GetIndexedValue(const VARIANT& Index1, const VARIANT& Index2, const VARIANT& Index3, const VARIANT& Index4)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index1, &Index2, &Index3, &Index4);
	return result;
}

void Property::SetIndexedValue(const VARIANT& Index1, const VARIANT& Index2, const VARIANT& Index3, const VARIANT& Index4, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &Index1, &Index2, &Index3, &Index4, &newValue);
}

short Property::GetNumIndices()
{
	short result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString Property::GetName()
{
	CString result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH Property::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Property::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPUNKNOWN Property::GetObject()
{
	LPUNKNOWN result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Property::SetRefObject(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// _Properties properties

/////////////////////////////////////////////////////////////////////////////
// _Properties operations

LPDISPATCH _Properties::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH _Properties::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Properties::GetCount()
{
	long result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Properties::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _CodeModule properties

/////////////////////////////////////////////////////////////////////////////
// _CodeModule operations

LPDISPATCH _CodeModule::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodeModule::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _CodeModule::AddFromString(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

void _CodeModule::AddFromFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

CString _CodeModule::GetLines(long StartLine, long Count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		StartLine, Count);
	return result;
}

long _CodeModule::GetCountOfLines()
{
	long result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CodeModule::InsertLines(long Line, LPCTSTR String)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Line, String);
}

void _CodeModule::DeleteLines(long StartLine, long Count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StartLine, Count);
}

void _CodeModule::ReplaceLine(long Line, LPCTSTR String)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Line, String);
}

long _CodeModule::GetProcStartLine(LPCTSTR ProcName, long ProcKind)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ProcName, ProcKind);
	return result;
}

long _CodeModule::GetProcCountLines(LPCTSTR ProcName, long ProcKind)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ProcName, ProcKind);
	return result;
}

long _CodeModule::GetProcBodyLine(LPCTSTR ProcName, long ProcKind)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ProcName, ProcKind);
	return result;
}

CString _CodeModule::GetProcOfLine(long Line, long* ProcKind)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_PI4;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Line, ProcKind);
	return result;
}

long _CodeModule::GetCountOfDeclarationLines()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _CodeModule::CreateEventProc(LPCTSTR EventName, LPCTSTR ObjectName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020010, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		EventName, ObjectName);
	return result;
}

BOOL _CodeModule::Find(LPCTSTR Target, long* StartLine, long* StartColumn, long* EndLine, long* EndColumn, BOOL WholeWord, BOOL MatchCase, BOOL PatternSearch)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_BOOL VTS_BOOL VTS_BOOL;
	InvokeHelper(0x60020011, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target, StartLine, StartColumn, EndLine, EndColumn, WholeWord, MatchCase, PatternSearch);
	return result;
}

LPDISPATCH _CodeModule::GetCodePane()
{
	LPDISPATCH result;
	InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _CodePanes properties

/////////////////////////////////////////////////////////////////////////////
// _CodePanes operations

LPDISPATCH _CodePanes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodePanes::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodePanes::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long _CodePanes::GetCount()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN _CodePanes::_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _CodePane properties

/////////////////////////////////////////////////////////////////////////////
// _CodePane operations

LPDISPATCH _CodePane::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodePane::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodePane::GetWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _CodePane::GetSelection(long* StartLine, long* StartColumn, long* EndLine, long* EndColumn)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StartLine, StartColumn, EndLine, EndColumn);
}

void _CodePane::SetSelection(long StartLine, long StartColumn, long EndLine, long EndColumn)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StartLine, StartColumn, EndLine, EndColumn);
}

long _CodePane::GetTopLine()
{
	long result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _CodePane::SetTopLine(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _CodePane::GetCountOfVisibleLines()
{
	long result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _CodePane::GetCodeModule()
{
	LPDISPATCH result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _CodePane::Show()
{
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _CodePane::GetCodePaneView()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _References properties

/////////////////////////////////////////////////////////////////////////////
// _References operations

LPDISPATCH _References::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _References::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _References::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

long _References::GetCount()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN _References::_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH _References::AddFromGuid(LPCTSTR Guid, long Major, long Minor)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Guid, Major, Minor);
	return result;
}

LPDISPATCH _References::AddFromFile(LPCTSTR FileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName);
	return result;
}

void _References::Remove(LPDISPATCH Reference)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Reference);
}


/////////////////////////////////////////////////////////////////////////////
// Reference properties

/////////////////////////////////////////////////////////////////////////////
// Reference operations

LPDISPATCH Reference::GetCollection()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Reference::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Reference::GetName()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString Reference::GetGuid()
{
	CString result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Reference::GetMajor()
{
	long result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Reference::GetMinor()
{
	long result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Reference::GetFullPath()
{
	CString result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL Reference::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Reference::GetIsBroken()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long Reference::GetType()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Reference::GetDescription()
{
	CString result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _dispReferences_Events properties

/////////////////////////////////////////////////////////////////////////////
// _dispReferences_Events operations

void _dispReferences_Events::ItemAdded(LPDISPATCH Reference)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Reference);
}

void _dispReferences_Events::ItemRemoved(LPDISPATCH Reference)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Reference);
}

};