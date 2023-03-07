#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Triangle.h"
#include <algorithm>

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int argc, char *argv[]) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }

    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Mathimate", NULL, NULL);
    if (window == NULL) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        glfwTerminate();
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ShaderProgram shaderProgram;
    shaderProgram.loadShadersFromFile("vertex.shader", "fragment.shader");

    float color[] = { 0.0f, 1.0f, 0.0f };
    float startPosition[] = { -0.8f, 0.5f, 0.0f };
    float endPosition[] = { 0.8f, -0.5f, 0.0f };
    Triangle triangle(shaderProgram, color, startPosition, endPosition);

    ImVec2 scenePlaybackWindowSize(640, 360);

    GLuint fbo, framebufferColorTexture;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &framebufferColorTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferColorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scenePlaybackWindowSize.x, scenePlaybackWindowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferColorTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int frame = 0;
    int totalFrames = 59;
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, scenePlaybackWindowSize.x, scenePlaybackWindowSize.y);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        triangle.renderFrame(frame, totalFrames);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Frame Control");
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Frame");
        ImGui::PushButtonRepeat(true);
        ImGui::SameLine();
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
            frame = std::max(0, frame - 1);
        }
        ImGui::SameLine();
        ImGui::Text("%6d", frame);
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
            frame = std::min(frame + 1, totalFrames);
        }
        ImGui::PopButtonRepeat();
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(
            scenePlaybackWindowSize.x,
            scenePlaybackWindowSize.y + ImGui::GetFrameHeight()
        ));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Scene Playback");
        ImGui::Image(
            (void*)(uintptr_t)framebufferColorTexture,
            scenePlaybackWindowSize,
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
        ImGui::End();
        ImGui::PopStyleVar();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glDeleteFramebuffers(1, &fbo);
    shaderProgram.cleanup();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
