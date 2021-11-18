#include "../Registry.h"

namespace cement
{
    Index *Registry::AddProperty(Model *a_model, Property *a_property, const std::string &a_name)
    {
        auto index = new Index(a_name, a_property);
        m_properties[a_name] = index;
        a_model->GetIndexes().insert(index);
        return index;
    }

    Model *Registry::CreateModel(const std::string &a_name)
    {
        auto model = new Model(a_name);
        m_properties[a_name] = model;
        return model;
    }

    std::string Registry::Print()
    {
        std::string result;
        for (auto &prop : m_properties)
        {
            result += prop.second->Print();
        }
        return result;
    }

    std::vector<std::vector<Property *>> Registry::Visit()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &pair : m_properties)
        {
            for (auto &child : pair.second->VisitProperties())
            {
                result.push_back(child);
            }
        }

        return result;
    }
} // end namespace cement