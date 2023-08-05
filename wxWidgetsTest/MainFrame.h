#pragma once
#include <wx/wx.h>
#include "OptionsWindow.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void OnButtonClicked(wxCommandEvent& evt);
	void OnSliderChanged(wxCommandEvent& evt);
	void OnDropDownSelect(wxCommandEvent& evt);
	void OnOptionsWindowClosed(wxCloseEvent& evt);

	bool isOptionsWindowOpen;
	OptionsWindow* optionsWindow;


};

