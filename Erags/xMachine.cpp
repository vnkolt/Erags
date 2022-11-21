//
// xMachine.cpp
//
#include "stdafx.h"
#include "Erags.h"

#include "Defaults.h"
#include "EraForm.h"
#include "MainFrm.h"
#include "SecReg.h"
#include "xMachine.h"
#include "LogThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD g_dwDebugger_Present_1 = 999999;
CXMachine* g_pMachine = NULL;
BYTE  g_btDebugger_Present_2 = 0;
extern short g_SecurityKeysCheckedOk[];
extern short g_SecurityLoaded[];

TCHAR szKernel32[]          = { 'k'-0, 'e'-1, 'r'-2, 'n'-3, 'e'-4, 'l'-5, '3'-6, '2'-7, '.'-8, 'd'-9, 'l'-10, 'l'-11 };
TCHAR szIsDebuggerPresent[] = { 'I'-0, 's'-3, 'D'-6, 'e'-9, 'b'-12,'u'-15,'g'-18,'g'-21,'e'-24,'r'-27,'P'-30, 'r'-33, 'e'-36, 's'-39, 'e'-42, 'n'-45, 't'-48 };

typedef WINBASEAPI int (WINAPI pIsDebuggerPresent());

BOOL IsDebuggerAttachedForWin98() {
  try {
    CString sIsDebuggerPresent;
    int i;
    CString sKernel32;
    for( i=0; i < sizeof(szKernel32); i++ ) {
      sKernel32 += (TCHAR)((TCHAR)i+szKernel32[i]);
    }
    for( i=0; i < sizeof(szIsDebuggerPresent); i++ ) {
      sIsDebuggerPresent += (TCHAR)((TCHAR)(i*3)+szIsDebuggerPresent[i]);
    }
    HMODULE hKernel32 = ::GetModuleHandle(sKernel32);
    pIsDebuggerPresent* fIsDebuggerPresent = (pIsDebuggerPresent*)GetProcAddress(hKernel32, sIsDebuggerPresent);
    return fIsDebuggerPresent();
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("IsDA98"));
  }
  return false;
}

BOOL IsDebuggerAttached() {
  if ( g_Shell >= WinNT4 ) {
    DWORD dw(0);
    try {
      __asm {
        push eax    // Preserve the registers
        push ecx
        mov eax, fs:[0x18]  // Get the TIB's linear address
        mov eax, dword ptr [eax + 0x30]
        mov ecx, dword ptr [eax]    // Get the whole DWORD
        mov dw, ecx // Save it
        pop ecx // Restore the registers
        pop eax
      }
    }
    catch(...) {
      Log(_T("Нераспознанная ошибка"), _T("IDA4"));
    }
    // The 3rd byte is the byte we really need to check for the
    // presence of a debugger.
    // Check the 3rd byte
    return (BOOL)(dw & 0x00010000 ? TRUE : FALSE);
  }
  return IsDebuggerAttachedForWin98();
}

// CIsDebuggerAttached
CIsDebuggerAttached::CIsDebuggerAttached(void* pUnusedPointer1, void* pUnusedPointer2) {
  m_pUnusedPointer1 = pUnusedPointer1;
  m_pUnusedPointer2 = pUnusedPointer2;
}

void CIsDebuggerAttached::Do() {
  if ( IsDebuggerAttached() ) {
    #ifndef _DEBUG
      _asm {
        pop esp
        pop ecx
        pop ebp
        jmp dword ptr [edx]
      }
    #else
      TRACE0("IsDebuggerAttached() returned TRUE.\n");
    #endif
    return;
  }
}
// CIsDebuggerPresent
CIsDebuggerPresent::CIsDebuggerPresent(void* pUnusedPointer1, void* pUnusedPointer2) {
  m_pUnusedPointer1 = pUnusedPointer1;
  m_pUnusedPointer2 = pUnusedPointer2;
}

void CIsDebuggerPresent::Do() {
  int i;
  BYTE szKernel32[] = { ~('k'+'\00'), ~('e'+'\01'), ~('r'+'\02'), ~('n'+'\03'), ~('e'+'\04'), ~('l'+'\05'), ~('3'+'\06'), ~('2'+'\07'), ~('.'+'\10'), ~('d'+'\11'), ~('l'+'\12'), ~('l'+'\13') };
  CString s;
  for( i= 0; i < sizeof(szKernel32); i++ ) s += (BYTE)~(szKernel32[i]+(BYTE)i);
  HMODULE hKernel = GetModuleHandle(s);
  if ( hKernel ) {
    s.Empty();
    typedef BOOL (*pIsDebuggerPresent)();
    BYTE szIsDebuggerPresent[] = { 'I', 's'-1*2, 'D'-2*2, 'e'-3*2, 'b'-4*2, 'u'-5*2, 'g'-6*2, 'g'-7*2, 'e'-8*2, 'r'-9*2, 'P'-10*2, 'r'-11*2, 'e'-12*2, 's'-13*2, 'e'-14*2, 'n'-15*2, 't'-16*2 };
    for( i= 0; i < sizeof(szIsDebuggerPresent); i++ )
      s += (TCHAR)(szIsDebuggerPresent[i]+(i<<1));
    pIsDebuggerPresent fIsDebuggerPresent = (pIsDebuggerPresent)::GetProcAddress(hKernel, s/*"IsDebuggerPresent"*/);
    if ( fIsDebuggerPresent && fIsDebuggerPresent() ) {
      #ifndef _DEBUG
      __asm {
        mov ebp, this.m_pUnusedPointer1
        mov esp, this.m_pUnusedPointer2
        jmp dword ptr es:[edi]
      }
      #else
        TRACE0("IsDebuggerPresent() returned TRUE.\n");
      #endif
    }
  }
}
// CXMachine
IMPLEMENT_DYNCREATE(CXMachine, CWinThread)
BEGIN_MESSAGE_MAP(CXMachine, CWinThread)
	//{{AFX_MSG_MAP(CXMachine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXMachine::CXMachine() {
  m_fInProc = false;
  m_fQuit = false;
}
CXMachine::~CXMachine() {
}
BOOL CXMachine::InitInstance() {
  m_hEventStop    = CreateEvent(NULL, FALSE, FALSE, NULL);
  m_hEventStopped = CreateEvent(NULL, FALSE, FALSE, NULL);
  m_hEventCmd     = CreateEvent(NULL, FALSE, FALSE, NULL);
  return TRUE;
}
int CXMachine::ExitInstance() {
  CloseHandle(m_hEventStopped);
  CloseHandle(m_hEventStop);
  CloseHandle(m_hEventCmd);
  return 0;
}

bool CXMachine::IsQueueEmpty() {
  return m_cmdQueue.GetCount() == 0 ? true : false;
}
void CXMachine::Clear() {
  CXCommand* pCommand = GetCmdHead();
  while (pCommand) {
    delete pCommand;
		pCommand = GetCmdHead();
	}
}

void CXMachine::DoCmdQueue() {
  CXCommand* pCommand = GetCmdHead();
  while (pCommand) {
    if ( m_fQuit ) {
      delete pCommand;
      return;
    }
    pCommand->Do();
    delete pCommand;
		pCommand = GetCmdHead();
	}
}

CXCommand* CXMachine::GetCmdHead() {
	CSingleLock sl(&m_cs,TRUE);
	CXCommand* pCommand = NULL;
	if (!m_cmdQueue.IsEmpty()) {
	  pCommand = m_cmdQueue.RemoveHead();
	}
	return pCommand;
}

void CXMachine::AddCommandToHead(CXCommand* pCommand) {
  CSingleLock sl(&m_cs,TRUE);
  if ( m_fQuit ) {  // by VK 27.05.2004 at 12:30:14: We should not add new messages after Stop()
    delete pCommand;
    return;
  }
  m_cmdQueue.AddHead(pCommand);
  VERIFY(SetEvent(m_hEventCmd));
}

void CXMachine::AddCommand(CXCommand* pCommand) {
  CSingleLock sl(&m_cs, true);
  if ( m_fQuit ) {  // by VK 27.05.2004 at 12:30:14: We should not add new messages after Stop()
    delete pCommand;
    return;
  }
  m_cmdQueue.AddTail(pCommand);
  if ( FALSE==SetEvent(m_hEventCmd) ) {
    DWORD dwError = GetLastError();
  }
}

void CXMachine::Stop() {
  VERIFY(SetEvent(m_hEventStop));
  m_fQuit = true;
  DWORD dwWaitRes = WaitForSingleObject(m_hEventStopped, 3000);
}

int CXMachine::Run() {
  HANDLE hArray[2];
	hArray[0] = (HANDLE) m_hEventStop;
  hArray[1] = (HANDLE) m_hEventCmd;

  m_fInProc = true;

  while (TRUE ) {
    DWORD dwWaitRes = WaitForMultipleObjects(2, hArray, FALSE, INFINITE);
    if (WAIT_OBJECT_0==dwWaitRes)
      break;
    else if ((WAIT_OBJECT_0 + 1)==dwWaitRes)
      DoCmdQueue();
  }
  Clear();

  m_fInProc = false;
  VERIFY(SetEvent(m_hEventStopped));

  return ExitInstance();
}
