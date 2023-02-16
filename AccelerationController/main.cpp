#include <iostream>
#include "S_curve_controller.h"
#include <fstream>


int main()
{
	//S_curve_controller scc(1.5, 0.2);
	//float target_pos = 14.0f;
	S_curve_controller scc(1.0f, 0.1f);
	float target_pos = 20.0f;

	std::ofstream file("C:/Users/Skrum/OneDrive/Desktop/S_curve_data.txt");
	while(scc.get_current_pos() < target_pos)
	{
		float pos = scc.interpolate(target_pos, 0.10);
		//float pos = scc.interpolate(target_pos, 0.2);
		std::cout << pos << std::endl;
		file << pos << "\n";
	}
	file.close();

}