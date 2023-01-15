#include <iostream>
#include "S_curve_controller.h"
#include <fstream>


int main()
{
	std::cout << "Hello Michael!" << std::endl;
	S_curve_controller scc(0.5, 0.250);
	float target_pos = 1.0f;

	std::ofstream file("C:/Users/Skrum/OneDrive/Desktop/S_curve_data.txt");
	while(scc.get_current_pos() < target_pos)
	{
		//float pos = ac.interpolate(target_pos, 0.10);
		float pos = scc.interpolate(target_pos, 0.1);
		std::cout << pos << std::endl;
		file << pos << "\n";
	}
	file.close();

}