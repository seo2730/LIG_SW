// UDP ��� ��� ����
#include "UdpSocket.h"
#include <math.h>
#include <string>

// x,y ����
struct Vector2 {
	double x;
	double y;
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

	char send_buffer_data[BUFFER_SIZE];

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

	// ������ �۽�
	void send_data() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);	// �۽� ������ �޸� �ʱ�ȭ
		////////// send //////////
		//*udpsock.Buffer = *pose; // �۽� ������
		std::memcpy(&udpsock.Buffer, &send_buffer_data, BUFFER_SIZE);
		// sendto - �۽� ����, �۽� ������, ip, port �ʿ���
		sendto(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.send_addr, udpsock.send_size);
		std::cout << "�۽� ������ : " << udpsock.Buffer << endl;
	}
	// ������ ����
	void recv_data() {
		memset(udpsock.Buffer, 0x00, BUFFER_SIZE);
		if (strlen(udpsock.Buffer) == 0)
			std::cout << "������ �ʱ�ȭ ��" << endl;
		// recvfrom - �۽ŵ� ���� ���� ���� �ʿ���, ���� s_sock�� ������ �� / 5��°�� (sockaddr*)&udpsock.recv_addr �� �κп� �۽ŵ� ������ ������ �����
		recvfrom(udpsock.s_sock, udpsock.Buffer, BUFFER_SIZE, 0, (sockaddr*)&udpsock.recv_addr, &udpsock.recv_size);
	}

	// ������ ��ȯ
	// ���� ��ġ ��ȯ
	void double_to_char(Vector2 data) {
		string convert_data = to_string(data.x) + "," + to_string(data.y);
		strcpy(send_buffer_data, convert_data.c_str());
	}
	// �ʱ� ��ġ, ���� ��ġ, �ӷ� ��ȯ
	/*void char_to_double(char recv_data) {
		return;
	}*/

	// ��������⿡�� ������ �ó�����
	void Get_scenario(Vector2 start_pose, Vector2 end_pose, double _speed) {
		initial_pose = start_pose;
		current_pose = initial_pose;
		target_pose = end_pose;
		speed = _speed;
	}

	// ��������⿡�� �� ��ġ �۽����ִ� �Լ�
	Vector2 send_current_position() {
		return current_pose;
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
	ATS ats;
	Vector2 initial_pose = { 0.0, 0.0 };
	Vector2 target_pose = { 10.0, 5.0 };
	double speed = 0.5;

	ats.Get_scenario(initial_pose, target_pose, speed);
	ats.speed_to_velocity();
	std::cout << ats.velocity.x << " , " << ats.velocity.y << endl;
	while (!((ats.target_pose.x <= ats.current_pose.x) && (ats.target_pose.y <= ats.current_pose.y)))
	{
		ats.move_to_target();
		std::cout << ats.current_pose.x << " , " << ats.current_pose.y << endl;
	}
}