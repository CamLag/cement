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
        return "PROP_ID " + std::to_string(m_id) + " " + m_name;
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

} // end namespace cement
