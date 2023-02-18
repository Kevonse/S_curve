#include <iostream>
#include "S_curve_controller.h"
#include <fstream>


int main()
{
	//S_curve_controller scc(1.8f, 0.23f);
	//float target_pos = 20.0f;

	S_curve_controller scc(2.34f, 0.43f);
	float target_pos = 23.56f;

	std::ofstream file("C:/Users/Skrum/OneDrive/Desktop/S_curve_data.txt");
	while(!scc.done())
	{
		float pos = scc.interpolate(target_pos, 1.0);
		std::cout << pos << std::endl;
		file << pos << "\n";
	}
	file.close();

}