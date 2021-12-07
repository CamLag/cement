#include "../ModelWidget.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace cement
{
    ModelWidget::ModelWidget(Property *a_model, size_t a_instance, QWidget *a_parent) : QWidget(a_parent),
                                                                                        m_instance(a_instance),
                                                                                        m_model(a_model)
    {
        const auto &indexes = m_model->GetIndexes();
        std::string value;
        if (indexes.empty())
        {
            m_model->GetValue(a_instance, value);
            new QLabel(QString::fromStdString(value), this);
        }
        else
        {
            QFormLayout *layout = new QFormLayout();
            for (auto index : indexes)
            {
                QString name = QString::fromStdString(index->GetName());
                index->GetValue(a_instance, value);
                layout->addRow(name, new QLabel(QString::fromStdString(value)));
            }
            setLayout(layout);
        }

        // setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        // setStyleSheet("background-color:black;");
        // setStyleSheet("QWidget {border-width: 1px;border-style: solid;border-color: white;}");
    }

    // QSize ModelWidget::sizeHint() const
    // {
    //     return QSize(0, 0);
    // }
} // end namespace cement
