#include "GLExercise.h"

int main()
{
	unsigned int number;
	std::cout << "How many tori should spin?" << std::endl;
	std::cin >> number;
	cgCourse::GLExercise app(glm::uvec2(1200, 1000), "CG Exercise2 Solution", number);
	return app.run();
}

