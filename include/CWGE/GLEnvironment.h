#pragma once

#include "External.h"

using Clock = std::chrono::high_resolution_clock;
using Date = std::chrono::time_point<Clock>;
using ms = std::chrono::milliseconds;

struct Tick {
	static constexpr GLuint rate = 75; // Per second.
	const GLuint step = 1000 / rate; // Min N of ticks to "skip" before next update.
	static constexpr GLuint skip = 5; // Max N of frames before mandatory draw.

	DWORD last = GetTickCount();
	GLuint count = 0;
	GLfloat time = 0.0f;
	GLfloat rateCheck = 0.0f;

	void ResetCount() {
		count = 0;
		time = 0.0f;
	}
	bool UpdatesNotTooFast() const {
		return (GetTickCount() > last) && (count < skip);
	}
	void MakeStep(GLfloat _delta) {
		last += step;
		count++;
		time += _delta;
		rateCheck++;
	}	
	void CheckReset() {
		rateCheck = 0.0f;
	}
};
struct Frame {
	const GLfloat updateFreq = 0.5f; // In seconds.

	GLfloat updateTime = 0.0f;
	GLfloat count = 0.0f;

	void MakeStep() {
		count++;
	}
	bool TimeToUpdate(GLfloat _delta) {
		updateTime += _delta;
		return updateTime >= updateFreq;
	}
	void ResetCount() {
		count = 0;
		updateTime -= updateFreq;
	}
};

class Error : public std::exception {
	const char* data;
public:
	Error(const char* _data) : data(_data) {};
	const char* GetData() { return data; };
};

class GLEnvironment {
private:
	GLFWwindow* win;

	GLfloat lastX;
	GLfloat lastY;

	Date timeLast;
	Date timeCurrent;

	Tick tick;
	Frame frame;
	
	GLfloat aspect;
public:
	GLfloat delta;
	bool drawHits;
	
	GLFWwindow* GetWin() const noexcept;
	
	GLfloat MouseX(double);
	GLfloat MouseY(double);
	
	GLfloat CountTPS();
	GLfloat CountFPS();

	void UpdateDelta();

	void InitWin(int, int, const char*);

	void CallbackFramebufferSize(GLFWframebuffersizefun);
	void CallbackKey(GLFWkeyfun);
	void CallbackMouseButton(GLFWmousebuttonfun);
	void CallbackCursorPos(GLFWcursorposfun);
	void CallbackScroll(GLFWscrollfun);

	void SetInputMode();

	void InitGLAD();
	void ApplyTests();
	void Swap();
	void Loop(
		std::function<void()>, 
		std::function<void(glm::vec3, glm::mat4, GLfloat, bool)>, 
		glm::vec3, 
		glm::mat4, 
		std::function<void()> = 0
	);

	GLEnvironment();
	~GLEnvironment();

	GLEnvironment(const GLEnvironment &) = delete;
	GLEnvironment& operator=(const GLEnvironment &) = delete;
	GLEnvironment(GLEnvironment &&) = delete;
	GLEnvironment& operator=(GLEnvironment &&) = delete;
};