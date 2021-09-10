#include "../Registry.h"

namespace cement
{
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
} //end namespace cement