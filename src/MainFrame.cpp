#include "MainFrame.h"
#include "core/Actions.h"


// ---- Event table maps menu & button IDs -> member functions ----
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_TIMER(wxID_ANY, MainFrame::OnUpdateCountdown)

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

    // Add stretch so label sits at right side
    topBarSizer->AddStretchSpacer();

    //countdown label
    countdownLabel_ = new wxStaticText(topBar_, wxID_ANY, "Loading timer...");
    topBarSizer->Add(countdownLabel_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 6);

    //Start timer (fires every 60s = 60000 ms)
    countdownTimer_ = new wxTimer(this);
    countdownTimer_->Start(1000);
    UpdateCountdownLabel();

    topBarSizer->Add(btnLoadRec, 0, wxALL, 6);
    topBarSizer->Add(btnLoadVen, 0, wxALL, 6);
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
    SetStatusText("Load Vendor List clicked");
}

void MainFrame::OnExportUpdated(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage("Export Updated File clicked");
    SetStatusText("Export Updated File clicked");
}

void MainFrame::OnUpdateCountdown(wxTimerEvent& WXUNUSED(event))
{
    UpdateCountdownLabel();
}

void MainFrame::UpdateCountdownLabel()
{
    //Target line: 3PM EST (12 PT)
    wxDateTime now = wxDateTime::Now();

    //assume 3PM ET = 12PM PT -> just set noon PT
    wxDateTime noonPT(now.GetDay(), now.GetMonth(), now.GetYear(), 12, 0, 0);


    wxTimeSpan remaining = noonPT - now;

    wxString label;

    if (remaining.IsPositive())
    {
        label.Printf("Time remaining: %ldh %ldm to 3:00 PM ET", remaining.GetHours(), remaining.GetMinutes() % 60);
    }
    else
        label = "Deadline passed";

    countdownLabel_->SetLabel(label);
}
