#if !defined(ERAMESSAGES_H_INCLUDED)
#define ERAMESSAGES_H_INCLUDED

enum EMessageType { EM_INFO     = 0,
                    EM_WARNING  = 1,
                    EM_ERROR    = 2,
                    EM_RUSSIAN  = 3,
                    EM_ENGLISH  = 4
                  };

// EraMessages.h

#define WM_EM_HIDE_TOOLTIPS (WM_USER + 0x200)   // wParam=0, lParam=0
#define WM_EM_SHOW_TOOLTIPS (WM_USER + 0x201)   // wParam=0, lParam=0
#define WM_EM_DOZIP         (WM_USER + 0x202)
#define WM_EM_MESSAGE       (WM_USER + 0x203)   // wParam=EMessageType, lParam = (LPCTSTR)szMessage

#endif // ERAMESSAGES_H_INCLUDED