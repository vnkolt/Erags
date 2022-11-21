#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// ExtNotice.h
//

void    SetChangedBy(CDaoRecordset* pRS, CString& szExtNotice);
CString GetLastUpdatedDate(CDaoRecordset* pRS);
CString GetSpecPost(CDaoRecordset* pRS);
CString GetSpecName(CDaoRecordset* pRS);
