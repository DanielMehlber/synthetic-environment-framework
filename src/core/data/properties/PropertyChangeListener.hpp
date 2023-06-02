#pragma once

#include <algorithm>
#include <list>
#include <string>

namespace emit::core::data {
class PropertyGroup;

class PropertyGroupChangeListener {
  public:
    /**
     * @brief is called when the observed property group has changed,
     * @param property_group_id id of the property group that has changed
     */
    virtual void ApplyProperties(const std::string &property_group_id) = 0;

    virtual ~PropertyGroupChangeListener() {}
};
} // namespace emit::core::data
