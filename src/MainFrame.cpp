#include "MainFrame.h"

// ---- Event table maps menu & button IDs -> member functions ----
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_TIMER(wxID_ANY, MainFrame::OnUpdateCountdown)

    EVT_BUTTON(ID_LOAD_RECORDINGS, MainFrame::OnLoadRecordings)
    EVT_BUTTON(ID_LOAD_VENDORS, MainFrame::OnLoadVendors)
    EVT_BUTTON(ID_EXPORT_UPDATED, MainFrame::OnExportUpdated)
    EVT_DATAVIEW_ITEM_VALUE_CHANGED(wxID_ANY, MainFrame::OnRecordingsCellChanged)
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

    //Recordings tab
    auto* recordingsPanel = new wxPanel(notebook_);
    auto* recordingsSizer = new wxBoxSizer(wxVERTICAL);
    recordingsTable_ = new wxDataViewListCtrl(recordingsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES | wxDV_VERT_RULES);
    recordingsSizer->Add(recordingsTable_, 1, wxEXPAND | wxALL, 4);
    recordingsPanel->SetSizer(recordingsSizer);
    notebook_->AddPage(recordingsPanel, "Recordings");

    //Vendors Tab
    auto* vendorsPanel = new wxPanel(notebook_);
    auto* vendorsSizer = new wxBoxSizer(wxVERTICAL);
    vendorsTable_ = new wxDataViewListCtrl(vendorsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES | wxDV_VERT_RULES);
    vendorsSizer->Add(vendorsTable_, 1, wxEXPAND | wxALL, 4);
    vendorsPanel->SetSizer(vendorsSizer);
    notebook_->AddPage(vendorsPanel, "Vendors");

    //Output tab placeholder
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
    wxFileDialog openDialog(this, "Open Recordings CSV", "", "", "CSV files (*.csv)|*.csv|All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openDialog.ShowModal() != wxID_OK)
    {
        SetStatusText("Cancelled.");
        return;
    }

    const wxString selectedPath = openDialog.GetPath();
    auto parsedRows = Helpers::LoadCsv(selectedPath, 0);


    if (parsedRows.empty())
    {
        wxLogWarning("No data found in file: %s", selectedPath);
        SetStatusText("Failed to load recordings.");
        return;
    }

    //PopulateTable(recordingsTable_, parsedRows);
    //notebook_->ChangeSelection(0);
    //SetStatusText("Loaded recordings Preview");
    recordingRows_ = std::move(parsedRows);
    wxLogMessage("Header columns: %zu | first col '%s'", recordingRows_[0].size(), recordingRows_[0].empty() ? "<none>" : recordingRows_[0][0]);
    BuildRecordingsTableWithEditors();

    notebook_->ChangeSelection(0);
    SetStatusText("Loaded Recordings");
}

void MainFrame::OnLoadVendors(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog openDialog(this, "Open Vendor List CSV", "", "", "CSV files (*.csv)|*.csv|All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openDialog.ShowModal() != wxID_OK)
    {
        SetStatusText("Cancelled.");
        return;
    }

    const wxString selectedPath = openDialog.GetPath();
    auto parsedRows = Helpers::LoadCsv(selectedPath, 200);


    if (parsedRows.empty())
    {
        wxLogWarning("No data found in file: %s", selectedPath);
        SetStatusText("Failed to load: no rows found");
        return;
    }

    PopulateTable(vendorsTable_, parsedRows);
    notebook_->ChangeSelection(1);
    SetStatusText("Loaded vendor list Preview");
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

void MainFrame::PopulateTable(wxDataViewListCtrl* table, const std::vector<std::vector<wxString>>& rows)
{
    if (!table) return;

    //Clear any old data/colums
    table->Freeze();
    table->DeleteAllItems();
    table->ClearColumns();

    if (rows.empty())
    {
        table->Thaw();
        return;
    }

    //Use first row as header (or falback generic names)
    const auto& headerRow = rows[0];

    for (size_t colIndex = 0; colIndex < headerRow.size(); ++colIndex)
    {
        wxString columnName = headerRow[colIndex].IsEmpty() ? wxString::Format("Column %zu", colIndex + 1) : headerRow[colIndex];

    table->AppendTextColumn(columnName, wxDATAVIEW_CELL_INERT, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
    }

    for (size_t rowIndex = 1; rowIndex < rows.size(); ++rowIndex)
    {
        const auto& sourceRow = rows[rowIndex];

        wxVector<wxVariant> dvRow;
        dvRow.reserve(sourceRow.size());

        for (const auto& cell : sourceRow)
        {
            dvRow.push_back(wxVariant(cell));
        }

        table->AppendItem(dvRow);
    }

    for (unsigned int index = 0; index < table->GetColumnCount(); ++index)
    {
        if (auto* col = table->GetColumn(index))
        {
            col->SetWidth(wxCOL_WIDTH_AUTOSIZE);
        }
    }

    table->Thaw();
    table->Layout();
    table->GetParent()->Layout();
    Layout();
}

void MainFrame::BuildRecordingsTableWithEditors()
{
    if (!recordingsTable_ || recordingRows_.empty()) return;

    // Find CSV indices for special columns
    recordingsKeywordCol_ = -1;
    recordingsCommentsCol_ = -1;

    const auto& header = recordingRows_[0];
    for (size_t csvCol = 0; csvCol < header.size(); ++csvCol) {
        if (header[csvCol].CmpNoCase("Keyword") == 0) recordingsKeywordCol_ = static_cast<int>(csvCol);
        if (header[csvCol].CmpNoCase("Comments") == 0) recordingsCommentsCol_ = static_cast<int>(csvCol);
    }

    recordingsTable_->Freeze();
    recordingsTable_->DeleteAllItems();
    recordingsTable_->ClearColumns();

    recordingsModelToCsvCol_.clear();
    recordingsModelToCsvCol_.reserve(header.size());

    // ----- COLUMNS -----
    for (size_t csvCol = 0; csvCol < header.size(); ++csvCol) {
        const wxString colName = header[csvCol].IsEmpty()
            ? wxString::Format("Column %zu", csvCol + 1)
            : header[csvCol];

        // Model column index is sequential as we append
        const unsigned int modelCol = recordingsTable_->GetColumnCount();
        recordingsModelToCsvCol_.push_back(static_cast<int>(csvCol));

        if ((int)csvCol == recordingsKeywordCol_) {
            const wxArrayString& choices = Defaults::KeywordChoices();
            auto* renderer = new wxDataViewChoiceRenderer(choices, wxDATAVIEW_CELL_EDITABLE, wxALIGN_LEFT);
            auto* column = new wxDataViewColumn(colName, renderer, modelCol,
                wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
            recordingsTable_->AppendColumn(column);
        }
        else if ((int)csvCol == recordingsCommentsCol_) {
            // Make comments editable
            recordingsTable_->AppendTextColumn(colName, wxDATAVIEW_CELL_EDITABLE,
                wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
        }
        else {
            // <-- MISSING BEFORE: append all the other columns (read-only)
            recordingsTable_->AppendTextColumn(colName, wxDATAVIEW_CELL_INERT,
                wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
        }
    }

    // ----- ROWS -----
    for (size_t csvRow = 1; csvRow < recordingRows_.size(); ++csvRow) {
        const auto& source = recordingRows_[csvRow];

        wxVector<wxVariant> row;
        row.reserve(recordingsModelToCsvCol_.size());

        for (unsigned int modelCol = 0; modelCol < recordingsModelToCsvCol_.size(); ++modelCol) {
            const int csvCol = recordingsModelToCsvCol_[modelCol];
            const wxString val = (csvCol >= 0 && csvCol < (int)source.size()) ? source[csvCol] : wxString();
            row.push_back(wxVariant(val));
        }
        recordingsTable_->AppendItem(row);
    }

    // Auto-size for visibility
    for (unsigned int i = 0; i < recordingsTable_->GetColumnCount(); ++i) {
        if (auto* col = recordingsTable_->GetColumn(i)) col->SetWidth(wxCOL_WIDTH_AUTOSIZE);
    }

    recordingsTable_->Thaw();
}

void MainFrame::OnRecordingsCellChanged(wxDataViewEvent& event)
{
    // Only handle edits from the recordings table
    if (event.GetEventObject() != recordingsTable_) return;
    if (recordingRows_.empty()) return;

    wxDataViewItem item = event.GetItem();
    if (!item.IsOk()) return;

    const int viewRow = recordingsTable_->ItemToRow(item);
    const int modelCol = event.GetColumn();
    if (viewRow < 0 || modelCol < 0) return;

    // --- map view/model column -> CSV column ---
    if (modelCol >= (int)recordingsModelToCsvCol_.size()) return;
    const int csvCol = recordingsModelToCsvCol_[modelCol];

    // CSV row index (skip header row 0)
    const size_t csvRow = static_cast<size_t>(viewRow + 1);
    if (csvRow >= recordingRows_.size()) return;

    // Read new value from UI
    wxVariant newValue;
    recordingsTable_->GetValue(newValue, viewRow, modelCol);
    const wxString newText = newValue.GetString();

    // Ensure row is large enough, then write back to the CSV model
    if (csvCol >= (int)recordingRows_[csvRow].size())
        recordingRows_[csvRow].resize(csvCol + 1);
    recordingRows_[csvRow][csvCol] = newText;

    // --- Auto-fill default comment when Keyword changes and Comments is empty ---
    if (csvCol == recordingsKeywordCol_ && recordingsCommentsCol_ >= 0) {
        wxString currentComments;
        if (recordingsCommentsCol_ < (int)recordingRows_[csvRow].size())
            currentComments = recordingRows_[csvRow][recordingsCommentsCol_];

        //if (currentComments.IsEmpty()) {
            const wxString defaultText = Defaults::DefaultCommentFor(newText);
            if (!defaultText.IsEmpty()) {
                if (recordingsCommentsCol_ >= (int)recordingRows_[csvRow].size())
                    recordingRows_[csvRow].resize(recordingsCommentsCol_ + 1);
                recordingRows_[csvRow][recordingsCommentsCol_] = defaultText;

                // find the model column that maps to the CSV comments column
                int modelCommentsCol = -1;
                for (int m = 0; m < (int)recordingsModelToCsvCol_.size(); ++m) {
                    if (recordingsModelToCsvCol_[m] == recordingsCommentsCol_) { modelCommentsCol = m; break; }
                }
                if (modelCommentsCol >= 0) {
                    recordingsTable_->SetValue(wxVariant(defaultText), viewRow, modelCommentsCol);
                }
            }
        //}
    }
}
