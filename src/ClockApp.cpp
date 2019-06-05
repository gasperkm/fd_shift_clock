//---------------------------------------------------------------------------
//
// Name:        ClockApp.cpp
// Author:      Jos de Jong
// Created:     29-12-2007 11:42:36
// Description: 
//
//---------------------------------------------------------------------------

#include "ClockApp.h"
#include "ClockDlg.h"

IMPLEMENT_APP(ClockDlgApp)

bool ClockDlgApp::OnInit()
{
   ClockDlg* dialog = new ClockDlg(NULL);
   SetTopWindow(dialog);
   dialog->Show(true);		
   return true;
}
 
int ClockDlgApp::OnExit()
{
   return 0;
}
