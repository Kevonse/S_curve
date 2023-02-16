#include "S_curve_controller.h"
#include <iostream>

S_curve_controller::S_curve_controller(const float v_max, const float a_max) : v_max(v_max)
                                                                              ,a_max(a_max)
																			  ,time_passed(0)
																			  ,curr_pos(0)
																			  ,curr_v(0)
																			  ,p_acc(0)
																			  ,t_acc(v_max/a_max)
																			  ,t_lin(0)
																			  ,p_lin(0)
{}

S_curve_controller::~S_curve_controller() {}

float S_curve_controller::interpolate(float position, float time)
{
	float prev_pos = curr_pos;
	if(time_passed < t_acc) //if still accelerating - add distance criteria too
	{
		//if( distance covered is less than half) { deccelerate }
		curr_pos = get_p_acc(time_passed);
	}
	else
	{
		//if (t_acc == 0) t_acc = time_passed; //Log time it took to complete fase1 (acceleration)
		if (p_acc == 0) p_acc = curr_pos;
		if (p_lin == 0) p_lin = position - 2 * p_acc;
		if (t_lin == 0) t_lin = (position - p_acc * 2) / v_max;
		float remaining_time = get_t_total() - time_passed;
		//std::cout << "Remaining dist: " << remaining_dist << " , p_acc " << p_acc << std::endl;
		curr_pos = get_p_lin(position, time_passed); //linear coordinate, will change in next 'if' if in decelerating phase
		if (remaining_time <= t_acc) //acceleration time done
		{
			//std::cout << "Decelerating!" << std::endl; 
			curr_pos = get_p_decc(position, time_passed);
			std::cout << "Decelerating to pos: " << curr_pos << " , at time: " << time_passed << ", total time: "<< get_t_total() << std::endl;
		}
	}
	time_passed += time;
	//if (prev_pos > curr_pos) curr_pos = position;
	return curr_pos;
	
}

float S_curve_controller::get_current_pos()
{
	return curr_pos;
}

float S_curve_controller::get_v(float time)
{
	if (curr_v < v_max)
	{
		curr_v = a_max*time;
		return curr_v;
	}
	return v_max;
}

float S_curve_controller::get_p_acc(float time)
{
	return 0.5 * a_max * (time_passed * time_passed);
}

float S_curve_controller::get_p_lin(float pos, float time)
{
	return v_max * (time_passed - t_acc) + p_acc;
	//return v_max * time_passed - (v_max * v_max) / (2 * a_max);
}

float S_curve_controller::get_p_decc(float target, float time)
{
	//return (p_acc + p_lin) + v_max * time_passed + 0.5 * a_max * (get_t_total() - time_passed) * (get_t_total() - time_passed);
	float t_new = time_passed - (t_acc+t_lin);
	float p_new = p_acc + p_lin;
	//return target - 0.5 * a_max * (t_diff * t_diff);
	//return target - 0.5 * a_max * (get_t_total() - time_passed) * (get_t_total() - time_passed);
	return -0.5 * a_max * (t_new * t_new) + v_max * t_new + p_new;
}

float S_curve_controller::get_t_total()
{
	return 2 * t_acc + t_lin; //fase3 is estimated to take the same time as fase1.
}