#include "MainFrame.h"
#include "OptionsWindow.h"
#include <wx/wx.h>



MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this);

	wxButton* timeSelectButton = new wxButton(panel, wxID_ANY, "Reminder Settings", wxDefaultPosition, wxDefaultSize); //opens options for reminder time
	wxFont buttonFont(wxFontInfo(12)); 
	timeSelectButton->SetFont(buttonFont);

	wxArrayString tempChoices;
	tempChoices.Add("Default Audio");
	tempChoices.Add("Temp A");
	tempChoices.Add("Temp B");
	tempChoices.Add("Temp C");
	
	wxChoice* dropDown = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, tempChoices); //dropDown menu to select audio
	dropDown->Select(0);
	dropDown->SetFont(buttonFont);

	wxSlider* audioSlider = new wxSlider(panel, wxID_ANY, 50, 0, 100, wxDefaultPosition,
		wxDefaultSize, wxSL_VALUE_LABEL); //volume slider

	wxPNGHandler* handler = new wxPNGHandler; //handler for png
	wxImage::AddHandler(handler);						
	wxStaticBitmap* image = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("volumeIcon2.png", wxBITMAP_TYPE_PNG), 
		wxDefaultPosition, wxSize(50, 50)); //placed volumeIcon

	wxButton* Start = new wxButton(panel, wxID_ANY, "Start", wxDefaultPosition, wxDefaultSize); //creates a button to start program
	wxButton* Stop = new wxButton(panel, wxID_ANY, "Stop", wxDefaultPosition, wxDefaultSize); //creates a button to start program

	Start->SetFont(buttonFont);
	Stop->SetFont(buttonFont);

	timeSelectButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	audioSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	dropDown->Bind(wxEVT_CHOICE, &MainFrame::OnDropDownSelect, this);       //Dynamic Event Handling for main menu elements

	// Create the horizontal sizer for the button and drop-down menu
	wxBoxSizer* buttonDropDownSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonDropDownSizer->Add(timeSelectButton, 1, wxEXPAND | wxALL, 50); 
	buttonDropDownSizer->Add(dropDown, 1, wxEXPAND | wxALL, 50); 

	// Create the horizontal sizer for the audio slider and image
	wxBoxSizer* audioImageButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	audioImageButtonSizer->Add(image, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);
	audioImageButtonSizer->Add(audioSlider, 1, wxEXPAND | wxALL, 20);
	audioImageButtonSizer->Add(Start, 0, wxEXPAND  | wxTOP | wxBOTTOM | wxLEFT, 20);
	audioImageButtonSizer->Add(Stop, 0, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM | wxLEFT, 20);

	// Create the final vertical sizer to hold both horizontal sizers
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(buttonDropDownSizer, 0, wxEXPAND | wxTOP, 20);
	mainSizer->Add(audioImageButtonSizer, 0, wxEXPAND);

	panel->SetSizerAndFit(mainSizer);
}


void MainFrame::OnButtonClicked(wxCommandEvent& evt)
{
	if (!isOptionsWindowOpen)
	{
		optionsWindow = new OptionsWindow("Time Settings");
		optionsWindow->Show(true);

		// Set the flag to true since the OptionsWindow is now open.
		isOptionsWindowOpen = true;

		// Bind an event handler to catch when the OptionsWindow is closed.
		optionsWindow->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnOptionsWindowClosed, this);
	}
	else
	{

		if (optionsWindow->IsIconized())
			optionsWindow->Iconize(false);
		optionsWindow->Raise();                 //if the options menu is not in the forefront of the screen, clicking the button again will 
	}											//bring it up without opening a new window
}

void MainFrame::OnOptionsWindowClosed(wxCloseEvent& evt)
{
	// When the OptionsWindow is closed, reset the flag to false.
	isOptionsWindowOpen = false;
	evt.Skip(); // Allow the event to propagate
}

void MainFrame::OnDropDownSelect(wxCommandEvent& evt)
{
	
	wxLogStatus(evt.GetString());
}

void MainFrame::OnSliderChanged(wxCommandEvent& evt)
{
	wxString str = wxString::Format("Slider Value: %d", evt.GetInt());
	wxLogStatus(str);
}

