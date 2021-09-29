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

        template <typename T>
        void Init(const std::vector<T> &a_vector)
        {
            setColumnCount(a_vector.size());

            for (size_t i = 0; i < a_vector.size(); i++)
            {
                setItem(0, i, new QTableWidgetItem(QString::fromStdString(StringConversions::ToString<T>(a_vector[i]))));
            }
        }

        void UpdateRowCount();
        void UpdateColumnCount();
        void UpdateHeader();

        Registry *m_registry;
    };
} //end namespace cement
