//
// IsAdmin.cpp
//
#include "stdafx.h"
#include "IsAdmin.h"

BOOL IsAdmin() {
  HANDLE                   hAccessToken;
  BYTE                     *InfoBuffer;
  PTOKEN_GROUPS            ptgGroups;
  DWORD                    dwInfoBufferSize;
  PSID                     psidAdministrators;
  SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
  UINT                     i;
  BOOL                     bRet = FALSE;

  if(!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hAccessToken))
    goto cleanup;
    
  InfoBuffer = new BYTE[1024];
  if(!InfoBuffer)
    goto cleanup;

  bRet = GetTokenInformation(hAccessToken,
                             TokenGroups,
                             InfoBuffer,
                             1024,
                             &dwInfoBufferSize);

  CloseHandle( hAccessToken );
  if(!bRet)
    goto cleanup;

  if(!AllocateAndInitializeSid(&siaNtAuthority,
                               2,
                               SECURITY_BUILTIN_DOMAIN_RID,
                               DOMAIN_ALIAS_RID_ADMINS,
                               0,0,0,0,0,0,
                               &psidAdministrators))
    goto cleanup;

    bRet = FALSE;

    ptgGroups = (PTOKEN_GROUPS)InfoBuffer;

    for(i=0;i<ptgGroups->GroupCount;i++)
    {
        if(EqualSid(psidAdministrators,ptgGroups->Groups[i].Sid))
        {
            bRet = TRUE;
            break;
        }
    }

    FreeSid(psidAdministrators);

cleanup:

  if (InfoBuffer)
    delete InfoBuffer;

  return bRet;
}