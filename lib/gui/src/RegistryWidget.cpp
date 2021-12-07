#include "../RegistryWidget.h"

namespace cement
{
    RegistryWidget::RegistryWidget(Registry *a_registry, QWidget *a_parent) : m_registry(a_registry), QTableWidget(a_parent)
    {
        Update();
    }

    void RegistryWidget::UpdateTableSize()
    {
        size_t column_count = 0;
        size_t row_count = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size_t size = pair.second->Size();
            column_count = std::max(column_count, size);

            if (pair.second->Type() > 1)
            {
                row_count++;
            }
            else if (pair.second->GetIndexes().size() == 0) // empty models
            {
                row_count++;
            }
        }

        setColumnCount(column_count);
        setRowCount(row_count);
    }

    void RegistryWidget::Update()
    {
        UpdateTableSize();

        size_t row = 0;

        for (auto &pair : m_registry->m_properties)
        {
            if (pair.second->Type() == 7)
            {
                continue;
            }

            auto &indexes = pair.second->GetIndexes();

            if (indexes.empty()) // Instances or empty model
            {
                setVerticalHeaderItem(row, new QTableWidgetItem(QString::fromStdString(pair.second->GetName())));
                SetValues(row, pair.second);
                row++;
            }
            else
            {
                for (auto &index : indexes)
                {
                    QString name;
                    name += QString::fromStdString(pair.second->GetName());
                    name += " / ";
                    name += QString::fromStdString(index->GetName());
                    name += "->";
                    name += QString::fromStdString(index->GetIndexed()->GetName());
                    setVerticalHeaderItem(row, new QTableWidgetItem(name));
                    SetValues(row, index);
                    row++;
                }
            }
        }
    }

    void RegistryWidget::SetValue(size_t a_row, size_t a_column, const std::string &a_value)
    {
        setItem(a_row, a_column, new QTableWidgetItem(QString::fromStdString(a_value)));
    }

    void RegistryWidget::SetValues(size_t a_row, Property *a_property)
    {
        std::string value;
        for (size_t i = 0; i < a_property->Size(); i++)
        {
            a_property->GetValue(i, value);
            SetValue(a_row, i, value);
        }
    }

} // end namespace cement
