//
// Excel.cpp
//
#include "stdafx.h"
#include "Excel.h"


//#include <afxdisp.h>        // MFC Automation classes

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#pragma warning (disable:4192) 

#import "..\MSO\mso9.dll"    no_namespace rename("DocumentProperties", "DocumentPropertiesXL")
#import "..\MSO\vbe6ext.olb" no_namespace
#import "..\MSO\excel8.olb"  no_namespace rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces

//#include "..\MSO\


void CreateExcelAndPasteSelection() {
}