// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IAccessible wrapper class

class IAccessible : public COleDispatchDriver
{
public:
	IAccessible() {}		// Calls COleDispatchDriver default constructor
	IAccessible(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAccessible(const IAccessible& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// _IMsoDispObj wrapper class

class _IMsoDispObj : public COleDispatchDriver
{
public:
	_IMsoDispObj() {}		// Calls COleDispatchDriver default constructor
	_IMsoDispObj(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IMsoDispObj(const _IMsoDispObj& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
};
/////////////////////////////////////////////////////////////////////////////
// _IMsoOleAccDispObj wrapper class

class _IMsoOleAccDispObj : public COleDispatchDriver
{
public:
	_IMsoOleAccDispObj() {}		// Calls COleDispatchDriver default constructor
	_IMsoOleAccDispObj(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IMsoOleAccDispObj(const _IMsoOleAccDispObj& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
};
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
/////////////////////////////////////////////////////////////////////////////
// Adjustments wrapper class

class Adjustments : public COleDispatchDriver
{
public:
	Adjustments() {}		// Calls COleDispatchDriver default constructor
	Adjustments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Adjustments(const Adjustments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	float GetItem(long Index);
	void SetItem(long Index, float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CalloutFormat wrapper class

class CalloutFormat : public COleDispatchDriver
{
public:
	CalloutFormat() {}		// Calls COleDispatchDriver default constructor
	CalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CalloutFormat(const CalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void AutomaticLength();
	void CustomDrop(float Drop);
	void CustomLength(float Length);
	void PresetDrop(long DropType);
	long GetAccent();
	void SetAccent(long nNewValue);
	long GetAngle();
	void SetAngle(long nNewValue);
	long GetAutoAttach();
	void SetAutoAttach(long nNewValue);
	long GetAutoLength();
	long GetBorder();
	void SetBorder(long nNewValue);
	float GetDrop();
	long GetDropType();
	float GetGap();
	void SetGap(float newValue);
	float GetLength();
	long GetType();
	void SetType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ColorFormat wrapper class

class ColorFormat : public COleDispatchDriver
{
public:
	ColorFormat() {}		// Calls COleDispatchDriver default constructor
	ColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ColorFormat(const ColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetRgb();
	void SetRgb(long nNewValue);
	long GetSchemeColor();
	void SetSchemeColor(long nNewValue);
	long GetType();
};
/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat wrapper class

class ConnectorFormat : public COleDispatchDriver
{
public:
	ConnectorFormat() {}		// Calls COleDispatchDriver default constructor
	ConnectorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ConnectorFormat(const ConnectorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void BeginConnect(LPDISPATCH ConnectedShape, long ConnectionSite);
	void BeginDisconnect();
	void EndConnect(LPDISPATCH ConnectedShape, long ConnectionSite);
	void EndDisconnect();
	long GetBeginConnected();
	LPDISPATCH GetBeginConnectedShape();
	long GetBeginConnectionSite();
	long GetEndConnected();
	LPDISPATCH GetEndConnectedShape();
	long GetEndConnectionSite();
	long GetType();
	void SetType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// FillFormat wrapper class

class FillFormat : public COleDispatchDriver
{
public:
	FillFormat() {}		// Calls COleDispatchDriver default constructor
	FillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FillFormat(const FillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Background();
	void OneColorGradient(long Style, long Variant, float Degree);
	void Patterned(long Pattern);
	void PresetGradient(long Style, long Variant, long PresetGradientType);
	void PresetTextured(long PresetTexture);
	void Solid();
	void TwoColorGradient(long Style, long Variant);
	void UserPicture(LPCTSTR PictureFile);
	void UserTextured(LPCTSTR TextureFile);
	LPDISPATCH GetBackColor();
	void SetBackColor(LPDISPATCH newValue);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetGradientColorType();
	float GetGradientDegree();
	long GetGradientStyle();
	long GetGradientVariant();
	long GetPattern();
	long GetPresetGradientType();
	long GetPresetTexture();
	CString GetTextureName();
	long GetTextureType();
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder wrapper class

class FreeformBuilder : public COleDispatchDriver
{
public:
	FreeformBuilder() {}		// Calls COleDispatchDriver default constructor
	FreeformBuilder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FreeformBuilder(const FreeformBuilder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	LPDISPATCH ConvertToShape();
};
/////////////////////////////////////////////////////////////////////////////
// GroupShapes wrapper class

class GroupShapes : public COleDispatchDriver
{
public:
	GroupShapes() {}		// Calls COleDispatchDriver default constructor
	GroupShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupShapes(const GroupShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// LineFormat wrapper class

class LineFormat : public COleDispatchDriver
{
public:
	LineFormat() {}		// Calls COleDispatchDriver default constructor
	LineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LineFormat(const LineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBackColor();
	void SetBackColor(LPDISPATCH newValue);
	long GetBeginArrowheadLength();
	void SetBeginArrowheadLength(long nNewValue);
	long GetBeginArrowheadStyle();
	void SetBeginArrowheadStyle(long nNewValue);
	long GetBeginArrowheadWidth();
	void SetBeginArrowheadWidth(long nNewValue);
	long GetDashStyle();
	void SetDashStyle(long nNewValue);
	long GetEndArrowheadLength();
	void SetEndArrowheadLength(long nNewValue);
	long GetEndArrowheadStyle();
	void SetEndArrowheadStyle(long nNewValue);
	long GetEndArrowheadWidth();
	void SetEndArrowheadWidth(long nNewValue);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetPattern();
	void SetPattern(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWeight();
	void SetWeight(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNode wrapper class

class ShapeNode : public COleDispatchDriver
{
public:
	ShapeNode() {}		// Calls COleDispatchDriver default constructor
	ShapeNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNode(const ShapeNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetEditingType();
	VARIANT GetPoints();
	long GetSegmentType();
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNodes wrapper class

class ShapeNodes : public COleDispatchDriver
{
public:
	ShapeNodes() {}		// Calls COleDispatchDriver default constructor
	ShapeNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNodes(const ShapeNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
	void Delete(long Index);
	void Insert(long Index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	void SetEditingType(long Index, long EditingType);
	void SetPosition(long Index, float X1, float Y1);
	void SetSegmentType(long Index, long SegmentType);
};
/////////////////////////////////////////////////////////////////////////////
// PictureFormat wrapper class

class PictureFormat : public COleDispatchDriver
{
public:
	PictureFormat() {}		// Calls COleDispatchDriver default constructor
	PictureFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PictureFormat(const PictureFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementBrightness(float Increment);
	void IncrementContrast(float Increment);
	float GetBrightness();
	void SetBrightness(float newValue);
	long GetColorType();
	void SetColorType(long nNewValue);
	float GetContrast();
	void SetContrast(float newValue);
	float GetCropBottom();
	void SetCropBottom(float newValue);
	float GetCropLeft();
	void SetCropLeft(float newValue);
	float GetCropRight();
	void SetCropRight(float newValue);
	float GetCropTop();
	void SetCropTop(float newValue);
	long GetTransparencyColor();
	void SetTransparencyColor(long nNewValue);
	long GetTransparentBackground();
	void SetTransparentBackground(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ShadowFormat wrapper class

class ShadowFormat : public COleDispatchDriver
{
public:
	ShadowFormat() {}		// Calls COleDispatchDriver default constructor
	ShadowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShadowFormat(const ShadowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementOffsetX(float Increment);
	void IncrementOffsetY(float Increment);
	LPDISPATCH GetForeColor();
	void SetForeColor(LPDISPATCH newValue);
	long GetObscured();
	void SetObscured(long nNewValue);
	float GetOffsetX();
	void SetOffsetX(float newValue);
	float GetOffsetY();
	void SetOffsetY(float newValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	void SetType(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Shape wrapper class

class Shape : public COleDispatchDriver
{
public:
	Shape() {}		// Calls COleDispatchDriver default constructor
	Shape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shape(const Shape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Apply();
	void Delete();
	LPDISPATCH Duplicate();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	void PickUp();
	void RerouteConnections();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale);
	void Select(const VARIANT& Replace);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	long GetBlackWhiteMode();
	void SetBlackWhiteMode(long nNewValue);
	LPDISPATCH GetCallout();
	long GetConnectionSiteCount();
	long GetConnector();
	LPDISPATCH GetConnectorFormat();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
};
/////////////////////////////////////////////////////////////////////////////
// ShapeRange wrapper class

class ShapeRange : public COleDispatchDriver
{
public:
	ShapeRange() {}		// Calls COleDispatchDriver default constructor
	ShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeRange(const ShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
	void Align(long AlignCmd, long RelativeTo);
	void Apply();
	void Delete();
	void Distribute(long DistributeCmd, long RelativeTo);
	LPDISPATCH Duplicate();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	LPDISPATCH Group();
	void PickUp();
	LPDISPATCH Regroup();
	void RerouteConnections();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale);
	void Select(const VARIANT& Replace);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	long GetBlackWhiteMode();
	void SetBlackWhiteMode(long nNewValue);
	LPDISPATCH GetCallout();
	long GetConnectionSiteCount();
	long GetConnector();
	LPDISPATCH GetConnectorFormat();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
};
/////////////////////////////////////////////////////////////////////////////
// Shapes wrapper class

class Shapes : public COleDispatchDriver
{
public:
	Shapes() {}		// Calls COleDispatchDriver default constructor
	Shapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shapes(const Shapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddCurve(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height);
	LPDISPATCH AddPolyline(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top);
	LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1);
	LPDISPATCH Range(const VARIANT& Index);
	void SelectAll();
	LPDISPATCH GetBackground();
	LPDISPATCH GetDefault();
};
/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat wrapper class

class TextEffectFormat : public COleDispatchDriver
{
public:
	TextEffectFormat() {}		// Calls COleDispatchDriver default constructor
	TextEffectFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextEffectFormat(const TextEffectFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void ToggleVerticalText();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetFontBold();
	void SetFontBold(long nNewValue);
	long GetFontItalic();
	void SetFontItalic(long nNewValue);
	CString GetFontName();
	void SetFontName(LPCTSTR lpszNewValue);
	float GetFontSize();
	void SetFontSize(float newValue);
	long GetKernedPairs();
	void SetKernedPairs(long nNewValue);
	long GetNormalizedHeight();
	void SetNormalizedHeight(long nNewValue);
	long GetPresetShape();
	void SetPresetShape(long nNewValue);
	long GetPresetTextEffect();
	void SetPresetTextEffect(long nNewValue);
	long GetRotatedChars();
	void SetRotatedChars(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	float GetTracking();
	void SetTracking(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextFrame wrapper class

class TextFrame : public COleDispatchDriver
{
public:
	TextFrame() {}		// Calls COleDispatchDriver default constructor
	TextFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextFrame(const TextFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetMarginBottom();
	void SetMarginBottom(float newValue);
	float GetMarginLeft();
	void SetMarginLeft(float newValue);
	float GetMarginRight();
	void SetMarginRight(float newValue);
	float GetMarginTop();
	void SetMarginTop(float newValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat wrapper class

class ThreeDFormat : public COleDispatchDriver
{
public:
	ThreeDFormat() {}		// Calls COleDispatchDriver default constructor
	ThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ThreeDFormat(const ThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void IncrementRotationX(float Increment);
	void IncrementRotationY(float Increment);
	void ResetRotation();
	void SetThreeDFormat(long PresetThreeDFormat);
	void SetExtrusionDirection(long PresetExtrusionDirection);
	float GetDepth();
	void SetDepth(float newValue);
	LPDISPATCH GetExtrusionColor();
	long GetExtrusionColorType();
	void SetExtrusionColorType(long nNewValue);
	long GetPerspective();
	void SetPerspective(long nNewValue);
	long GetPresetExtrusionDirection();
	long GetPresetLightingDirection();
	void SetPresetLightingDirection(long nNewValue);
	long GetPresetLightingSoftness();
	void SetPresetLightingSoftness(long nNewValue);
	long GetPresetMaterial();
	void SetPresetMaterial(long nNewValue);
	long GetPresetThreeDFormat();
	float GetRotationX();
	void SetRotationX(float newValue);
	float GetRotationY();
	void SetRotationY(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Assistant wrapper class

class Assistant : public COleDispatchDriver
{
public:
	Assistant() {}		// Calls COleDispatchDriver default constructor
	Assistant(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Assistant(const Assistant& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Move(long xLeft, long yTop);
	void SetTop(long nNewValue);
	long GetTop();
	void SetLeft(long nNewValue);
	long GetLeft();
	void Help();
	long StartWizard(BOOL On, LPCTSTR Callback, long PrivateX, const VARIANT& Animation, const VARIANT& CustomTeaser, const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right);
	void EndWizard(long WizardID, BOOL varfSuccess, const VARIANT& Animation);
	void ActivateWizard(long WizardID, long act, const VARIANT& Animation);
	void ResetTips();
	LPDISPATCH GetNewBalloon();
	long GetBalloonError();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetAnimation();
	void SetAnimation(long nNewValue);
	BOOL GetReduced();
	void SetReduced(BOOL bNewValue);
	void SetAssistWithHelp(BOOL bNewValue);
	BOOL GetAssistWithHelp();
	void SetAssistWithWizards(BOOL bNewValue);
	BOOL GetAssistWithWizards();
	void SetAssistWithAlerts(BOOL bNewValue);
	BOOL GetAssistWithAlerts();
	void SetMoveWhenInTheWay(BOOL bNewValue);
	BOOL GetMoveWhenInTheWay();
	void SetSounds(BOOL bNewValue);
	BOOL GetSounds();
	void SetFeatureTips(BOOL bNewValue);
	BOOL GetFeatureTips();
	void SetMouseTips(BOOL bNewValue);
	BOOL GetMouseTips();
	void SetKeyboardShortcutTips(BOOL bNewValue);
	BOOL GetKeyboardShortcutTips();
	void SetHighPriorityTips(BOOL bNewValue);
	BOOL GetHighPriorityTips();
	void SetTipOfDay(BOOL bNewValue);
	BOOL GetTipOfDay();
	void SetGuessHelp(BOOL bNewValue);
	BOOL GetGuessHelp();
	void SetSearchWhenProgramming(BOOL bNewValue);
	BOOL GetSearchWhenProgramming();
	CString GetItem();
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	CString GetName();
};
/////////////////////////////////////////////////////////////////////////////
// Balloon wrapper class

class Balloon : public COleDispatchDriver
{
public:
	Balloon() {}		// Calls COleDispatchDriver default constructor
	Balloon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Balloon(const Balloon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetCheckboxes();
	LPDISPATCH GetLabels();
	void SetBalloonType(long nNewValue);
	long GetBalloonType();
	void SetIcon(long nNewValue);
	long GetIcon();
	void SetHeading(LPCTSTR lpszNewValue);
	CString GetHeading();
	void SetText(LPCTSTR lpszNewValue);
	CString GetText();
	void SetMode(long nNewValue);
	long GetMode();
	void SetAnimation(long nNewValue);
	long GetAnimation();
	void SetButton(long nNewValue);
	long GetButton();
	void SetCallback(LPCTSTR lpszNewValue);
	CString GetCallback();
	void SetPrivate(long nNewValue);
	long GetPrivate();
	void SetAvoidRectangle(long Left, long Top, long Right, long Bottom);
	CString GetName();
	long Show();
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// BalloonCheckboxes wrapper class

class BalloonCheckboxes : public COleDispatchDriver
{
public:
	BalloonCheckboxes() {}		// Calls COleDispatchDriver default constructor
	BalloonCheckboxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	BalloonCheckboxes(const BalloonCheckboxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetName();
	LPDISPATCH GetParent();
	LPDISPATCH GetItem(long Index);
	long GetCount();
	void SetCount(long nNewValue);
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// BalloonCheckbox wrapper class

class BalloonCheckbox : public COleDispatchDriver
{
public:
	BalloonCheckbox() {}		// Calls COleDispatchDriver default constructor
	BalloonCheckbox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	BalloonCheckbox(const BalloonCheckbox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetItem();
	CString GetName();
	LPDISPATCH GetParent();
	void SetChecked(BOOL bNewValue);
	BOOL GetChecked();
	void SetText(LPCTSTR lpszNewValue);
	CString GetText();
};
/////////////////////////////////////////////////////////////////////////////
// BalloonLabels wrapper class

class BalloonLabels : public COleDispatchDriver
{
public:
	BalloonLabels() {}		// Calls COleDispatchDriver default constructor
	BalloonLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	BalloonLabels(const BalloonLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetName();
	LPDISPATCH GetParent();
	LPDISPATCH GetItem(long Index);
	long GetCount();
	void SetCount(long nNewValue);
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// BalloonLabel wrapper class

class BalloonLabel : public COleDispatchDriver
{
public:
	BalloonLabel() {}		// Calls COleDispatchDriver default constructor
	BalloonLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	BalloonLabel(const BalloonLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetItem();
	CString GetName();
	LPDISPATCH GetParent();
	void SetText(LPCTSTR lpszNewValue);
	CString GetText();
};
/////////////////////////////////////////////////////////////////////////////
// IFoundFiles wrapper class

class IFoundFiles : public COleDispatchDriver
{
public:
	IFoundFiles() {}		// Calls COleDispatchDriver default constructor
	IFoundFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFoundFiles(const IFoundFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetItem(long Index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// IFind wrapper class

class IFind : public COleDispatchDriver
{
public:
	IFind() {}		// Calls COleDispatchDriver default constructor
	IFind(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFind(const IFind& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetSearchPath();
	CString GetName();
	BOOL GetSubDir();
	CString GetTitle();
	CString GetAuthor();
	CString GetKeywords();
	CString GetSubject();
	long GetOptions();
	BOOL GetMatchCase();
	CString GetText();
	BOOL GetPatternMatch();
	VARIANT GetDateSavedFrom();
	VARIANT GetDateSavedTo();
	CString GetSavedBy();
	VARIANT GetDateCreatedFrom();
	VARIANT GetDateCreatedTo();
	long GetView();
	long GetSortBy();
	long GetListBy();
	long GetSelectedFile();
	LPDISPATCH GetResults();
	long Show();
	void SetSearchPath(LPCTSTR lpszNewValue);
	void SetName(LPCTSTR lpszNewValue);
	void SetSubDir(BOOL bNewValue);
	void SetTitle(LPCTSTR lpszNewValue);
	void SetAuthor(LPCTSTR lpszNewValue);
	void SetKeywords(LPCTSTR lpszNewValue);
	void SetSubject(LPCTSTR lpszNewValue);
	void SetOptions(long nNewValue);
	void SetMatchCase(BOOL bNewValue);
	void SetText(LPCTSTR lpszNewValue);
	void SetPatternMatch(BOOL bNewValue);
	void SetDateSavedFrom(const VARIANT& newValue);
	void SetDateSavedTo(const VARIANT& newValue);
	void SetSavedBy(LPCTSTR lpszNewValue);
	void SetDateCreatedFrom(const VARIANT& newValue);
	void SetDateCreatedTo(const VARIANT& newValue);
	void SetView(long nNewValue);
	void SetSortBy(long nNewValue);
	void SetListBy(long nNewValue);
	void SetSelectedFile(long nNewValue);
	void Execute();
	void Load(LPCTSTR bstrQueryName);
	void Save(LPCTSTR bstrQueryName);
	void Delete(LPCTSTR bstrQueryName);
	long GetFileType();
	void SetFileType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// FoundFiles wrapper class

class FoundFiles : public COleDispatchDriver
{
public:
	FoundFiles() {}		// Calls COleDispatchDriver default constructor
	FoundFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FoundFiles(const FoundFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetItem(long Index);
	long GetCount();
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// PropertyTest wrapper class

class PropertyTest : public COleDispatchDriver
{
public:
	PropertyTest() {}		// Calls COleDispatchDriver default constructor
	PropertyTest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PropertyTest(const PropertyTest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	CString GetName();
	long GetCondition();
	VARIANT GetValue();
	VARIANT GetSecondValue();
	long GetConnector();
};
/////////////////////////////////////////////////////////////////////////////
// PropertyTests wrapper class

class PropertyTests : public COleDispatchDriver
{
public:
	PropertyTests() {}		// Calls COleDispatchDriver default constructor
	PropertyTests(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PropertyTests(const PropertyTests& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetItem(long Index);
	long GetCount();
	void Add(LPCTSTR Name, long Condition, const VARIANT& Value, const VARIANT& SecondValue, long Connector);
	void Remove(long Index);
	LPUNKNOWN Get_NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// FileSearch wrapper class

class FileSearch : public COleDispatchDriver
{
public:
	FileSearch() {}		// Calls COleDispatchDriver default constructor
	FileSearch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileSearch(const FileSearch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	BOOL GetSearchSubFolders();
	void SetSearchSubFolders(BOOL bNewValue);
	BOOL GetMatchTextExactly();
	void SetMatchTextExactly(BOOL bNewValue);
	BOOL GetMatchAllWordForms();
	void SetMatchAllWordForms(BOOL bNewValue);
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	long GetFileType();
	void SetFileType(long nNewValue);
	long GetLastModified();
	void SetLastModified(long nNewValue);
	CString GetTextOrProperty();
	void SetTextOrProperty(LPCTSTR lpszNewValue);
	CString GetLookIn();
	void SetLookIn(LPCTSTR lpszNewValue);
	long Execute(long SortBy, long SortOrder, BOOL AlwaysAccurate);
	void NewSearch();
	LPDISPATCH GetFoundFiles();
	LPDISPATCH GetPropertyTests();
};
