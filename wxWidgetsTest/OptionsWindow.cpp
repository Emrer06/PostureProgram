#include "OptionsWindow.h"
#include <wx/spinctrl.h>

OptionsWindow::OptionsWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, 
	wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX)) //prevents user from resizing the frame 
{
    wxPanel* panel = new wxPanel(this);
	SetPosition(wxPoint(800, 400));

		wxArrayString radioChoices;
		radioChoices.Add("Random");
		radioChoices.Add("Set Time");

		wxRadioBox* radioBox = new wxRadioBox(panel, wxID_ANY, "Choose Reminder Type", wxDefaultPosition, wxDefaultSize, radioChoices);
		radioBox->SetSelection(1);

		timeCtrl = new wxSpinCtrl(panel, wxID_ANY, "Set Reminder (Min)", wxDefaultPosition, wxSize(200, -1),
			wxSP_ARROW_KEYS, 0, 60, 30);

		wxFont buttonFont(wxFontInfo(8));
		timeCtrl->SetFont(buttonFont);
		
		wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
		horizontalSizer->Add(radioBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);
		horizontalSizer->Add(timeCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 20);

		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(horizontalSizer, 1, wxALIGN_CENTER | wxALL, 20);

		panel->SetSizerAndFit(mainSizer);

		radioBox->Bind(wxEVT_RADIOBOX, &OptionsWindow::OnRadioSelect, this);
}
		
void OptionsWindow::OnRadioSelect(wxCommandEvent& event)
{
	if(event.GetInt() == 0 )
	{
		timeCtrl->Enable(false);
	}else if(event.GetInt() == 1)
	{
		timeCtrl->Enable(true);
	}
}
