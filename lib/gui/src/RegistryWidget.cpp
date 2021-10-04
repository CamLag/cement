#include "../RegistryWidget.h"

namespace cement
{
    RegistryWidget::RegistryWidget(Registry *a_registry, QWidget *a_parent) : m_registry(a_registry), QTableWidget(a_parent)
    {
        Update();
        UpdateColumnCount();
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

    void RegistryWidget::Update()
    {
        UpdateColumnCount();

        size_t size = 0;

        for (auto &pair : m_registry->m_properties)
        {
            size += pair.second->PropertyCount();
        }

        setRowCount(size);

        size_t counter = 0;

        for (auto &pair : m_registry->m_properties)
        {
            switch (pair.second->Type())
            {
            case 1: // Model
            {
                auto model = dynamic_cast<Model *>(pair.second);

                for (auto &model_pair : model->m_indexes)
                {
                    QString name;
                    name += QString::fromStdString(model->m_name);
                    name += " / ";
                    name += QString::fromStdString(model_pair.first->m_name);
                    setVerticalHeaderItem(counter, new QTableWidgetItem(name));
                    SetValues(counter, model_pair.second);
                    counter++;
                }

                break;
            }
            case 2: // long
            {
                setVerticalHeaderItem(counter, new QTableWidgetItem(QString::fromStdString(pair.second->m_name)));
                SetValues(counter, dynamic_cast<Instances<long> *>(pair.second)->GetValues());
                counter++;
                break;
            }
            case 3: // bool
            {
                setVerticalHeaderItem(counter, new QTableWidgetItem(QString::fromStdString(pair.second->m_name)));
                SetValues(counter, dynamic_cast<Instances<bool> *>(pair.second)->GetValues());
                counter++;
                break;
            }
            case 4: // double
            {
                setVerticalHeaderItem(counter, new QTableWidgetItem(QString::fromStdString(pair.second->m_name)));
                SetValues(counter, dynamic_cast<Instances<double> *>(pair.second)->GetValues());
                counter++;
                break;
            }
            case 5: // string
                setVerticalHeaderItem(counter, new QTableWidgetItem(QString::fromStdString(pair.second->m_name)));
                SetValues(counter, dynamic_cast<Instances<std::string> *>(pair.second)->GetValues());
                counter++;
                break;
            }
        }
    }

} //end namespace cement
