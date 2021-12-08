#include "../InstanceWidget.h"

#include <QVBoxLayout>
#include <QLabel>

namespace cement
{
    InstanceWidget::InstanceWidget(Property *a_model, size_t a_instance, QWidget *a_parent) : QWidget(a_parent),
                                                                                              m_instance(a_instance),
                                                                                              m_model(a_model)
    {
        const auto &indexes = m_model->GetIndexes();
        std::string value;
        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(new QLabel(QString::number(a_instance)));
        if (indexes.empty())
        {
            m_model->GetValue(a_instance, value);
            layout->addWidget(new QLabel(QString::fromStdString(value), this));
        }
        else
        {
            for (auto index : indexes)
            {
                index->GetValue(a_instance, value);
                layout->addWidget(new QLabel(QString::fromStdString(value)));
            }
        }
        setLayout(layout);

        // setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        // setStyleSheet("QWidget {border-width: 1px;border-style: solid;border-color: white;}");
    }

} // end namespace cement
