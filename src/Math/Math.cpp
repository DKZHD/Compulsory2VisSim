#include "pch.h"
#include "Math.h"

// Helper function to calculate a B-Spline point given control points in 2D grid
glm::vec3 Math::CalculateBSplineSurfacePoint(const std::vector<std::vector<glm::vec3>>& controlPoints, 
                                             const std::vector<float>& knotVectorU, 
                                             const std::vector<float>& knotVectorV, 
                                             float u, float v, int degreeU, int degreeV) 
{
    int numControlPointsU = controlPoints.size();    // Number of control points in U direction
    int numControlPointsV = controlPoints[0].size(); // Number of control points in V direction
 
    glm::vec3 surfacePoint(0.0f);

    // Loop over all control points in the grid and accumulate the weighted sum
    for (int i = 0; i < numControlPointsU; ++i) {
        for (int j = 0; j < numControlPointsV; ++j) {
            // Calculate the basis function value in both U and V directions
            float basisU = BasisFunction(degreeU, knotVectorU, i, u);
            float basisV = BasisFunction(degreeV, knotVectorV, j, v);

            // Combine the control point with the basis functions
            surfacePoint += basisU * basisV * controlPoints[i][j];
        }
    }

    return surfacePoint;
}

std::vector<float> Math::CalculateKnotVector(int numControlPoints, int degree)
{
    int totalKnots = numControlPoints + degree + 1;
    std::vector<float> knotVector;
	knotVector.reserve(totalKnots);

    for (int i = 0; i <= degree; ++i) {
        knotVector.emplace_back(0.f);
    }
    for (int i = degree + 1; i < numControlPoints; ++i) {
        knotVector.emplace_back(static_cast<float>(i - degree) / (numControlPoints - degree));
    }
    for (int i = numControlPoints; i < totalKnots; ++i) {
        knotVector.emplace_back(1.f);
    }

    return knotVector;
}

std::vector<glm::vec3> Math::CalculateSurface(int samples, const std::vector<std::vector<glm::vec3>>& controlPoints) 
{
    int numControlPointsU = controlPoints.size();    // Number of control points in U direction
    int numControlPointsV = controlPoints[0].size(); // Number of control points in V direction
    
    // Knot vectors for U and V directions
    std::vector<float> knotVectorU = CalculateKnotVector(numControlPointsU, 2);
    std::vector<float> knotVectorV = CalculateKnotVector(numControlPointsV, 2);

    // Prepare container for the resulting surface points
    std::vector<glm::vec3> surfacePoints;

    // Loop through all samples in the U and V directions
    for (int i = 0; i < samples; ++i) {
        float u = static_cast<float>(i) / (samples - 1);  // Parameter in U direction

        for (int j = 0; j < samples-1; ++j) {
            float v = static_cast<float>(j) / (samples - 1);  // Parameter in V direction
            
            // Calculate a point on the surface for the current (u, v)
            glm::vec3 surfacePoint = CalculateBSplineSurfacePoint(controlPoints, knotVectorU, knotVectorV, u, v, 2, 2);
            surfacePoints.push_back(surfacePoint);
        }
    }

    return surfacePoints;
}

float Math::BasisFunction(int k, const std::vector<float>& knots, int i, float t) 
{
    if (k == 0) {
        return (t >= knots[i] && t < knots[i + 1]) ? 1.0f : 0.0f;
    }

    float leftWeight = 0.0f;
    if (knots[i + k] - knots[i] != 0.0f) {
        leftWeight = (t - knots[i]) / (knots[i + k] - knots[i]);
    }
    float leftBasis = leftWeight * BasisFunction(k - 1, knots, i, t);

    float rightWeight = 0.0f;
    if (knots[i + k + 1] - knots[i + 1] != 0.0f) {
        rightWeight = (knots[i + k + 1] - t) / (knots[i + k + 1] - knots[i + 1]);
    }
    float rightBasis = rightWeight * BasisFunction(k - 1, knots, i + 1, t);

    return leftBasis + rightBasis;
}
