// UDP ��� ��� ����
#include "UdpSocket.h"
#include <math.h>
#include <string>

// x,y ����
struct Vector2 {
	double x;
	double y;
};

// �ó����� ����ü
struct Initial_Scenario {
	Vector2 initial_pose;
	Vector2 target_pose;
	double speed;
};

class ATS {
public:
	// UDP ���� ����
	UdpSock udpsock;
	// �ʱ� ��ġ
	Vector2 initial_pose;
	// ��ǥ ��ġ
	Vector2 target_pose;
	// ���� ��ġ
	Vector2 current_pose;
	// x,y �ӵ�
	Vector2 velocity;

	// ��������⿡�� ������ �ӷ�
	double speed;
	// ���� �ֱ�?
	double dt=0.1;

	Initial_Scenario* send_scenario_data;
	Initial_Scenario* recv_scenario_data;

	Vector2 *send_current_pose;
	Vector2 *recv_current_pose;
	char message[BUFFER_SIZE];

	// ��� ����
	void set_UDP() {
		// winsock�� �����ϰڴ�? �̷� ����
		if (WSAStartup(MAKEWORD(2, 2), &udpsock.wsadata) != 0)		
		{
			cout << "winsock �ʱ�ȭ ����!" << endl;
		}

		// SOCK_DGRAM - UDP protocol, �ᱹ �̺κ��� �Ȱ��� ���
		udpsock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);		
		// ip 127.0.0.1�� ���� - ���� �κ�
		udpsock.send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		
		//����
		udpsock.send_addr.sin_family = AF_INET;		
		// port 1000���� ����
		udpsock.send_addr.sin_port = htons(1000);	

		// bind �κ� / �ǵ帱 �ʿ� x
		if (bind(udpsock.s_sock, (sockaddr*)&udpsock.send_addr, udpsock.send_size) == SOCKET_ERROR)
		{
			cout << "bind ����!" << endl;
			return;
		}
	}

	// �ó����� ������ �۽�
	void send_scenario() {
		//// ����ü ��� ////
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		memcpy(udpsock.Buffer, send_scenario_data, BUFFER_SIZE);
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);
		std::cout << "�ó����� ����" << endl;
		/////////////////////
	}
	// �ó����� ������ ����
	void recv_scenario() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		if (strlen(udpsock.Buffer) == 0)
			std::cout << "���� ������ �ʱ�ȭ ��" << endl;
		// recvfrom - �۽ŵ� ���� ���� ���� �ʿ���, ���� s_sock�� ������ �� / 5��°�� (sockaddr*)&udpsock.recv_addr �� �κп� �۽ŵ� ������ ������ �����
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);
		recv_scenario_data = (Initial_Scenario*)udpsock.Buffer;
		std::cout << "�ó����� ���ſϷ�" << endl;
	}

	// ��������⿡�� �� ��ġ �۽����ִ� �Լ�
	//void send_current_position() {
	//	//// ����ü ��� ////
	//	memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
	//	memcpy(udpsock.Buffer, send_current_pose, BUFFER_SIZE);
	//	//std::cout << "�۽� ������ char �� Buffer : " << udpsock.Buffer << endl;
	//	//Vector2* test;
	//	//test = (Vector2*)udpsock.Buffer;
	//	//std::cout << "�۽� ������ Vector2 �� Buffer : " << test->x << endl;
	//	sendto(udpsock.r_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);
	//	std::cout << "���̴ٸ��Ǳ� ������ �۽� �Ϸ�" << endl;
	//	/////////////////////
	//}
	//// ��ġ ������ ����
	//void recv_current_position() {
	//	memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
	//	if (strlen(udpsock.Buffer) == 0)
	//		std::cout << "������ �ʱ�ȭ ��" << endl;
	//	// recvfrom - �۽ŵ� ���� ���� ���� �ʿ���, ���� s_sock�� ������ �� / 5��°�� (sockaddr*)&udpsock.recv_addr �� �κп� �۽ŵ� ������ ������ �����
	//	recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);
	//	recv_current_pose = (Vector2*)udpsock.Buffer;
	//}

	// ������ ��ȯ
	// ���� ��ġ ��ȯ
	//void double_to_char(Vector2 data) {
	//	string convert_data = to_string(data.x) + "," + to_string(data.y);
	//	//strcpy(send_buffer_data, convert_data.c_str());
	//}
	//// �ʱ� ��ġ, ���� ��ġ, �ӷ� ��ȯ
	//void char_to_double(char recv_data) {
	//	return;
	//}

	// ��������⿡�� ������ �ó�����
	void Get_scenario(Initial_Scenario *scenario) {
		initial_pose = scenario->initial_pose;
		current_pose = initial_pose;
		target_pose = scenario->target_pose;
		speed = scenario->speed;
		speed_to_velocity();
		std::cout << "�����������Ǳ� �ó����� ���� �Ϸ�" << endl;
	}

	// �ӷ��� ����ȭ�ϴ� �Լ�
	void speed_to_velocity() {
		double distance_x = (target_pose.x - initial_pose.x);
		double distance_y = (target_pose.y - initial_pose.y);
		double distance = sqrt(pow((target_pose.x - initial_pose.x),2) + pow((target_pose.y - initial_pose.y),2));

		double Cos = distance_x / distance;
		double Sin = distance_y / distance;

		velocity.x = speed * Cos;
		velocity.y = speed * Sin;
	}

	// �⵿ �����ϴ� �Լ�
	void move_to_target() {
		current_pose.x += velocity.x * dt;
		current_pose.y += velocity.y * dt;
	}

};

int main()
{
	// ����� �����ٴ� ����
	ATS ats;
	Initial_Scenario scenario;
	scenario.initial_pose = {0.0, 0.0};
	scenario.target_pose = { 10.0, 3.0 };
	scenario.speed = 0.9;
	ats.send_scenario_data = &scenario;

	ats.set_UDP();

	ats.send_scenario();
	ats.recv_scenario();

	ats.Get_scenario(ats.recv_scenario_data);

	std::cout << "�����������Ǳ� ����" << endl;
	while (!((ats.target_pose.x <= ats.current_pose.x) && (ats.target_pose.y <= ats.current_pose.y)))
	{
		ats.move_to_target();
		std::cout << ats.current_pose.x << " , " << ats.current_pose.y << endl;
	}

	return 0;
}