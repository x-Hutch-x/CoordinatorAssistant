#pragma once
#include <wx/wx.h>
#include <wx/arrstr.h>

namespace Defaults
{
	// The list that appears in the Keyword dropdown (order matters)
	const wxArrayString& KeywordChoices();


	// Returns the default comment text for a given keyword (or empty if none)
	wxString DefaultCommentFor(const wxString& keyword);




} // namespace Defaults
