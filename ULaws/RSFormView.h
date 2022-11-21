#if !defined(RSFORMVIEW_H_INCLUDED)
#define RSFORMVIEW_H_INCLUDED

//
// RSFormView.h
//

#define SCALE_NONE  0     // 00000000
#define SCALE_WIDTH 1     // 00000001
#define SCALE_HEIGH 2     // 00000010
#define SCALE_ALL   3     // 00000011

struct SResizeWndInfo {
  RECT  rect;
  WORD  wFlags;
};

typedef CMap<HWND, HWND, SResizeWndInfo, SResizeWndInfo>  ResizeMap;

////////////////////////////////////////////////////////////////////////////
// CResizableFormView
class CResizableFormView : public CFormView {
  DECLARE_DYNAMIC(CResizableFormView)
// Construction
protected:
  CResizableFormView(LPCTSTR lpszTemplateName);
  CResizableFormView(UINT nIDTemplate);
  ~CResizableFormView();

// Attributes
protected:
  BOOL        m_fRestoredRectSaved;
  BOOL        m_ResizableEnabled;
  CRect       m_RestoredRect;
  ResizeMap   m_ResizeMap;

  CPtrArray     m_Statics;
  CMapPtrToPtr  m_Brushes;
  LOGFONT       m_OriginLogFont;

// Operations
protected:
  virtual void SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void OnMoveControl(CWnd* pWnd, LPRECT lpRect, BOOL bRepaint = TRUE);

  BOOL         SetRect(CWnd* pWnd, const RECT* pNewRect);
  void         FillChildsMap();
  void         SetFontForChildren(CFont* pFont);

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CResizableFormView)
  protected:
  virtual void OnInitialUpdate(); // called first time after construct
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CResizableFormView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif // RSFORMVIEW_H_INCLUDED