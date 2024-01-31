//
// Created by Matej on 29/12/2023.
//

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "common.h"
#include "app.h"

using namespace minecraft;

void App::init_imgui() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMono-Regular.ttf", 20.0f);

    auto& style = ImGui::GetStyle();

    style.WindowRounding = 4.0f;
    style.FrameRounding = 4.0f;

    ImGui_ImplGlfw_InitForOpenGL(m_window.handle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    spdlog::debug("Initialized ImGui");
}

void App::update_imgui(AppOptions* options)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    auto& io = ImGui::GetIO();
    (void)io;

    if (ImGui::Begin("Options"))
    {
        ImGui::Checkbox("Wireframe Mode (F1)", &options->wireframe);
        ImGui::Checkbox("Cull Faces (F2)", &options->cull_faces);
        ImGui::Checkbox("Draw Chunk Border (F3)", &options->draw_chunk_border);
        ImGui::NewLine();
        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextColored(
                ImVec4(3 / 255.f, 252 / 255.f, 157 / 255.f, 1.f),
                "x=%.3f, y=%.3f, z=%.3f",
                options->camera->position().x,
                options->camera->position().y,
                options->camera->position().z
            );
            ImGui::NewLine();
            ImGui::DragFloat("Speed", &options->camera_speed, 0.5, 1, 50);
            ImGui::SliderFloat("FOV", &options->camera->fov, 30, 120);
            ImGui::Text("yaw: %.3f", options->camera->yaw());
            ImGui::Text("pitch: %.3f", options->camera->pitch());
        }
        ImGui::NewLine();
    }
    ImGui::End();

    if (ImGui::Begin("FPS"))
    {
        ImGui::Text("%.1f", io.Framerate);
    }
    ImGui::End();

    if (ImGui::Begin("World"))
    {
        ImGui::Text("Seed: %d", m_world.seed());
        ImGui::Text("Chunks: %d", m_world.m_chunks.size());
        ImGui::NewLine();

        if (ImGui::Button("Regenerate"))
        {
            m_world.clear();
            m_world.generate();
        }
    }
    ImGui::End();

    // ImGui::ShowDemoWindow();

    if (ImGui::GetCurrentContext() == nullptr || !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
    {
        if (io.MouseDrawCursor)
            io.MouseDrawCursor = false;
    }

    ImGui::Render();
}

void App::render_imgui() const
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        auto* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
