#include "Cementgui.h"
#include <stdio.h>
#include "imgui.h"
#include "bindings/imgui_impl_sdl.h"
#include "bindings/imgui_impl_opengl2.h"

namespace cement
{
    void Gui::Show()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::BeginMainMenuBar();
        if (ImGui::MenuItem("Summary")) m_show_summary = !m_show_summary;
        ImGui::EndMainMenuBar();
        if (m_show_summary) ShowSummary();
    }

    void Gui::ShowSummary()
    {
        ImGui::Begin("Registry");
        if (ImGui::Button("model"))
        {
            m_registry.CreateProperty(pt_model, "", true);
        }
        ImGui::SameLine();
        if (ImGui::Button("string"))
        {
            m_registry.CreateProperty(pt_string, "", true);
        }
        ImGui::SameLine();
        if (ImGui::Button("double"))
        {
            m_registry.CreateProperty(pt_double, "", true);
        }
        ImGui::SameLine();
        if (ImGui::Button("int"))
        {
            m_registry.CreateProperty(pt_long, "", true);
        }
        ImGui::SameLine();
        if (ImGui::Button("bool"))
        {
            m_registry.CreateProperty(pt_bool, "", true);
        }

        ImGui::Text("Size = %ld", m_registry.m_properties->Size());
        ImGui::Text("%s", m_registry.Print().c_str());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

//        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
        ImGui::End();
    }
}
