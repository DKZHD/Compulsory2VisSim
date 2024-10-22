#pragma once

class Math
{
public:
	static glm::vec3 CalculateBSplineSurfacePoint(const std::vector<std::vector<glm::vec3>>& controlPoints, const std::vector<float>& knotVectorU, const std::vector<float>& knotVectorV, float u, float v, int degreeU, int degreeV);
	static std::vector<float> CalculateKnotVector(int amount_p, int degree);
	static std::vector<glm::vec3> CalculateSurface(int samples, const std::vector<std::vector<glm::vec3>>& controlPoints);
	static float BasisFunction(int k, const std::vector<float>& knots, int i, float t);
};

