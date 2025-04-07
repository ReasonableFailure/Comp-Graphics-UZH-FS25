#include "GLExercise.h"

#include "Cube.h"

#include <iostream>

namespace cgCourse
{
	GLExercise::GLExercise(const glm::uvec2 & windowSize, const std::string & title, const unsigned int toruses): GLApp(windowSize, title, false)
	{
		// normalsTorus = MultiLine(torus.positions, torus.normals);
		no_tori = toruses;
	}
	
	bool GLExercise::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
		glm::vec3(3, 3, -3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
	
		
		programForShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Shape");
		programForTorusNormals = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");
		programForUnitCube = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/UnitCube");

		animationSteps = 300;

		// Init models VAO
		if(!cube.createVertexArray(0, 1, 2))
			return false;
		cube.setScaling(glm::vec3(scaleFactor,scaleFactor,scaleFactor));

		if (!unitCube.createVertexArray(0, 1, 2)) 
			return false;
		// std::cout<<no_tori <<std::endl
		for(unsigned i = 0 ; i < no_tori; ++i){
			auto torus = std::make_unique<Torus>();
			if(!torus->createVertexArray(0,1,2)) return false;
			
			relativeAngle = 2*M_PI/no_tori;
			torus->setPosition(glm::vec3(
				cos(-relativeAngle*i)*scaleFactor*3.0,
				0,
				sin(-relativeAngle*i)*scaleFactor*3.0
				)
			);
			torus->setScaling(glm::vec3(scaleFactor*0.3,scaleFactor*0.3,scaleFactor*0.3));
			auto normalsTorus = std::make_unique<MultiLine>(torus->positions,torus->normals);
			if(!normalsTorus->createVertexArray(0,1,2)) return false;
			tori.push_back(std::move(torus));
			normalsTori.push_back(std::move(normalsTorus));			
		}

		return true;
	}

	bool GLExercise::update()
	{
		// TODO: implement the animation of the cube and toruses
		if(!animation) return true;
		float minSize = 0.4;
		float maxSize = 2.0;
		float rotationAngle = animationTicks * 2 * M_PI/animationSteps;
		float scaleStep = 1.0/animationSteps;
		
		cube.setRotation(rotationAngle,glm::vec3(0,1,0));
		if(maxSize <= scaleFactor+scaleStep){ //next step would be too large ->  decrease instead
			growing = -1;
		}else if(minSize >= scaleFactor-scaleStep){ //next step would be too small -> increase instead
			growing = 1;
		} else {
			growing = growing;
		}
		// std::cout<<growing<<std::endl;
		scaleFactor += growing*scaleStep;
		cube.setScaling(glm::vec3(scaleFactor,scaleFactor,scaleFactor));
		for(unsigned int i = 0; i < no_tori; ++i){
			auto &torus = tori[i];
			torus->setRotation(rotationAngle*1.5,glm::vec3(0,0,1));
			torus->setPosition(glm::vec3(
					scaleFactor*3*cos(-(relativeAngle*i+rotationAngle)),
					0,
					scaleFactor*3*sin(-(relativeAngle*i+rotationAngle))
				)
			);
			torus->setScaling(glm::vec3(scaleFactor*0.7,scaleFactor*0.7,scaleFactor*0.7));
		}

		return true;
	}

	bool GLExercise::render()
	{
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		++animationTicks;
		update();

		glProgramUniform1i(*programForTorusNormals, programForTorusNormals->getUniformLocation("useNormalMatrix"), useNormalMatrix);
		glProgramUniform1i(*programForShape, programForShape->getUniformLocation("useNormalMatrix"), useNormalMatrix);
		glProgramUniform1i(*programForShape, programForShape->getUniformLocation("normalsAsColor"), normalsAsColor);

		renderCubes();
		renderTorus();
		if (drawUnitCube)
			renderUnitCube();

		return true;
	}

	void GLExercise::renderCubes()
	{
		programForShape->bind();

		mvpMatrix = cam.getViewProjectionMatrix() * cube.modelMatrix;
		// normalMatrix = TODO: compute the normal matrix
		normalMatrix = glm::mat3(glm::inverse(glm::transpose(cube.getModelMatrix())));
		glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		glUniformMatrix3fv(programForShape->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
		cube.draw();

		programForShape->unbind();
	}

	void GLExercise::renderUnitCube()
	{
		programForUnitCube->bind();
		mvpMatrix = cam.getViewProjectionMatrix() * unitCube.modelMatrix;
		glUniformMatrix4fv(programForUnitCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		unitCube.draw();
		programForUnitCube->unbind();
	}

	void GLExercise::renderTorus()
	{
		programForShape->bind();

		for(auto & torus: tori)
		{
			mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
			// normalMatrix = TODO: compute the normal matrix
			normalMatrix = glm::mat3(glm::inverse(glm::transpose(torus->getModelMatrix())));
			glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
			glUniformMatrix3fv(programForShape->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
			torus->draw();
		}

		programForShape->unbind();


		if(!drawTorusNormals) return;

		// TODO: draw the torus normals using the multiline object
		programForTorusNormals->bind();
		for(unsigned int  i = 0; i < no_tori; ++i)
		{	
			auto & torus = tori[i];
			auto & normalsTorus = normalsTori[i];
			mvpMatrix = cam.getViewProjectionMatrix()*torus->getModelMatrix();
			glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"),1,GL_FALSE,&mvpMatrix[0][0]);
			normalsTorus->draw();
		}
		programForTorusNormals->unbind();

	}

	bool GLExercise::end()
	{
		return true;
	}

	void GLExercise::imgui()
	{
		ImGui::SetNextWindowSize(ImVec2(200, -1));
		ImGui::Begin("status", nullptr, ImGuiWindowFlags_NoTitleBar);
		ImGui::Checkbox("drawTorusNormals", &drawTorusNormals);
		ImGui::Checkbox("drawUnitCube", &drawUnitCube);
		ImGui::Checkbox("useNormalMatrix", &useNormalMatrix);
		ImGui::Checkbox("normalsAsColor", &normalsAsColor);
		ImGui::Checkbox("animation", &animation);
		ImGui::End();
	}
}

