#pragma once
#include <Windows.h>

class CBank;

class CBankClient
{
public:
	unsigned GetId();
    int GetBalance();

private:
	CBankClient(CBank *bank, unsigned id);
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
    static int GetIteractionCount();

	friend CBank;

	CBank *m_bank;
	unsigned m_id;
    int m_balance;
};