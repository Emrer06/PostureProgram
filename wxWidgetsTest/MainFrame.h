#pragma once
#include <wx/wx.h>
#include "OptionsWindow.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	wxButton* Start;
	wxButton* Stop;

private:
	void OnButtonClicked(wxCommandEvent& evt); //button in this case is the Time Settings button
	void OnSliderChanged(wxCommandEvent& evt);
	void OnDropDownSelect(wxCommandEvent& evt);
	void OnOptionsWindowClosed(wxCloseEvent& evt);
	void OnStartClicked(wxCommandEvent& evt);
	void OnStopClicked(wxCommandEvent& evt);



	bool isOptionsWindowOpen;
	OptionsWindow* optionsWindow;

	


};

