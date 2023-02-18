#pragma once

class S_curve_controller
{
public:
	S_curve_controller(const float v_max, const float a_max);
	~S_curve_controller();

	float interpolate(float position, float time);
	float done();
	float get_p_acc(float time);
	float get_p_lin(float time);
	float get_p_decc(float target, float time);
	float get_t_total();

private:
	const float v_max; //Max velocity
	const float a_max; //Max acceleration
	float time_passed;
	float curr_pos;
	float curr_v;
	float p_acc;
	float t_acc; //Time in acceleration
	float t_lin; //Time in linear mode 
	float p_lin;
	bool is_done;
};

