#include "../RegistryWidget.h"

namespace cement
{
    RegistryWidget::RegistryWidget(Registry *a_registry, QWidget *a_parent) : m_registry(a_registry), QTableWidget(a_parent)
    {
    }

    void RegistryWidget::UpdateRowCount()
    {
        size_t counter = 0;

        for (auto &pair : m_registry->m_properties)
        {
            counter += pair.second->PropertyCount();
        }

        setRowCount(counter);
    }

    void RegistryWidget::UpdateColumnCount()
    {
        size_t max = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size_t size = pair.second->Size();
            max = std::max(max, size);
        }

        setColumnCount(max);
    }

    void RegistryWidget::UpdateHeader()
    {
        for (size_t i = 0; i < rowCount(); i++)
        {
            auto it = m_registry->m_properties.begin();
            it++;
            setVerticalHeaderItem(0, new QTableWidgetItem(QString::fromStdString(it->second->m_name)));
        }
    }

} //end namespace cement
