#pragma once

class S_curve_controller
{
public:
	S_curve_controller(const float v_max, const float a_max);
	~S_curve_controller();

	float interpolate(float position, float time);
	float get_current_pos();

private:
	float curr_pos;
	float curr_v;
	float p_v_max; //Time it took to reach v_max
	const float v_max; //Max velocity
	const float a_max; //Max acceleration
};

