#pragma once
#include <wx/wx.h>

class OptionsWindow : public wxFrame
{
public:
    OptionsWindow(const wxString& title);
    wxSpinCtrl* timeCtrl;
    wxRadioBox* radioBox;

    int GetReminderTime();
    bool GetRandomStatus();

private:
    void OnRadioSelect(wxCommandEvent& event);
    void OnSpinControl(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void SetReminderTime(int rTime);
    void SetRandomStatus(bool status);
    
    int reminderTime = 30;
    bool RStatus;
    

};
