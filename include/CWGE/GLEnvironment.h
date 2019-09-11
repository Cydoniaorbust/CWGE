#pragma once

#include "External.h"

using Clock = std::chrono::high_resolution_clock;
using Date = std::chrono::time_point<Clock>;
using ms = std::chrono::milliseconds;

struct Tick {
	// Per second.
	static constexpr GLuint rate = 75.0;
	// Min N of ticks to "skip" before next update.
	Clock::duration step = std::chrono::duration_cast<Clock::duration>(std::chrono::duration<long, std::ratio <1, rate>> {1}); 
	// Max N of ticks before mandatory draw.
	static constexpr GLuint skip = 5;

	Clock::time_point last = Clock::now();
	GLuint count = 0;
	GLfloat time = 0.0f;
	GLfloat rateCheck = 0.0f;

	void ResetCount() {
		count = 0;
		time = 0.0f;
	}
	bool UpdatesNotTooFast() const {
		return (Clock::now() > last) && (count < skip);
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
	const char* what() const noexcept { return data; };
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
	GLdouble delta;
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