#pragma once
#include <wx/wx.h>
#include <vector>

namespace Helpers
{
	// Basic CSV reader: returns rows -> cells. If maxRows > 0, cap rows.
	std::vector<std::vector<wxString>> LoadCsv(const wxString& path, size_t maxRows = 0);

	// Simple CSV splitter (handles commas and quoted fields minimally).
	std::vector<wxString> SplitCsvLine(const wxString& line);

}