#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/dataview.h> 
#include "core/Actions.h"
#include "core/Helpers.h"

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

    //Countdown
    void OnUpdateCountdown(wxTimerEvent& event);
    void UpdateCountdownLabel();

    //UI Pointers
    wxPanel* root_ = nullptr;
    wxPanel* topBar_ = nullptr;
    wxNotebook* notebook_ = nullptr;

    //Countdown members
    wxStaticText* countdownLabel_ = nullptr;
    wxTimer* countdownTimer_ = nullptr;

    //Data Tables
    wxDataViewListCtrl* recordingsTable_ = nullptr;
    wxDataViewListCtrl* vendorsTable_ = nullptr;

    // Helper to fill a table from parsed CSV
    void PopulateTable(wxDataViewListCtrl* table, const std::vector<std::vector<wxString>>& rows);

    wxDECLARE_EVENT_TABLE();
};