#include "../RegistryModel.h"

#include <algorithm>

namespace cement
{
    class DisabledItem : public QStandardItem
    {
    public:
        DisabledItem()
        {
            setEditable(false);
            setText("WHOO");
//            setForeground(QBrush(Qt::red));
//            setBackground(QBrush(Qt::red));
        }

        virtual QStandardItem* clone() const override
        {
            return new DisabledItem();
        }
    };

    RegistryModel::RegistryModel(Registry *a_registry, QObject *a_parent) : QStandardItemModel(a_parent),
                                                                            m_registry(a_registry),
                                                                            m_header_color{52, 16, 41}
    {
        auto prototype = new DisabledItem();
        setItemPrototype(prototype);

        size_t column_count = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size_t size = pair.second->Size();
            column_count = std::max(column_count, size);
        }

        setHorizontalHeaderItem(0, new QStandardItem("Property"));
        setHorizontalHeaderItem(1, new QStandardItem("Model"));
        setHorizontalHeaderItem(2, new QStandardItem("Indexed"));

        for (size_t i = 0; i < column_count; i++)
        {
            setHorizontalHeaderItem(i + 3, new QStandardItem(QString::number(i)));
        }

        Update();

        connect(this, &RegistryModel::itemChanged, this, &RegistryModel::WriteFromItem);
    }

    size_t RegistryModel::GetFirstRow(Property *a_property)
    {
        //TODO optimize
        size_t rowcount = RowCount();
        auto name = a_property->GetName();
        auto col = 0;
        QStandardItem* item = nullptr;
        for (size_t row = 0; row < rowcount; ++row)
        {
            item = RegistryModel::item(row, col);
            if (item && item->text().toStdString() == name)
            {
                return row;
            }
        }

        return -1;
    }
/*
    std::pair<size_t, size_t> RegistryModel::GetRows(Property *a_property)
    {
        auto first = GetFirstRow(a_property);
        if (first == -1ul)
        {
            return {-1ul, -1ul};
        }
        return {first, GetEndRow(first)};
    }

    size_t RegistryModel::GetEndRow(size_t a_row)
    {
        size_t end = a_row;
        auto name_item = item(a_row);
        auto name = name_item->text();

        while (end < RowCount() and name == item(end)->text())
        {
            end++;
        }
        return end;
    }
*/
    Property *RegistryModel::GetProperty(size_t a_row)
    {
        auto type = headerData(a_row, Qt::Vertical, dr_type).toInt();
        int col = 0;
        if (type == PropertyType::pt_index)
        {
            col = 1;
        }
        auto name_item = item(a_row, col);
        auto name = name_item->text();
        return m_registry->GetProperty(name.toStdString());
    }

    Property *RegistryModel::GetModel(size_t a_row)
    {
        auto name_item = item(a_row);
        auto name = name_item->text();
        return m_registry->GetProperty(name.toStdString());
    }

    bool RegistryModel::IsModelEmpty(size_t a_row)
    {
        auto property = GetProperty(a_row);
        auto index_item = item(a_row, 1);
        return (property->Type() == pt_model && index_item == itemPrototype());
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
//        std::cout << m_registry->Print();

        for (auto &pair : m_registry->m_properties)
        {
            AddProperty(pair.second);

//            std::string debu;
//            for (int i = 0; i < rowCount(); i++)
//            {
//                for (int j = 0; j < 3; j++)
//                {
//                    auto item_0 = item(i, j);
//                    if (item_0) debu += item_0->text().toStdString() += "/"; else debu.append("NULL/");
//                }
//                debu.append("\n");
//            }
//            std::cout << debu;
//            std::cout << "**end**" << std::endl;
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

    size_t RegistryModel::RowCount()
    {
        return static_cast<size_t>(rowCount());
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

    void RegistryModel::AddProperty(Property *a_property, bool a_add_indexes)
    {
        std::cout << "AddProperty " << a_property->GetName() << std::endl;
        size_t row = GetFirstRow(a_property);

        if (row == -1ul) // new property
        {
            row = RowCount();
        }
        else // already here, only updating the values
        {
            FillRow(a_property);
            return;
        }

        auto AddPropertyBaseData = [this](Property *a_property, size_t a_row)
        {
            auto item = new QStandardItem(QString::fromStdString(a_property->GetName()));
            item->setBackground(m_header_color);
            setItem(a_row, 0, item);
            setHeaderData(a_row, Qt::Vertical, a_property->IsShared(), dr_shown);
            setHeaderData(a_row, Qt::Vertical, a_property->Type(), dr_type);
            setHeaderData(a_row, Qt::Vertical, false, dr_sub_shared);
            FillRow(a_property);
        };

        switch (a_property->Type()) {
        case pt_model:
        {
            AddPropertyBaseData(a_property, row);
            if (a_add_indexes)
            {
                auto &indexes = a_property->GetIndexes();
                for (auto &index : indexes)
                {
                    AddProperty(index);
                }
            }
            break;
        }
        case pt_index:
        {
            auto index = dynamic_cast<Index*>(a_property);
            auto model = index->GetModel();
            AddProperty(model, false);
            row = GetFirstRow(model);
            row++;
            insertRow(row, {});
            AddPropertyBaseData(index, row);

            auto index_item = new QStandardItem(QString::fromStdString(model->GetName()));
            index_item->setBackground(m_header_color);

            auto indexed_item = new QStandardItem(QString::fromStdString(index->GetIndexed()->GetName()));
            indexed_item->setBackground(m_header_color);

            setItem(row, 1, index_item);
            setItem(row, 2, indexed_item);

            setHeaderData(row, Qt::Vertical, true, dr_shown);
            setHeaderData(row, Qt::Vertical, index->Type(), dr_type);
            setHeaderData(row, Qt::Vertical, index->GetIndexed()->IsShared(), dr_sub_shared);
            setHeaderData(row, Qt::Vertical, static_cast<qulonglong>(GetFirstRow(index->GetIndexed())), dr_pointed_row);
            FillRow(a_property);
            break;
        }
        case pt_bool:
        case pt_double:
        case pt_long:
        case pt_string:
        case pt_u_long:
        {
            AddPropertyBaseData(a_property, row);
            FillRow(a_property);
            break;
        }

        default:
            break;
        }
    }

    void RegistryModel::AddIndex(Index *a_index)
    {
 //       auto model = a_index->GetModel();
//        auto span = GetRows(model);

//        if (span.first == - 1ul)
//        {
//            AddProperty(model);
//            span = GetRows(model);
//        }

//        auto model_item = new QStandardItem(QString::fromStdString(model->GetName()));
//        model_item->setBackground(m_header_color);
//        auto index_item = new QStandardItem(QString::fromStdString(a_index->GetName()));
//        index_item->setBackground(m_header_color);
//        auto indexed_item = new QStandardItem(QString::fromStdString(a_index->GetIndexed()->GetName()));
//        indexed_item->setBackground(m_header_color);

//        auto row = span.second;

//        if (IsModelEmpty(GetFirstRow(model)))
//        {
//            setItem(row, 1, index_item);
//            setItem(row, 2, indexed_item);
//        }
//        else
//        {
//            insertRow(span.second, {model_item, index_item, indexed_item});
//        }

//        setHeaderData(row, Qt::Vertical, true, dr_shown);
//        setHeaderData(row, Qt::Vertical, a_index->Type(), dr_type);
//        setHeaderData(row, Qt::Vertical, a_index->GetIndexed()->IsShared(), dr_sub_shared);
//        setHeaderData(row, Qt::Vertical, static_cast<qulonglong>(GetFirstRow(a_index->GetIndexed())), dr_pointed_row);
//        FillRow(a_index);
    }

    void RegistryModel::RemoveProperty(Property *a_property)
    {

    }

    void RegistryModel::AddColumn(size_t a_row)
    {

    }

    void RegistryModel::CreateProperty()
    {
//        m_registry->CreateProperty()
    }

    void RegistryModel::SetValueFromModel(Property *a_property, size_t a_instance)
    {
        size_t row = GetFirstRow(a_property);
        std::cout << "RegistryModel::SetValueFromModel" << a_property->GetName() << " row " << row;
        if (row == -1ul)
        {
            std::cout << std::endl;
            return;
        }

        std::string value;
        a_property->Get(a_instance, value);
        std::cout << " value " << value << std::endl;
        setItem(row, a_instance + 3, new QStandardItem(QString::fromStdString(value)));
    }

    void RegistryModel::FillRow(Property *a_property)
    {
        if (a_property->Type() == pt_model)
        {
            return;
        }

        size_t i = 0;
        for (; i < a_property->Size(); i++)
        {
            SetValueFromModel(a_property, i);
        }

        auto slot = [=](size_t index){ SetValueFromModel(a_property, index); };
        auto connection = a_property->m_instance_changed.Connect(slot);
    }

} // end namespace cement
