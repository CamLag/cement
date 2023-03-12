#include "Cementgui.h"
#include <stdio.h>
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

        ImGui::Columns(5);
        ImGui::SetColumnWidth(0, 100.f);
        ImGui::SetColumnWidth(1, 20.f);
        ImGui::SetColumnWidth(2, 150.f);
        ImGui::SetColumnWidth(3, 30.f);

        for (auto& pair : m_registry.m_properties->GetProperties())
        {
            ImGui::Text("%s", StringConversions::ToString(pair.second->Type()).c_str());
            ImGui::NextColumn();

            ImGui::Text("%d", pair.second->IsShared());
            ImGui::NextColumn();

            ImGui::PushID(pair.first);
            ImGui::InputText("", &(pair.second->GetName()));
            ImGui::PopID();
            ImGui::NextColumn();

            ImGui::PushID(pair.first);
            if (ImGui::SmallButton("+")) pair.second->Instanciate();
            ImGui::PopID();
            ImGui::NextColumn();

            ImGui::PushItemWidth(80.f);
            ShowPropertyValues(pair.second);
            ImGui::PopItemWidth();
            ImGui::NextColumn();
        }

        ImGui::End();
    }

    void Gui::ShowPropertyValues(Property* a_property)
    {
        switch (a_property->Type())
        {
        case pt_long :
        {
            CastToInstancesAndShowValues<long>(a_property);
            break;
        }
        case pt_bool :
        {
            CastToInstancesAndShowValues<bool>(a_property);
            break;
        }
        case pt_double :
        {
            CastToInstancesAndShowValues<double>(a_property);
            break;
        }
        case pt_string :
        {
            CastToInstancesAndShowValues<std::string>(a_property);
            break;
        }
        case pt_u_long :
        {
            CastToInstancesAndShowValues<unsigned long>(a_property);
            break;
        }
        case pt_index :
        case pt_model :
        case pt_property :
        default:
        {
            break;
        }
        }
    }

    template<>
    void Gui::ShowPropertyValue(Instances<long>* a_property, size_t a_position)
    {
        ImGui::InputInt("", reinterpret_cast<int*>(a_property->GetPointerAt(a_position)));
    }

    template<>
    void Gui::ShowPropertyValue(Instances<bool>* a_property, size_t a_position)
    {
        bool b = a_property->GetAt(a_position);
        if (ImGui::Checkbox("", &b))
        {
            a_property->SetAt(a_position, !a_property->GetAt(a_position));
        }
    }

    template<>
    void Gui::ShowPropertyValue(Instances<double>* a_property, size_t a_position)
    {
        ImGui::InputDouble("", a_property->GetPointerAt(a_position));
    }

    template<>
    void Gui::ShowPropertyValue(Instances<std::string>* a_property, size_t a_position)
    {
        ImGui::InputText("", a_property->GetPointerAt(a_position));
    }

    template<>
    void Gui::ShowPropertyValue(Instances<unsigned long>* a_property, size_t a_position)
    {
        ImGui::InputInt("", reinterpret_cast<int*>(a_property->GetPointerAt(a_position)));
    }
}

