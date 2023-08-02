#include<iostream>
#include<math.h>

struct Vector2 {
	double x;
	double y;
};

class ATS {
public:
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
	double dt;

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
		current_pose.x += current_pose.x + velocity.x * dt;
		current_pose.y += current_pose.y + velocity.y * dt;
	}

};

int main()
{

}