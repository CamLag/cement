#pragma once

#include "lib/core/StringConversions.h"
#include "lib/core/Registry.h"

#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>

namespace cement
{
    class RegistryWidget : public QTableView
    {
        Q_OBJECT

    public:
        RegistryWidget(Registry *a_registry, QWidget *a_parent = nullptr);

        void UpdateTableSize();
        void Update();
        void SetValue(size_t a_row, size_t a_column, const std::string &a_value);
        void SetValues(size_t a_row, Property *a_property);

    protected:
        Registry *m_registry;
        QStandardItemModel *m_q_model;
    };
} // end namespace cement
