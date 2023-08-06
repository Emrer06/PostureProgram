#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/mediactrl.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);
    
    sound = new wxMediaCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(0, 0), 0);
    sound->Load("mixkit-achievement-bell-600.wav");
}

