#pragma once

#include <algorithm>
#include <list>
#include <set>
#include <string>

namespace emit::core::data {
class PropertyGroup;

class PropertyGroupChangeListener {
  public:
    /**
     * @brief This method is called when the listener has detected changes in
     * the observed group.
     * @param property_group_id id of the property group where the changes
     * occurred
     * @param changed_property_ids set of ids of the changed properties in this
     * group
     */
    virtual void
    ApplyProperties(const std::string &property_group_id,
                    const std::set<std::string> &changed_property_ids) = 0;

    virtual ~PropertyGroupChangeListener() {}
};
} // namespace emit::core::data
