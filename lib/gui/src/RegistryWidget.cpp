#include "../RegistryWidget.h"

#include <QComboBox>
#include <QStyledItemDelegate>

namespace cement
{
    RegistryWidget::RegistryWidget(RegistryModel *a_registry_model, bool a_core, QWidget *a_parent) : m_registry_model(a_registry_model), m_core(a_core), QTableView(a_parent)
    {
        m_delegate = new SharedValueDelegate(a_registry_model);
        setModel(m_registry_model);

        // debugging purpose
        for (size_t row = 0; row < a_registry_model->rowCount(); row++)
        {
            for (size_t col = 0; col < a_registry_model->columnCount(); col++)
            {
                a_registry_model->GetValue(row, col);
            }
        }

        if (!m_core)
        {
            hideColumn(2);

            for (size_t row = 0; row < m_registry_model->rowCount(); row++)
            {
                auto hide = !m_registry_model->headerData(row, Qt::Vertical, RegistryModel::dr_shown).toBool();
                if (hide)
                {
                    hideRow(row);
                }
                else
                {
                    auto type = m_registry_model->headerData(row, Qt::Vertical, RegistryModel::dr_type).toInt();

                    std::cout << "registryWidget Update row = " << row << " type = " << type << std::endl;

                    if (type != pt_index) // cannot be model
                    {
                        setSpan(row, 0, 1, 2);
                    }
                    else if (m_registry_model->headerData(row, Qt::Vertical, RegistryModel::dr_sub_shared).toBool())
                    {
                        for (int column = 2; column < m_registry_model->columnCount(); column++)
                        {

                            setItemDelegateForRow(row, m_delegate);

                            // auto combo_box = new ValueComboBox(m_registry_model, row, column);
                            // setIndexWidget(m_registry_model->index(row, column), combo_box);
                        }
                    }
                }
            }
        }
    }


    QSet<Property*> RegistryWidget::SelectedProperties()
    {
        QSet<Property*> result;
        auto list = selectionModel()->selection().indexes();
        for (auto& item : list)
        {
            size_t row = item.row();
            result.insert(m_registry_model->GetProperty(row));
        }

        return result;
    }

    QVector<Value> RegistryWidget::SelectedValues()
    {
        QVector<Value> result;
        auto list = selectionModel()->selection().indexes();
        for (auto& item : list)
        {
            result.push_back(m_registry_model->ValueFromIndex(item));
        }

        return result;
    }

} // end namespace cement
