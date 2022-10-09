#include "../Property.h"
#include "../Index.h"

namespace cement
{
    Property::Property(size_t a_id, const std::string &a_name, bool a_shared) :
                                                                    m_id(a_id),
                                                                    m_name(a_name),
                                                                    m_shared(a_shared)
    {
    }

    Property::~Property()
    {
    }

    std::string Property::Print() const
    {
        return "PROP " + std::to_string(m_id) + " " + StringConversions::ToString(Type()) + " \"" + m_name + "\"";
    }

    void Property::DeleteInstance(Id a_instance)
    {
        if (IsShared())
        {
            int total_count = 0;
            for (auto index : m_index_references)
            {
                total_count += index->CountValues(a_instance);
            }

            if (total_count == 0) // Nobody points on this instance
            {
                auto last_index = Size() - 1;

                InternalDeleteInstance(a_instance);

                for (auto index : m_index_references)
                {
                    index->ReplaceValues(last_index, a_instance);
                    // Due to the swap we have to update all the pointers to the last value
                }
            }
        }
        else
        {
            auto last_index = Size() - 1;

            InternalDeleteInstance(a_instance);

            for (auto index : m_index_references)
            {
                index->ReplaceValues(last_index, a_instance);
                // Due to the swap we have to update all the pointers to the last value
            }
        }
        // TODO error logs
    }

    size_t Property::Depth() const
    {
        return 1;
    }

    size_t Property::PropertyCount() const
    {
        return 1;
    }

    template <>
    PropertyType Property::GetPropType<long>()
    {
        return pt_long;
    }

    template <>
    PropertyType Property::GetPropType<bool>()
    {
        return pt_bool;
    }

    template <>
    PropertyType Property::GetPropType<double>()
    {
        return pt_double;
    }

    template <>
    PropertyType Property::GetPropType<std::string>()
    {
        return pt_string;
    }

    template <>
    PropertyType Property::GetPropType<unsigned long>()
    {
        return pt_u_long;
    }

    std::vector<std::vector<Property *>> Property::VisitProperties()
    {
        return {{this}};
    }

    bool Property::IsShared() const
    {
        return m_shared;
    }

    const std::string &Property::GetName() const
    {
        return m_name;
    }

    const std::set<Index *> &Property::GetIndexReferences() const
    {
        return m_index_references;
    }

    void Property::AddIndexReference(Index *a_index)
    {
        m_index_references.insert(a_index);
    }

    void Property::Get(Id /*a_instance*/, std::string &/*a_string_value*/)
    {
    }

    void Property::Set(Id /*a_instance*/, const std::string &/*a_string_value*/)
    {

    }

    const std::set<Index *> &Property::GetIndexes() const
    {
        static const std::set<Index *> blank_index;
        return blank_index;
    }

    void Property::GetPointedValue(Id /*a_instance*/, std::string &/*a_string_value*/)
    {

    }

    std::string Property::PrettyPrint(Id a_instance, int a_depth)
    {
        std::string result;

        auto indexes = GetIndexes();

        if (!IsLeaf())
        {
            result += GetName();
            result += "\r\n";
            ++a_depth;
        }
        else
        {
            std::string temp;
            Get(a_instance, temp);
            result += temp;
        }

        auto makeIndent = [=](bool a_last)
        {
            std::string indent_result(a_depth - 1, ' ');

            if (a_last)
            {
                indent_result.append("└");
            }
            else
            {
                indent_result.append("├");
            }

            return indent_result;
        };

        int count = GetIndexes().size();
        for (auto index : GetIndexes())
        {
            Property* child_prop = index->GetIndexed();
            auto child_index = index->Get(a_instance);
            result += makeIndent(count == 1);
            result += index->GetName();
            result += ": ";
            result += child_prop->PrettyPrint(child_index, a_depth);
            result += "\r\n";

            --count;
        }

        --a_depth;

        return result;
    }

    bool Property::IsLeaf()
    {
        return Type() == pt_bool || Type() == pt_double || Type() == pt_long || Type() == pt_string || Type() == pt_u_long;
    }

} // end namespace cement
