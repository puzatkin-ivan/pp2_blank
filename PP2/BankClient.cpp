#include "BankClient.h"
#include "Bank.h"


CBankClient::CBankClient(CBank *bank, unsigned id)
	: m_bank(bank)
	, m_id(id)
{
	CreateThread(NULL, 0, ThreadFunction, this, 0, NULL);
}


unsigned CBankClient::GetId()
{
	return m_id;
}

int CBankClient::GetBalance()
{
    return m_balance;
}

DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	srand(client->m_id);

    int iteractionCount = GetIteractionCount();
	for (int i = 0; i < iteractionCount; ++i)
	{
		Sleep(GetSleepDuration(client));
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
	}
	return 0;
}

int CBankClient::GetIteractionCount()
{
    return (10 + rand() % 10);
}

unsigned CBankClient::GetSleepDuration(CBankClient *client)
{
	return (1000 + rand() % 3000) * (client->m_id + 1);
}


unsigned CBankClient::GetBalanceChangeValue()
{
    return rand() % 201 - 100;
}