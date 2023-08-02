#pragma once
#include <iostream>
#include <WinSock2.h>		// ���� ���� ���
#pragma comment (lib,"ws2_32.lib")		// ���� ���� ���
using namespace std;

#define BUFFER_SIZE 256		// ������ ������ 

class UdpSock
{
public:
	WSADATA wsadata;	// ���� �𸣴µ� �־����
	SOCKET s_sock;		// send ����
	SOCKET r_sock;		// recv ����
	SOCKADDR_IN send_addr = {};		// ���� ���� ���� �� - send ���� ����
	SOCKADDR_IN recv_addr = {};		// ���� ���� ���� �� - recv ���� ����
	int send_size = sizeof(send_addr);		//	 ���� ���� ũ��
	int recv_size = sizeof(recv_addr);		//	 ���� ���� ũ��

	char Buffer[BUFFER_SIZE];		// �۽�, ���� ������ - ������ �۽� char, ���� char ���� ��������
};