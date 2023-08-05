#pragma once
#include <wx/spinctrl.h>
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	wxButton* Start;
	wxButton* Stop;
	wxSpinCtrl* timeCtrl;
	wxRadioBox* radioBox;
	int GetReminderTime();
    bool GetRandomStatus();


private:
	void OnSliderChanged(wxCommandEvent& evt);
	void OnDropDownSelect(wxCommandEvent& evt);
	void OnOptionsWindowClosed(wxCloseEvent& evt);
	void OnStartClicked(wxCommandEvent& evt);
	void OnStopClicked(wxCommandEvent& evt);
	void OnRadioSelect(wxCommandEvent& event);
	void OnSpinControl(wxCommandEvent& event);


};

