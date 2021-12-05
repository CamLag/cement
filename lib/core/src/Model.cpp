#include "../Model.h"
#include "../StringConversions.h"
#include "../Log.h"

namespace cement
{
    Model::Model(const std::string &a_name, bool a_shared) : Property(a_name, a_shared),
                                                             m_size(0)
    {
    }

    size_t Model::Instanciate()
    {
        for (auto &index : m_indexes)
        {
            unsigned long instance = NO_VALUE;
            if (!index->GetIndexed()->IsShared())
            {
                instance = index->GetIndexed()->Instanciate();
            }
            auto position = index->Instanciate();
            index->SetValue(position, instance);
        }
        m_size++;
        return m_size - 1;
    }

    void Model::DeleteInstance(size_t a_instance)
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

                DeleteSubInstance(a_instance);

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

            DeleteSubInstance(a_instance);

            for (auto index : m_index_references)
            {
                index->ReplaceValues(last_index, a_instance);
                // Due to the swap we have to update all the pointers to the last value
            }
        }
        // TODO error logs
    }

    void Model::DeleteSubInstance(size_t a_instance)
    {
        for (auto index : m_indexes)
        {
            if (!index->GetIndexed()->IsShared()) // the property value is owned by this model and can be deleted
            {
                index->GetIndexed()->DeleteInstance(index->GetValue(a_instance));
            }
            index->DeleteInstance(a_instance);
        }
    }

    const size_t Model::Size() const
    {
        return m_size;
    }

    std::string Model::Print() const
    {
        std::string result;

        result += Property::Print();

        for (auto &index : m_indexes)
        {
            result += "\n  ";
            result += index->Print();
        }
        result += "\n";

        return result;
    }

    const int Model::Type() const
    {
        return 1;
    }

    const size_t Model::Depth() const
    {
        size_t counter = 1;
        size_t max = 1;
        for (auto &index : m_indexes)
        {
            size_t depth = index->GetIndexed()->Depth();
            if (depth > max)
            {
                max = depth;
            }
        }
        counter += max;

        return counter;
    }

    const size_t Model::PropertyCount() const
    {
        return m_indexes.size();
    }

    std::vector<std::vector<Property *>> Model::VisitProperties()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &index : m_indexes)
        {
            for (auto &child : index->VisitProperties())
            {
                result.emplace_back();
                result.back().push_back(this);
                std::copy(child.begin(), child.end(), std::back_inserter(result.back()));
            }
        }

        return result;
    }

    void Model::AddIndex(Index *a_index)
    {
        m_indexes.insert(a_index);
    }

    const std::set<Index *> &Model::GetIndexes() const
    {
        return m_indexes;
    }
} // end namespace cement