#include "../RegistryModel.h"

namespace cement
{

    RegistryModel::RegistryModel(Registry *a_registry, QObject *a_parent) : QStandardItemModel(a_parent),
                                                                            m_registry(a_registry)
    {
    }

} // end namespace cement
