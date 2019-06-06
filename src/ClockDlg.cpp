//---------------------------------------------------------------------------
//
// Name:        ClockDlg.cpp
// Author:      Jos de Jong
// Created:     29-12-2007 11:42:36
// Description: ClockDlg class implementation
//
//---------------------------------------------------------------------------

#include "ClockDlg.h"

//----------------------------------------------------------------------------
// ClockDlg
//----------------------------------------------------------------------------
// Event table
BEGIN_EVENT_TABLE(ClockDlg,wxDialog)
   EVT_CLOSE(ClockDlg::OnClose)
   EVT_SIZE(ClockDlg::ClockDlgSize)
   EVT_PAINT(ClockDlg::ClockDlgPaint)
   EVT_TIMER(ID_WXTIMER1,ClockDlg::WxTimer1Timer)
   EVT_TIMER(ID_WXTIMER2,ClockDlg::WxTimer2Timer)
END_EVENT_TABLE()

// Creating the Clock Dialog window
ClockDlg::ClockDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
   CreateGUIControls();
}

// Destroying the Clock Dialog window
ClockDlg::~ClockDlg()
{
} 

// Creating just the controls (not populating the dialog yet)
void ClockDlg::CreateGUIControls()
{
   SetTitle(wxT("FD shift clock"));
   SetIcon(wxNullIcon);
   SetSize(8,8,300,600);
   Center();
   
   WxTimer1 = new wxTimer();
   WxTimer1->SetOwner(this, ID_WXTIMER1);
   WxTimer1->Start(200);

   WxTimer2 = new wxTimer();
   WxTimer2->SetOwner(this, ID_WXTIMER2);
   WxTimer2->Start(200);
}

void ClockDlg::OnClose(wxCloseEvent&)
{
   Destroy();
}

int toInt(float value)
{
   return static_cast<int>(value);
}

// Populate the dialog window
void ClockDlg::ClockDlgPaint(wxPaintEvent& WXUNUSED(event))
{
   SetBackgroundStyle(wxBG_STYLE_CUSTOM);
   wxBufferedPaintDC dc(this);

   // Get window dimensions
   wxSize sz = GetClientSize();

   // PAINT THE FIRST CLOCK ------------------------------------------
   wxPoint center = wxPoint(sz.x / 2, sz.y / 4 + 12);
   wxCoord radius = wxMin(sz.x / 2 - 20, sz.y / 4 - 20);
   radius = wxMax(radius, 50);

   float factor = wxMax(radius/60.0, 1.0);

   // create a few colors
   wxColour lightblue = wxColour(220, 245, 255);
   wxColour darkblue = wxColour(0, 0, 120);

   // draw lightblue background
   dc.SetPen(lightblue);
   dc.SetBrush(lightblue);
   dc.DrawRectangle(0, 0, sz.x, sz.y/2);

   // draw clock border
   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(*wxBLACK_BRUSH);
   dc.DrawCircle(center, radius);
   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(*wxWHITE_BRUSH);
   dc.DrawCircle(center, toInt(radius - 3.0 * factor));

   // paint lines for minutes
   float pi = 3.141592654;
   float r_outer = radius - 5 * factor;
   float r_inner_min = radius - 7 * factor;
   float r_inner_hour = radius - 10 * factor;
   float r_inner_text = radius - 15 * factor;
   int linewidth = 1;
   for (int r = 1; r <= 60; r ++)
   {
      float s = sin(r/60.0*2.0*pi);
      float c = -cos(r/60.0*2.0*pi);
      
      linewidth = wxMax(toInt(factor / 2), 1);
      dc.SetPen(wxPen(*wxBLACK, linewidth));
      wxPoint outer = wxPoint(toInt(r_outer * s), toInt(r_outer * c));
      wxPoint inner = wxPoint(toInt(r_inner_min * s), toInt(r_inner_min * c));
      dc.DrawLine(center + inner, center + outer);
      
      if (r % 5 == 0)
      {
         linewidth = wxMax(toInt(factor), 1);
         dc.SetPen(wxPen(*wxBLACK, linewidth));
   
         // paint larger lines for the hours
         outer = wxPoint(toInt(r_outer * s), toInt(r_outer * c));
         inner = wxPoint(toInt(r_inner_hour * s), toInt(r_inner_hour * c));
         dc.DrawLine(center + inner, center + outer);

         // paint value of the hour
         wxString hour;
         hour.Printf("%i", r / 5);
         
         dc.SetFont(wxFont(toInt(5 * factor), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "tahoma", wxFONTENCODING_DEFAULT));
         
         // calculate the size of the text and paint it in the window
         wxCoord w = 0, h = 0;
         dc.GetTextExtent(hour, &w, &h);
         wxPoint text_pos = wxPoint(toInt(r_inner_text * s - w / 2), toInt(r_inner_text * c - h / 2));
         dc.DrawText(hour, center + text_pos);
         //dc.DrawRotatedText(hour, center.x + text_pos.x, center.y + text_pos.y, (60-r)/60.0*360);  // cool :)
      }
   }
   
   // draw hour, minute and second hand of the clock
   wxDateTime time = wxDateTime::Now();    
   int h = time.GetHour();
   int m = time.GetMinute();
   int s = time.GetSecond();

   int r = 1;
   float h_rad = (h % 12 + m / 60.0 + s / 3600.0) / 12.0 * 2.0 * pi;
   float m_rad = (m / 60.0 + s / 3600.0) * 2.0 * pi;    
   float s_rad = s / 60.0 * 2.0 * pi;

/*   // show digital time in caption
   wxString title;
   title.Printf("Clock %i:%.2i:%.2i", h, m, s);
   SetTitle(title);*/

   r = toInt(factor * 20);
   linewidth = wxMax(toInt(factor * 5), 1);
   dc.SetPen(wxPen(*wxBLACK, linewidth));
   dc.DrawLine(center, center + wxPoint(toInt(r * sin(h_rad)), toInt(r * -cos(h_rad))));

   r = toInt(factor * 40);
   linewidth = wxMax(toInt(factor * 2), 1);
   dc.SetPen(wxPen(*wxBLACK, linewidth));
   dc.DrawLine(center, center + wxPoint(toInt(r * sin(m_rad)), toInt(r * -cos(m_rad))));

   r = toInt(factor * 50);
   linewidth = wxMax(toInt(factor), 1);
   dc.SetPen(wxPen(*wxRED, linewidth));
   dc.DrawLine(center, center + wxPoint(toInt(r * sin(s_rad)), toInt(r * -cos(s_rad))));

   // PAINT THE SECOND CLOCK ------------------------------------------
   wxPoint center2 = wxPoint(sz.x / 2, 3 * sz.y / 4 + 12);
   wxCoord radius2 = wxMin(sz.x / 2 - 20, sz.y / 4 - 20);
   radius2 = wxMax(radius2, 50);

   float factor2 = wxMax(radius2/60.0, 1.0);

   // draw lightblue background
   dc.SetPen(lightblue);
   dc.SetBrush(lightblue);
   dc.DrawRectangle(0, sz.y/2, sz.x, sz.y);

   // draw clock border
   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(*wxBLACK_BRUSH);
   dc.DrawCircle(center2, radius2);
   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(*wxWHITE_BRUSH);
   dc.DrawCircle(center2, toInt(radius2 - 3.0 * factor2));

   // paint lines for minutes
/*   float r_outer = radius2 - 5 * factor2;
   float r_inner_min = radius2 - 7 * factor2;
   float r_inner_hour = radius2 - 10 * factor2;
   float r_inner_text = radius2 - 15 * factor2;
   int linewidth = 1;*/
   for (int r = 1; r <= 60; r ++)
   {
      float s = sin(r/60.0*2.0*pi);
      float c = -cos(r/60.0*2.0*pi);
      
      linewidth = wxMax(toInt(factor2 / 2), 1);
      dc.SetPen(wxPen(*wxBLACK, linewidth));
      wxPoint outer = wxPoint(toInt(r_outer * s), toInt(r_outer * c));
      wxPoint inner = wxPoint(toInt(r_inner_min * s), toInt(r_inner_min * c));
      dc.DrawLine(center2 + inner, center2 + outer);
      
      if (r % 5 == 0)
      {
         linewidth = wxMax(toInt(factor2), 1);
         dc.SetPen(wxPen(*wxBLACK, linewidth));
   
         // paint larger lines for the hours
         outer = wxPoint(toInt(r_outer * s), toInt(r_outer * c));
         inner = wxPoint(toInt(r_inner_hour * s), toInt(r_inner_hour * c));
         dc.DrawLine(center2 + inner, center2 + outer);

         // paint value of the hour
         wxString hour;
         hour.Printf("%i", r / 5);
         
         dc.SetFont(wxFont(toInt(5 * factor2), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "tahoma", wxFONTENCODING_DEFAULT));
         
         // calculate the size of the text and paint it in the window
         wxCoord w = 0, h = 0;
         dc.GetTextExtent(hour, &w, &h);
         wxPoint text_pos = wxPoint(toInt(r_inner_text * s - w / 2), toInt(r_inner_text * c - h / 2));
         dc.DrawText(hour, center2 + text_pos);
         //dc.DrawRotatedText(hour, center2.x + text_pos.x, center2.y + text_pos.y, (60-r)/60.0*360);  // cool :)
      }
   }
   
   // draw hour, minute and second hand of the clock
   wxDateTime time2 = (wxDateTime::Now()).ToTimezone(wxDateTime::TZ::GMT_3);
   int h2 = time2.GetHour();
   int m2 = time2.GetMinute();
   int s2 = time2.GetSecond();

   int r2 = 1;
   float h_rad2 = (h2 % 12 + m2 / 60.0 + s2 / 3600.0) / 12.0 * 2.0 * pi;
   float m_rad2 = (m2 / 60.0 + s2 / 3600.0) * 2.0 * pi;    
   float s_rad2 = s2 / 60.0 * 2.0 * pi;

/*   // show digital time in caption
   wxString title;
   title.Printf("Clock %i:%.2i:%.2i", h, m, s);
   SetTitle(title);*/

   r2 = toInt(factor2 * 20);
   linewidth = wxMax(toInt(factor2 * 5), 1);
   dc.SetPen(wxPen(*wxBLACK, linewidth));
   dc.DrawLine(center2, center2 + wxPoint(toInt(r2 * sin(h_rad2)), toInt(r2 * -cos(h_rad2))));

   r2 = toInt(factor2 * 40);
   linewidth = wxMax(toInt(factor2 * 2), 1);
   dc.SetPen(wxPen(*wxBLACK, linewidth));
   dc.DrawLine(center2, center2 + wxPoint(toInt(r2 * sin(m_rad2)), toInt(r2 * -cos(m_rad2))));

   r2 = toInt(factor2 * 50);
   linewidth = wxMax(toInt(factor2), 1);
   dc.SetPen(wxPen(*wxRED, linewidth));
   dc.DrawLine(center2, center2 + wxPoint(toInt(r2 * sin(s_rad2)), toInt(r2 * -cos(s_rad2))));

   // Paint clock names
   dc.SetTextForeground(darkblue);
   dc.SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "arial", wxFONTENCODING_DEFAULT));
   dc.DrawText("Local time", toInt(15), toInt(5));
   dc.DrawText("Argentina time", toInt(15), toInt(sz.y/2 + 5));

   wxString clockval, clockval2;
   clockval.Printf("%i:%.2i:%.2i", h, m, s);
   clockval2.Printf("%i:%.2i:%.2i", h2, m2, s2);
   dc.DrawText(clockval, toInt(sz.x - 26 - GetWidth(&clockval)), toInt(5));
   dc.DrawText(clockval2, toInt(sz.x - 26 - GetWidth(&clockval2)), toInt(sz.y/2 + 5));
}

void ClockDlg::ClockDlgSize(wxSizeEvent& WXUNUSED(event))
{
   Refresh();
}

void ClockDlg::WxTimer1Timer(wxTimerEvent& WXUNUSED(event))
{
   Refresh();
}

void ClockDlg::WxTimer2Timer(wxTimerEvent& WXUNUSED(event))
{
   Refresh();
}

int ClockDlg::GetWidth(wxString *str)
{
   wxCoord width, height;
   wxScreenDC dc;

   dc.GetTextExtent(*str, &width, &height);

   return (int)width;
}
