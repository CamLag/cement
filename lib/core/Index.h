#pragma once

#include "Instances.h"

namespace cement
{
    class Index : public Instances<unsigned long>
    {
        friend class Registry;

    public:
        virtual void SetValue(size_t a_pos, const unsigned long &a_val = NO_VALUE) override;
        unsigned long GetValue(size_t a_pos);

        Property *GetIndexed() const;

        int Count(size_t a_property_instance);
        int Replace(size_t a_new_property_instance, size_t a_old_property_instance);

    private:
        Index(const std::string &a_name, Property *a_indexed);

        Property *m_indexed;
    };
} // end namespace cement
