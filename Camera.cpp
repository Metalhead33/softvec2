#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
// #include "../audio/AL/OpenALWrapper.hpp"

const float Camera::YAW =-90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.05f;
const float Camera::ZOOM = 45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: MovementSpeed(SPEED),
	  MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
float Camera::getZoom()
{
	return Zoom;
}
Camera::Camera(float posX, float posY, float posZ, float upX,
	   float upY, float upZ, float yaw, float pitch)
	: MovementSpeed(SPEED),
	  MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Front = glm::vec3(0.0f, 0.0f, 1.0f);
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, float W, float H, bool constrainPitch)
{
	// yoffset *= -1.00f;
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw   += xoffset / W;
	Pitch += yoffset / H;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}
void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	//updateCameraVectors();
	// alListener3f(AL_POSITION,Position.x,Position.y,Position.z);
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
float Camera::getYaw() const
{
	return Yaw;
}

void Camera::setYaw(float value)
{
	Yaw = value;
}

float Camera::getPitch() const
{
	return Pitch;
}

void Camera::setPitch(float value)
{
	Pitch = value;
}

float Camera::getMovementSpeed() const
{
	return MovementSpeed;
}

void Camera::setMovementSpeed(float value)
{
	MovementSpeed = value;
}

float Camera::getMouseSensitivity() const
{
	return MouseSensitivity;
}

void Camera::setMouseSensitivity(float value)
{
	MouseSensitivity = value;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cosf(glm::radians(Yaw)) * cosf(glm::radians(Pitch));
	front.y = sinf(glm::radians(Pitch));
	front.z = sinf(glm::radians(Yaw)) * cosf(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = glm::normalize(glm::cross(Right, Front));
	// alListenerfv(AL_ORIENTATION,reinterpret_cast<const ALfloat*>(&alRelevant));
}
