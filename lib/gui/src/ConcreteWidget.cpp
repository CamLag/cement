#include "../ConcreteWidget.h"
#include "../ModelWidget.h"

#include <QGridLayout>
#include <QLabel>

namespace cement
{
    ConcreteWidget::ConcreteWidget(Registry *a_registry, QWidget *a_parent) : QScrollArea(a_parent),
                                                                              m_registry(a_registry)
    {
        QGridLayout *layout = new QGridLayout();
        layout->setSizeConstraint(QLayout::SetFixedSize);
        int row = 0;
        for (auto &pair : m_registry->m_properties)
        {
            if (pair.second->Type() == 7 || !pair.second->IsShared())
            {
                continue;
            }
            auto label = new QLabel(QString::fromStdString(pair.second->GetName()));
            label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            layout->addWidget(label);

            for (size_t column = 1; column < pair.second->Size() + 1; column++)
            {
                layout->addWidget(new ModelWidget(pair.second, column - 1), row, column);
            }
            row++;
        }

        setLayout(layout);
    }
} // end namespace cement
