#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <SDL2/SDL_mixer.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	~MainFrame();
	wxButton* Start;
	wxButton* Stop;
	wxSpinCtrl* timeCtrl;
	wxRadioBox* radioBox;
	wxChoice* dropDown;
	wxTimer* timer;
	Mix_Chunk* sound;

	int GetReminderTime();
    bool GetRandomStatus();
	int GetRandomNumber(int min, int max);
	bool GetSpinFlag();
	int GetChoice();
	int volume = 50;

private:
	void OnSliderChanged(wxCommandEvent& evt);
	void OnDropDownSelect(wxCommandEvent& evt);
	void OnOptionsWindowClosed(wxCloseEvent& evt);
	void OnStartClicked(wxCommandEvent& evt);
	void OnStopClicked(wxCommandEvent& evt);
	void OnRadioSelect(wxCommandEvent& evt);
	void OnSpinControl(wxCommandEvent& evt);
	void SetReminderTime(int minutes);
	void SetRandomStatus(bool status);
	void OnTimer(wxTimerEvent& evt);
	void SetSpinFlag(bool spin);
	void SetChoice(int choice);


	int remindTime = 30;
	int audioChoice = 1;
	bool randStatus = false;
	bool spinOn = true;

	
};

