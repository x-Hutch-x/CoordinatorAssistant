#include "Helpers.h"


namespace Helpers
{
	static bool IsQuoteCharacter(wxChar character)
	{
		return character == '"' || character == '\'';
	}





	std::vector<std::vector<wxString>> LoadCsv(const wxString& filePath, size_t maxRows)
	{
		std::vector<std::vector<wxString>> allRows;
		wxFileInputStream fileStream(filePath);

		if (!fileStream.IsOk())
		{
			wxLogError("Could not open CSV file: %s", filePath);
			return allRows;
		}

		wxTextInputStream textStream(fileStream, "\n", wxConvUTF8);
		
		size_t rowCount = 0;
		bool firstLine = true;

		while (fileStream.IsOk() && !fileStream.Eof())
		{
			wxString lineBuffer = textStream.ReadLine();
			lineBuffer.Trim(true).Trim(false);

			if (lineBuffer.empty()) continue;

			if (firstLine && !lineBuffer.empty() && lineBuffer[0] == 0xFEFF)
			{
				lineBuffer = lineBuffer.Mid(1);
			}

			firstLine = false;
			allRows.push_back(SplitCsvLine(lineBuffer));

			if (maxRows && ++rowCount >= maxRows)
			{
				break;
			}

		}

		if (allRows.empty())
		{
			wxLogWarning("CSV parsed zero rows: %s", filePath);
		}
		else
		{
			wxLogMessage("CSV loaded: %zu rows from %s", allRows.size(), filePath);
		}

		return allRows;
	}





	std::vector<wxString> SplitCsvLine(const wxString& line)
	{
		std::vector<wxString> parsedCells;
		wxString currentCell;
		bool insideQuotes = false;
		wxChar activeQuoteChar = 0;

		for (size_t index = 0; index < line.length(); ++index)
		{
			wxChar currentChar = line[index];

			if (insideQuotes)
			{
				if (currentChar == activeQuoteChar)
				{
					if (index + 1 < line.length() && line[index + 1] == activeQuoteChar)
					{
						currentCell += activeQuoteChar;
						++index;
					}
					else
					{
						insideQuotes = false;
					}
				}
				else
				{
					currentCell += currentChar;
				}
			}
			else
			{
				if (currentChar == ',')
				{
					parsedCells.push_back(currentCell);
					currentCell.clear();
				}
				else if (IsQuoteCharacter(currentChar))
				{
					insideQuotes = true;
					activeQuoteChar = currentChar;
				}
				else
				{
					currentCell += currentChar;
				}
			}
		}

		parsedCells.push_back(currentCell);
		return parsedCells;
	}

	wxString PromptExtraNotes(wxWindow* parent, const wxString& title, const wxString& placeholder, const wxString& prefill)
	{
		wxDialog dlg(parent, wxID_ANY, title, wxDefaultPosition, wxSize(480, 280),
			wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

		auto* vbox = new wxBoxSizer(wxVERTICAL);
		auto* lbl = new wxStaticText(&dlg, wxID_ANY, placeholder);
		auto* txt = new wxTextCtrl(&dlg, wxID_ANY, prefill,
			wxDefaultPosition, wxDefaultSize,
			wxTE_MULTILINE | wxTE_RICH2);

		auto* btns = dlg.CreateSeparatedButtonSizer(wxOK | wxCANCEL);

		vbox->Add(lbl, 0, wxALL, 8);
		vbox->Add(txt, 1, wxEXPAND | wxLEFT | wxRIGHT, 8);
		vbox->Add(btns, 0, wxEXPAND | wxALL, 8);
		dlg.SetSizerAndFit(vbox);

		if (dlg.ShowModal() == wxID_OK) {
			return txt->GetValue().Trim(true).Trim(false);
		}


		return wxEmptyString;
	}

}
