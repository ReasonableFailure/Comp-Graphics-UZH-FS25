#include "MultiLine.h"

#include <iostream>
#include <cmath>

namespace cgCourse
{
	MultiLine::MultiLine(const std::vector<glm::vec3> & _vertices,
						 const std::vector<glm::vec3> & _normals
						 ) : Shape()
	{
		// TODO: initialize positions, colors, and normals
		for(unsigned int i = 0; i < _vertices.size(); ++i){
			const float offSet = 0.38757;
			positions.push_back(_vertices[i]);
			positions.push_back(_vertices[i] + offSet * _normals[i]);

			normals.push_back(_normals[i]);
			normals.push_back(_normals[i]);

			
		}
	}

	void MultiLine::draw() const
	{
		// TODO: complete the code to draw the normals as lines
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, posBufferID);
		glDrawArrays(GL_LINES,0, positions.size());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

