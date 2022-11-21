// This is part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// ULawsDoc.h : interface of the CULawsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ULAWSDOC_H__47FF4083_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
#define AFX_ULAWSDOC_H__47FF4083_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CULawsDoc : public CDocument
{
protected: // create from serialization only
	CULawsDoc();
	DECLARE_DYNCREATE(CULawsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CULawsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CULawsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CULawsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULAWSDOC_H__47FF4083_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
