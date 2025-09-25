#pragma once
#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/textctrl.h>

class StatesDialog : public wxDialog
{
public:
    explicit StatesDialog(wxWindow* parent);

private:
    void OnFilterText(wxCommandEvent& ev);
    void Populate(const wxString& needle);

    wxTextCtrl* searchBox_ = nullptr;
    wxDataViewListCtrl* list_ = nullptr;

    wxDECLARE_EVENT_TABLE();
};
