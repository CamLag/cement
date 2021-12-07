#include "../ModelWidget.h"

#include <QFormLayout>
#include <QLabel>

namespace cement
{
    ModelWidget::ModelWidget(Model *a_model, size_t a_instance, QWidget *a_parent) : QWidget(a_parent),
                                                                                     m_instance(a_instance),
                                                                                     m_model(a_model)
    {
        QFormLayout *layout = new QFormLayout();
        for (auto index : m_model->GetIndexes())
        {
            QString name = QString::fromStdString(index->GetName() + "->" + index->GetIndexed()->GetName());

            // layout->addRow(name, new QLabel(StringConversions::ToString()));
        }
    }
} // end namespace cement
