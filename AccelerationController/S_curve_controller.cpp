#include "S_curve_controller.h"
#include <iostream>

S_curve_controller::S_curve_controller(float v_max, float a_max) : v_max(v_max), a_max(a_max), curr_pos(0), curr_v(0), p_v_max(0) {}

S_curve_controller::~S_curve_controller() {}

float S_curve_controller::interpolate(float position, float time)
{
	if (curr_v >= v_max && (p_v_max == 0)) //check if max velocity reached - and that it is only set once, hence the check  for 0.
	{
		//curr_v = v_max; //Adjust to match max in case of too large increment value.
		p_v_max = curr_pos; //distance covered to reach max velocity.
	}
	float dist_remain = position - curr_pos;
	//std::cout << "Remaining distance: " << dist_remain << std::endl;
	//std::cout << "Max v reached at pos: " << p_v_max << std::endl;
	if (dist_remain <= p_v_max) //deaccelerate if remaining distance is the same as it took to reach max velocity.
	{
		//std::cout << "Remaining distance: " << dist_remain << std::endl;
		//std::cout << "v_max distance    : " << p_v_max << std::endl;
		//std::cout << "Current distance  : " << curr_pos << std::endl;
		//std::cout << "Current a         : " << curr_a << std::endl;
		std::cout << "Current v : " << curr_v << std::endl;
		//if (curr_a > 0) curr_a -= a_inc;
		curr_v -= (a_max * time);
	}
	else
	{   //Start of movement towards target
		//if (curr_a < a_max) curr_a += a_inc; //increase acceleration
		if (curr_v < v_max) curr_v += a_max * time;//increase velocity
	}
	curr_pos += (curr_v * time); //new position
	/*
	if (curr_v < 0)
	{
		return curr_pos = position;
	}
	*/
	return curr_pos;
	
}

float S_curve_controller::get_current_pos()
{
	return curr_pos;
}
