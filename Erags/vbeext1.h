// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Application wrapper class
namespace VBEEXT1 {

class Application : public COleDispatchDriver
{
public:
	Application() {}		// Calls COleDispatchDriver default constructor
	Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Application(const Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetVersion();
};
/////////////////////////////////////////////////////////////////////////////
// VBE wrapper class

class VBE : public COleDispatchDriver
{
public:
	VBE() {}		// Calls COleDispatchDriver default constructor
	VBE(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	VBE(const VBE& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetVersion();
	LPDISPATCH GetVBProjects();
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetCodePanes();
	LPDISPATCH GetWindows();
	LPDISPATCH GetEvents();
	LPDISPATCH GetActiveVBProject();
	void SetRefActiveVBProject(LPDISPATCH newValue);
	LPDISPATCH GetSelectedVBComponent();
	LPDISPATCH GetMainWindow();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetActiveCodePane();
	void SetRefActiveCodePane(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// Window wrapper class

class Window : public COleDispatchDriver
{
public:
	Window() {}		// Calls COleDispatchDriver default constructor
	Window(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Window(const Window& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetVbe();
	LPDISPATCH GetCollection();
	void Close();
	CString GetCaption();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	void SetFocus();
	long GetType();
	LPDISPATCH GetLinkedWindows();
	LPDISPATCH GetLinkedWindowFrame();
};
/////////////////////////////////////////////////////////////////////////////
// _Windows wrapper class

class _Windows : public COleDispatchDriver
{
public:
	_Windows() {}		// Calls COleDispatchDriver default constructor
	_Windows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Windows(const _Windows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetVbe();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// _LinkedWindows wrapper class

class _LinkedWindows : public COleDispatchDriver
{
public:
	_LinkedWindows() {}		// Calls COleDispatchDriver default constructor
	_LinkedWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_LinkedWindows(const _LinkedWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetVbe();
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
	void Remove(LPDISPATCH Window);
	void Add(LPDISPATCH Window);
};
/////////////////////////////////////////////////////////////////////////////
// Events wrapper class

class Events : public COleDispatchDriver
{
public:
	Events() {}		// Calls COleDispatchDriver default constructor
	Events(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Events(const Events& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN GetReferencesEvents(LPDISPATCH VBProject);
	LPUNKNOWN GetCommandBarEvents(LPDISPATCH CommandBarControl);
};
/////////////////////////////////////////////////////////////////////////////
// _dispVBProjectsEvents wrapper class

class _dispVBProjectsEvents : public COleDispatchDriver
{
public:
	_dispVBProjectsEvents() {}		// Calls COleDispatchDriver default constructor
	_dispVBProjectsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_dispVBProjectsEvents(const _dispVBProjectsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void ItemAdded(LPDISPATCH VBProject);
	void ItemRemoved(LPDISPATCH VBProject);
	void ItemRenamed(LPDISPATCH VBProject, LPCTSTR OldName);
	void ItemActivated(LPDISPATCH VBProject);
};
/////////////////////////////////////////////////////////////////////////////
// _dispVBComponentsEvents wrapper class

class _dispVBComponentsEvents : public COleDispatchDriver
{
public:
	_dispVBComponentsEvents() {}		// Calls COleDispatchDriver default constructor
	_dispVBComponentsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_dispVBComponentsEvents(const _dispVBComponentsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void ItemAdded(LPDISPATCH VBComponent);
	void ItemRemoved(LPDISPATCH VBComponent);
	void ItemRenamed(LPDISPATCH VBComponent, LPCTSTR OldName);
	void ItemSelected(LPDISPATCH VBComponent);
	void ItemActivated(LPDISPATCH VBComponent);
	void ItemReloaded(LPDISPATCH VBComponent);
};
/////////////////////////////////////////////////////////////////////////////
// _dispReferencesEvents wrapper class

class _dispReferencesEvents : public COleDispatchDriver
{
public:
	_dispReferencesEvents() {}		// Calls COleDispatchDriver default constructor
	_dispReferencesEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_dispReferencesEvents(const _dispReferencesEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void ItemAdded(LPDISPATCH Reference);
	void ItemRemoved(LPDISPATCH Reference);
};
/////////////////////////////////////////////////////////////////////////////
// _dispCommandBarControlEvents wrapper class

class _dispCommandBarControlEvents : public COleDispatchDriver
{
public:
	_dispCommandBarControlEvents() {}		// Calls COleDispatchDriver default constructor
	_dispCommandBarControlEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_dispCommandBarControlEvents(const _dispCommandBarControlEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Click(LPDISPATCH CommandBarControl, BOOL* handled, BOOL* CancelDefault);
};
/////////////////////////////////////////////////////////////////////////////
// _ProjectTemplate wrapper class

class _ProjectTemplate : public COleDispatchDriver
{
public:
	_ProjectTemplate() {}		// Calls COleDispatchDriver default constructor
	_ProjectTemplate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ProjectTemplate(const _ProjectTemplate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// _VBProject wrapper class

class _VBProject : public COleDispatchDriver
{
public:
	_VBProject() {}		// Calls COleDispatchDriver default constructor
	_VBProject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_VBProject(const _VBProject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHelpFile();
	void SetHelpFile(LPCTSTR lpszNewValue);
	long GetHelpContextID();
	void SetHelpContextID(long nNewValue);
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	long GetMode();
	LPDISPATCH GetReferences();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetVbe();
	LPDISPATCH GetCollection();
	long GetProtection();
	BOOL GetSaved();
	LPDISPATCH GetVBComponents();
};
/////////////////////////////////////////////////////////////////////////////
// _VBProjects wrapper class

class _VBProjects : public COleDispatchDriver
{
public:
	_VBProjects() {}		// Calls COleDispatchDriver default constructor
	_VBProjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_VBProjects(const _VBProjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH GetVbe();
	LPDISPATCH GetParent();
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// SelectedComponents wrapper class

class SelectedComponents : public COleDispatchDriver
{
public:
	SelectedComponents() {}		// Calls COleDispatchDriver default constructor
	SelectedComponents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SelectedComponents(const SelectedComponents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(long index);
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// _Components wrapper class

class _Components : public COleDispatchDriver
{
public:
	_Components() {}		// Calls COleDispatchDriver default constructor
	_Components(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Components(const _Components& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	void Remove(LPDISPATCH Component);
	LPDISPATCH Add(long ComponentType);
	LPDISPATCH Import(LPCTSTR FileName);
	LPDISPATCH GetVbe();
};
/////////////////////////////////////////////////////////////////////////////
// _VBComponents wrapper class

class _VBComponents : public COleDispatchDriver
{
public:
	_VBComponents() {}		// Calls COleDispatchDriver default constructor
	_VBComponents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_VBComponents(const _VBComponents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH GetParent();
	long GetCount();
	void Remove(LPDISPATCH VBComponent);
	LPDISPATCH Add(long ComponentType);
	LPDISPATCH Import(LPCTSTR FileName);
	LPDISPATCH GetVbe();
};
/////////////////////////////////////////////////////////////////////////////
// _Component wrapper class

class _Component : public COleDispatchDriver
{
public:
	_Component() {}		// Calls COleDispatchDriver default constructor
	_Component(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Component(const _Component& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsDirty();
	void SetIsDirty(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// _VBComponent wrapper class

class _VBComponent : public COleDispatchDriver
{
public:
	_VBComponent() {}		// Calls COleDispatchDriver default constructor
	_VBComponent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_VBComponent(const _VBComponent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetSaved();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetDesigner();
	LPDISPATCH GetCodeModule();
	long GetType();
	void Export(LPCTSTR FileName);
	LPDISPATCH GetVbe();
	LPDISPATCH GetCollection();
	BOOL GetHasOpenDesigner();
	LPDISPATCH GetProperties();
	LPDISPATCH DesignerWindow();
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// Property wrapper class

class Property : public COleDispatchDriver
{
public:
	Property() {}		// Calls COleDispatchDriver default constructor
	Property(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Property(const Property& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
	VARIANT GetIndexedValue(const VARIANT& Index1, const VARIANT& Index2, const VARIANT& Index3, const VARIANT& Index4);
	void SetIndexedValue(const VARIANT& Index1, const VARIANT& Index2, const VARIANT& Index3, const VARIANT& Index4, const VARIANT& newValue);
	short GetNumIndices();
	CString GetName();
	LPDISPATCH GetVbe();
	LPDISPATCH GetCollection();
	LPUNKNOWN GetObject();
	void SetRefObject(LPUNKNOWN newValue);
};
/////////////////////////////////////////////////////////////////////////////
// _Properties wrapper class

class _Properties : public COleDispatchDriver
{
public:
	_Properties() {}		// Calls COleDispatchDriver default constructor
	_Properties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Properties(const _Properties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& index);
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH GetVbe();
};
/////////////////////////////////////////////////////////////////////////////
// _CodeModule wrapper class

class _CodeModule : public COleDispatchDriver
{
public:
	_CodeModule() {}		// Calls COleDispatchDriver default constructor
	_CodeModule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_CodeModule(const _CodeModule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParent();
	LPDISPATCH GetVbe();
	void AddFromString(LPCTSTR String);
	void AddFromFile(LPCTSTR FileName);
	CString GetLines(long StartLine, long Count);
	long GetCountOfLines();
	void InsertLines(long Line, LPCTSTR String);
	void DeleteLines(long StartLine, long Count);
	void ReplaceLine(long Line, LPCTSTR String);
	long GetProcStartLine(LPCTSTR ProcName, long ProcKind);
	long GetProcCountLines(LPCTSTR ProcName, long ProcKind);
	long GetProcBodyLine(LPCTSTR ProcName, long ProcKind);
	CString GetProcOfLine(long Line, long* ProcKind);
	long GetCountOfDeclarationLines();
	long CreateEventProc(LPCTSTR EventName, LPCTSTR ObjectName);
	BOOL Find(LPCTSTR Target, long* StartLine, long* StartColumn, long* EndLine, long* EndColumn, BOOL WholeWord, BOOL MatchCase, BOOL PatternSearch);
	LPDISPATCH GetCodePane();
};
/////////////////////////////////////////////////////////////////////////////
// _CodePanes wrapper class

class _CodePanes : public COleDispatchDriver
{
public:
	_CodePanes() {}		// Calls COleDispatchDriver default constructor
	_CodePanes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_CodePanes(const _CodePanes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParent();
	LPDISPATCH GetVbe();
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
	LPUNKNOWN _NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// _CodePane wrapper class

class _CodePane : public COleDispatchDriver
{
public:
	_CodePane() {}		// Calls COleDispatchDriver default constructor
	_CodePane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_CodePane(const _CodePane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetCollection();
	LPDISPATCH GetVbe();
	LPDISPATCH GetWindow();
	void GetSelection(long* StartLine, long* StartColumn, long* EndLine, long* EndColumn);
	void SetSelection(long StartLine, long StartColumn, long EndLine, long EndColumn);
	long GetTopLine();
	void SetTopLine(long nNewValue);
	long GetCountOfVisibleLines();
	LPDISPATCH GetCodeModule();
	void Show();
	long GetCodePaneView();
};
/////////////////////////////////////////////////////////////////////////////
// _References wrapper class

class _References : public COleDispatchDriver
{
public:
	_References() {}		// Calls COleDispatchDriver default constructor
	_References(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_References(const _References& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParent();
	LPDISPATCH GetVbe();
	LPDISPATCH Item(const VARIANT& index);
	long GetCount();
	LPUNKNOWN _NewEnum();
	LPDISPATCH AddFromGuid(LPCTSTR Guid, long Major, long Minor);
	LPDISPATCH AddFromFile(LPCTSTR FileName);
	void Remove(LPDISPATCH Reference);
};
/////////////////////////////////////////////////////////////////////////////
// Reference wrapper class

class Reference : public COleDispatchDriver
{
public:
	Reference() {}		// Calls COleDispatchDriver default constructor
	Reference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Reference(const Reference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetCollection();
	LPDISPATCH GetVbe();
	CString GetName();
	CString GetGuid();
	long GetMajor();
	long GetMinor();
	CString GetFullPath();
	BOOL GetBuiltIn();
	BOOL GetIsBroken();
	long GetType();
	CString GetDescription();
};
/////////////////////////////////////////////////////////////////////////////
// _dispReferences_Events wrapper class

class _dispReferences_Events : public COleDispatchDriver
{
public:
	_dispReferences_Events() {}		// Calls COleDispatchDriver default constructor
	_dispReferences_Events(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_dispReferences_Events(const _dispReferences_Events& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void ItemAdded(LPDISPATCH Reference);
	void ItemRemoved(LPDISPATCH Reference);
};

};