#include "../Dialogs.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>

namespace cement
{

    PropertyCreationDialog::PropertyCreationDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
    {
        setWindowTitle("Property Options");
        QFormLayout* layout = new QFormLayout();
        m_name_edit = new QLineEdit();
        m_combo_box = new QComboBox();
        m_combo_box->addItem("model", pt_model);
        m_combo_box->addItem("long", pt_long);
        m_combo_box->addItem("bool", pt_bool);
        m_combo_box->addItem("double", pt_double);
        m_combo_box->addItem("string", pt_string);
        m_check_box = new QCheckBox();
        auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addRow("Name", m_name_edit);
        layout->addRow("Type", m_combo_box);
        layout->addRow("Shared", m_check_box);
        layout->addRow(button_box);
        setLayout(layout);
        connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    PropertyDescriptor PropertyCreationDialog::GetResult()
    {
        return
        {
            m_name_edit->text().toStdString(),
            static_cast<PropertyType>(m_combo_box->currentData().toInt()),
            m_check_box->isChecked()
        };
    }

} // end namespace cement
