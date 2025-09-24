#include "Helpers.h"
#include <wx/textfile.h>

namespace Helpers
{
	static bool IsQuoteCharacter(wxChar character)
	{
		return character == '"' || character == '\'';
	}





	std::vector<std::vector<wxString>> LoadCsv(const wxString& filePath, size_t maxRows)
	{
		std::vector<std::vector<wxString>> allRows;
		wxTextFile inputFile;

		if (!inputFile.IsOpened()) return allRows;

		
		size_t rowCount = 0;

		for (size_t index = 0; index < inputFile.GetLineCount(); ++index)
		{
			wxString lineBuffer = inputFile.GetLine(index);
			lineBuffer.Trim(true).Trim(false);

			allRows.push_back(SplitCsvLine(lineBuffer));

			if (maxRows && ++rowCount >= maxRows)
			{
				break;
			}
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
