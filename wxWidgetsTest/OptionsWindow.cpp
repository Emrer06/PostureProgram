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

		radioBox = new wxRadioBox(panel, wxID_ANY, "Choose Reminder Type", wxDefaultPosition, wxDefaultSize, radioChoices);
		radioBox->SetSelection(1); 

		timeCtrl = new wxSpinCtrl(panel, wxID_ANY, "Set Reminder (Min)", wxDefaultPosition, wxSize(200, 30),
			wxSP_ARROW_KEYS | wxSP_WRAP, 0, 60, 30);
		

		wxFont buttonFont(wxFontInfo(12));
		timeCtrl->SetFont(buttonFont);  //setting font of the timeCtrl

		wxButton* save = new wxButton(panel, wxID_ANY, "Save Settings", wxDefaultPosition, wxSize(100,40)); //opens options for reminder time

		wxFont saveFont(wxFontInfo(11));
		save->SetFont(saveFont);  //setting font of the timeCtrl

		wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
		horizontalSizer->Add(radioBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);
		horizontalSizer->Add(timeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);

		wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
		buttonSizer->Add(save, 0, wxALL, 10);

		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(horizontalSizer, 1, wxALIGN_CENTER | wxTOP, 10);
		mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER, 0);
		mainSizer->AddSpacer(30);

		panel->SetSizerAndFit(mainSizer);

		timeCtrl->Bind(wxEVT_SPINCTRL, &OptionsWindow::OnSpinControl, this); //bind spinCtrl event handler
		radioBox->Bind(wxEVT_RADIOBOX, &OptionsWindow::OnRadioSelect, this); //bind radioBox event handler
		save->Bind(wxEVT_BUTTON, &OptionsWindow::OnSave, this); //bind save event handler
		
}
void OptionsWindow::OnSave(wxCommandEvent& event)
{
	if(radioBox->GetSelection() == 0)
	{
		SetRandomStatus(true); //ensures RandomStatus is true
	}else
	{
		SetRandomStatus(false);
		SetReminderTime(timeCtrl->GetValue()); //saves timeCtrl value
	}
	wxWindow::Close(); //closes window when save is pressed
	event.Skip();
}

void OptionsWindow::OnRadioSelect(wxCommandEvent& event)
{
	if(event.GetInt() == 0 )
	{
		timeCtrl->Enable(false);
		SetRandomStatus(true);
		event.Skip();
	}else if(event.GetInt() == 1)
	{
		timeCtrl->Enable(true);
		SetRandomStatus(false);
		event.Skip();
	}
}

void OptionsWindow::OnSpinControl(wxCommandEvent& event)
{
	SetReminderTime(event.GetInt());
	event.Skip();
}

void OptionsWindow::SetReminderTime(int rTime)
{
	reminderTime = rTime;
}

int OptionsWindow::GetReminderTime()
{
	return reminderTime;
}

void OptionsWindow::SetRandomStatus(bool status)
{
	RStatus = status;
}

bool OptionsWindow::GetRandomStatus()
{
	return RStatus;
}
