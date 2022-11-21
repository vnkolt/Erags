/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2001-2002 by David Yuheng Zhao
//
// Distribute and change freely, except: don't remove my name from the source 
//
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Partly based on the _ThemeHelper struct in MFC7.0 source code (winctrl3.cpp), 
// and the difference is that this implementation wraps the full set of 
// visual style APIs from the platform SDK August 2001
//
// If you have any questions, I can be reached as follows:
//	yuheng_zhao@yahoo.com
//
//
// How to use:
// Instead of calling the API directly, 
//    OpenThemeData(...);
// use the global variable
//    g_xpStyle.OpenThemeData(...);
//
//
//
// Date: 2002-07-27
// This update was made by Mathias Tunared. 
// He changed the function variable to static to make the code faster. 
// He also added the function 'UseVisualStyles()' so you can check if to
// draw with the visual styles or not. That function checks first the 
// version of the 'ComCtl32.dll' and the checks if the theme is activated 
// and the HTHEME handle is not NULL.
//
// CAdvComboBox Control
// Version: 2.1
// Date: August 2002
// Author: Mathias Tunared
// Email: Mathias@inorbit.com
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _VISUALSTYLE_XP_H_
#define _VISUALSTYLE_XP_H_

#pragma once

#pragma warning( disable : 4100 )

//#include <uxtheme.h>
//#include <tmschema.h>

#if !defined(THEME)
typedef HANDLE HTHEME;          // handle to a section of theme data for class
#endif

#ifndef THEMEAPI
typedef struct _MARGINS
{
    int cxLeftWidth;      // width of left border that retains its size
    int cxRightWidth;     // width of right border that retains its size
    int cyTopHeight;      // height of top border that retains its size
    int cyBottomHeight;   // height of bottom border that retains its size
} MARGINS, *PMARGINS;

enum {
 	CBXS_NORMAL = 1,
 	CBXS_HOT = 2,
 	CBXS_PRESSED = 3,
 	CBXS_DISABLED = 4
 };

enum COMBOBOXPARTS {
  CP_DROPDOWNBUTTON = 1
};

enum UxThemeButtonParts {
    BP_PUSHBUTTON = 1,
    BP_RADIOBUTTON = 2,
    BP_CHECKBOX = 3,
    BP_GROUPBOX = 4,
    BP_USERBUTTON = 5
};

enum UxThemePushButtonStates {
    PBS_NORMAL = 1,
    PBS_HOT = 2,
    PBS_PRESSED = 3,
    PBS_DISABLED = 4,
    PBS_DEFAULTED = 5
};

enum UxThemeRadioButtonStates {
    RBS_UNCHECKEDNORMAL   = 1,
    RBS_UNCHECKEDHOT      = 2,
    RBS_UNCHECKEDPRESSED  = 3,
    RBS_UNCHECKEDDISABLED = 4,
    RBS_CHECKEDNORMAL     = 5,
    RBS_CHECKEDHOT        = 6,
    RBS_CHECKEDPRESSED    = 7,
    RBS_CHECKEDDISABLED   = 8
};

enum UxThemeGroupBoxStates {
    GBS_NORMAL   = 1,
    GBS_DISABLED = 2
};

enum UxThemeWindowParts {
    WP_CAPTION = 1,
    WP_SMALLCAPTION = 2,
    WP_MINCAPTION = 3,
    WP_SMALLMINCAPTION = 4,
    WP_MAXCAPTION = 5,
    WP_SMALLMAXCAPTION = 6,
    WP_FRAMELEFT = 7,
    WP_FRAMERIGHT = 8,
    WP_FRAMEBOTTOM = 9,
    WP_SMALLFRAMELEFT = 10,
    WP_SMALLFRAMERIGHT = 11,
    WP_SMALLFRAMEBOTTOM = 12,
    //---- window frame buttons ----
    WP_SYSBUTTON = 13,
    WP_MDISYSBUTTON = 14,
    WP_MINBUTTON = 15,
    WP_MDIMINBUTTON = 16,
    WP_MAXBUTTON = 17,
    WP_CLOSEBUTTON = 18,
    WP_SMALLCLOSEBUTTON = 19,
    WP_MDICLOSEBUTTON = 20,
    WP_RESTOREBUTTON = 21,
    WP_MDIRESTOREBUTTON = 22,
    WP_HELPBUTTON = 23,
    WP_MDIHELPBUTTON = 24,
    //---- scrollbars
    WP_HORZSCROLL = 25,
    WP_HORZTHUMB = 26,
    WP_VERTSCROLL = 27,
    WP_VERTTHUMB = 28,
    //---- dialog ----
    WP_DIALOG = 29,
    //---- hit-test templates ---
    WP_CAPTIONSIZINGTEMPLATE = 30,
    WP_SMALLCAPTIONSIZINGTEMPLATE = 31,
    WP_FRAMELEFTSIZINGTEMPLATE = 32,
    WP_SMALLFRAMELEFTSIZINGTEMPLATE = 33,
    WP_FRAMERIGHTSIZINGTEMPLATE = 34,
    WP_SMALLFRAMERIGHTSIZINGTEMPLATE = 35,
    WP_FRAMEBOTTOMSIZINGTEMPLATE = 36,
    WP_SMALLFRAMEBOTTOMSIZINGTEMPLATE = 37
};

enum UxThemeColorProperties {
  TMT_BORDERCOLOR = 3801,             // color of borders for BorderFill 
  TMT_FILLCOLOR = 3802,               // color of bg fill 
  TMT_TEXTCOLOR = 3803,               // color text is drawn in
  TMT_EDGELIGHTCOLOR = 3804,          // edge color
  TMT_EDGEHIGHLIGHTCOLOR = 3805,      // edge color
  TMT_EDGESHADOWCOLOR = 3806,         // edge color
  TMT_EDGEDKSHADOWCOLOR = 3807,       // edge color
  TMT_EDGEFILLCOLOR = 3808,           // edge color
  TMT_TRANSPARENTCOLOR = 3809,        // color of pixels that are treated as transparent (not drawn
  TMT_GRADIENTCOLOR1 = 3810,          // first color in gradient
  TMT_GRADIENTCOLOR2 = 3811,          // second color in gradient
  TMT_GRADIENTCOLOR3 = 3812,          // third color in gradient
  TMT_GRADIENTCOLOR4 = 3813,          // forth color in gradient
  TMT_GRADIENTCOLOR5 = 3814,          // fifth color in gradient
  TMT_SHADOWCOLOR = 3815,             // color of text shadow
  TMT_GLOWCOLOR = 3816,               // color of glow produced by DrawThemeIcon
  TMT_TEXTBORDERCOLOR = 3817,         // color of text border
  TMT_TEXTSHADOWCOLOR = 3818,         // color of text shadow
  TMT_GLYPHTEXTCOLOR = 3819,          // color that font-based glyph is drawn with
  TMT_GLYPHTRANSPARENTCOLOR = 3820,   // color of transparent pixels in GlyphImageFile
  TMT_FILLCOLORHINT = 3821,           // hint about fill color used (for custom controls)
  TMT_BORDERCOLORHINT = 3822,         // hint about border color used (for custom controls)
  TMT_ACCENTCOLORHINT = 3823          // hint about accent color used (for custom controls)
};

enum DrawTextFlags {
    DTF_TOP = 0x0000,
    DTF_LEFT = 0x0000,
    DTF_CENTER = 0x0001,
    DTF_RIGHT = 0x0002,
    DTF_VCENTER = 0x0004,
    DTF_BOTTOM = 0x0008,
    DTF_WORDBREAK = 0x0010,
    DTF_SINGLELINE = 0x0020,
    DTF_EXPANDTABS = 0x0040,
    DTF_TABSTOP = 0x0080,
    DTF_NOCLIP = 0x0100,
    DTF_EXTERNALLEADING = 0x0200,
    DTF_CALCRECT = 0x0400,
    DTF_NOPREFIX = 0x0800,
    DTF_INTERNAL = 0x1000,
    DTF_EDITCONTROL = 0x2000,
    DTF_PATH_ELLIPSIS = 0x4000,
    DTF_END_ELLIPSIS = 0x8000,
    DTF_MODIFYSTRING = 0x10000,
    DTF_RTLREADING = 0x20000,
    DTF_WORD_ELLIPSIS = 0x40000,
    DTF_NOFULLWIDTHCHARBREAK = 0x80000,
    DTF_HIDEPREFIX = 0x100000,
    DTF_PREFIXONLY = 0x200000
};

#endif // ifndef THEMEAPI


#define DET_BDR_RAISEDOUTER 0x0001
#define DET_BDR_SUNKENOUTER 0x0002
#define DET_BDR_RAISEDINNER 0x0004
#define DET_BDR_SUNKENINNER 0x0008

#define DET_BDR_OUTER (DET_BDR_RAISEDOUTER | DET_BDR_SUNKENOUTER)
#define DET_BDR_INNER (DET_BDR_RAISEDINNER | DET_BDR_SUNKENINNER)
#define DET_BDR_RAISED (DET_BDR_RAISEDOUTER | DET_BDR_RAISEDINNER)
#define DET_BDR_SUNKEN (DET_BDR_SUNKENOUTER | DET_BDR_SUNKENINNER)


#define DET_EDGE_RAISED (DET_BDR_RAISEDOUTER | DET_BDR_RAISEDINNER)
#define DET_EDGE_SUNKEN (DET_BDR_SUNKENOUTER | DET_BDR_SUNKENINNER)
#define DET_EDGE_ETCHED (DET_BDR_SUNKENOUTER | DET_BDR_RAISEDINNER)
#define DET_EDGE_BUMP (DET_BDR_RAISEDOUTER | DET_BDR_SUNKENINNER)

#ifndef DFCS_TRANSPARENT
#define DFCS_TRANSPARENT        0x0800
#endif
#ifndef DFCS_HOT
#define DFCS_HOT                0x1000
#endif

#ifndef THEMEAPI
#if !defined(INTLIST)
//-----------------------------------------------------------------------
#define MAX_INTLIST_COUNT 10
typedef struct _INTLIST
{
    int iValueCount;      // number of values in iValues
    int iValues[MAX_INTLIST_COUNT];
} INTLIST, *PINTLIST;
#endif
#endif

class CVisualStylesXP
{
private:
	static HMODULE m_hThemeDll;
  static int     m_nUseCount;

	void* GetProc(LPCSTR szProc, void* pfnFail);

	typedef HTHEME(__stdcall *PFNOPENTHEMEDATA)(HWND hwnd, LPCWSTR pszClassList);
	static HTHEME OpenThemeDataFail(HWND , LPCWSTR )
	{return NULL;}

	typedef HRESULT(__stdcall *PFNCLOSETHEMEDATA)(HTHEME hTheme);
	static HRESULT CloseThemeDataFail(HTHEME)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, const RECT *pRect,  const RECT *pClipRect);
	static HRESULT DrawThemeBackgroundFail(HTHEME, HDC, int, int, const RECT *, const RECT *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMETEXT)(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);
	static HRESULT DrawThemeTextFail(HTHEME, HDC, int, int, LPCWSTR, int, DWORD, DWORD, const RECT*)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	static HRESULT GetThemeBackgroundContentRectFail(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect)
	{return E_FAIL;}
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDEXTENT)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	static HRESULT GetThemeBackgroundExtentFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNGETTHEMEPARTSIZE)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, RECT * pRect, enum THEMESIZE eSize,  SIZE *psz);
	static HRESULT GetThemePartSizeFail(HTHEME, HDC, int, int, RECT *, enum THEMESIZE, SIZE *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTEXTENT)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	static HRESULT GetThemeTextExtentFail(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTMETRICS)(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm);
	static HRESULT GetThemeTextMetricsFail(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDREGION)(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion);
	static HRESULT GetThemeBackgroundRegionFail(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNHITTESTTHEMEBACKGROUND)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	static HRESULT HitTestThemeBackgroundFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEEDGE)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	static HRESULT DrawThemeEdgeFail(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEICON)(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
	static HRESULT DrawThemeIconFail(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEPARTDEFINED)(HTHEME hTheme, int iPartId, 
		int iStateId);
	static BOOL IsThemePartDefinedFail(HTHEME hTheme, int iPartId, 
		int iStateId)
	{return FALSE;}

	typedef BOOL (__stdcall *PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)(HTHEME hTheme, 
		int iPartId, int iStateId);
	static BOOL IsThemeBackgroundPartiallyTransparentFail(HTHEME hTheme, 
		int iPartId, int iStateId)
	{return FALSE;}

	typedef HRESULT (__stdcall *PFNGETTHEMECOLOR)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor);
	static HRESULT GetThemeColorFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMETRIC)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT GetThemeMetricFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESTRING)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars);
	static HRESULT GetThemeStringFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBOOL)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal);
	static HRESULT GetThemeBoolFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINT)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT GetThemeIntFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEENUMVALUE)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT GetThemeEnumValueFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPOSITION)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint);
	static HRESULT GetThemePositionFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFONT)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont);
	static HRESULT GetThemeFontFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMERECT)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect);
	static HRESULT GetThemeRectFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMARGINS)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins);
	static HRESULT GetThemeMarginsFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINTLIST)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList);
	static HRESULT GetThemeIntListFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPROPERTYORIGIN)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin);
	static HRESULT GetThemePropertyOriginFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNSETWINDOWTHEME)(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	static HRESULT SetWindowThemeFail(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFILENAME)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars);
	static HRESULT GetThemeFilenameFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars)
	{return E_FAIL;}

	typedef COLORREF (__stdcall *PFNGETTHEMESYSCOLOR)(HTHEME hTheme, int iColorId);
	static COLORREF GetThemeSysColorFail(HTHEME hTheme, int iColorId)
	{return RGB(255,255,255);}

	typedef HBRUSH (__stdcall *PFNGETTHEMESYSCOLORBRUSH)(HTHEME hTheme, int iColorId);
	static HBRUSH GetThemeSysColorBrushFail(HTHEME hTheme, int iColorId)
	{return NULL;}

	typedef BOOL (__stdcall *PFNGETTHEMESYSBOOL)(HTHEME hTheme, int iBoolId);
	static BOOL GetThemeSysBoolFail(HTHEME hTheme, int iBoolId)
	{return FALSE;}

	typedef int (__stdcall *PFNGETTHEMESYSSIZE)(HTHEME hTheme, int iSizeId);
	static int GetThemeSysSizeFail(HTHEME hTheme, int iSizeId)
	{return 0;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSFONT)(HTHEME hTheme, int iFontId,  LOGFONT *plf);
	static HRESULT GetThemeSysFontFail(HTHEME hTheme, int iFontId,  LOGFONT *plf)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSSTRING)(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars);
	static HRESULT GetThemeSysStringFail(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSINT)(HTHEME hTheme, int iIntId, int *piValue);
	static HRESULT GetThemeSysIntFail(HTHEME hTheme, int iIntId, int *piValue)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEACTIVE)();
	static BOOL IsThemeActiveFail()
	{return FALSE;}

	typedef BOOL(__stdcall *PFNISAPPTHEMED)();
	static BOOL IsAppThemedFail()
	{return FALSE;}

	typedef HTHEME (__stdcall *PFNGETWINDOWTHEME)(HWND hwnd);
	static HTHEME GetWindowThemeFail(HWND hwnd)
	{return NULL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMEDIALOGTEXTURE)(HWND hwnd, DWORD dwFlags);
	static HRESULT EnableThemeDialogTextureFail(HWND hwnd, DWORD dwFlags)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEDIALOGTEXTUREENABLED)(HWND hwnd);
	static BOOL IsThemeDialogTextureEnabledFail(HWND hwnd)
	{return FALSE;}

	typedef DWORD (__stdcall *PFNGETTHEMEAPPPROPERTIES)();
	static DWORD GetThemeAppPropertiesFail()
	{return 0;}

	typedef void (__stdcall *PFNSETTHEMEAPPPROPERTIES)(DWORD dwFlags);
	static void SetThemeAppPropertiesFail(DWORD dwFlags)
	{return;}

	typedef HRESULT (__stdcall *PFNGETCURRENTTHEMENAME)(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars);
	static HRESULT GetCurrentThemeNameFail(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEDOCUMENTATIONPROPERTY)(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars);
	static HRESULT GetThemeDocumentationPropertyFail(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEPARENTBACKGROUND)(HWND hwnd, HDC hdc,  RECT* prc);
	static HRESULT DrawThemeParentBackgroundFail(HWND hwnd, HDC hdc,  RECT* prc)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMING)(BOOL fEnable);
	static HRESULT EnableThemingFail(BOOL fEnable)
	{return E_FAIL;}
public:
	HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList);
	HRESULT CloseThemeData(HTHEME hTheme);
	HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect);
	HRESULT DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);

  BOOL DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCTSTR lpszText, DWORD dwTextFlags, DWORD dwTextFlags2, const RECT *pRect);
  
  HRESULT GetThemeBackgroundContentRect(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	HRESULT GetThemeBackgroundExtent(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	HRESULT GetThemePartSize(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, RECT * pRect, enum THEMESIZE eSize, SIZE *psz);
	HRESULT GetThemeTextExtent(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	HRESULT GetThemeTextMetrics(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm);
	HRESULT GetThemeBackgroundRegion(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion);
	HRESULT HitTestThemeBackground(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	HRESULT DrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
	BOOL IsThemePartDefined(HTHEME hTheme, int iPartId, 
		int iStateId);
	BOOL IsThemeBackgroundPartiallyTransparent(HTHEME hTheme, 
		int iPartId, int iStateId);
	HRESULT GetThemeColor(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor);
	HRESULT GetThemeMetric(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemeString(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars);
	HRESULT GetThemeBool(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal);
	HRESULT GetThemeInt(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemeEnumValue(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemePosition(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint);
	HRESULT GetThemeFont(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont);
	HRESULT GetThemeRect(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect);
	HRESULT GetThemeMargins(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins);
	HRESULT GetThemeIntList(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList);
	HRESULT GetThemePropertyOrigin(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin);
	HRESULT SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	HRESULT GetThemeFilename(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars);
	COLORREF GetThemeSysColor(HTHEME hTheme, int iColorId);
	HBRUSH GetThemeSysColorBrush(HTHEME hTheme, int iColorId);
	BOOL GetThemeSysBool(HTHEME hTheme, int iBoolId);
	int GetThemeSysSize(HTHEME hTheme, int iSizeId);
	HRESULT GetThemeSysFont(HTHEME hTheme, int iFontId,  LOGFONT *plf);
	HRESULT GetThemeSysString(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars);
	HRESULT GetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue);
	BOOL IsThemeActive();
	BOOL IsAppThemed();	
	HTHEME GetWindowTheme(HWND hwnd);
	HRESULT EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags);
	BOOL IsThemeDialogTextureEnabled(HWND hwnd);
	DWORD GetThemeAppProperties();
	void SetThemeAppProperties(DWORD dwFlags);
	HRESULT GetCurrentThemeName(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars);
	HRESULT GetThemeDocumentationProperty(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars);
	HRESULT DrawThemeParentBackground(HWND hwnd, HDC hdc,  RECT* prc);
	HRESULT EnableTheming(BOOL fEnable);
public:
	CVisualStylesXP(void);
	~CVisualStylesXP(void);

	BOOL UseVisualStyles();	// Added by Mathias Tunared 2002-07-27
  BOOL IsThemeLibAvailable() { return m_hThemeDll!=NULL; }

};

extern CVisualStylesXP g_xpStyle;

#endif