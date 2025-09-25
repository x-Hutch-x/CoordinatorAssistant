#include "Defaults.h"
#include <unordered_map>

namespace Defaults
{
	const wxArrayString& KeywordChoices()
	{
		static wxArrayString choices;

		if (choices.IsEmpty())
		{
			choices.Add(wxS("VENDOR ISSUE"));
			choices.Add(wxS("UPS ISSUE"));
			choices.Add(wxS("STATUSED"));
			choices.Add(wxS("QA REJECTS"));
			choices.Add(wxS("MPD ISSUE"));
			choices.Add(wxS("DOCS IN HOUSE"));
			choices.Add(wxS("COURTHOUSE"));
			choices.Add(wxS("CANCELED"));
		}

		return choices;
	}

	wxString DefaultCommentFor(const wxString& keyword)
	{
		static std::unordered_map<wxString, wxString, wxStringHash, wxStringEqual> defaults;

		if (defaults.empty())
		{
			defaults.emplace(wxS("VENDOR ISSUE"), wxS("Followed up with vendor for status; awaiting ETA."));
			defaults.emplace(wxS("UPS ISSUE"), wxS("Carrier delay/loss reported; tracking pending update."));
			defaults.emplace(wxS("STATUSED"), wxS("Order completed. Status updated in EXOS."));
			defaults.emplace(wxS("QA REJECTS"), wxS("QA rejected; requesting corrected documents."));
			defaults.emplace(wxS("MPD ISSUE"), wxS("Docs not sent to vendor; no tracking on Item States tab."));
			defaults.emplace(wxS("DOCS IN HOUSE"), wxS("Docs returned to SL; rejected on [date], tracking noted."));
			defaults.emplace(wxS("COURTHOUSE"), wxS("Docs presented. Book/Page expected next business day."));
			defaults.emplace(wxS("CANCELED"), wxS("Order canceled in EXOS."));
		}

		auto it = defaults.find(keyword);
		return (it != defaults.end()) ? it->second : wxString();
	}




} // namespace Defaults