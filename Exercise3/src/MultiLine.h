#ifndef MULTILINE_H
#define MULTILINE_H

#include "Shape.h"

namespace cgCourse
{
	class MultiLine : public Shape
	{
	public:
		MultiLine(	const std::vector<glm::vec3> & _vertices,
					const std::vector<glm::vec3> & _normals);

		void draw() const override;
	};
}

#endif // MULTILINE_H

