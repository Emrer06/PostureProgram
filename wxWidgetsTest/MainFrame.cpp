#include "MainFrame.h"
#include <wx/wx.h>


MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this);

	wxButton* timeSelectButton = new wxButton(panel, wxID_ANY, "Time Select", wxPoint(120, 60), wxSize(100, 25)); //opens options for reminder time

	wxArrayString tempChoices;
	tempChoices.Add("Default Audio");
	tempChoices.Add("Temp A");
	tempChoices.Add("Temp B");
	tempChoices.Add("Temp C");

	wxChoice* dropDown = new wxChoice(panel, wxID_ANY, wxPoint(380, 60), wxSize(100, -1), tempChoices); //dropDown menu to select audio
	dropDown->Select(0);


	//wxFont volumeFont(wxFontInfo(12).Family(wxFONTFAMILY_DEFAULT).Bold());
	//wxStaticText* volume = new wxStaticText(panel, wxID_ANY, "Volume:", wxPoint(156,187)); //volume slider text
	//volume->SetFont(volumeFont); 

	wxSlider* audioSlider = new wxSlider(panel, wxID_ANY, 50, 0, 100, wxPoint(215, 165), 
		wxSize(250, -1), wxSL_VALUE_LABEL); //volume slider

	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxStaticBitmap* image = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("volumeIcon2.png", wxBITMAP_TYPE_PNG), wxPoint(153, 165), wxSize(50, 50));
	
}

