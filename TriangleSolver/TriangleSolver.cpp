// TriangleSolver.cpp
#include "TriangleSolver.h"
#include <cmath>
#include <iostream>

void SolveSAS(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC) {
    std::cout << "Initial values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;

    float knownAngleRadians = 0.0f;
    if (angleA > 0) {
        knownAngleRadians = DegToRad(angleA);
        std::cout << "Known angle A in radians: " << knownAngleRadians << std::endl;

        sideA = std::sqrt(sideB * sideB + sideC * sideC - 2 * sideB * sideC * std::cos(knownAngleRadians));
        std::cout << "Calculated sideA using Law of Cosines: " << sideA << std::endl;

        angleB = RadToDeg(std::asin(sideB * std::sin(knownAngleRadians) / sideA));
        std::cout << "Calculated angleB using Law of Sines: " << angleB << std::endl;

        angleC = 180.0f - angleA - angleB;
        std::cout << "Calculated angleC by angle sum property: " << angleC << std::endl;
    }
    else if (angleB > 0) {
        knownAngleRadians = DegToRad(angleB);
        std::cout << "Known angle B in radians: " << knownAngleRadians << std::endl;

        // Calculate sideB using Law of Cosines
        sideB = std::sqrt(sideA * sideA + sideC * sideC - 2 * sideA * sideC * std::cos(knownAngleRadians));
        std::cout << "Calculated sideB using Law of Cosines: " << sideB << std::endl;

        // Calculate angleA using Law of Sines
        angleA = RadToDeg(std::asin(sideA * std::sin(knownAngleRadians) / sideB));
        std::cout << "Calculated angleA using Law of Sines: " << angleA << std::endl;

        // Calculate angleC by angle sum property
        angleC = 180.0f - angleA - angleB;
        std::cout << "Calculated angleC by angle sum property: " << angleC << std::endl;
    }
    else if (angleC > 0) {
        knownAngleRadians = DegToRad(angleC);
        std::cout << "Known angle C in radians: " << knownAngleRadians << std::endl;

        // Calculate sideC using Law of Cosines
        sideC = std::sqrt(sideA * sideA + sideB * sideB - 2 * sideA * sideB * std::cos(knownAngleRadians));
        std::cout << "Calculated sideC using Law of Cosines: " << sideC << std::endl;

        // Calculate angleB using Law of Sines
        angleB = RadToDeg(std::asin(sideB * std::sin(knownAngleRadians) / sideC));
        std::cout << "Calculated angleB using Law of Sines: " << angleB << std::endl;

        // Calculate angleA by angle sum property
        angleA = 180.0f - angleB - angleC;
        std::cout << "Calculated angleA by angle sum property: " << angleA << std::endl;
    }

    std::cout << "Calculated values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;
}


void SolveASA(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC) {
    std::cout << "Initial values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;

    // Convert angles from degrees to radians for trigonometric functions
    float angleARad = DegToRad(angleA);
    float angleBRad = DegToRad(angleB);
    float angleCRad = DegToRad(angleC);

    // Identify which side is known and calculate the others based on the known side and angles
    if (angleA > 0 && angleB > 0 && sideC > 0) { // Known: Angle A, Angle B, Side C
        std::cout << "Known configuration: Angle A, Angle B, Side C" << std::endl;
        angleC = 180.0f - angleA - angleB;
        float sideC_ratio = sideC / std::sin(DegToRad(angleC));
        sideA = std::sin(angleARad) * sideC_ratio;
        sideB = std::sin(angleBRad) * sideC_ratio;
    }
    else if (angleA > 0 && angleC > 0 && sideB > 0) { // Known: Angle A, Angle C, Side B
        std::cout << "Known configuration: Angle A, Angle C, Side B" << std::endl;
        angleB = 180.0f - angleA - angleC;
        float sideB_ratio = sideB / std::sin(DegToRad(angleB));
        sideA = std::sin(angleARad) * sideB_ratio;
        sideC = std::sin(angleCRad) * sideB_ratio;
    }
    else if (angleB > 0 && angleC > 0 && sideA > 0) { // Known: Angle B, Angle C, Side A
        std::cout << "Known configuration: Angle B, Angle C, Side A" << std::endl;
        angleA = 180.0f - angleB - angleC;
        float sideA_ratio = sideA / std::sin(DegToRad(angleA));
        sideB = std::sin(angleBRad) * sideA_ratio;
        sideC = std::sin(angleCRad) * sideA_ratio;
    }

    // Ensure all angles are recalculated to account for any rounding errors in calculations
    angleARad = DegToRad(angleA);
    angleBRad = DegToRad(angleB);
    angleCRad = DegToRad(angleC);

    // Recalculate sides to ensure consistency
    if (sideA == 0) sideA = std::sin(angleARad) * (sideB / std::sin(angleBRad));
    if (sideB == 0) sideB = std::sin(angleBRad) * (sideA / std::sin(angleARad));
    if (sideC == 0) sideC = std::sin(angleCRad) * (sideA / std::sin(angleARad));

    std::cout << "Calculated values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;
}

void SolveAAS(float& sideA, float& sideB, float& sideC, float& angleA, float& angleB, float& angleC) {
    std::cout << "Initial values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;

    // Find the missing angle
    if (angleA > 0 && angleB > 0) {
        angleC = 180.0f - angleA - angleB;
    }
    else if (angleA > 0 && angleC > 0) {
        angleB = 180.0f - angleA - angleC;
    }
    else if (angleB > 0 && angleC > 0) {
        angleA = 180.0f - angleB - angleC;
    }

    // Convert angles from degrees to radians for trigonometric functions
    float angleARad = DegToRad(angleA);
    float angleBRad = DegToRad(angleB);
    float angleCRad = DegToRad(angleC);

    // Law of Sines to find the unknown sides based on the known side
    if (sideA > 0) {
        float sideA_ratio = sideA / std::sin(angleARad);
        sideB = std::sin(angleBRad) * sideA_ratio;
        sideC = std::sin(angleCRad) * sideA_ratio;
    }
    else if (sideB > 0) {
        float sideB_ratio = sideB / std::sin(angleBRad);
        sideA = std::sin(angleARad) * sideB_ratio;
        sideC = std::sin(angleCRad) * sideB_ratio;
    }
    else if (sideC > 0) {
        float sideC_ratio = sideC / std::sin(angleCRad);
        sideA = std::sin(angleARad) * sideC_ratio;
        sideB = std::sin(angleBRad) * sideC_ratio;
    }

    std::cout << "Calculated values: sideA=" << sideA << ", sideB=" << sideB
        << ", sideC=" << sideC << ", angleA=" << angleA
        << ", angleB=" << angleB << ", angleC=" << angleC << std::endl;
}


