#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser(string sFilePath)
{
	sFileName = sFilePath;
	finput.open(sFileName);
	if (!finput.is_open())
		throw 1;
}


FileParser::~FileParser()
{
	finput.close();
}

bool FileParser::GetCurrOperationInfo(int* piTime, bool* pbAddDel, int* piId, double* pdCost)
{
	std::wstring sLine = L"";
	char c;
	int iNumItems = 0;
	while (finput.get(c))
	{
		if (c == '\r' || c == '\n')
		{
			if (iNumItems == 2)
				*piId = _wtoi(sLine.c_str());
			else
				*pdCost = stod(sLine);
			return true;
		}
		else if (c == ' ')
		{
			switch (iNumItems)
			{
				case 0:
					*piTime = _wtoi(sLine.c_str());
					iNumItems++;
					break;
				case 1:
					if (sLine == L"I")
						*pbAddDel = true;
					else
						*pbAddDel = false;
					iNumItems++;
					break;
				case 2:
					*piId = _wtoi(sLine.c_str());
					iNumItems++;
					break;
			}
			sLine = L"";
		}
		else
			sLine += c;
	}
	if (iNumItems > 0)
	{
		if (sLine != L"")
		{
			if (iNumItems == 2)
				*piId = _wtoi(sLine.c_str());
			else
				*pdCost = stod(sLine);
		}
		return true;
	}	
	return false;

}
