/////////////////////////////////////////////////////////////////////////////
// CommandBars wrapper class

class CommandBars : public COleDispatchDriver
{
public:
	CommandBars() {}		// Calls COleDispatchDriver default constructor
	CommandBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBars(const CommandBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetActionControl();
	LPDISPATCH GetActiveMenuBar();
	LPDISPATCH Add(const VARIANT& Name, const VARIANT& Position, const VARIANT& MenuBar, const VARIANT& Temporary);
	long GetCount();
	BOOL GetDisplayTooltips();
	void SetDisplayTooltips(BOOL bNewValue);
	BOOL GetDisplayKeysInTooltips();
	void SetDisplayKeysInTooltips(BOOL bNewValue);
	LPDISPATCH FindControl(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible);
	LPDISPATCH GetItem(const VARIANT& Index);
	BOOL GetLargeButtons();
	void SetLargeButtons(BOOL bNewValue);
	long GetMenuAnimationStyle();
	void SetMenuAnimationStyle(long nNewValue);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetParent();
	void ReleaseFocus();
};
/////////////////////////////////////////////////////////////////////////////
// CommandBar wrapper class

class CommandBar : public COleDispatchDriver
{
public:
	CommandBar() {}		// Calls COleDispatchDriver default constructor
	CommandBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBar(const CommandBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetBuiltIn();
	CString GetContext();
	void SetContext(LPCTSTR lpszNewValue);
	LPDISPATCH GetControls();
	void Delete();
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	LPDISPATCH FindControl(const VARIANT& Type, const VARIANT& Id, const VARIANT& Tag, const VARIANT& Visible, const VARIANT& Recursive);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetIndex();
	long GetLeft();
	void SetLeft(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetNameLocal();
	void SetNameLocal(LPCTSTR lpszNewValue);
	LPDISPATCH GetParent();
	long GetPosition();
	void SetPosition(long nNewValue);
	long GetRowIndex();
	void SetRowIndex(long nNewValue);
	long GetProtection();
	void SetProtection(long nNewValue);
	void Reset();
	void ShowPopup(const VARIANT& x, const VARIANT& y);
	long GetTop();
	void SetTop(long nNewValue);
	long GetType();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarControls wrapper class

class CommandBarControls : public COleDispatchDriver
{
public:
	CommandBarControls() {}		// Calls COleDispatchDriver default constructor
	CommandBarControls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarControls(const CommandBarControls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH Add(const VARIANT& Type, const VARIANT& Id, const VARIANT& Parameter, const VARIANT& Before, const VARIANT& Temporary);
	long GetCount();
	LPDISPATCH GetItem(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarControl wrapper class

class CommandBarControl : public COleDispatchDriver
{
public:
	CommandBarControl() {}		// Calls COleDispatchDriver default constructor
	CommandBarControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarControl(const CommandBarControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	BOOL GetBuiltIn();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH Copy(const VARIANT& Bar, const VARIANT& Before);
	void Delete(const VARIANT& Temporary);
	CString GetDescriptionText();
	void SetDescriptionText(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	void Execute();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetHelpContextId();
	void SetHelpContextId(long nNewValue);
	CString GetHelpFile();
	void SetHelpFile(LPCTSTR lpszNewValue);
	long GetId();
	long GetIndex();
	LPDISPATCH Move(const VARIANT& Bar, const VARIANT& Before);
	long GetLeft();
	long GetOLEUsage();
	void SetOLEUsage(long nNewValue);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	LPDISPATCH GetParent();
	CString GetParameter();
	void SetParameter(LPCTSTR lpszNewValue);
	long GetPriority();
	void SetPriority(long nNewValue);
	void Reset();
	void SetFocus();
	CString GetTag();
	void SetTag(LPCTSTR lpszNewValue);
	CString GetTooltipText();
	void SetTooltipText(LPCTSTR lpszNewValue);
	long GetTop();
	long GetType();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarButton wrapper class

class CommandBarButton : public COleDispatchDriver
{
public:
	CommandBarButton() {}		// Calls COleDispatchDriver default constructor
	CommandBarButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarButton(const CommandBarButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	BOOL GetBuiltIn();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH Copy(const VARIANT& Bar, const VARIANT& Before);
	void Delete(const VARIANT& Temporary);
	CString GetDescriptionText();
	void SetDescriptionText(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	void Execute();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetHelpContextId();
	void SetHelpContextId(long nNewValue);
	CString GetHelpFile();
	void SetHelpFile(LPCTSTR lpszNewValue);
	long GetId();
	long GetIndex();
	LPDISPATCH Move(const VARIANT& Bar, const VARIANT& Before);
	long GetLeft();
	long GetOLEUsage();
	void SetOLEUsage(long nNewValue);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	LPDISPATCH GetParent();
	CString GetParameter();
	void SetParameter(LPCTSTR lpszNewValue);
	long GetPriority();
	void SetPriority(long nNewValue);
	void Reset();
	void SetFocus();
	CString GetTag();
	void SetTag(LPCTSTR lpszNewValue);
	CString GetTooltipText();
	void SetTooltipText(LPCTSTR lpszNewValue);
	long GetTop();
	long GetType();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	BOOL GetBuiltInFace();
	void SetBuiltInFace(BOOL bNewValue);
	void CopyFace();
	long GetFaceId();
	void SetFaceId(long nNewValue);
	void PasteFace();
	CString GetShortcutText();
	void SetShortcutText(LPCTSTR lpszNewValue);
	long GetState();
	void SetState(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup wrapper class

class CommandBarPopup : public COleDispatchDriver
{
public:
	CommandBarPopup() {}		// Calls COleDispatchDriver default constructor
	CommandBarPopup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarPopup(const CommandBarPopup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	BOOL GetBuiltIn();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH Copy(const VARIANT& Bar, const VARIANT& Before);
	void Delete(const VARIANT& Temporary);
	CString GetDescriptionText();
	void SetDescriptionText(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	void Execute();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetHelpContextId();
	void SetHelpContextId(long nNewValue);
	CString GetHelpFile();
	void SetHelpFile(LPCTSTR lpszNewValue);
	long GetId();
	long GetIndex();
	LPDISPATCH Move(const VARIANT& Bar, const VARIANT& Before);
	long GetLeft();
	long GetOLEUsage();
	void SetOLEUsage(long nNewValue);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	LPDISPATCH GetParent();
	CString GetParameter();
	void SetParameter(LPCTSTR lpszNewValue);
	long GetPriority();
	void SetPriority(long nNewValue);
	void Reset();
	void SetFocus();
	CString GetTag();
	void SetTag(LPCTSTR lpszNewValue);
	CString GetTooltipText();
	void SetTooltipText(LPCTSTR lpszNewValue);
	long GetTop();
	long GetType();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	LPDISPATCH GetCommandBar();
	LPDISPATCH GetControls();
	long GetOLEMenuGroup();
	void SetOLEMenuGroup(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarComboBox wrapper class

class CommandBarComboBox : public COleDispatchDriver
{
public:
	CommandBarComboBox() {}		// Calls COleDispatchDriver default constructor
	CommandBarComboBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarComboBox(const CommandBarComboBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	BOOL GetBuiltIn();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH Copy(const VARIANT& Bar, const VARIANT& Before);
	void Delete(const VARIANT& Temporary);
	CString GetDescriptionText();
	void SetDescriptionText(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	void Execute();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetHelpContextId();
	void SetHelpContextId(long nNewValue);
	CString GetHelpFile();
	void SetHelpFile(LPCTSTR lpszNewValue);
	long GetId();
	long GetIndex();
	LPDISPATCH Move(const VARIANT& Bar, const VARIANT& Before);
	long GetLeft();
	long GetOLEUsage();
	void SetOLEUsage(long nNewValue);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	LPDISPATCH GetParent();
	CString GetParameter();
	void SetParameter(LPCTSTR lpszNewValue);
	long GetPriority();
	void SetPriority(long nNewValue);
	void Reset();
	void SetFocus();
	CString GetTag();
	void SetTag(LPCTSTR lpszNewValue);
	CString GetTooltipText();
	void SetTooltipText(LPCTSTR lpszNewValue);
	long GetTop();
	long GetType();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	void AddItem(LPCTSTR Text, const VARIANT& Index);
	void Clear();
	long GetDropDownLines();
	void SetDropDownLines(long nNewValue);
	long GetDropDownWidth();
	void SetDropDownWidth(long nNewValue);
	CString GetList(long Index);
	void SetList(long Index, LPCTSTR lpszNewValue);
	long GetListCount();
	long GetListHeaderCount();
	void SetListHeaderCount(long nNewValue);
	long GetListIndex();
	void SetListIndex(long nNewValue);
	void RemoveItem(long Index);
	long GetStyle();
	void SetStyle(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
};
