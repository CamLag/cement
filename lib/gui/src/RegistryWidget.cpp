#include "../RegistryWidget.h"
#include "../ValueComboBox.h"

namespace cement
{
    RegistryWidget::RegistryWidget(Registry *a_registry, bool a_core, QWidget *a_parent) : m_registry(a_registry), m_core(a_core), QTableView(a_parent)
    {
        m_q_model = new QStandardItemModel();
        setModel(m_q_model);
        Update();
    }

    void RegistryWidget::UpdateTableSize()
    {
        size_t column_count = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size_t size = pair.second->Size();
            column_count = std::max(column_count, size);
        }

        m_q_model->setHorizontalHeaderItem(0, new QStandardItem("Model"));
        m_q_model->setHorizontalHeaderItem(1, new QStandardItem("Property"));

        if (m_core)
        {
            m_q_model->setHorizontalHeaderItem(2, new QStandardItem("Indexed"));
        }

        for (int i = 0; i < column_count; i++)
        {
            m_q_model->setHorizontalHeaderItem(i + StartingIndex(), new QStandardItem(QString::number(i)));
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

            if (!m_core && !pair.second->IsShared())
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
                setSpan(row, 0, 1, StartingIndex());
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

                    if (m_core)
                    {
                        item = new QStandardItem(QString::fromStdString(index->GetIndexed()->GetName()));
                        item->setBackground(color);
                        m_q_model->setItem(row, 2, item);
                    }

                    SetValues(row, index);
                    row++;
                }
            }
        }
    }

    void RegistryWidget::SetValue(size_t a_row, size_t a_column, Property *a_property, size_t a_instance)
    {
        std::string value;
        a_property->GetValue(a_instance, value);
        m_q_model->setItem(a_row, a_column, new QStandardItem(QString::fromStdString(value)));

        if (!m_core && !a_property->IsShared() && a_property->Type() == 7)
        {
            setIndexWidget(m_q_model->index(a_row, a_column), new ValueComboBox(dynamic_cast<Index *>(a_property), a_instance));
        }
    }

    void RegistryWidget::SetValues(size_t a_row, Property *a_property)
    {
        for (size_t i = 0; i < a_property->Size(); i++)
        {
            SetValue(a_row, i + StartingIndex(), a_property, i);
        }
    }

    int RegistryWidget::StartingIndex()
    {
        if (m_core)
        {
            return 3;
        }

        return 2;
    }

} // end namespace cement
