#include "Window.h"

int Window::m_JoystickId = -1;

Window::Window(int width, int height, std::string title) : 
	m_Width(width),
	m_Height(height),
	m_Title(title),
	m_Window(nullptr),
	m_StartTime(std::chrono::high_resolution_clock::now()),
	m_FPS(0)
{
	m_ExecutablePath.resize(MAX_PATH);

	// Change the current path to executable path
	if (GetModuleFileName(NULL, &m_ExecutablePath[0], MAX_PATH)) {
		auto found = m_ExecutablePath.find_last_of('\\');
		m_ExecutablePath = m_ExecutablePath.substr(0, found);

		_chdir(m_ExecutablePath.c_str());
	}

	if (!glfwInit())
	{
		LOG_ERROR("Failed to initialize the required dependencies.");
		return;
	}

	const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = videoMode->width;
	height = videoMode->height;

	glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!m_Window)
	{
		LOG_ERROR("Failed to create window.");
		return;
	}

	memset(this->m_KeysPressed, 0, MAX_KEYS);
	memset(this->m_KeysDown, 0, MAX_KEYS);

	// Set the window user pointer to this for easier retreival from other functions
	glfwSetWindowUserPointer(m_Window, this);

	// Set the glfw Event Handlers
	glfwSetFramebufferSizeCallback(m_Window, &Window::setSize);
	glfwSetKeyCallback(m_Window, &Window::keyCallback);
	glfwSetCursorPosCallback(m_Window, &Window::mouseMoveCallback);
	glfwSetMouseButtonCallback(m_Window, &Window::mouseButtonCallback);
	glfwSetJoystickCallback(&Window::joystickConfigCallback);

	// Center the window on the screen
	glfwSetWindowPos(m_Window, videoMode->width / 2 - width / 2, videoMode->height / 2 - height / 2);

	// Initialize the opengl context
	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		LOG_ERROR("Failed to initialize GLEW");
		return;
	}

	// Set the opengl viewport
	glViewport(0, 0, width, height);

	// Enable Alpha Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	if (Window::m_JoystickId != -1 || glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		int count;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

		int axescount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axescount);

		for (int i = 0; i < count; i++)
		{
			if (buttons[i] == GLFW_PRESS)
			{
				m_JoystickButtonsPressed[i] = true;
			}
			else if (buttons[i] == GLFW_RELEASE)
			{
				m_JoystickButtonsPressed[i] = false;
			}
		}

		for (int i = 0; i < axescount; i++)
		{
			m_JoystickAxes[i] = axes[i];
		}
	}

	// FPS Counter
	auto current = std::chrono::high_resolution_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(current - m_StartTime).count() >= 1)
	{
		this->Title(this->m_Title + " (FPS: " + std::to_string(this->m_FPS) + ")");
		m_StartTime = current;
		m_FPS = 0;
	}

	m_FPS++;
}

void Window::setSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::mouseMoveCallback(GLFWwindow* window, double x, double y)
{
	Window* windowClass = (Window*)glfwGetWindowUserPointer(window);

	windowClass->mouseX = x;
	windowClass->mouseY = y;
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* windowClass = (Window*)glfwGetWindowUserPointer(window);

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		windowClass->m_MouseButtons = MouseButtons::BUTTON_LEFT;
	}
	else if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		windowClass->m_MouseButtons = MouseButtons::BUTTON_RIGHT;
	}
}

void Window::joystickConfigCallback(int joy, int event)
{
	if (event == GLFW_CONNECTED)
	{
		Window::m_JoystickId = joy;
		std::cout << glfwGetJoystickName(joy) << " with ID " << joy << " was connected." << std::endl;
	}
	else if (event == GLFW_DISCONNECTED)
	{
		Window::m_JoystickId = -1;
		std::cout << glfwGetJoystickName(joy) << " with ID " << joy << " was disconnected." << std::endl;
	}
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* windowClass = (Window*)glfwGetWindowUserPointer(window);

	if (action == GLFW_PRESS)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was pressed." << std::endl;
#endif
		windowClass->m_KeysPressed[key] = 1;
		windowClass->m_KeysDown[key] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was released." << std::endl;
#endif
		// Release both key states
		windowClass->m_KeysDown[key] = 0;
		windowClass->m_KeysPressed[key] = 0;
	}
	else if(action == GLFW_REPEAT)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was repeatedly pressed." << std::endl;
#endif
		// If the key is pressed, unset it
		if (windowClass->m_KeysPressed[key])
		{
			//windowClass->m_KeysPressed[key] = 0;
		}

		windowClass->m_KeysPressed[key] = 1;
		windowClass->m_KeysDown[key] = 1;
	}
}

bool Window::IsKeyPressed(uint16_t keycode)
{
	if (this->m_KeysPressed[keycode] == 1)
	{
		// unset the key
		this->m_KeysPressed[keycode] = 0;
		return true;
	}

	return false;
}

bool Window::IsKeyDown(uint16_t keycode)
{
	return this->m_KeysDown[keycode] == 1;
}

bool Window::IsKeyReleased(uint16_t keycode)
{
	return this->m_KeysDown[keycode] == 0;
}

bool Window::IsJoystickButtonPressed(uint8_t button)
{
	return this->m_JoystickButtonsPressed[button];
}

void Window::Title(const std::string& title) const
{
	glfwSetWindowTitle(this->m_Window, title.c_str());
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

bool Window::IsLeftStickMoved(uint8_t axis)
{
	if (m_JoystickAxes[axis] == 0.0f)
		return false;

	if (axis == JOYSTICK_LEFT_AXIS)
	{
		return this->m_JoystickAxes[JOYSTICK_LEFT_AXIS] < this->m_JoystickAxes[JOYSTICK_RIGHT_AXIS];
	}
	else if (axis == JOYSTICK_RIGHT_AXIS)
	{
		return this->m_JoystickAxes[JOYSTICK_LEFT_AXIS] > this->m_JoystickAxes[JOYSTICK_RIGHT_AXIS];
	}

	return false;
}

void Window::Close()
{
	glfwDestroyWindow(m_Window);
	m_Window = nullptr;
}

Window::~Window()
{
	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

	glfwTerminate();
}