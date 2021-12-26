#include "../RegistryWidget.h"

namespace cement
{
    RegistryWidget::RegistryWidget(Registry *a_registry, QWidget *a_parent) : m_registry(a_registry), QTableView(a_parent)
    {
        m_q_model = new QStandardItemModel();
        setModel(m_q_model);
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

        m_q_model->setColumnCount(column_count + 3);
        m_q_model->setRowCount(row_count);

        m_q_model->setHorizontalHeaderItem(0, new QStandardItem("Model"));
        m_q_model->setHorizontalHeaderItem(1, new QStandardItem("Property"));
        m_q_model->setHorizontalHeaderItem(2, new QStandardItem("Indexed"));

        for (int i = 0; i < column_count; i++)
        {
            m_q_model->setHorizontalHeaderItem(i + 3, new QStandardItem(QString::number(i)));
        }
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
            auto color = QColor(52, 16, 41);

            if (indexes.empty()) // Instances or empty model
            {
                auto item = new QStandardItem(QString::fromStdString(pair.second->GetName()));
                item->setBackground(color);
                m_q_model->setItem(row, 0, item);
                setSpan(row, 0, 1, 3);
                SetValues(row, pair.second);
                row++;
            }
            else
            {
                for (auto &index : indexes)
                {
                    auto item = new QStandardItem(QString::fromStdString(pair.second->GetName()));
                    item->setBackground(color);
                    m_q_model->setItem(row, 0, item);
                    item = new QStandardItem(QString::fromStdString(index->GetName()));
                    item->setBackground(color);
                    m_q_model->setItem(row, 1, item);
                    item = new QStandardItem(QString::fromStdString(index->GetIndexed()->GetName()));
                    item->setBackground(color);
                    m_q_model->setItem(row, 2, item);
                    // m_q_model->setVerticalHeaderItem(row, new QStandardItem(name));
                    SetValues(row, index);
                    row++;
                }
            }
        }
    }

    void RegistryWidget::SetValue(size_t a_row, size_t a_column, const std::string &a_value)
    {
        m_q_model->setItem(a_row, a_column, new QStandardItem(QString::fromStdString(a_value)));
        // setItem(a_row, a_column, new QTableWidgetItem(QString::fromStdString(a_value)));
    }

    void RegistryWidget::SetValues(size_t a_row, Property *a_property)
    {
        std::string value;
        for (size_t i = 0; i < a_property->Size(); i++)
        {
            a_property->GetValue(i, value);
            SetValue(a_row, i + 3, value);
        }
    }

} // end namespace cement
