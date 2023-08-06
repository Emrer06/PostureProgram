#include "MainFrame.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
	int init = SDL_Init(SDL_INIT_EVERYTHING);
	int init2 = Mix_Init(0);

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
	tempChoices.Add("Random Voice");
	tempChoices.Add("Default Audio");
	tempChoices.Add("A Wise Guy");
	tempChoices.Add("Disappointed Grandfather");
	tempChoices.Add("Motivational Man");
	tempChoices.Add("Motivational Women");


	dropDown = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, tempChoices); //dropDown menu to select audio
	dropDown->Select(1);
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
	radioBox->Bind(wxEVT_RADIOBOX, &MainFrame::OnRadioSelect, this);       //bind radioBox event handler
	timeCtrl->Bind(wxEVT_SPINCTRL, &MainFrame::OnSpinControl, this);


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
	mainSizer->Add(buttonDropDownSizer, 0, wxEXPAND | wxTOP, 40);
	mainSizer->Add(audioImageButtonSizer, 0, wxEXPAND |wxTOP | wxBOTTOM , 30);
	
	panel->SetSizerAndFit(mainSizer);


	timer = new wxTimer(this, wxID_ANY);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL, this);

}

void MainFrame::OnTimer(wxTimerEvent& evt){

	
	std::vector<std::string> audioChoices = {
			"", //choice 0 cannot be selection so it will be an empty string
			"Default Audio.wav", // Placeholder for choice 1 (index 1) will correspond to tempChoices array
			"PesciPosture2.wav",
			"Disapointed Grandfather.wav",
			"Motivational Man.wav",
			"Motivational Women.wav"

	};


	int selection = GetChoice();
	if (selection == 0) {
		selection = GetRandomNumber(1, audioChoices.size() - 1);
	}

	std::string audioChoice = audioChoices[selection];

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	sound = Mix_LoadWAV(audioChoice.c_str()); //loads audiochoice as a string
	if (!sound)
	{

		wxLogMessage(Mix_GetError());

	}
	Mix_VolumeChunk(sound, volume);
	Mix_PlayChannel(-1, sound, 0);
}


void MainFrame::OnStartClicked(wxCommandEvent& evt)
{
	wxColour LightGreen(144, 238, 144);
	Start->SetBackgroundColour(LightGreen);
	Stop->SetBackgroundColour(wxNullColour); //sets stop back to default color



	if(GetSpinFlag() == true)
	{
		timeCtrl->Enable(false);
	}							//checks if the timeCtrl is already disabled from the radiobox, if it isnt it turns it off when start is pressed

	radioBox->Enable(false);
	dropDown->Enable(false);
	Start->Enable(false);
	Stop->Enable(true);

	if(GetRandomStatus())
	{
		timer->Start(2000); //gets a random number from 1 to 60 and multiplies by 60,000 to convert to milliseconds
		
	}else
	{
		timer->Start(4000);
	}
}

void MainFrame::OnStopClicked(wxCommandEvent& evt)
{
	wxColour LightRed(255, 71, 71);
	Stop->SetBackgroundColour(LightRed);
	Start->SetBackgroundColour(wxNullColour); //sets start back to the default color

	if (GetSpinFlag() == true)
	{
		timeCtrl->Enable(true);
	}			//checks if the timeCtrl is already disabled from the radiobox, if it isnt disabled due to radiobox
	            //it turns it on when stop is pressed


	radioBox->Enable(true);
	dropDown->Enable(true);
	Start->Enable(true);
	Stop->Enable(false);

	timer->Stop();

	Mix_VolumeChunk(sound, 0);
}

void MainFrame::OnDropDownSelect(wxCommandEvent& evt)
{
	SetChoice(dropDown->GetSelection());
}

void MainFrame::OnSliderChanged(wxCommandEvent& evt)
{
	volume = (evt.GetInt() * 128) / 100; //the volume control method in SDL_mixer ranges to 128, so this normalizes the 0-100 range to a 0 to 128 range as accuracy in
	evt.Skip();                          //this regard is not an issue for this program
}

void MainFrame::OnRadioSelect(wxCommandEvent& evt)
{
	int time = GetReminderTime();
	if (evt.GetInt() == 0)
	{
		
		timeCtrl->Enable(false);
		SetSpinFlag(false);
		SetRandomStatus(true);
		
		evt.Skip();
	}
	else if (evt.GetInt() == 1)
	{
		timeCtrl->Enable(true);
		SetSpinFlag(true);
		SetRandomStatus(false);
		
		evt.Skip();
	}
}


void MainFrame::OnSpinControl(wxCommandEvent& evt)
{
	SetReminderTime(evt.GetInt());
	evt.Skip();
}

void MainFrame::SetReminderTime(int minutes)
{
	remindTime = minutes;
}

int MainFrame::GetReminderTime()
{
	return remindTime;
}

void MainFrame::SetRandomStatus(bool status)
{
	randStatus = status;
}

bool MainFrame::GetRandomStatus()
{
	return randStatus;
}

int MainFrame::GetRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(gen);
}

void MainFrame::SetSpinFlag(bool spin)
{
	spinOn = spin;
}

bool MainFrame::GetSpinFlag()
{
	return spinOn;
}

void MainFrame::SetChoice(int choice)
{
	audioChoice = choice;
}

int MainFrame::GetChoice()
{
	return audioChoice;
}


MainFrame::~MainFrame()
{
	// Clean up SDL_mixer
	Mix_CloseAudio();
}