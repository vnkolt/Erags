#if !defined(XMACHINE_H_INCLUDED)
#define XMACHINE_H_INCLUDED

#define DEBUGGER_PRESENT_1  (DWORD)(-1)
#define DEBUGGER_PRESENT_2  (BYTE)('v'+'n'+'k'+'@'+'u'+'k'+'r'+'.'+'n'+'e'+'t')

extern DWORD g_dwDebugger_Present_1;
extern BYTE  g_btDebugger_Present_2;


///////////////////////////////////////////////////////////////////////////////////
// CXCommand
class CXCommand : public CObject {
public:
  CXCommand(){}
  virtual ~CXCommand(){}
	virtual void Do() = 0;
};

class CDisableCommands : public CXCommand {
public:
  void *m_pUnusedPointer;
  CDisableCommands(void* pUnusedPointer);
  virtual void Do();
};


class CSetDebuggerPresent1 : public CXCommand {
public:
  CSetDebuggerPresent1(){}
  virtual void Do() { g_dwDebugger_Present_1 = DEBUGGER_PRESENT_1; }
};

class CIsDebuggerAttached : public CXCommand {
public:
  void *m_pUnusedPointer1, *m_pUnusedPointer2;
  CIsDebuggerAttached(void* pUnusedPointer1, void* pUnusedPointer2);
  virtual void Do();
};

class CIsDebuggerPresent : public CXCommand {
public:
  void *m_pUnusedPointer1, *m_pUnusedPointer2;
  CIsDebuggerPresent(void* pUnusedPointer1, void* pUnusedPointer2);
  virtual void Do();
};

/************************************** : by VK at 23.06.2006 8:09:20 **\
class CCloseAllDocuments : public CXCommand {
public:
  void *m_pUnusedPointer1, *m_pUnusedPointer2;
  CCloseAllDocuments(void* pUnusedPointer1, void* pUnusedPointer2);
  virtual void Do();
};
\************************************** : by VK at 23.06.2006 8:09:24 **/
/////////////////////////////////////////////////////////////////////////////
// CXMachine thread
class CXMachine : public CWinThread {
	DECLARE_DYNCREATE(CXMachine)
protected:
	CXMachine();           // protected constructor used by dynamic creation
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMachine)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Operations:
public:
  bool       IsQueueEmpty();
  void       AddCommandToHead(CXCommand* pCommand);
  void       AddCommand(CXCommand* pCommand);
  void       Stop();
private:
  void       Clear();
  void       DoCmdQueue();
  CXCommand* GetCmdHead();
// data members:
protected:
  bool                         m_fQuit;
  HANDLE                       m_hEventStop; 
  HANDLE                       m_hEventStopped; 
  HANDLE                       m_hEventCmd;
  CCriticalSection             m_cs;
  CList<CXCommand*,CXCommand*> m_cmdQueue;
public:
  BOOL                         m_fInProc;
// Implementation
protected:
	virtual ~CXMachine();
	// Generated message map functions
	//{{AFX_MSG(CXMachine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CXMachine* g_pMachine;

#endif