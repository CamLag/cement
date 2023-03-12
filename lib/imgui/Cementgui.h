#pragma once

#include "imgui.h"
#include "lib/core/Registry.h"

namespace cement
{
    class Gui
    {
    public:
        void Show();

    private:
        void ShowSummary();
        void ShowProperties();
        void ShowPropertyValues(Property* a_property);

        template<typename T>
        void ShowPropertyValue(Instances<T>* a_property, size_t a_position);

        template<typename T>
        void CastToInstancesAndShowValues(Property* a_property)
        {
            for (size_t i = 0; i < a_property->Size(); ++i)
            {
                ImGui::PushID(a_property->m_id * std::numeric_limits<unsigned short>::max() + i);
                ImGui::SameLine();
                ShowPropertyValue(dynamic_cast<Instances<T>*>(a_property), i);
                ImGui::PopID();
            }
        }

        Registry m_registry;
        bool m_show_summary{true};
        bool m_show_properties{true};
        bool m_show_demo_window{false};
        bool m_is_shared_checkbox{true};
    };

} // end namespace cement
