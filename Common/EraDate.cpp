//
// EraDate.cpp
//
#include "stdafx.h"
#include "EraDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL AFXAPI AfxFieldText(CDataExchange* pDX, int nIDC, void* pv, CDaoRecordset* pRecordset); // in DaoView.cpp


COleDateTime ParseDate(const CString& szDate) {
  COleDateTime odt;
  LCID lcID = MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN),SORT_DEFAULT);
  odt.ParseDateTime(szDate, VAR_DATEVALUEONLY, lcID);
  return odt;
}
BOOL CEraDate::ParseDate(const CString& szDate) {
  LCID lcID = MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN),SORT_DEFAULT);
  return ParseDateTime(szDate, VAR_DATEVALUEONLY, lcID);
}


/////////////////////////////////////////////////////////////////////////////
// DDX for mask control
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, CEraDate& value) {
	CString s;
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate) {
		int nLen = ::GetWindowTextLength(hWndCtrl);

		::GetWindowText(hWndCtrl, s.GetBufferSetLength(nLen), nLen+1);
		s.ReleaseBuffer();

    //LCID lcID = MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN),SORT_DEFAULT);
		if (!value.ParseDate(s)) { // throws exception
			// Can't convert string to datetime
			AfxMessageBox(AFX_IDP_PARSE_DATETIME);
			pDX->Fail();    // throws exception
		}
	}
	else {
    s.Format(_T(""), value.GetDay(), value.GetMonth(), value.GetYear());
		AfxSetWindowText(hWndCtrl, s);
	}
}

void AFXAPI DDX_FieldText(CDataExchange* pDX, int nIDC, CEraDate& value, CDaoRecordset* pRecordset) {
	if (!AfxFieldText(pDX, nIDC, &value, pRecordset))
		DDX_Text(pDX, nIDC, value);
}
