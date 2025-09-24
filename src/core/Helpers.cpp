#include "Helpers.h"
#include <wx/ffile.h>

namespace Helpers
{
	static bool IsQuoteCharacter(wxChar character)
	{
		return character == '"' || character == '\'';
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
					insideQuotes = false;
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

}
