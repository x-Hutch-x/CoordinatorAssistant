#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/dataview.h> 
#include "core/Actions.h"
#include "core/Helpers.h"
#include "core/Defaults.h"
#include "core/States.h"
#include <wx/textctrl.h>
#include "ui/StatesDialog.h"
#include <wx/ffile.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/datetime.h>
#include <wx/utils.h>


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

    // store recordings CSV in memory so edits can be exported
    std::vector<std::vector<wxString>> recordingRows_;
    int recordingsKeywordCol_ = -1;
    int recordingsCommentsCol_ = -1;

    // path of the loaded recordings CSV (set in OnLoadRecordings)
    wxString recordingsPath_;

    //model/view col index -> CSV col index
    std::vector<int> recordingsModelToCsvCol_;

    // Helper to fill a table from parsed CSV
    void PopulateTable(wxDataViewListCtrl* table, const std::vector<std::vector<wxString>>& rows);

    // Build table using CSV header but give special editors to Keyword/Comments
    void BuildRecordingsTableWithEditors();

    // React to cell edits (auto-fill comments, write back to recordingsRows_)
    void OnRecordingsCellChanged(wxDataViewEvent& event);

    //states cheat sheet
    void OnShowStatesCheatSheet(wxCommandEvent& event);

    static wxString CsvEscape(const wxString& s);
    

    wxDECLARE_EVENT_TABLE();
};