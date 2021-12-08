#include "../ModelWidget.h"
#include "../InstanceWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace cement
{
    ModelWidget::ModelWidget(Property *a_model, QWidget *a_parent) : QWidget(a_parent),
                                                                     m_model(a_model)
    {
        QHBoxLayout *h_layout = new QHBoxLayout();

        auto &indexes = a_model->GetIndexes();

        if (indexes.empty())
        {
            h_layout->addStretch();
            h_layout->addWidget(new QLabel(QString::fromStdString(a_model->GetName())));
        }
        else
        {
            h_layout->addWidget(new QLabel(QString::fromStdString(a_model->GetName())));
            QVBoxLayout *v_layout = new QVBoxLayout();
            for (auto index : indexes)
            {
                v_layout->addWidget(new QLabel(QString::fromStdString(index->GetName())));
            }
            h_layout->addLayout(v_layout);
        }

        for (size_t i = 0; i < a_model->Size(); i++)
        {
            h_layout->addWidget(new InstanceWidget(a_model, i, this));
        }

        setLayout(h_layout);
    }

} // end namespace cement
