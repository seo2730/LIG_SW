#include<iostream>
#include<math.h>

struct Vector2 {
	double x;
	double y;
};

class ATS {
public:
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

}