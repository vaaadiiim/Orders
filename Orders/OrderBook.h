#include  <list>


#pragma once

using namespace std;

struct Order
{
	int iTime;
	int iId;
	double dCost;
};

class OrderBook
{
private:
	list<Order> lOrderList;
	int iStartTime;
	int iCurrTime;
	int iTotalTime;
	double dTWCost;//time weighted but not averaged
	double dMaxCost;
	int iMaxAddTime;
	void FindMaxCost();
	void CalcAvgMaxCost();
public:
	OrderBook();
	~OrderBook();
	void AddOrder(int iTime, int iId, double dCost);
	void DeleteOrder(int iTime, int iId);
	double GetMaxCost();
	double GetAvgMaxCost();
};

