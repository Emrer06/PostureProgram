#include "MainFrame.h"
#include <wx/wx.h>



MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	wxPanel* panel = new wxPanel(this);

	wxArrayString radioChoices;
	radioChoices.Add("Random");
	radioChoices.Add("Set Time (Min)");

	radioBox = new wxRadioBox(panel, wxID_ANY, "Choose Reminder Type", wxDefaultPosition, wxDefaultSize, radioChoices);
	radioBox->SetSelection(1);
	timeCtrl = new wxSpinCtrl(panel, wxID_ANY, "30", wxDefaultPosition, wxSize(100, 20),
		wxSP_ARROW_KEYS | wxSP_WRAP, 0, 60, 30);

	wxFont buttonFont(wxFontInfo(15));
	timeCtrl->SetFont(buttonFont);  //setting font of the timeCtrl


	wxArrayString tempChoices;
	tempChoices.Add("Default Audio");
	tempChoices.Add("Temp A");
	tempChoices.Add("Temp B");
	tempChoices.Add("Temp C");

	wxChoice* dropDown = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, tempChoices); //dropDown menu to select audio
	dropDown->Select(0);
	wxFont buttonFont2(wxFontInfo(13));
	dropDown->SetFont(buttonFont2);

	wxSlider* audioSlider = new wxSlider(panel, wxID_ANY, 50, 0, 100, wxDefaultPosition,
		wxDefaultSize, wxSL_VALUE_LABEL); //volume slider

	wxPNGHandler* handler = new wxPNGHandler; //handler for png
	wxImage::AddHandler(handler);
	wxStaticBitmap* image = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("volumeIcon2.png", wxBITMAP_TYPE_PNG),
		wxDefaultPosition, wxSize(50, 50)); //placed volumeIcon

	Start = new wxButton(panel, wxID_ANY, "Start", wxDefaultPosition, wxDefaultSize); //creates a button to start program
	Stop = new wxButton(panel, wxID_ANY, "Stop", wxDefaultPosition, wxDefaultSize); //creates a button to start program

	Start->SetFont(buttonFont);
	Stop->SetFont(buttonFont);


	audioSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	dropDown->Bind(wxEVT_CHOICE, &MainFrame::OnDropDownSelect, this);       //Dynamic Event Handling for main menu elements
	Start->Bind(wxEVT_BUTTON, &MainFrame::OnStartClicked, this);
	Stop->Bind(wxEVT_BUTTON, &MainFrame::OnStopClicked, this);
	radioBox->Bind(wxEVT_RADIOBOX, &MainFrame::OnRadioSelect, this); //bind radioBox event handler
	

	// Create the horizontal sizer for the button and drop-down menu
	wxBoxSizer* buttonDropDownSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonDropDownSizer->Add(radioBox, 3, wxALIGN_LEFT | wxLEFT | wxTOP |wxBOTTOM | wxRIGHT , 20);
	buttonDropDownSizer->Add(timeCtrl, 1, wxEXPAND |wxTOP | wxBOTTOM | wxRIGHT, 33);
	buttonDropDownSizer->Add(dropDown, 0, wxEXPAND | wxALL, 30); 

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

void MainFrame::OnStartClicked(wxCommandEvent& evt)
{
	wxColour LightGreen(144, 238, 144);
	Start->SetBackgroundColour(LightGreen);
	Stop->SetBackgroundColour(wxNullColour); //sets stop back to default color
}

void MainFrame::OnStopClicked(wxCommandEvent& evt)
{
	wxColour LightRed(255, 71, 71);
	Stop->SetBackgroundColour(LightRed);
	Start->SetBackgroundColour(wxNullColour); //sets start back to the default color
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

void MainFrame::OnRadioSelect(wxCommandEvent& event)
{
	if (event.GetInt() == 0)
	{
		timeCtrl->Enable(false);
		wxLogMessage("RANDOM SELECTED");
		event.Skip();
	}
	else if (event.GetInt() == 1)
	{
		timeCtrl->Enable(true);
		wxLogMessage("RANDOM NOT SELECTED");
		event.Skip();
	}
}