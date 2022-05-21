#include "../Index.h"

namespace cement
{
    Index::Index(const std::string &a_name, Property *a_indexed, Model *a_model) :
        Instances<unsigned long>(a_name, false),
        m_indexed(a_indexed),
        m_model(a_model)
    {
    }

    void Index::SetValue(size_t a_pos, const unsigned long &a_val)
    {
        Instances<unsigned long>::SetValue(a_pos, a_val);
    }

    PropertyType Index::Type() const
    {
        return pt_index;
    }

    void Index::GetPointedValue(size_t a_instance, std::string &a_string_value)
    {
        m_indexed->GetValue(m_values[a_instance], a_string_value);
    }

    Property* Index::GetIndexed() const
    {
        return m_indexed;
    }

    Model* Index::GetModel() const
    {
        return m_model;
    }

    std::string Index::Print() const
    {
        std::string result = "(";
        result += m_indexed->GetName();
        result += ") ";
        result += Instances::Print();
        return result;
    }


} // end namespace cement
