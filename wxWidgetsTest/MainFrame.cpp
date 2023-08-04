#include "MainFrame.h"
#include <wx/wx.h>



MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this);

	wxButton* timeSelectButton = new wxButton(panel, wxID_ANY, "Time Select", wxDefaultPosition, wxDefaultSize); //opens options for reminder time
	wxFont buttonFont(wxFontInfo(14)); 
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

	timeSelectButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	audioSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	dropDown->Bind(wxEVT_CHOICE, &MainFrame::OnDropDownSelect, this);       //Dynamic Event Handling for main menu elements




	// Create the horizontal sizer for the button and drop-down menu
	wxBoxSizer* buttonDropDownSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonDropDownSizer->Add(timeSelectButton, 1, wxEXPAND | wxALL, 50); 
	buttonDropDownSizer->Add(dropDown, 1, wxEXPAND | wxALL, 50); 

	// Create the horizontal sizer for the audio slider and image
	wxBoxSizer* audioImageSizer = new wxBoxSizer(wxHORIZONTAL);
	audioImageSizer->Add(image, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);
	audioImageSizer->Add(audioSlider, 1, wxEXPAND | wxALL, 20);

	// Create the final vertical sizer to hold both horizontal sizers
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(buttonDropDownSizer, 0, wxEXPAND | wxTOP, 20);
	mainSizer->Add(audioImageSizer, 0, wxEXPAND);

	panel->SetSizerAndFit(mainSizer);
}


void MainFrame::OnButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("Button Clicked");
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