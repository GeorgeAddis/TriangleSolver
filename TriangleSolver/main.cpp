#include <glew.h>
#include <glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

// Assuming TriangleSolver.h defines SolveSAS, SolveASA, SolveAAS
#include "TriangleSolver.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLuint LoadTextureFromFile(const char* filename);

int main(int, char**) {
    // Initialize all parameters to 0 to show 0s initially
    float sideA = 0.0f, sideB = 0.0f, sideC = 0.0f;
    float angleA = 0.0f, angleB = 0.0f, angleC = 0.0f;
    bool showReset = false; // To control triangle rendering
    std::string statusMessage = ""; // Variable to hold status messages

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Triangle Solver", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Load triangle texture
    GLuint triangleTexture = LoadTextureFromFile("Resources/abc_triangle.png");



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Calculate the size for the image to be 1/3 of the screen width
        ImVec2 imageSize = ImVec2(ImGui::GetIO().DisplaySize.x / 3, ImGui::GetIO().DisplaySize.y / 3);

        // Calculate the position to center the image on the screen
        ImVec2 imagePos = ImVec2((ImGui::GetIO().DisplaySize.x - imageSize.x) / 2,
            (ImGui::GetIO().DisplaySize.y - imageSize.y) / 1.5);

        // Set next window position and size to match the image size and position
        ImGui::SetNextWindowPos(imagePos);
        ImGui::SetNextWindowSize(imageSize);

        // Create a window without borders, title bar, etc., just to hold the image
        ImGui::Begin("ImageBackground", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

        // Draw the image within this window
        ImGui::Image((void*)(intptr_t)triangleTexture, imageSize);

        // End the window
        ImGui::End();

        // Calculate a suitable window size
        float windowWidth = 400; 
        float windowHeight = 285; 

        // Before the main GUI window
        ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));

        // Main GUI window
        ImGui::Begin("Triangle Solver");

        // Explanation text
        ImGui::Text("Enter values for two sides and the included angle (SAS),\n"
            "two angles and the side between them (ASA),\n"
            "or two angles and a non-included side (AAS).");
        ImGui::Text("");

        // Inputs for all sides and angles
        ImGui::InputFloat("Side a", &sideA, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Side b", &sideB, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Side c", &sideC, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Angle A (degrees)", &angleA, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Angle B (degrees)", &angleB, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Angle C (degrees)", &angleC, 0.0f, 0.0f, "%.2f");

        std::string buttonText = showReset ? "Reset" : "Calculate";

        // Display the status message if it's not empty
        if (!statusMessage.empty()) {
            ImGui::Text("%s", statusMessage.c_str());
        }

        if (ImGui::Button(buttonText.c_str())) {
            if (!showReset) {
                // Perform calculation based on the input (SAS, ASA, AAS)
                try {
                    // Check for SAS combinations
                    if ((sideA > 0 && sideC > 0 && angleB > 0) || // Side a, Angle B, Side c
                        (sideB > 0 && sideA > 0 && angleC > 0) || // Side b, Angle C, Side a
                        (sideC > 0 && sideB > 0 && angleA > 0)) {  // Side c, Angle A, Side b

                        SolveSAS(sideA, sideB, sideC, angleA, angleB, angleC);
                        showReset = true;
                        statusMessage = "";
                    }
                    // Check for ASA combination
                    else if ((angleA > 0 && sideB > 0 && angleC > 0) || 
                        (angleB > 0 && sideC > 0 && angleA > 0) || 
                        (angleC > 0 && sideA > 0 && angleB > 0)) {
                        SolveASA(sideA, sideB, sideC, angleA, angleB, angleC);
                        showReset = true;
                        statusMessage = "";
                    }
                    // Check for AAS combination
                    else if ((angleA > 0 && angleB > 0 && (sideA > 0 || sideB > 0 || sideC > 0)) ||
                        (angleB > 0 && angleC > 0 && (sideA > 0 || sideB > 0 || sideC > 0)) ||
                        (angleC > 0 && angleA > 0 && (sideA > 0 || sideB > 0 || sideC > 0))) {

                        SolveAAS(sideA, sideB, sideC, angleA, angleB, angleC);
                        showReset = true;
                        statusMessage = "";
                    }
                    else {
                        statusMessage = "Invalid combination or insufficient data.\nValid combinations are SAS, ASA, AAS.";
                        showReset = false;
                    }
                }
                catch (const std::exception& e) {
                    statusMessage = "Error: " + std::string(e.what());
                    showReset = false;
                }

            }
            else {
                // Reset all inputs and flags
                sideA = sideB = sideC = angleA = angleB = angleC = 0.0f;
                showReset = false;
            }
        }
        ImGui::End();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteTextures(1, &triangleTexture);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


GLuint LoadTextureFromFile(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL) {
        std::cerr << "Error loading image: " << filename << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);

    return textureID;
}