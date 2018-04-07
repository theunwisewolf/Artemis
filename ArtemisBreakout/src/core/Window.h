#pragma once

#include <string>
#include <chrono>
#include <thread>

#define NOGDI
#define WIN32_MEAN_AND_LEAN

#include <direct.h>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/core/Common.h>

#define MAX_KEYS 1024

// Standard XBox 360 Controller
#define JOYSTICK_BUTTON_A 0
#define JOYSTICK_BUTTON_B 1
#define JOYSTICK_BUTTON_X 2
#define JOYSTICK_BUTTON_Y 3

#define JOYSTICK_BUTTON_RB 4
#define JOYSTICK_BUTTON_LB 5

#define JOYSTICK_BUTTON_BACK 6
#define JOYSTICK_BUTTON_START 7

#define JOYSTICK_BUTTON_LEFT_STICK_CLICK 8
#define JOYSTICK_BUTTON_RIGHT_STICK_CLICK 9

#define JOYSTICK_BUTTON_UP 10
#define JOYSTICK_BUTTON_RIGHT 11
#define JOYSTICK_BUTTON_BOTTOM 12
#define JOYSTICK_BUTTON_LEFT 13

#define JOYSTICK_LEFT_AXIS 0
#define JOYSTICK_RIGHT_AXIS 1

//#define INPUT_DEBUG

class Window
{
public:
	uint16_t m_KeysDown[MAX_KEYS];
	uint16_t m_KeysPressed[MAX_KEYS];
	bool m_JoystickButtonsPressed[16] = { false };

	float m_JoystickAxes[10] = { 0.0f };

	enum class MouseButtons { BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE };
	MouseButtons m_MouseButtons;

	static int m_JoystickId;

private:
	std::chrono::high_resolution_clock::time_point m_StartTime;

	uint32_t m_FPS;
	
	int m_Height;
	int m_Width;
	std::string m_Title;

	GLFWwindow* m_Window;

	int mouseX;
	int mouseY;

	std::string m_ExecutablePath;

public:
	Window(int width, int height, std::string title);

	static void setSize(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int actions, int mods);
	static void mouseMoveCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void joystickConfigCallback(int joy, int event);

	void Title(const std::string& title) const;

	int Height()				 const { return m_Height; }
	int Width()					 const { return m_Width; }
	std::string Title()			 const { return m_Title; }
	std::string ExecutablePath() const { return m_ExecutablePath; }

	bool IsKeyPressed(uint16_t keycode);
	bool IsKeyDown(uint16_t keycode);
	bool IsKeyReleased(uint16_t keycode);
	bool IsJoystickButtonPressed(uint8_t button);
	bool IsLeftStickMoved(uint8_t axis);

	void Update();
	void Close();

	bool ShouldClose() const;

	~Window();
};