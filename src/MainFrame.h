#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame 
{
public:
    explicit MainFrame(const wxString& title);

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);


    wxDECLARE_EVENT_TABLE();

};