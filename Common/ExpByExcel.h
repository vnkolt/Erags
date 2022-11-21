#if !defined(EXPBYEXCEL_H_INCLUDED)
#define EXPBYEXCEL_H_INCLUDED

#pragma warning (push)
#pragma warning (disable:4146)
#pragma warning (disable:4192)
#import "..\MSO\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL")
#import "..\MSO\vbe6ext.olb" no_namespace    
#import "..\MSO\excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces 

using namespace Excel;

//
// ExpByExcel.h
//
class CExpByExcel {
public:
  CExpByExcel();
  ~CExpByExcel();
private:
  _ApplicationPtr m_pXL;
private:
  void  ReportComError(_com_error &e);
public:
  void          Quit();
  BOOL          CreateInstance();
  WorkbooksPtr  GetWorkbooks();
  _WorkbookPtr  Add(WorkbooksPtr pBooks);
  _WorksheetPtr GetActiveSheet();
  void          SetSheetName(_WorksheetPtr pSheet, LPCTSTR szName);
};

#pragma warning (pop)

#endif // EXPBYEXCEL_H_INCLUDED