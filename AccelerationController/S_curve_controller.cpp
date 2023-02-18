#include "S_curve_controller.h"
#include <iostream>

S_curve_controller::S_curve_controller(const float v_max, const float a_max) : v_max(v_max)
                                                                              ,a_max(a_max)
																			  ,time_passed(0)
																			  ,curr_pos(0)
																			  ,p_acc(0)
																			  ,t_acc(v_max/a_max)
																			  ,t_lin(0)
																			  ,p_lin(0)
																			  ,is_done(false)
{}

S_curve_controller::~S_curve_controller() {}

float S_curve_controller::interpolate(float position, float time)
{
	//Save time and distance variables of first phase. Should only be set once therefore if not zero it must have been set.
	if (p_acc == 0) p_acc = get_p_acc(t_acc);
	if (p_lin == 0) p_lin = position - (2 * p_acc);
	if (t_lin == 0) t_lin = p_lin/v_max;
	float prev_pos = curr_pos;
	if(time_passed < t_acc) //In acceleration phase
	{
		//if( distance covered is less than half) { deccelerate }
		curr_pos = get_p_acc(time_passed);
	}
	else if (time_passed >= t_acc && time_passed <= (t_acc + t_lin)) //In linear phase
	{
		std::cout << "Linear phase!" << std::endl;
		curr_pos = get_p_lin(time_passed); //linear coordinate, will change in next 'if' if in decelerating phase
	}
	else //if none of the above we must be in deceleration phase
	{
		std::cout << "Decelerating phase!" << std::endl;
		curr_pos = get_p_decc(position, time_passed);

		float next_pos = get_p_decc(position, time_passed + time); //Look ahead to determine if max has been reached.
		if (next_pos < curr_pos)
		{
			std::cout << "Next_coord: " << next_pos << std::endl;
			is_done = true;
		}
	}

	time_passed += time;
	return curr_pos;
	
}

float S_curve_controller::done()
{
	return is_done;
}

float S_curve_controller::get_p_acc(float time)
{
	return 0.5 * a_max * (time * time);
}

float S_curve_controller::get_p_lin(float time)
{
	float b = get_p_acc(t_acc) - v_max * t_acc;
	return v_max * (time) + b; 
}

float S_curve_controller::get_p_decc(float target, float time)
{
	float t_new = time - get_t_total();
	return -0.5 * a_max * (t_new * t_new) + target;
}

float S_curve_controller::get_t_total()
{
	return (2 * t_acc) + t_lin; //fase3 is estimated to take the same time as fase1.
}