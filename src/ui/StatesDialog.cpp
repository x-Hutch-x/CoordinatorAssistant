#include "ui/StatesDialog.h"
#include "core/States.h"
#include "core/Actions.h"

wxBEGIN_EVENT_TABLE(StatesDialog, wxDialog)
EVT_TEXT(ID_STATES_SEARCHBOX, StatesDialog::OnFilterText)
EVT_TEXT_ENTER(ID_STATES_SEARCHBOX, StatesDialog::OnFilterText)
wxEND_EVENT_TABLE()

StatesDialog::StatesDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "State Abbreviations",
        wxDefaultPosition, wxSize(420, 520),
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    auto* vbox = new wxBoxSizer(wxVERTICAL);

    searchBox_ = new wxTextCtrl(this, ID_STATES_SEARCHBOX, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    list_ = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxDV_ROW_LINES | wxDV_VERT_RULES);

    list_->AppendTextColumn("State", wxDATAVIEW_CELL_INERT, 260,
        wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
    list_->AppendTextColumn("Abbr", wxDATAVIEW_CELL_INERT, 80,
        wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);

    vbox->Add(searchBox_, 0, wxEXPAND | wxALL, 8);
    vbox->Add(list_, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    vbox->Add(CreateSeparatedButtonSizer(wxOK), 0, wxEXPAND | wxALL, 8);
    SetSizerAndFit(vbox);

    Populate("");
}

void StatesDialog::OnFilterText(wxCommandEvent& ev)
{
    Populate(ev.GetString());
}

void StatesDialog::Populate(const wxString& needle)
{
    list_->DeleteAllItems();
    const wxString lo = needle.Lower();

    for (const auto& e : kStates) {
        const wxString name = wxString::FromUTF8(e.name);
        const wxString abbr = wxString::FromUTF8(e.abbr);
        if (lo.IsEmpty() || name.Lower().Contains(lo) || abbr.Lower().Contains(lo)) {
            wxVector<wxVariant> row;
            row.push_back(wxVariant(name));
            row.push_back(wxVariant(abbr));
            list_->AppendItem(row);
        }
    }
}
