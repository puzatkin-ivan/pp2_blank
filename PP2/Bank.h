#pragma once
#include <iostream>
#include <vector>
#include <mutex>

#include "BankClient.h"

enum Primitive
{
    CriticalSection = 1,
    Mutex = 2
};

class CBank
{
public:
	CBank(Primitive primitive);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
    int GetTotalBalance();
    std::vector<CBankClient> GetClients();

private:
    CRITICAL_SECTION m_balancaUpdateCriticalSection;
    std::mutex m_balancaUpdateMutex;

    Primitive m_primitive;
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	void SetTotalBalance(int value);
	void SomeLongOperations();
    void Lock();
    void Unlock();
};