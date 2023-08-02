#include "UdpSocket.h"

int main()
{
	UdpSock udpsock;

	if (WSAStartup(MAKEWORD(2, 2), &udpsock.wsadata) != 0)		// winsock을 시작하겠다? 이런 느낌
	{
		cout << "winsock 초기화 실패!" << endl;
	}	


	////////////////////// 송신 ///////////////////////
	udpsock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);		// SOCK_DGRAM - UDP protocol, 결국 이부분은 똑같이 사용
	udpsock.send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		//	 ip 127.0.0.1로 설정 - 고정 부분
	udpsock.send_addr.sin_family = AF_INET;		//	 고정
	udpsock.send_addr.sin_port = htons(1000);		// port 1000으로 설정

	// bind 부분 / 건드릴 필요 x
	if (bind(udpsock.s_sock, (sockaddr*)&udpsock.send_addr, udpsock.send_size) == SOCKET_ERROR)
	{
		cout << "bind 실패!" << endl;
		return 0;
	}

	memset(udpsock.Buffer, 0x00, BUFFER_SIZE);	// 송신 데이터 메모리 초기화
	
	while (1) // send + recv - 나중에 송신, 수신 thread 따로 만들어야함
	{
		////////// send //////////
		*udpsock.Buffer = *"a"; // 송신 데이터
		// sendto - 송신 소켓, 송신 데이터, ip, port 필요함
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);

		////////// recv //////////
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		// recvfrom - 송신된 곳의 소켓 정보 필요함, 따라서 s_sock의 정보가 들어감 / 5번째에 (sockaddr*)&udpsock.recv_addr 이 부분에 송신된 소켓의 정보가 복사됨
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);


		char SRCip[BUFFER_SIZE]; // 출력을 위한 char
		memset(SRCip, 0x00, BUFFER_SIZE);

		cout << udpsock.Buffer << endl; // 출력 부분
	}

	return 0;
}