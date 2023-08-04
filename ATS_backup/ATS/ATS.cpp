// UDP 통신 헤더 파일
#include "UdpSocket.h"
#include <math.h>
#include <string>

// x,y 벡터
struct Vector2 {
	double x;
	double y;
};

// 시나리오 구조체
struct Initial_Scenario {
	Vector2 initial_pose;
	Vector2 target_pose;
	double speed;
};

class ATS {
public:
	// UDP 설정 변수
	UdpSock udpsock;
	// 초기 위치
	Vector2 initial_pose;
	// 목표 위치
	Vector2 target_pose;
	// 현재 위치
	Vector2 current_pose;
	// x,y 속도
	Vector2 velocity;

	// 운용통제기에서 설정한 속력
	double speed;
	// 제어 주기?
	double dt=0.1;

	Initial_Scenario send_scenario_data;
	Initial_Scenario recv_scenario_data;

	Vector2 *send_current_pose;
	Vector2 *recv_current_pose;
	char message[BUFFER_SIZE];

	// 통신 설정
	void set_UDP() {
		// winsock을 시작하겠다? 이런 느낌
		if (WSAStartup(MAKEWORD(2, 2), &udpsock.wsadata) != 0)		
		{
			cout << "winsock 초기화 실패!" << endl;
		}

		// SOCK_DGRAM - UDP protocol, 결국 이부분은 똑같이 사용
		udpsock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);		
		// ip 127.0.0.1로 설정 - 고정 부분
		udpsock.send_addr.sin_addr.s_addr = inet_addr("172.16.12.220"); //172.16.12.220, 127.0.0.1
		//고정
		udpsock.send_addr.sin_family = AF_INET;		
		// port 1000으로 설정
		udpsock.send_addr.sin_port = htons(1000);	

		// bind 부분 / 건드릴 필요 x
		if (bind(udpsock.s_sock, (sockaddr*)&udpsock.send_addr, udpsock.send_size) == SOCKET_ERROR)
		{
			cout << "bind 실패!" << endl;
			return;
		}
	}

	// 시나리오 데이터 송신
	void send_scenario() {
		//// 구조체 통신 ////
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		memcpy(udpsock.Buffer, &send_scenario_data, BUFFER_SIZE);
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);
		std::cout << "시나리오 배포" << endl;
		/////////////////////
	}
	// 시나리오 데이터 수신
	void recv_scenario() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		if (strlen(udpsock.Buffer) == 0)
			std::cout << "버퍼 데이터 초기화 됨" << endl;
		// recvfrom - 송신된 곳의 소켓 정보 필요함, 따라서 s_sock의 정보가 들어감 / 5번째에 (sockaddr*)&udpsock.recv_addr 이 부분에 송신된 소켓의 정보가 복사됨
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);

		//byte array -> 구조체
		memcpy(&recv_scenario_data, udpsock.Buffer, BUFFER_SIZE);
	
		std::cout << "시나리오 수신완료" << endl;
	}

	// 운용통제기에서 설정한 시나리오
	void Get_scenario(Initial_Scenario scenario) {
		initial_pose = scenario.initial_pose;
		current_pose = initial_pose;
		target_pose = scenario.target_pose;
		speed = scenario.speed;
		speed_to_velocity();
		std::cout << "공중위협모의기 시나리오 설정 완료" << endl;
	}

	// 속력을 벡터화하는 함수
	void speed_to_velocity() {
		double distance_x = (target_pose.x - initial_pose.x);
		double distance_y = (target_pose.y - initial_pose.y);
		double distance = sqrt(pow((target_pose.x - initial_pose.x),2) + pow((target_pose.y - initial_pose.y),2));

		double Cos = distance_x / distance;
		double Sin = distance_y / distance;

		velocity.x = speed * Cos;
		velocity.y = speed * Sin;
	}

	// 기동 수행하는 함수
	void move_to_target() {
		current_pose.x += velocity.x * dt;
		current_pose.y += velocity.y * dt;
	}

};

int main()
{
	// 운용이 보낸다는 가정
	/*ATS ats;
	Initial_Scenario scenario;
	scenario.initial_pose = {10.0, 5.0};
	scenario.target_pose = { 0.0, 5.0 };
	scenario.speed = 0.9;
	ats.send_scenario_data = scenario;

	ats.set_UDP();

	ats.send_scenario();
	ats.recv_scenario();

	ats.Get_scenario(ats.recv_scenario_data);

	std::cout << "공중위협모의기 시작" << endl;
	while (!((abs(ats.target_pose.x - ats.current_pose.x)<=1) && (abs(ats.target_pose.y - ats.current_pose.y)<=1)))
	{
		ats.move_to_target();
		std::cout << ats.current_pose.x << " , " << ats.current_pose.y << endl;
	}*/

	WSADATA wsadata;   // 뭔지 모르는데 있어야함
	SOCKET s_sock;
	SOCKET r_sock;   // recv 소켓
	SOCKADDR_IN send_addr = {};      // 소켓 정보 들어가는 곳 - send 소켓 정보
	SOCKADDR_IN recv_addr = {};      // 소켓 정보 들어가는 곳 - recv 소켓 정보
	int send_size = sizeof(send_addr);      //    소켓 정보 크기
	int recv_size = sizeof(recv_addr);      //    소켓 정보 크기

	char Buffer[256];      // 송신, 수신 데이터 - 실제론 송신 char, 수신 char 따로 만들어야함

	WSAStartup(MAKEWORD(2, 2), &wsadata);
	r_sock = socket(AF_INET, SOCK_DGRAM, 0);      // SOCK_DGRAM - UDP protocol, 결국 이부분은 똑같이 사용
	recv_addr.sin_addr.s_addr = inet_addr("172.16.12.220");      //    ip 127.0.0.1로 설정 - 고정 부분
	recv_addr.sin_family = AF_INET;      //    고정
	recv_addr.sin_port = htons(5000);      // port 1000으로 설정
	bind(r_sock, (sockaddr*)&recv_addr, recv_size);

	while(1)
	{
		memset(Buffer, 0x00, 256);
		// recvfrom - 송신된 곳의 소켓 정보 필요함, 따라서 s_sock의 정보가 들어감 / 5번째에 (sockaddr*)&udpsock.recv_addr 이 부분에 송신된 소켓의 정보가 복사됨
		recvfrom(r_sock, Buffer, 256, 0, (sockaddr*)&send_addr, &send_size);


		char SRCip[256]; // 출력을 위한 char
		memset(SRCip, 0x00, 256);

		cout << Buffer << endl; // 출력 부분
	}
	

	return 0;
}