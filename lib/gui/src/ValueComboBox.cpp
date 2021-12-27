#include "../ValueComboBox.h"

namespace cement
{

    ValueComboBox::ValueComboBox(Index *a_index, size_t a_instance, QWidget *a_parent) : QComboBox(a_parent),
                                                                                         m_index(a_index)
    {
        for (size_t i = 0; i < a_index->GetIndexed()->Size(); i++)
        {
            std::string value;
            a_index->GetIndexed()->GetValue(i, value);
            addItem(QString::fromStdString(value));
            setCurrentIndex(a_index->GetValue(a_instance));
        }
    }

} // end namespace cement
