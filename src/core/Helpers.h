#pragma once
#include <wx/wx.h>
#include <vector>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>

namespace Helpers
{
	// Basic CSV reader: returns rows -> cells. If maxRows > 0, cap rows.
	std::vector<std::vector<wxString>> LoadCsv(const wxString& path, size_t maxRows = 0);

	// Simple CSV splitter (handles commas and quoted fields minimally).
	std::vector<wxString> SplitCsvLine(const wxString& line);

	// Reusable separator so we can preserve notes when keyword changes again
	inline const wxString kNotesSeparator = wxS("\n— extra notes —\n");

	// Opens a small modal dialog with a multiline textbox.
    // Returns empty string if user cancels.
	wxString PromptExtraNotes(wxWindow* parent,
		const wxString& title = wxS("Add any additional notes (optional)"),
		const wxString& placeholder = wxS("Type any extra details here…"),
		const wxString& prefill = wxEmptyString);

}