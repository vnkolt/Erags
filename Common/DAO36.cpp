//
// DAO36.cpp
//
#include "stdafx.h"
#include "DAO36.h"

#include <afxdao.h>
#include <dbdaoid.h>
#include "daoimpl.h"

#ifndef _AFX_NO_DAO_SUPPORT
class _AFX_DAO_STATE;
#endif

DEFINE_DAOGUID(CLSID35_CDAODBEngine,		0x00000010);

_AFX_DAO_STATE* AFX_CDECL AfxGetDaoState();

#define new DEBUG_NEW


void AFXAPI AfxDaoInit36() {
	_AFX_DAO_STATE* pDaoState = AfxGetDaoState();

	// Attempt to initialize OLE component objects
	//  (use default IMalloc allocator)
	DAO_CHECK_ERROR(::CoInitialize(NULL),
		AFX_DAO_ERROR_ENGINE_INITIALIZATION);
	pDaoState->m_bOleInitialized = TRUE;

	// Hook AfxDaoTerm to CWinApp, otherwise explicit AfxDaoTerm call req'd
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->m_lpfnDaoTerm = AfxDaoTerm;

	BYTE bUseDao = 36;

	CLSID clsidEngine;
	COleVariant varKey;
	GUID guidEngine;

	// Set the interface type
#ifdef _UNICODE
			guidEngine = IID_IDAODBEngineW;
#else
			guidEngine = IID_IDAODBEngine;
#endif

	// DAO 3.5 and 3.6 runtime key
	varKey = _T("mbmabptebkjcdlgtjmskjwtsdhjbmkmwtrak");

	switch (bUseDao)
	{
		case 35:
			// Use DAO 3.5
			clsidEngine = CLSID35_CDAODBEngine;
			break;

		case 30:
			// Use DAO 3.0
			clsidEngine = CLSID30_CDAODBEngine;

			// DAO 3.0 runtime key
			varKey = _T("mjgcqcejfchcijecpdhckcdjqigdejfccjri");

			// Set the interface type
#ifdef _UNICODE
			guidEngine = IID30_IDAODBEngineW;
#else
			guidEngine = IID30_IDAODBEngine;
#endif
			break;

		case 36:
			// Use DAO 3.6
			clsidEngine = CLSID_CDAODBEngine;
			break;

		default:
			ASSERT(FALSE);
	}

	LPCLASSFACTORY2 pCF2;
	DAO_CHECK_ERROR(::CoGetClassObject(clsidEngine,
		CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory2, (LPVOID*)&pCF2),
		AFX_DAO_ERROR_ENGINE_INITIALIZATION);

	TRY
	{
		DAO_CHECK_ERROR(pCF2->CreateInstanceLic( NULL, NULL, guidEngine,
			V_BSTR(&varKey), (LPVOID*)&pDaoState->m_pDAODBEngine),
			AFX_DAO_ERROR_ENGINE_INITIALIZATION);
	}
	CATCH_ALL(e)
	{
		pCF2->Release();
		THROW_LAST();
	}
	END_CATCH_ALL

	pCF2->Release();
}

