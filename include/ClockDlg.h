//---------------------------------------------------------------------------
//
// Name:        ClockDlg.h
// Author:      Jos de Jong
// Created:     29-12-2007 11:42:36
// Description: ClockDlg class declaration
//
//---------------------------------------------------------------------------

#ifndef __CLOCKDLG_h__
#define __CLOCKDLG_h__

#include <wx/wx.h>
#include <wx/dialog.h>

#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include <cmath>

#undef ClockDlg_STYLE
#define ClockDlg_STYLE wxSUNKEN_BORDER | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class ClockDlg : public wxDialog
{
private:
   DECLARE_EVENT_TABLE();
	
public:
   ClockDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Clock"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ClockDlg_STYLE);
   virtual ~ClockDlg();
   void ClockDlgPaint(wxPaintEvent& event);
   void ClockDlgSize(wxSizeEvent& event);
   void WxTimer1Timer(wxTimerEvent& event);
   void WxTimer2Timer(wxTimerEvent& event);
   int GetWidth(wxString *str);

private:
   // Timer variables
   wxTimer *WxTimer1;
   wxTimer *WxTimer2;
	
private:
   // Event ID values
   enum
   {
      ID_WXTIMER1 = 1001,
      ID_WXTIMER2 = 1002,
      ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
   };

private:
   void OnClose(wxCloseEvent& event);
   void CreateGUIControls();
};

#endif
