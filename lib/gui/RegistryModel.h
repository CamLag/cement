#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include "lib/core/Registry.h"

namespace cement
{
    class RegistryModel : public QStandardItemModel
    {
        Q_OBJECT

    public:
        RegistryModel(Registry *a_registry, QObject *a_parent = nullptr);

        void Update();

        enum DataRole
        {
            dr_shown = 257,
            dr_type,
            dr_sub_shared,
            dr_pointed_row
        };

        size_t GetRow(Property *a_property);
        QString GetValue(size_t a_row, size_t a_column) const;
        size_t ColumnCount(size_t a_row);
        void SetValue(size_t a_row, size_t a_column, QString a_value);

    protected:
        void SetValue(size_t a_row, size_t a_column, Property *a_property, size_t a_instance);
        void SetValues(size_t a_row, Property *a_property);
        Registry *m_registry;
    };
} // end namespace cement
