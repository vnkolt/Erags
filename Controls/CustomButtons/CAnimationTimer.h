//---------------------------------------------------------------------------
//	THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
//	THE AUTHOR DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR IMPLIED, 
//	INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
//	PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
//	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL, 
//	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, 
//
//	By John Curtis, Dec 1999.   
//---------------------------------------------------------------------------

#ifndef _CANIMATIONTIMER_
#define _CANIMATIONTIMER_


/////////////////////////////////////////////////////////////////////////////
// CAnimationTimer
//
// Stores data about animation frames - Used by CCustomButton class.
// Posts a WM_TIMER message to a specific window on each timer event.
// Implemented using the  ::SetTimer() function. The timer is automatically stopped 
// when the object is destroyed.
/////////////////////////////////////////////////////////////////////////////
class CAnimationTimer
{
public:
	CAnimationTimer()
	:	m_Hwnd(NULL),m_Elapse(0),m_RequestedEventID(0),
		m_TimerID(0),m_nNoOfFrames(0),m_nFrame(0){}
	virtual ~CAnimationTimer(){Stop();}

	//Activates the timer
	bool		Start(HWND hWnd,UINT uElapse,UINT nIDEvent,int nFrames=10);
	//Deactivates the timer.
	void		Stop();	

	//Timer data
	bool		IsTiming()const			{return m_TimerID!=0;}//Returns nonzero if the timer is active.
	UINT		GetTimeOut() const	{return m_Elapse;}		//The time-out value, in milliseconds.
	HWND		GetHwnd() const			{return m_Hwnd;}			//window to be associated with the timer. 
	UINT		GetEventID()const		{return m_TimerID;}		//Returns the timer identifier	

	//Frame data
	int			GetFrame() const		{return m_nFrame;}
	int			GetNoOfFrames()const{return m_nNoOfFrames;}

	//Call to increment frame number. Usually called in CCustomButton::OnTimer()
	int			IncrementFrame(int nInc=1);	

protected:
	//Timer data
	HWND	m_Hwnd;							//The window to which WM_TIMER messages will be sent
	UINT	m_Elapse;						//Time between messages
	UINT	m_RequestedEventID; //ID to pass with this message
	UINT	m_TimerID;					//The timer

	//Frame data
	int		m_nNoOfFrames;				//No of frames in animation
	int		m_nFrame;							//Which frame we are at.
};


/////////////////////////////////////////////////////////////////////////////
// Initializes the timer object and start timing
// Sets the appropriate system timer to be associated with this timer object.
// Posts a WM_TIMER to a window using ::SetTimer().
//
inline bool CAnimationTimer::Start(HWND hWnd,UINT uElapse,UINT nIDEvent,int nFrames)
{
	ASSERT(::IsWindow(hWnd));
	ASSERT(uElapse>0 && nIDEvent!=0);
	ASSERT(nFrames>0);

	Stop();	//Clean up in case already started

	m_Hwnd=hWnd;
	m_Elapse=uElapse;
	m_RequestedEventID=nIDEvent;
	m_TimerID =::SetTimer(m_Hwnd,m_RequestedEventID,m_Elapse,NULL);
	m_nNoOfFrames=nFrames;
	m_nFrame=1;

	ASSERT(IsTiming());
	return IsTiming();
}

/////////////////////////////////////////////////////////////////////////////
// Kills the appropriate system timer associated with this timer object.
//
inline void CAnimationTimer::Stop()
{
	if(IsTiming())
		{
		::KillTimer(m_Hwnd,m_TimerID);
		*this=CAnimationTimer();	//Init all data
		}
}

/////////////////////////////////////////////////////////////////////////////
//
inline int	CAnimationTimer::IncrementFrame(int nInc)
{
if(m_nFrame+nInc>GetNoOfFrames())
	m_nFrame=1; 
else
	m_nFrame+=nInc; 

return m_nFrame;
}

/////////////////////////////////////////////////////////////////////////////

#endif
