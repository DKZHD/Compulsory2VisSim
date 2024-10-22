#include "pch.h"
#include "Camera.h"

void Camera::UpdateCamPos(glm::vec3 pos)
{
	camPos += pos;
}

glm::vec3& Camera::getCamFwd()
{
	return camFwd;
}

glm::mat4 Camera::getProjMat()
{
	return glm::perspective(glm::radians(60.f), 16.f / 9.f, 0.01f, 10000.f);
}

glm::mat4 Camera::getViewMat()
{
	return glm::lookAt(camPos,camPos+camFwd,camUp);
}

void Camera::UpdateMats(uint32_t program)
{
	glm::mat4 combined = glm::mat4(1.f) * getProjMat() * getViewMat();
	glUniformMatrix4fv(glGetUniformLocation(program, "CamMatrix"), 1, GL_FALSE, &combined[0][0]);
}
