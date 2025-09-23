#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>

class MainFrame : public wxFrame 
{
public:
    explicit MainFrame(const wxString& title);

private:
    //Menu Handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    //Top-bar button handlers
    void OnLoadRecordings(wxCommandEvent& event);
    void OnLoadVendors(wxCommandEvent& event);
    void OnExportUpdated(wxCommandEvent& event);

    //UI Pointers
    wxPanel* root_ = nullptr;
    wxPanel* topBar_ = nullptr;
    wxNotebook* notebook_ = nullptr;

    wxDECLARE_EVENT_TABLE();

};