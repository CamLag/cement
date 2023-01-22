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
        Registry m_registry;
        bool m_show_summary{true};
    };

} // end namespace cement
