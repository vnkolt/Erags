// By Xiao Wu Guang

// KMComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKMComboBox window
#ifndef _KMCOMBOBOX_H_
#define _KMCOMBOBOX_H_
 
#define LEFTMARGIN_OF_DROPDOWNLIST		2
#define LEFTMARGIN_OF_CONTROL			1
#define RIGHTMARGIN_OF_DROPDOWNLIST		4 
#define SPACE_BETWEEN_COLUMN			1 

#include "EraControls.h"

class CKMComboBox : public CEraComboBox {
// Construction
public:
	CKMComboBox();
	
// Attributes
public:
	void	FormatComboBox(UINT TotalColumn = 2, UINT BoundColumn = 0);
	void	SetColumnWidth(UINT ColumnWidth0, ...);
	void	SetColumnAlignStyle(UINT ColumnAlignStyle0, ...);

// Operations
public:
	void	ResetContent();
	int		AddRow(LPCTSTR lpszString0, ...);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKMComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetColumnText(int nItem, int nCol);
	virtual ~CKMComboBox();

	// Generated message map functions
protected:
private:
	UINT			m_TotalColumn;
	UINT			m_BoundColumn;
	UINT			m_TextItemHeight;
	CPen			m_LightGrayPen;
	UINT*			m_ColumnWidth;
	UINT*			m_ColumnAlignStyle;
	CStringList*	m_ColumnItemList;
	HWND			m_hListBox;

	//{{AFX_MSG(CKMComboBox)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
  afx_msg LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
