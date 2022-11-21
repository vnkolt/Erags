#if !defined(SHELLTYPE_H_INCLUDED)
#define SHELLTYPE_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Constans for detecting OS-Type
enum Win32Type
{
  Win32s,
  WinNT3,
  Win95,
  Win98,
  WinME,
  WinNT4,
  Win2000,
  WinXP,
  Win2003,
  Win200X
};

Win32Type IsShellType();

extern Win32Type g_Shell;

#endif // SHELLTYPE_H_INCLUDED
