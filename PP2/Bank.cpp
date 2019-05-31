#include "Bank.h"

CBank::CBank(Primitive primitive)
{
    m_primitive = primitive;
    InitializeCriticalSection(&m_balancaUpdateCriticalSection);
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
    Lock();
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
    Unlock();
}

void CBank::Lock()
{
    if (m_primitive == Primitive::CriticalSection)
    {
        EnterCriticalSection(&m_balancaUpdateCriticalSection);
    }
    else if (m_primitive == Primitive::Mutex)
    {
        m_balancaUpdateMutex.lock();
    }
}

void CBank::Unlock()
{
    if (m_primitive == Primitive::CriticalSection)
    {
        LeaveCriticalSection(&m_balancaUpdateCriticalSection);
    }
    else if (m_primitive == Primitive::Mutex)
    {
        m_balancaUpdateMutex.unlock();
    }
}

int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
    Sleep(1000);
}

std::vector<CBankClient> CBank::GetClients()
{
    return m_clients;
}
