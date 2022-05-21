#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include "lib/core/Registry.h"
#include "lib/core/Value.h"

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
        Property* GetProperty(size_t a_row);
        Property* GetModel(size_t a_row);
        Value ValueFromIndex(QModelIndex a_index);

        QString GetValue(size_t a_row, size_t a_column) const;
        size_t ColumnCount(size_t a_row);
        void SetValue(size_t a_row, size_t a_column, QString a_value);

    public slots:
        void WriteFromCell(size_t a_row, size_t a_column);
        void WriteFromItem(QStandardItem *a_item);
        void AddProperty(Property *a_property);
        void AddIndex(Index *a_index);
        void RemoveProperty(Property *a_property);
        void AddColumn(size_t a_row);

    protected:
        void SetValueFromModel(Property *a_property, size_t a_instance);
        void FillRow(Property *a_property);

        Registry *m_registry;
        QColor m_header_color;

    private:

    };
} // end namespace cement
