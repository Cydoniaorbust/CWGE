#include "Camera.h"

Camera::Camera() :
	UpWorld(glm::vec3(0, 1, 0)), Front(0), Up(0), Right(0),
	MovementSpeed(3.0f), MouseSensitivity(0.25f), Zoom(45.0f),
	Position(0), Yaw(-90.0f), Pitch(0) {}
Camera::Camera(glm::vec3 position) : Camera() {
	Position = position;

	UpdateCameraVectors();
}
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera() {
	Position = position;
	UpWorld = up;
	Yaw = yaw;
	Pitch = pitch;

	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
	return lookAt(Position, Position + Front, Up);
}
glm::vec3 Camera::GetFront() const {
	return Front;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)	Position += Front * velocity;
	if (direction == BACKWARD)	Position -= Front * velocity;
	if (direction == LEFT)	Position -= Right * velocity;
	if (direction == RIGHT)	Position += Right * velocity;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	UpdateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset) {
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
void Camera::UpdateCameraVectors() {
	//Front + Right + Up
	glm::vec3 front;

	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Front = normalize(front);
	Right = normalize(cross(Front, UpWorld));
	Up = normalize(cross(Right, Front));
}