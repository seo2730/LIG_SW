#include "pch.h"

#include "ATS.h"

// 운용통제기에게 현 위치 송신해주는 함수
double ATS::ATS_Scenario::send_current_position_x() {
	return current_pose.x;
}

double ATS::ATS_Scenario::send_current_position_y() {
	return current_pose.y;
}

// 속력을 벡터화하는 함수
void ATS::ATS_Scenario::speed_to_velocity() {
	double distance_x = (target_pose.x - initial_pose.x);
	double distance_y = (target_pose.y - initial_pose.y);
	double distance = sqrt(pow((target_pose.x - initial_pose.x), 2) + pow((target_pose.y - initial_pose.y), 2));

	double Cos = distance_x / distance;
	double Sin = distance_y / distance;

	velocity.x = speed * Cos;
	velocity.y = speed * Sin;
}

// 기동 수행하는 함수
void ATS::ATS_Scenario::move_to_target() {
	current_pose.x += current_pose.x + velocity.x * dt;
	current_pose.y += current_pose.y + velocity.y * dt;
}