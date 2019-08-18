#pragma once

#include "External.h"

enum Camera_Movement { 
	FORWARD, BACKWARD, LEFT, RIGHT 
};

class Camera {
private:
	glm::vec3 UpWorld;

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	float MovementSpeed;
	float MouseSensitivity;

public:
	glm::vec3 Position;

	float Yaw;
	float Pitch;

	float Zoom;

	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetFront() const;

	void ProcessKeyboard(Camera_Movement, float);
	void ProcessMouseMovement(float, float);
	void ProcessMouseScroll(float);
	void UpdateCameraVectors();	

	Camera();
	~Camera() {};

	Camera(glm::vec3);
	Camera(glm::vec3, glm::vec3, float, float);
	
	Camera(const Camera &) = delete;
	Camera& operator=(const Camera &) = delete;

	Camera(Camera &&) = delete;
	Camera& operator=(Camera &&) = delete;	
};