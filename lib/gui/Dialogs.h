#pragma once

#include "lib/core/Property.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>

namespace cement
{
    struct PropertyDescriptor
    {
        std::string m_name;
        PropertyType m_type;
        bool m_shared;
    };

    class PropertyCreationDialog : public QDialog
    {
        Q_OBJECT

    public:
        PropertyCreationDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        PropertyDescriptor GetResult();

    protected:
        QLineEdit* m_name_edit{ nullptr };
        QCheckBox* m_check_box{ nullptr };
        QComboBox* m_combo_box{ nullptr };
    };
} // end namespace cement
