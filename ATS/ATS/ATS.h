#pragma once
#include<iostream>
#include<math.h>

using namespace System;

// x,y 구조체
public ref struct Vector2 {
	double x;
	double y;
};

namespace ATS {
	public ref class ATS_Scenario
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
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
		ATS_Scenario(Vector2 start_pose, Vector2 end_pose, double _speed) {
			initial_pose.x = start_pose.x;
			initial_pose.y = start_pose.y;
			current_pose.x = initial_pose.x;
			current_pose.y = initial_pose.y;
			target_pose.x = end_pose.x;
			target_pose.y = end_pose.y;
			speed = _speed;
		}

		// 운용통제기에게 현 위치 송신해주는 함수
		double send_current_position_x();
		double send_current_position_y();

		// 속력을 벡터화하는 함수
		void speed_to_velocity();

		// 기동 수행하는 함수
		void move_to_target();
	};
}
