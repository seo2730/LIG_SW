#pragma once
#include <iostream>
#include <WinSock2.h>		// 소켓 쓰는 헤더
#pragma comment (lib,"ws2_32.lib")		// 소켓 쓰는 헤더
using namespace std;

#define BUFFER_SIZE 256		// 데이터 사이즈 

class UdpSock
{
public:
	WSADATA wsadata;	// 뭔지 모르는데 있어야함
	SOCKET s_sock;		// send 소켓
	SOCKET r_sock;		// recv 소켓
	SOCKADDR_IN send_addr = {};		// 소켓 정보 들어가는 곳 - send 소켓 정보
	SOCKADDR_IN recv_addr = {};		// 소켓 정보 들어가는 곳 - recv 소켓 정보
	int send_size = sizeof(send_addr);		//	 소켓 정보 크기
	int recv_size = sizeof(recv_addr);		//	 소켓 정보 크기

	char Buffer[BUFFER_SIZE];		// 송신, 수신 데이터 - 실제론 송신 char, 수신 char 따로 만들어야함
};