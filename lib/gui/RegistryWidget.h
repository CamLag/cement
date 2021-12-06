#pragma once

#include "lib/core/StringConversions.h"
#include "lib/core/Registry.h"

#include <QTableWidget>

namespace cement
{
    class RegistryWidget : public QTableWidget
    {
        Q_OBJECT

    public:
        RegistryWidget(Registry *a_registry, QWidget *a_parent = nullptr);

        void UpdateColumnCount();
        void Update();

        template <typename T>
        void SetValues(size_t a_row, const Pool<T> &a_vector)
        {
            for (size_t i = 0; i < a_vector.Size(); i++)
            {
                setItem(a_row, i, new QTableWidgetItem(QString::fromStdString(StringConversions::ToString<T>(a_vector[i]))));
            }
        }

        Registry *m_registry;
    };
} // end namespace cement
