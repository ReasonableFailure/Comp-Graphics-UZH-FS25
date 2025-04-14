#include "GLExample.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title): GLApp(_windowSize, _title, false) {}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
					glm::vec3(5, 5, -5),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
					);

		programForLightBox = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");
        programForShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Shape");
        programForNormal = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");

		// create box for light position
		lightbox = std::make_shared<Cube>();
		if(!lightbox->createVertexArray(0, 1, 2))
			return false;

		lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
		lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));

		// Init models

        // create textured cube
		cube = std::make_shared<Cube>();
		if(!cube->createVertexArray(0, 1, 2))
			return false;

        cube->setPosition(glm::vec3(-1.5, 0.5, 3.5));
        cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

        // create torus
		torus = std::make_shared<Torus>();
		if(!torus->createVertexArray(0, 1, 2))
			return false;

		torus->setPosition(glm::vec3(3.0, 0.0, 1));
		torus->setScaling(glm::vec3(1.5, 1.5, 1.5));

        // create torus knot
        torusKnot = std::make_shared<TorusKnot>();
        if(!torusKnot->createVertexArray(0, 1, 2))
            return false;
        torusKnot->setRotation(90.0, glm::vec3(1.0, 0.0, 0.0));
        torusKnot->setPosition(glm::vec3(-1.0, -1, -3.0));
        torusKnot->setScaling(glm::vec3(2.0, 2.0, 2.0));

		// Init multiline field for normals of objects
        normalsTorus = std::make_shared<MultiLine>(torus->positions,
                                                   torus->normals);
        if(!normalsTorus->createVertexArray(0, 1, 2))
            return false;

		normalsTorusKnot = std::make_shared<MultiLine>(torusKnot->positions,
                                                   torusKnot->normals);
		if(!normalsTorusKnot->createVertexArray(0, 1, 2))
			return false;
        
        SettingsStruct settings = {1,1,1,1};
        MaterialStruct material = {0.3f,0.8f,0.6f,10.0f};
        LightStruct light;
        light.lightPosition = glm::vec4(0.0f,0.0f,0.0f,1.0f);
        light.lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


		return true;
	}

	bool GLExample::update()
	{
        if (stopAnimation) return true;

		torusKnot->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if(animation > 4.0) {
                animationDir = Backward;
            } else {
                animation += 0.01;
            }
		}
		else
		{
			if(animation < -5.0) {
                animationDir = Forward;
            } else {
                animation -= 0.01;
            }
		}
        

        // TODO (Optional): Implement a toggleLightPosition variable that, when enabled,
        // overrides the animated light position with a fixed one (e.g., (3.0, 1.5, -1.0))
        // You can add a checkbox to the UI (ImGui) and use it to control this behavior.

		lightbox->setPosition(glm::vec3(animation, 1.5, -0.0));

		return true;
	}

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);

		// Clear the color and depth buffers
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		update();

		renderLightBox();

        addLightVariables(programForShape);

        if (drawCube) renderCube();
        if (drawTorus) renderTorus();
        if (drawTorusKnot) renderTorusKnot();

		return true;
	}

    /* TODO update this function to set the light information for the
	 * shaders. Don't forget that shader have to be bound before shader uniform can be set..
	 */
	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram> & program)
	{
        GLuint settingsBO, materialBO, lightBO, settingsLoc, materialsLoc,lightLoc;
        
        GLuint shaderProgram = program->bind();
        // load settings buffer
		glGenBuffers(1, &settingsBO);
        glBindBuffer(GL_UNIFORM_BUFFER, settingsBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(settings), &settings, GL_DYNAMIC_DRAW);
        
        // the next 2 lines connect the uniform name and bufferobject to the same index 0
        settingsLoc = glGetUniformBlockIndex(shaderProgram,"settingsBlock");
        glUniformBlockBinding(shaderProgram, settingsLoc, 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, settingsBO);

        // setup material buffer
        glGenBuffers(1, &materialBO);
        glBindBuffer(GL_UNIFORM_BUFFER, materialBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(material), &material, GL_DYNAMIC_DRAW);

        // the next 2 lines connect the uniform name and bufferobject to the same index 1
        materialsLoc = glGetUniformBlockIndex(shaderProgram,"materialBlock");
        glUniformBlockBinding(shaderProgram, materialsLoc, 1);
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, materialBO);

        // setup uniform light data buffers
        glGenBuffers(1, &lightBO);
        glBindBuffer(GL_UNIFORM_BUFFER, lightBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(light), &light, GL_DYNAMIC_DRAW);

        // the next 2 lines connect the uniform name and bufferobject to the same index 2
        lightLoc = glGetUniformBlockIndex(shaderProgram,"lightBlock");
        glUniformBlockBinding(shaderProgram, lightLoc, 2);
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, lightBO);

        program->unbind();
    }
    // END TODO

    void GLExample::renderCube() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        cube->draw();
        programForShape->unbind();
    }

    void GLExample::renderTorus() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        torus->draw();
        programForShape->unbind();

        if(drawTorusNormals) {
            programForNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
            glUniformMatrix4fv(programForNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorus->draw();
            programForNormal->unbind();
        }
    }

    void GLExample::renderTorusKnot() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * torusKnot->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torusKnot->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        torusKnot->draw();
        programForShape->unbind();

        if(drawTorusKnotNormals) {
            programForNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * torusKnot->getModelMatrix();
            glUniformMatrix4fv(programForNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorusKnot->draw();
            programForNormal->unbind();
        }
    }

	void GLExample::renderLightBox()
	{
		programForLightBox->bind();
		mvpMatrix = cam.getViewProjectionMatrix() * lightbox->getModelMatrix();
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1, &lightColor[0]);
		glUniformMatrix4fv(programForLightBox->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		lightbox->draw();
		programForLightBox->unbind();
	}

	bool GLExample::end()
	{
		programForShape->deleteShaderProgramFromGPU();
		programForNormal->deleteShaderProgramFromGPU();
        programForLightBox->deleteShaderProgramFromGPU();
        return true;
	}

    void GLExample::imgui()
    {
        bool open = true;
        ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

        // Light Color
        ImGui::ColorEdit3("Light Color", lightColor);
        ImGui::Checkbox("Pause Animation", &stopAnimation);
        ImGui::Separator();
        ImGui::RadioButton("Gouraud Shading", &renderMode, GOURAUD_SHADING);
        ImGui::RadioButton("Phong Shading", &renderMode, PHONG_SHADING);
        ImGui::Separator();
        ImGui::Checkbox("Render Cube", &drawCube);
        ImGui::Checkbox("Render Torus", &drawTorus);
        ImGui::Checkbox("Render Torus Knot", &drawTorusKnot);
        ImGui::Separator();
        ImGui::Checkbox("Render Torus Normals", &drawTorusNormals);
        ImGui::Checkbox("Render Torus Knot Normals", &drawTorusKnotNormals);
        ImGui::Separator();
        ImGui::Checkbox("Bonus Task", &bonusTask);
        ImGui::End();
    }
}

