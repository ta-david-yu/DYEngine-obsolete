#include "DYEngine/IApplication.h"
#include "DYEngine/Time.h"
#include "DYEngine/util/Logger.h"
#include "DYEngine/Resource.h"

#include "DYEngine/graphics/Mesh.h"
#include "DYEngine/graphics/Texture.h"
#include "DYEngine/graphics/Material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace DYE
{

	void IApplication::Run()
	{
		init();
		gameLoop();
		release();
	}

	void IApplication::init()
	{
		LogInfo("Init app");
		m_pCore = new GameCore(this);
		m_pCore->Init();

		initGL();

		m_IsRunning = true;
	}

	void IApplication::gameLoop()
	{
		LogInfo("Start game loop");
		// create scene, load scene function into each scene
		setupScenes();

		TIME->tickInit();

		// notice that the scene SceneID == 0 is always the first loaded scene
		SCENE_MGR->loadScene(0);

		// game loop
		{
			while (true)
			{
				SYSTEM_MGR->Awake();

				SYSTEM_MGR->Start();

				double fixedUpdateLag = 0.0f;

				int framesCounter = 0;
				double timeAccumulator = 0;

				do
				{
#ifdef DYE_DEBUG
					////// FPS //////
					framesCounter++;
					timeAccumulator += TIME->frameDuration();
					if (timeAccumulator > 1.0f)
					{
						double fps = framesCounter / timeAccumulator;
						LogDebug("FPS: %f  %f", fps, timeAccumulator);

						timeAccumulator = 0;
						framesCounter = 0;
					}
					////// FPS //////

					move_timer += TIME->DeltaTime();
					if (move_timer > move_max)
						move_timer = 0.0f;
#endif // DEBUG

					////// IN FRAME //////
					SYSTEM_MGR->EarlyUpdate();									// EarlyUpdate

					fixedUpdateLag += TIME->frameDuration();

					while (fixedUpdateLag >= TIME->UnScaled_FixedDeltaTime())
					{
						SYSTEM_MGR->FixedUpdate();								// FixedUpdate (and physics)
						fixedUpdateLag -= TIME->UnScaled_FixedDeltaTime();
					}

					SYSTEM_MGR->Update();										// Update
						
					SYSTEM_MGR->LateUpdate();									// LateUpdate

					SYSTEM_MGR->RegisterRenderer();								// Register Renderer to Graphics Engine

					render();													// Render

					////// END FRAME //////
					Base::DestructionUpdate();									// Delay Destruction for Base Object (Entity, Component...)

					TIME->tickUpdate();											// Update timer

					if (checkIfWindowClosed())
						m_IsRunning = false;

				} while (!SCENE_MGR->IsLoadingNextScene() && m_IsRunning );

				if (!m_IsRunning)
					break;

				if (SCENE_MGR->IsLoadingNextScene())
				{
					SCENE_MGR->LoadNextScene();
					onNextSceneLoaded();
				}
			}
		}
		// end of game loop
	}

	void IApplication::release()
	{
		releaseGL();
	}

	void IApplication::initGL()
	{
		LogInfo("Init GL");

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWmonitor* monitor = NULL;//glfwGetPrimaryMonitor();

		m_pWindow = glfwCreateWindow(640, 480, m_WindowName.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_pWindow);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
#ifdef DYE_DEBUG
		debugGLSetup();
#endif // DEBUG
	}

	void IApplication::releaseGL()
	{
		glfwDestroyWindow(m_pWindow);
	}

	bool IApplication::checkIfWindowClosed()
	{
		return glfwWindowShouldClose(m_pWindow) == 1;
	}

	void IApplication::render()
	{
		// TODO: Render (Camera Loop)

		glClearColor(1.0f, 0.3f, 0.7f, 1.0f);
#ifdef DYE_DEBUG
		glClearColor(1.0f, 0.3f, move_timer, 1.0f);
#endif // DEBUG

		glClear(GL_COLOR_BUFFER_BIT);

#ifdef DYE_DEBUG
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
								//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

#endif // DEBUG

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}

	void IApplication::onNextSceneLoaded()
	{
		LogInfo("Next scene loaded");
	}

	void IApplication::onRelease()
	{
		LogInfo("Shutting down application");
	}

	void IApplication::SetWindowName(std::string _name)
	{
		m_WindowName = _name;
	}

#ifdef DYE_DEBUG
	void IApplication::debugGLSetup()
	{
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		// build and compile our shader program
		// ------------------------------------
		// vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}
#endif // DEBUG

	IApplication::IApplication()
	{

	}

	IApplication::~IApplication()
	{

	}
}