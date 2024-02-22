// TriangleSolver.h
#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// constexpr functions can be defined in the header because they are implicitly inline
constexpr float DegToRad(float degrees) {
    return degrees * M_PI / 180.0f;
}

constexpr float RadToDeg(float radians) {
    return radians * 180.0f / M_PI;
}

void SolveSAS(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC);

void SolveASA(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC);

void SolveAAS(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC);