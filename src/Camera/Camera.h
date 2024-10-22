#pragma once
class Camera
{
public:
	void UpdateCamPos(glm::vec3 pos);
	glm::vec3& getCamFwd();
	glm::mat4 getProjMat();
	glm::mat4 getViewMat();
	void UpdateMats(uint32_t program);
	float camSpeed = 0.05f;
private:
	glm::vec3 camPos = glm::vec3(0.f,0.f,3.f);
	glm::vec3 camUp = glm::vec3(0.f,1.f,0.f);
	glm::vec3 camFwd = glm::vec3(0.f,0.f,-1.f);
};

