#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600)) 
{
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
}


void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("Coordinator Assistant\nBuilt with wxWidgets", "About", wxOK | wxICON_INFORMATION, this);
}
