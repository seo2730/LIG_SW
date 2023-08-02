#include "UdpSocket.h"

int main()
{
	UdpSock udpsock;

	if (WSAStartup(MAKEWORD(2, 2), &udpsock.wsadata) != 0)		// winsock�� �����ϰڴ�? �̷� ����
	{
		cout << "winsock �ʱ�ȭ ����!" << endl;
	}	


	////////////////////// �۽� ///////////////////////
	udpsock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);		// SOCK_DGRAM - UDP protocol, �ᱹ �̺κ��� �Ȱ��� ���
	udpsock.send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		//	 ip 127.0.0.1�� ���� - ���� �κ�
	udpsock.send_addr.sin_family = AF_INET;		//	 ����
	udpsock.send_addr.sin_port = htons(1000);		// port 1000���� ����

	// bind �κ� / �ǵ帱 �ʿ� x
	if (bind(udpsock.s_sock, (sockaddr*)&udpsock.send_addr, udpsock.send_size) == SOCKET_ERROR)
	{
		cout << "bind ����!" << endl;
		return 0;
	}

	memset(udpsock.Buffer, 0x00, BUFFER_SIZE);	// �۽� ������ �޸� �ʱ�ȭ
	
	while (1) // send + recv - ���߿� �۽�, ���� thread ���� ��������
	{
		////////// send //////////
		*udpsock.Buffer = *"a"; // �۽� ������
		// sendto - �۽� ����, �۽� ������, ip, port �ʿ���
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);

		////////// recv //////////
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		// recvfrom - �۽ŵ� ���� ���� ���� �ʿ���, ���� s_sock�� ������ �� / 5��°�� (sockaddr*)&udpsock.recv_addr �� �κп� �۽ŵ� ������ ������ �����
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);


		char SRCip[BUFFER_SIZE]; // ����� ���� char
		memset(SRCip, 0x00, BUFFER_SIZE);

		cout << udpsock.Buffer << endl; // ��� �κ�
	}

	return 0;
}