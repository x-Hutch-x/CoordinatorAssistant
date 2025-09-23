#include "MainFrame.h"
#include "core/Actions.h"


// ---- Event table maps menu & button IDs -> member functions ----
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)

    EVT_BUTTON(ID_LOAD_RECORDINGS, MainFrame::OnLoadRecordings)
    EVT_BUTTON(ID_LOAD_VENDORS, MainFrame::OnLoadVendors)
    EVT_BUTTON(ID_EXPORT_UPDATED, MainFrame::OnExportUpdated)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 650)) 
{
    // --- Menu bar (File/Help) ---
    auto* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, "&Exit\tAlt-F4", "Quit the application");

    auto* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "&About\tF1", "About this app");

    auto* bar = new wxMenuBar;
    bar->Append(menuFile, "&File");
    bar->Append(menuHelp, "&Help");
    SetMenuBar(bar);

    CreateStatusBar();
    SetStatusText("Welcome to Coordinator Assistant!");

    // --- Root panel & layout ---
    root_ = new wxPanel(this);
    auto* rootSizer = new wxBoxSizer(wxVERTICAL);

    // --- Top bar (buttons) ---
    topBar_ = new wxPanel(root_);
    auto* topBarSizer = new wxBoxSizer(wxHORIZONTAL);


    auto* btnLoadRec = new wxButton(topBar_, ID_LOAD_RECORDINGS, "Load Recordings");
    auto* btnLoadVen = new wxButton(topBar_, ID_LOAD_VENDORS, "Load Vendor List");
    auto btnExport = new wxButton(topBar_, ID_EXPORT_UPDATED, "Export Updated File");

    topBarSizer->Add(btnLoadRec, 0, wxALL, 6);
    topBarSizer->Add(btnLoadVen, 0, wxALL, 6);
    topBarSizer->AddStretchSpacer();
    topBarSizer->Add(btnExport, 0, wxALL, 6);
    topBar_->SetSizer(topBarSizer);

    // --- Notebook (tabs) ---
    notebook_ = new wxNotebook(root_, wxID_ANY);
    notebook_->AddPage(new wxPanel(notebook_), "Recordings");
    notebook_->AddPage(new wxPanel(notebook_), "Vendors");
    notebook_->AddPage(new wxPanel(notebook_), "Output");

    // --- Compose layout ---
    rootSizer->Add(topBar_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 6);
    rootSizer->Add(notebook_, 1, wxEXPAND | wxALL, 6);
    root_->SetSizer(rootSizer);

    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(root_, 1, wxEXPAND);
    SetSizer(frameSizer);

}


void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("Coordinator Assistant\nBuilt with wxWidgets", "About", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnLoadRecordings(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage("Load Recordings clicked");
    SetStatusText("Load Recordings clicked");
}

void MainFrame::OnLoadVendors(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage("Load Vendor List clicked");
    SetStatusText("Load Vendor List clicke");
}

void MainFrame::OnExportUpdated(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage("Export Updated File clicked");
    SetStatusText("Export Updated File clicked");
}
