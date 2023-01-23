#include "Cementgui.h"
#include <stdio.h>
#include "imgui.h"
#include "bindings/imgui_impl_sdl.h"
#include "bindings/imgui_impl_opengl2.h"
#include "imgui_stdlib.h"

namespace cement
{
    void Gui::Show()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::BeginMainMenuBar();
        if (ImGui::MenuItem("Demo")) m_show_demo_window = !m_show_demo_window;
        if (ImGui::MenuItem("Summary")) m_show_summary = !m_show_summary;
        if (ImGui::MenuItem("Properties")) m_show_properties = !m_show_properties;
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::EndMainMenuBar();
        if (m_show_summary) ShowSummary();
        if (m_show_properties) ShowProperties();
        if (m_show_demo_window) ImGui::ShowDemoWindow();
    }

    void Gui::ShowSummary()
    {
        ImGui::Begin("Registry", &m_show_summary);
        ImGui::Text("Size = %ld", m_registry.m_properties->Size());
        ImGui::Text("%s", m_registry.Print().c_str());
        ImGui::End();
    }

    void Gui::ShowProperties()
    {
        ImGui::Begin("Properties", &m_show_properties);
        if (ImGui::Button("model"))
        {
            m_registry.CreateProperty(pt_model, "", m_is_shared_checkbox);
        }
        ImGui::SameLine();
        if (ImGui::Button("string"))
        {
            m_registry.CreateProperty(pt_string, "", m_is_shared_checkbox);
        }
        ImGui::SameLine();
        if (ImGui::Button("double"))
        {
            m_registry.CreateProperty(pt_double, "", m_is_shared_checkbox);
        }
        ImGui::SameLine();
        if (ImGui::Button("int"))
        {
            m_registry.CreateProperty(pt_long, "", m_is_shared_checkbox);
        }
        ImGui::SameLine();
        if (ImGui::Button("bool"))
        {
            m_registry.CreateProperty(pt_bool, "", m_is_shared_checkbox);
        }
        ImGui::SameLine();
        ImGui::Checkbox("shared", &m_is_shared_checkbox);

        for (auto& pair : m_registry.m_properties->GetProperties())
        {
            ImGui::Text("%s", StringConversions::ToString(pair.second->Type()).c_str());
            ImGui::SameLine();
            ImGui::Text("%d", pair.second->IsShared());
            ImGui::SameLine();
            ImGui::PushID(pair.first);
            ImGui::InputText("", &(pair.second->GetName()));
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID(pair.first);
            if (ImGui::SmallButton("+")) pair.second->Instanciate();
            ImGui::PopID();
            for (size_t i = 0; i < pair.second->Size(); ++i)
            {
//                ImGui::PushID(pair.first - 1 - i);
                ImGui::SameLine();
                ImGui::Text("%s", StringConversions::ToString(pair.second->Get(i)).c_str());
//                ImGui::PopID();
            }
        }

        ImGui::End();
    }
}
