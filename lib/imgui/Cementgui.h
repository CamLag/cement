#pragma once

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
        Registry m_registry;
        bool m_show_summary{true};
        bool m_show_properties{true};
        bool m_show_demo_window{false};
        bool m_is_shared_checkbox{true};
    };

} // end namespace cement
