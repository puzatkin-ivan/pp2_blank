#include "stdafx.h"
#include <string>
#include <iostream>
#include <istream>

#include "Bank.h"
#include "BankClient.h"

namespace
{

const int DEFAULT_CLIENT_COUNT = 2;

}

void ShowStatisticsByBalance(CBank* bank);
int tryParseIntFromString(const std::string& clientCount);
void ShowInstructions(std::ostream& stream);
void CreateClient(CBank* bank, int clientCount);
void WaitInputExitCommand(std::istream& stream);

int main(int argc, char* argv[])
{
    if (argc == 2 && argv[1] == "/?")
    {
        ShowInstructions(std::cout);
        return 0;
    }

    int clientCount = DEFAULT_CLIENT_COUNT;
    if (argc >= 2)
    {
        std::string clientCountParam = argv[1];
        clientCount = tryParseIntFromString(clientCountParam);
    }

    int primitiveType = 1;
    if (argc == 3)
    {
        std::string primitiveParam = argv[2];
        primitiveType = tryParseIntFromString(primitiveParam);
    }

    if (clientCount == -1 || primitiveType == -1)
    {
        std::cout << "Invalid application arguments." << std::endl;
        ShowInstructions(std::cout);
        return 1;
    }

	CBank* bank = new CBank();
    CreateClient(bank, clientCount);

    WaitInputExitCommand(std::cin);

    ShowStatisticsByBalance(bank);
    return 0;
}

int tryParseIntFromString(const std::string& clientCount)
{
    int result = 0;
    try
    {
        result = std::stoi(clientCount, nullptr, 10);
    }
    catch (std::invalid_argument ex)
    {
        result = -1;
    }
    return result;
}

void ShowStatisticsByBalance(CBank* bank)
{
    std::cout << "Bank balance: " << bank->GetTotalBalance() << std::endl;

    int totalClientBalance = 0;
    std::cout << "Clients balance: " << std::endl;
    for (auto client : bank->GetClients())
    {
        totalClientBalance += client.GetBalance();
        std::cout << "- " << "Client " << client.GetId()
            << " balance : " << client.GetBalance() << std::endl;
    }

    std::cout << "Total client balance: " << totalClientBalance << std::endl;
}

void ShowInstructions(std::ostream& stream)
{
    stream << "Usage: PP2.exe <clients> <primitive>" << std::endl;
}

void CreateClient(CBank* bank, int clientCount)
{
    if (clientCount < 2)
    {
        return;
    }

    for (int counter = 0; counter < clientCount; ++counter)
    {
        bank->CreateClient();
    }
}

void WaitInputExitCommand(std::istream& stream)
{
    bool isExit = false;
    while (!isExit)
    {
        std::string exit;
        stream >> exit;
        isExit = (exit == "exit" || exit == "quit");
    }
}
