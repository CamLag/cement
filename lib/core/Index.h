#pragma once

#include "Instances.h"

namespace cement
{
    class Index : public Instances<unsigned long>
    {
        friend class Registry;

    public:
        virtual void SetValue(size_t a_pos, const unsigned long &a_val = NO_VALUE) override;
        virtual PropertyType Type() const override;
        Property *GetIndexed() const;

        virtual std::string Print() const override
        {
            std::string result = "(";
            result += m_indexed->GetName();
            result += ") ";
            result += Instances::Print();
            return result;
        }

    private:
        Index(const std::string &a_name, Property *a_indexed);

        Property *m_indexed;
    };
} // end namespace cement
