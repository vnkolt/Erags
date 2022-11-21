//
// Shell.cpp
//
#include "stdafx.h"
#include <ShlObj.h>
#include <Shlwapi.h>
#include <Atlbase.h>
#include "Shell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************** : by VK at 11.03.2004 16:41:39 **\
LPITEMIDLIST CreatePIDL(DWORD dwType, LPCWSTR pwszDisplayName) {
  LPMYPIDLDATA   pidlOut;
  USHORT         uSize;

  pidlOut = NULL;

  //Calculate the size of the MYPIDLDATA structure.

  uSize = sizeof(MYPIDLDATA);

  //
  // Allocate enough memory for the PIDL to hold a 
  // MYPIDLDATA structure plus the terminator
  //

  pidlOut = (LPMYPIDLDATA)m_pMalloc->Alloc(uSize + sizeof(USHORT));

  if(pidlOut) {
   //Assign values to the members of the MYPIDLDATA structure
   //that is the PIDL's first SHITEMID structure
   
   pidlOut->cb = uSize;
   pidlOut->dwType = dwType;
   lstrcpy(pidlOut->wszDisplayName,pwszDisplayName);
    
   //Advance the pointer to the start of the next SHITEMID structure.

   pidlOut = (LPMYPIDLDATA)((LPBYTE)pidlOut + pidlOut->cb);
   
   //Create the NULL terminator by setting cb to 0.
   pidlOut->cb = 0;
  }

  return pidlOut;
}
\************************************** : by VK at 11.03.2004 16:41:42 **/

// Use the shell's IMalloc implementation to free resources
HRESULT FreeResources(LPVOID pData) {
   HRESULT hr;
   LPMALLOC pMalloc = NULL;

   if (SUCCEEDED(hr = SHGetMalloc(&pMalloc))) {
      pMalloc->Free((LPVOID)pData);
      pMalloc->Release();
   }

   return hr;
}

//
// SHGetDesktopFolder
//

// CreateLink - uses the Shell's IShellLink and IPersistFile interfaces 
//   to create and store a shortcut to the specified object. 
// Returns the result of calling the member functions of the interfaces. 
// lpszPathObj - address of a buffer containing the path of the object. 
// lpszPathLink - address of a buffer containing the path where the 
//   Shell link is to be stored. 
// lpszDesc - address of a buffer containing the description of the 
//   Shell link. 
 
HRESULT CreateLink(LPCSTR lpszPathObj, LPCSTR lpszPathLink, LPCSTR lpszDesc, LPCSTR pszIconPath, int iIcon, LPCSTR pszArgs) { 
  HRESULT hres; 
  IShellLink* psl; 
 
  // Get a pointer to the IShellLink interface. 
  hres = CoCreateInstance(CLSID_ShellLink, NULL,  CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl); 
  if (SUCCEEDED(hres)) {
    IPersistFile* ppf; 
 
    // Set the path to the shortcut target and add the 
    // description. 
    psl->SetPath(lpszPathObj); 
    psl->SetDescription(lpszDesc);

    if ( pszArgs )
      psl->SetArguments(pszArgs);

    if (pszIconPath)
      psl->SetIconLocation(pszIconPath, iIcon);
 
    // Query IShellLink for the IPersistFile interface for saving the 
    // shortcut in persistent storage. 
    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf); 
 
    if (SUCCEEDED(hres)) { 
      WCHAR wsz[MAX_PATH]; 
 
      // Ensure that the string is Unicode. 
      MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH); 
 
      // Save the link by calling IPersistFile::Save. 
      hres = ppf->Save(wsz, TRUE); 

      ppf->Release(); 
    } 
    psl->Release(); 
  } 
  return hres; 
}


HRESULT CreateShellFolder(LPCSTR lpszPathObj, LPCSTR pszIconPath/*=NULL*/, int iIcon/*=0*/) {
  HRESULT hRes; 
  IShellFolder* psf;

  LPMALLOC pMalloc;

  if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
 
    // Get a pointer to the IShellFolder interface. 
    hRes = SHGetDesktopFolder(&psf);

    if (SUCCEEDED(hRes)) {
      LPITEMIDLIST pidl = NULL;
      ULONG chEaten;
      ULONG celtFetched;
      CComBSTR bstr(lpszPathObj);
      hRes = psf->ParseDisplayName(NULL, NULL, bstr, &chEaten, &pidl, NULL);
      if ( pidl  )
        pMalloc->Free(pidl);

/************************************** : by VK at 11.03.2004 18:19:30 **\
      IEnumIDList* pEnumIDList;
      hRes = psf->EnumObjects(NULL, SHGDN_FORPARSING, &pEnumIDList);
      if (SUCCEEDED(hRes)) {
        hRes = pEnumIDList->Reset();
        while( S_OK==hRes ) {
          LPITEMIDLIST   pidl = NULL;
          hRes = pEnumIDList->Next(1, &pidl, NULL);
          if ( pidl ) {
            IShellFolder *psfOut;
            hRes = psf->BindToObject(pidl, NULL, IID_IShellFolder, (VOID**)&psfOut);
            if (SUCCEEDED(hRes)) {
              STRRET strName;
              TCHAR szDisplayName[MAX_PATH];
              psfOut->GetDisplayNameOf(pidl, SHGDN_INFOLDER, &strName);
              if (STRRET_WSTR == strName.uType)
                FreeResources((LPVOID)strName.pOleStr);
              psfOut->Release();
            }

            pMalloc->Free(pidl);
          }
        }
        pEnumIDList->Release();
      }

\************************************** : by VK at 11.03.2004 18:19:40 **/
      IExtractIcon* pExtractIcon;
      // Query IExtractIcon
      hRes = psf->QueryInterface(IID_IExtractIcon, (VOID**)&pExtractIcon);
 
      if (SUCCEEDED(hRes)) { 
        WCHAR wsz[MAX_PATH]; 
 /************************************** : by VK at 11.03.2004 14:43:41 **\
        // Ensure that the string is Unicode. 
        MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH); 
 
        // Save the link by calling IPersistFile::Save. 
        hres = ppf->Save(wsz, TRUE); 
\************************************** : by VK at 11.03.2004 14:43:43 **/
        pExtractIcon->Release(); 
      } 
      psf->Release(); 
    }
    pMalloc->Release();
  }
  return hRes;
}