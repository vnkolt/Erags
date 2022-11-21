#if !defined(HELPMAN_H_INCLUDED)
#define HELPMAN_H_INCLUDED

#define UNM_HYPERLINK_CLICKED	(WM_APP + 0x100)

class CPPToolTip;

class CToolTipCache  {
public:
  CToolTipCache();
  ~CToolTipCache();
// Data members:
  CMapStringToString  m_map;
// Operations:
public:
  void    Clear();
  void    Add(LPCTSTR szParentName, LPCTSTR szControlName, CString& szContent);
  CString Lookup(LPCTSTR szParentName, LPCTSTR szControlName);
  void    FillForParent(TCHAR* pBuffer, CWnd* pParent, LPCTSTR szFormName, CPPToolTip* pTooltip);
  void    Fill(CWnd* pParent, LPCTSTR szFormName, CPPToolTip* pTooltip);
  void    FillForToolBar(CToolBar* pParent, LPCTSTR szName, CPPToolTip* pTooltip);
};

extern  CToolTipCache theToolTipCache;

void    SetDefaults(CPPToolTip* pPPToolTip);
void    AddTool(CWnd* pParent, CPPToolTip* pPPToolTip, LPCTSTR szParentName, UINT CtrlId);

void    ShowHelpTooltip(CPPToolTip* pPPToolTip, CToolBar* pParent, LPCTSTR szParentName, UINT CtrlId);
void    ShowHelpTooltipSetFocus(CPPToolTip* pPPToolTip, CWnd* pParent, LPCTSTR szParentName, CWnd* pControl, UINT CtrlId);
void    ShowHelpTooltip(CPPToolTip* pPPToolTip, CWnd* pParent, LPCTSTR szParentName, UINT CtrlId);

#endif // HELPMAN_H_INCLUDED