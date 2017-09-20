#include "stdafx.h"
#include "OrderBook.h"


OrderBook::OrderBook()
{
	lOrderList.clear();
	iStartTime = 0;
	iCurrTime = 0;
	iTotalTime = 0;
	dTWCost = 0;
	dMaxCost = 0;
	iMaxAddTime = 0;
}


OrderBook::~OrderBook()
{
}

void OrderBook::AddOrder(int iTime, int iId, double dCost)
{
	if (iStartTime == 0)
		iStartTime = iTime;
	if (iCurrTime < iTime)
	{
		iCurrTime = iTime;
		iTotalTime = iCurrTime - iStartTime;
	}
	Order order;
	order.iTime = iTime;
	order.iId = iId;
	order.dCost = dCost;
	lOrderList.push_back(order);
	if (dCost > dMaxCost)
	{
		CalcAvgMaxCost();
		dMaxCost = dCost;
		iMaxAddTime = iTime;
	}
}

void OrderBook::DeleteOrder(int iTime, int iId)
{
	if (iCurrTime < iTime)
	{
		iCurrTime = iTime;
		iTotalTime = iCurrTime - iStartTime;
	}
	for (auto it = lOrderList.begin(); it != lOrderList.end(); it++)
	{
		if (it->iId == iId)
		{
			bool bToFindMax = false;
			if (it->dCost == dMaxCost)
				bToFindMax = true;
			lOrderList.erase(it);
			if (lOrderList.begin() == lOrderList.end())
			{
				CalcAvgMaxCost();
				iTotalTime = iCurrTime - iStartTime;
				iStartTime = 0;
				dMaxCost = 0;
				iMaxAddTime = 0;
				return;
			}
			if (bToFindMax)
				FindMaxCost();
			return;
		}
	}
}

void OrderBook::FindMaxCost()
{
	double dPrevMax = dMaxCost;
	double dMax = 0;
	int iTime = 0;
	for (auto it = lOrderList.begin(); it != lOrderList.end(); it++)
	{
		if (it->dCost > dMax)
		{
			dMax = it->dCost;
			iTime = it->iTime;
		}
	}
	if (dMax != dPrevMax)
	{
		CalcAvgMaxCost();
		dMaxCost = dMax;
		iMaxAddTime = iCurrTime;
	}
}

void OrderBook::CalcAvgMaxCost()
{
	dTWCost += dMaxCost*(iCurrTime - iMaxAddTime);
}

double OrderBook::GetMaxCost()
{
	return dMaxCost;
}

double OrderBook::GetAvgMaxCost()
{
	if (iTotalTime != 0)
		return dTWCost / iTotalTime;
	else
		return 0;
}
