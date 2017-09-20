#include  <string>
#include <fstream>

#pragma once

using namespace std;

class FileParser
{
private:
	string sFileName;
	ifstream finput;
public:
	FileParser() = delete;
	FileParser(string sFilePath);
	~FileParser();
	bool GetCurrOperationInfo(int* piTime, bool* pbAddDel, int* piId, double* pdCost);//return false mean end of file
};

