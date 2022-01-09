#pragma once

#include "lib/core/StringConversions.h"
#include "lib/core/Registry.h"

#include "lib/gui/RegistryModel.h"

#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>

namespace cement
{
    class RegistryWidget : public QTableView
    {
        Q_OBJECT

    public:
        RegistryWidget(Registry *a_registry, bool a_core, QWidget *a_parent = nullptr);

        void UpdateTableSize();
        void Update();
        void SetValue(size_t a_row, size_t a_column, Property *a_property, size_t a_instance);
        void SetValues(size_t a_row, Property *a_property);
        int StartingIndex();

    protected:
        Registry *m_registry;
        RegistryModel *m_q_model;

    private:
        const bool m_core;
    };
} // end namespace cement
