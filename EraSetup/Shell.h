#if !defined(SHELL_H_INCLUDED)
#define SHELL_H_INCLUDED

HRESULT CreateLink(LPCSTR lpszPathObj, LPCSTR lpszPathLink, LPCSTR lpszDesc, LPCSTR pszIconPath=NULL, int iIcon=0, LPCSTR pszArgs=NULL);

//HRESULT CreateShellFolder(LPCSTR lpszPathObj, LPCSTR lpszPathLink, LPCSTR pszIconPath=NULL, int iIcon=0);

/************************************** : by VK at 01.03.2004 1:50:29 **\

#include "EnumIDL.h"

class CShellFolder : public IShellFolder, public IPersistFolder {
friend class CShellView;
friend class CEnumIDList;
friend class CDataObject;
protected:
	ULONG m_ulRef;

public:
	CShellFolder(CShellFolder*, LPCITEMIDLIST lpidl);
	~CShellFolder();

	//IUnknown methods
	STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
	STDMETHOD_ (ULONG, AddRef) (void);
	STDMETHOD_ (ULONG, Release) (void);

	//IPersist methods
	STDMETHODIMP GetClassID(LPCLSID);

	//IPersistFolder methods
	STDMETHODIMP Initialize(LPCITEMIDLIST);

	//IShellFolder methods
	STDMETHOD (ParseDisplayName) (HWND, LPBC, LPOLESTR, LPDWORD, LPITEMIDLIST*, LPDWORD);
	STDMETHOD (EnumObjects) (HWND, DWORD, LPENUMIDLIST*);
	STDMETHOD (BindToObject) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
	STDMETHOD (BindToStorage) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
	STDMETHOD (CompareIDs) (LPARAM, LPCITEMIDLIST, LPCITEMIDLIST);
	STDMETHOD (CreateViewObject) (HWND, REFIID, LPVOID* );
	STDMETHOD (GetAttributesOf) (UINT, LPCITEMIDLIST*, LPDWORD);
	STDMETHOD (GetUIObjectOf) (HWND, UINT, LPCITEMIDLIST*, REFIID, LPUINT, LPVOID*);
	STDMETHOD (GetDisplayNameOf) (LPCITEMIDLIST, DWORD, LPSTRRET);
	STDMETHOD (SetNameOf) (HWND, LPCITEMIDLIST, LPCOLESTR, DWORD, LPITEMIDLIST*);
private:
	FOLDERSETTINGS	m_fsFolderSettings;
	LPMALLOC		    m_pMalloc;
	LPPIDLMGR		    m_pPidlMgr;
private:
	LPCITEMIDLIST	  m_pidl;
	LPITEMIDLIST	  m_pidlFQ;
private:
	CShellFolder	*m_psfParent;
};
\************************************** : by VK at 01.03.2004 1:50:32 **/

#endif // SHELL_H_INCLUDED