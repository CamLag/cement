#include "../ConcreteWidget.h"
#include "../ModelWidget.h"

#include <QLabel>
#include <QVBoxLayout>

namespace cement
{
    ConcreteWidget::ConcreteWidget(Registry *a_registry, QWidget *a_parent) : QScrollArea(a_parent),
                                                                              m_registry(a_registry)
    {
        QVBoxLayout *layout = new QVBoxLayout();
        layout->setSizeConstraint(QLayout::SetFixedSize);
        int row = 0;

        for (auto &pair : m_registry->m_properties)
        {
            if (pair.second->Type() == 7 || !pair.second->IsShared())
            {
                continue;
            }

            layout->addWidget(new ModelWidget(pair.second));

            row++;
        }

        setLayout(layout);
    }
} // end namespace cement
