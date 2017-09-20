// Orders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "OrderBook.h"
#include "FileParser.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		
		string sFilePath(argv[1]);
		cout << sFilePath << endl;
		OrderBook obBook;
		try
		{
			FileParser fpParser(sFilePath);
			bool bRead = true;
			while (bRead)
			{
				int iTime = 0;
				bool bAddDel = 0;
				int iId = 0;
				double dCost = 0;
				bRead = fpParser.GetCurrOperationInfo(&iTime, &bAddDel, &iId, &dCost);
				if (bRead)
				{
					if (bAddDel)
						obBook.AddOrder(iTime, iId, dCost);
					else
						obBook.DeleteOrder(iTime, iId);
				}
			}
			cout << "Average maximum cost: " << obBook.GetAvgMaxCost() << endl;
		}
		catch (int ex)
		{
			if (ex == 1)
			{
				cout << "Bad path!" << endl;
			}
		}
	}
	else
		cout << "No path!" << endl;
	system("pause");
	return 0;
}

