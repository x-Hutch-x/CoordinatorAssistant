#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(CoordinatorApp);

bool CoordinatorApp::OnInit()
{
    if (!wxApp::OnInit()) 
        return false;

    auto* frame = new MainFrame("Coordinator Assistant");
    frame->Show(true);
    return true;
}
