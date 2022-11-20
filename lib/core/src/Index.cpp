#include "../Index.h"

namespace cement
{
    Index::Index(Id a_id, const std::string &a_name, Property *a_indexed, Model *a_model) :
        Instances<unsigned long>(a_id, a_name, false),
        m_indexed(a_indexed),
        m_model(a_model)
    {
    }

    PropertyType Index::Type() const
    {
        return pt_index;
    }

    void Index::GetPointedValue(Id a_instance, std::string &a_string_value)
    {
        m_indexed->Get(m_values[a_instance], a_string_value);
    }

    Property* Index::GetIndexed() const
    {
        return m_indexed;
    }

    Model* Index::GetModel() const
    {
        return m_model;
    }

    Id Index::Instanciate()
    {
        unsigned long instance = NO_VALUE;
        if (!m_indexed->IsShared())
        {
            instance = m_indexed->Instanciate();
        }
        auto id = Instances<Id>::Instanciate();
        SetValue(id, instance);
        return id;
    }

    void Index::InternalDeleteInstance(Id a_instance)
    {
        Instances<Id>::InternalDeleteInstance(a_instance);

        if (!GetIndexed()->IsShared()) // the property value is owned by this model and can be deleted
        {
            GetIndexed()->DeleteInstance(Get(a_instance));
        }
    }

    size_t Index::Depth() const
    {
        return m_indexed->Depth() + 1;
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
