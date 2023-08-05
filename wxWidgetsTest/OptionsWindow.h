#pragma once
#include <wx/wx.h>

class OptionsWindow : public wxFrame
{
public:
    OptionsWindow(const wxString& title);
   

private:
    void OnRadioSelect(wxCommandEvent& event);
    wxSpinCtrl* timeCtrl;
};
