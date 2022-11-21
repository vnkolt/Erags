// GetTreeDoc.h : interface of the CGeoTreeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOTREEDOC_H__6E51006B_1A14_11D8_9063_00409533E092__INCLUDED_)
#define AFX_GEOTREEDOC_H__6E51006B_1A14_11D8_9063_00409533E092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeType.h"

enum FILE_FORMAT
{
    FF_TREE_TYPE,
    FF_INDENT_TYPE,
    FF_CSV_TYPE,
	FF_MAX_TYPES,

	FF_DIRECTORY_TYPE, // Special type to read directories
	FF_CLIPBOARD_TYPE, // Special type to copy to/from the Clipboard
};


enum HINT
{
	HINT_NONE = 0,
	HINT_NEW,
	HINT_LOAD_DIRECTORY,
	HINT_LOAD_TREE_TYPE,
	HINT_LOAD_IDENT_TYPE,
	HINT_LOAD_CSV_TYPE,
	HINT_SAVE_TREE_TYPE,
	HINT_SAVE_IDENT_TYPE,
	HINT_SAVE_CSV_TYPE,
};

struct EXTENSION
{
	char *m_text;
	char *m_name;

	EXTENSION(char *text, char *name)
	{
		m_text = text;
		m_name = name;
	}
};

struct  HINT_EXT
{
	HINT m_hint;
	FILE_FORMAT m_ff;

	HINT_EXT(HINT hint, FILE_FORMAT ff)
	{
		m_hint = hint;
		m_ff = ff;
	}
};

class CGeoTreeDoc : public CDocument
{
protected: // create from serialization only
	CGeoTreeDoc();
	DECLARE_DYNCREATE(CGeoTreeDoc)

	void OnButtonBrowse();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTreeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGeoTreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoTreeDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTREEDOC_H__6E51006B_1A14_11D8_9063_00409533E092__INCLUDED_)
