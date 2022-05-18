#include "../RegistryModel.h"

#include <algorithm>

namespace cement
{
    RegistryModel::RegistryModel(Registry *a_registry, QObject *a_parent) : QStandardItemModel(a_parent),
                                                                            m_registry(a_registry)
    {
        size_t column_count = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size_t size = pair.second->Size();
            column_count = std::max(column_count, size);
        }

        setHorizontalHeaderItem(0, new QStandardItem("Model"));
        setHorizontalHeaderItem(1, new QStandardItem("Property"));
        setHorizontalHeaderItem(2, new QStandardItem("Indexed"));

        for (size_t i = 0; i < column_count; i++)
        {
            setHorizontalHeaderItem(i + 3, new QStandardItem(QString::number(i)));
        }

        Update();

        connect(this, &RegistryModel::itemChanged, this, &RegistryModel::WriteFromItem);
    }

    size_t RegistryModel::GetRow(Property *a_property)
    {
        return std::distance(m_registry->m_properties.begin(), m_registry->m_properties.find(a_property->GetName())) - 1;
    }

    Property *RegistryModel::GetProperty(size_t a_row)
    {
        return m_registry->GetProperty(a_row);
    }

    Value RegistryModel::ValueFromIndex(QModelIndex a_index)
    {
        return
        {
            GetProperty(a_index.row()),
            static_cast<size_t>(a_index.column())
        };
    }

    void RegistryModel::Update()
    {
        size_t row = 0;

        for (auto &pair : m_registry->m_properties)
        {
            if (pair.second->Type() == pt_index)
            {
                continue;
            }

            auto &indexes = pair.second->GetIndexes();
            auto color = QColor(52, 16, 41);

            if (indexes.empty()) // Instances or empty model
            {
                auto item = new QStandardItem(QString::fromStdString(pair.second->GetName()));
                item->setBackground(color);
                setItem(row, 0, item);
                FillRow(row, pair.second);

                setHeaderData(row, Qt::Vertical, pair.second->IsShared(), dr_shown);
                setHeaderData(row, Qt::Vertical, pair.second->Type(), dr_type);
                setHeaderData(row, Qt::Vertical, false, dr_sub_shared);
                std::cout << "set " << pair.second->Type() << std::endl;
                row++;
            }
            else
            {
                for (auto &index : indexes)
                {
                    auto item = new QStandardItem(QString::fromStdString(pair.second->GetName()));
                    item->setBackground(color);
                    setItem(row, 0, item);
                    item = new QStandardItem(QString::fromStdString(index->GetName()));
                    item->setBackground(color);
                    setItem(row, 1, item);
                    item = new QStandardItem(QString::fromStdString(index->GetIndexed()->GetName()));
                    item->setBackground(color);
                    setItem(row, 2, item);

                    FillRow(row, index);

                    setHeaderData(row, Qt::Vertical, true, dr_shown);
                    setHeaderData(row, Qt::Vertical, index->Type(), dr_type);
                    setHeaderData(row, Qt::Vertical, index->GetIndexed()->IsShared(), dr_sub_shared);
                    setHeaderData(row, Qt::Vertical, static_cast<qulonglong>(GetRow(index->GetIndexed())), dr_pointed_row);
                    row++;
                }
            }
        }
    }

    QString RegistryModel::GetValue(size_t a_row, size_t a_column) const
    {
        auto item = this->item(a_row, a_column);

        std::cout << "GetValue row " << a_row << " column " << a_column << " value = ";
        if (item)
        {
            std::cout << item->text().toStdString() << std::endl;
            return item->text();
        }
        else
        {
            std::cout << "No value" << std::endl;
            return "";
        }
    }

    size_t RegistryModel::ColumnCount(size_t a_row)
    {
        auto it = m_registry->m_properties.begin();
        std::advance(it, a_row);
        std::cout << "RowCount row = " << a_row << " prop name = " << it->second->GetName() << std::endl;
        return it->second->Size();
    }

    void RegistryModel::SetValue(size_t a_row, size_t a_column, QString a_value)
    {
        item(a_row, a_column)->setData(a_value);
    }

    void RegistryModel::WriteFromCell(size_t a_row, size_t a_column)
    {
        auto prop = GetProperty(a_row);
        auto val = GetValue(a_row, a_column);
        prop->Set(a_column - 3, val.toStdString());
    }

    void RegistryModel::WriteFromItem(QStandardItem *a_item)
    {
        auto index = a_item->index();
        WriteFromCell(index.row(), index.column());
    }

    void RegistryModel::AddProperty(Property *a_property)
    {
        auto &indexes = a_property->GetIndexes();
        auto color = QColor(52, 16, 41);

        int row = rowCount();
        setRowCount(row);

        if (indexes.empty()) // Instances or empty model
        {
            auto item = new QStandardItem(QString::fromStdString(a_property->GetName()));
            item->setBackground(color);
            setItem(row, 0, item);
            FillRow(row, a_property);
            setHeaderData(row, Qt::Vertical, a_property->IsShared(), dr_shown);
            setHeaderData(row, Qt::Vertical, a_property->Type(), dr_type);
            setHeaderData(row, Qt::Vertical, false, dr_sub_shared);
            FillRow(rowCount() + 1, a_property);
        }
        else
        {
            for (auto &index : indexes)
            {
                auto item = new QStandardItem(QString::fromStdString(a_property->GetName()));
                item->setBackground(color);
                setItem(row, 0, item);
                item = new QStandardItem(QString::fromStdString(index->GetName()));
                item->setBackground(color);
                setItem(row, 1, item);
                item = new QStandardItem(QString::fromStdString(index->GetIndexed()->GetName()));
                item->setBackground(color);
                setItem(row, 2, item);
                setHeaderData(row, Qt::Vertical, true, dr_shown);
                setHeaderData(row, Qt::Vertical, index->Type(), dr_type);
                setHeaderData(row, Qt::Vertical, index->GetIndexed()->IsShared(), dr_sub_shared);
                setHeaderData(row, Qt::Vertical, static_cast<qulonglong>(GetRow(index->GetIndexed())), dr_pointed_row);
                FillRow(row, index);
            }
        }
    }

    void RegistryModel::RemoveProperty(Property *a_property)
    {

    }

    void RegistryModel::SetValueFromModel(size_t a_row, Property *a_property, size_t a_instance)
    {
        std::string value;
        a_property->Get(a_instance, value);
        std::cout << "RegistryModel::SetValueFromModel " << value << std::endl;
        setItem(a_row, a_instance + 3, new QStandardItem(QString::fromStdString(value)));
    }

    void RegistryModel::FillRow(size_t a_row, Property *a_property)
    {
        for (size_t i = 0; i < a_property->Size(); i++)
        {
            SetValueFromModel(a_row, a_property, i);
        }

        auto slot = [=](size_t index){ SetValueFromModel(a_row, a_property, index); };
        auto connection = a_property->m_instance_changed.Connect(slot);
    }

} // end namespace cement
