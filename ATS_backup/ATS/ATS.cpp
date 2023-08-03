// UDP 통신 헤더 파일
#include "UdpSocket.h"
#include <math.h>
#include <string>

// x,y 벡터
struct Vector2 {
	double x;
	double y;
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
	double dt;

	char pose[BUFFER_SIZE];
	char SRCip[BUFFER_SIZE]; // 출력을 위한 char

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
		udpsock.send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		
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

	// 데이터 송신
	void send_data() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);	// 송신 데이터 메모리 초기화
		////////// send //////////
		//*udpsock.Buffer = *pose; // 송신 데이터
		std::memcpy(&udpsock.Buffer, &pose, BUFFER_SIZE);
		// sendto - 송신 소켓, 송신 데이터, ip, port 필요함
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);
		std::cout << "송신 데이터 : " << udpsock.Buffer << endl;
	}
	// 데이터 수신
	void recv_data() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		if (strlen(udpsock.Buffer) == 0)
			std::cout << "데이터 초기화 됨" << endl;
		// recvfrom - 송신된 곳의 소켓 정보 필요함, 따라서 s_sock의 정보가 들어감 / 5번째에 (sockaddr*)&udpsock.recv_addr 이 부분에 송신된 소켓의 정보가 복사됨
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);
		
		memset(SRCip, 0x00, BUFFER_SIZE);
	}

	// 데이터 변환
	void double_to_char(Vector2 data) {
		string send_data = to_string(data.x) + "," + to_string(data.y);
		strcpy(pose, send_data.c_str());
	}

	// 운용통제기에서 설정한 시나리오
	void Get_scenario(Vector2 start_pose, Vector2 end_pose, double _speed) {
		initial_pose = start_pose;
		current_pose = initial_pose;
		target_pose = end_pose;
		speed = _speed;
	}

	// 운용통제기에게 현 위치 송신해주는 함수
	Vector2 send_current_position() {
		return current_pose;
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
		current_pose.x += current_pose.x + velocity.x * dt;
		current_pose.y += current_pose.y + velocity.y * dt;
	}

};

int main()
{
	ATS ats;
	Vector2 data = { 0.1,0.2 };
	ats.double_to_char(data);

	ats.set_UDP();

	ats.send_data();
	ats.recv_data();
	std::cout << "수신 데이터 Buffer : " << ats.udpsock.Buffer << endl;
}