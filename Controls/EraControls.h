#if !defined(ERACONTROL_H_INCLUDED)
#define ERACONTROL_H_INCLUDED

#if defined(_ERAGS)
#include "..\Erags\Erags.h"
#elif defined(_ERAABC)
#include "..\EraABC\EraABC.h"
#elif defined(SETUP_EXE)
#include "..\EraSetup\EraSetup.h"
#endif
#include "..\Common\CyrString.h"
#include "..\Common\Monthes.h"


class CEraControlProperties {
public:
  CEraControlProperties();
  ~CEraControlProperties();
protected:
  COLORREF  m_clrBackColor, m_clrForeColor,
            m_clrFocusBackColor, m_clrFocusForeColor;
public:
  COLORREF  GetBackColor() const { return m_clrBackColor; }
  COLORREF  GetForeColor() const { return m_clrForeColor; }
  COLORREF  GetFocusBackColor() const { return m_clrFocusBackColor; }
  COLORREF  GetFocusForeColor() const { return m_clrFocusForeColor; }

  COLORREF  SetBackColor(COLORREF clr) {
              COLORREF clrRet = m_clrBackColor;
              m_clrBackColor = clr;
              return clrRet;
            }
  COLORREF  SetForeColor(COLORREF clr) {
              COLORREF clrRet = m_clrForeColor;
              m_clrForeColor = clr;
              return clrRet;
            }
  COLORREF  SetFocusBackColor(COLORREF clr) {
              COLORREF clrRet = m_clrFocusBackColor;
              m_clrFocusBackColor = clrRet;
              return clrRet;
            }
  COLORREF  SetFocusForeColor(COLORREF clr) {
              COLORREF clrRet = m_clrFocusForeColor;
              return clrRet;
            }
};

class CEraTextBoxProperties : public CEraControlProperties {
public:
  CEraTextBoxProperties()  {}
  ~CEraTextBoxProperties() {}
};

class CEraComboBoxProperties : public CEraControlProperties {
public:
  CEraComboBoxProperties()  {}
  ~CEraComboBoxProperties() {}
};

class CEraToggleButtonProperties : public CEraControlProperties {
public:
  CEraToggleButtonProperties()  {}
  ~CEraToggleButtonProperties() {}
};

void SendKeys(BYTE bKey, BYTE bCtrlKey, BYTE bShiftKey=0);

#include "EraButton.h"
#include "EraComboBox.h"
#include "EraEdit.h"
#include "EraLabel.h"
#include "XButtonXP.h"


#endif//ERACONTROL_H_INCLUDED
