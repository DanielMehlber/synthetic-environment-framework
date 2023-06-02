#pragma once

#include "../exceptions/EmitException.hpp"
#include "Property.hpp"
#include "PropertyChangeListener.hpp"
#include <algorithm>
#include <list>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>

namespace emit::core::data {

/**
 * @brief A proprety group conatins properties of a certain domain (e.g. a
 * plugin, functinality). Change listeneres can attach to a group in order to
 * get notified, when values in this group changed.
 */
class PropertyGroup {
  protected:
    /**
     * @brief id of this group. All properties assigned to this group can be
     * accessed through this id + the properties id.
     */
    const std::string m_id;

    /**
     * @brief metadata: display name of the property group. This is used for
     * display purposes.
     */
    const std::string m_display_name;

    /**
     * @brief this map contains all properties owned by this group. A property
     * could theoretically be assigned to multiple groups, but this is not
     * recommended because it could lead to bugs.
     */
    std::unordered_map<std::string, std::shared_ptr<PropertyBase>>
        m_property_map;

    /**
     * @brief contains all change listeners of the property group. All entries
     * will be notified about the change.
     */
    std::list<PropertyGroupChangeListener *> m_change_listeners;

    /**
     * @brief this set of property ids remembers all properties that have
     * changed since the last apply
     */
    std::set<std::string> m_changed_props;

    /**
     * @brief get a property of this group.
     * @param prop_id id of the wanted property
     * @return optional containing the property object if prop_id is valid
     */
    template <typename T>
    std::optional<std::shared_ptr<Property<T>>>
    GetProperty(const std::string &prop_id) const;

    /**
     * @brief tries to find the property base using the passed id in this group
     * @param prop_id id of the requested property in this group
     * @return optionally (if id exists) the property base of the requested
     * property
     */
    inline std::optional<std::shared_ptr<PropertyBase>>
    GetBase(const std::string &prop_id) const;

  public:
    PropertyGroup() = delete;
    PropertyGroup(std::string id, std::string display_name);
    PropertyGroup(PropertyGroup &copy) = delete;
    PropertyGroup(PropertyGroup &&copy) = delete;
    virtual ~PropertyGroup();

    /**
     * @brief adds property to this group. If a property with this name already
     * exists, this throws an exception.
     * @throws exception if property with this name already exists in group
     * @param new_property
     */
    void RegisterProperty(std::shared_ptr<PropertyBase> new_property);

    /**
     * @brief adds property to this group. If a property with this name already
     * exists, this throws an exception
     * @throws exception if property with this name already exists in group
     * @tparam T
     * @param typed_prop
     */
    template <typename T> void RegisterProperty(Property<T> typed_prop);

    /**
     * @brief checks if this group contains a property with this id
     * @param prop_id id of property
     * @return true, if this contains property with passed id
     */
    inline bool Contains(const std::string &prop_id) const;

    /**
     * @brief checks if this is listened to by a specific changae listener
     * @param listener listener that might listen to changes in this group
     * @return true, if the listener is listening to changes in this group
     */
    inline bool
    HasChangeListener(const PropertyGroupChangeListener *listener) const;

    /**
     * @brief fetches property with id and returns its value directly
     * @tparam T type of requested property
     * @param prop_id id of property
     * @return value of requested property
     */
    template <typename T>
    inline std::optional<T> Get(const std::string &prop_id) const;

    /**
     * @brief sets value of property with id directly (if it exists).
     * @tparam T type of value to be set (must equal property value type)
     * @param prop_id id of property
     * @param t value that should be set a new value for property
     * @throws when
     */
    template <typename T>
    inline void Set(const std::string &prop_id, const T &t);

    /**
     * @brief Apply changes of properties by notifying all change listeners of
     * this group.
     */
    void Apply();

    void AddChangeListener(PropertyGroupChangeListener *listener);
    void RemoveChangeListener(PropertyGroupChangeListener *listener);
    void RemoveAllChangeListeners();
};

template <typename T>
void PropertyGroup::RegisterProperty(Property<T> typed_prop) {
    if (/* this group already */ Contains(typed_prop.GetId())) {
        throw "this property already exists";
    }

    PropertyBase *_base = new Property<T>(typed_prop);
    std::shared_ptr<PropertyBase> base(_base);

    m_property_map[base->GetId()] = base;
}

template <typename T>
std::optional<std::shared_ptr<Property<T>>>
PropertyGroup::GetProperty(const std::string &prop_id) const {
    auto optional_property_base = GetBase(prop_id);
    if (optional_property_base.has_value()) {
        auto property_base = optional_property_base.value();

        if (property_base->IsOfType<T>()) {
            const std::shared_ptr<Property<T>> typed_property =
                std::static_pointer_cast<Property<T>>(property_base);
            return typed_property;
        }
    }

    return {}; /* if the property was not found or has wrong type */
}

template <typename T>
inline std::optional<T> PropertyGroup::Get(const std::string &prop_id) const {
    auto prop = GetProperty<T>(prop_id);
    if (prop.has_value()) {
        return prop.value()->GetValue();
    } else {
        return {};
    }
}

template <typename T>
inline void PropertyGroup::Set(const std::string &prop_id, const T &t) {
    auto prop_opt = GetProperty<T>(prop_id);
    if (prop_opt.has_value()) {
        auto prop = prop_opt.value();
        prop->SetValue(t);

        /* remember changed properties */
        m_changed_props.insert(prop->GetId());
    } else {
        throw core::exceptions::EmitException("this property does not exist");
    }
}

inline bool PropertyGroup::Contains(const std::string &prop_id) const {
    return m_property_map.find(prop_id) != m_property_map.end();
}

inline bool PropertyGroup::HasChangeListener(
    const PropertyGroupChangeListener *listener) const {
    return std::find(m_change_listeners.begin(), m_change_listeners.end(),
                     listener) != m_change_listeners.end();
}

std::optional<std::shared_ptr<PropertyBase>> inline PropertyGroup::GetBase(
    const std::string &prop_id) const {
    if (/* this group */ Contains(prop_id)) {
        std::shared_ptr<PropertyBase> base = m_property_map.at(prop_id);
        return base;
    } else {
        return {}; // empty optional
    }
}

} // namespace emit::core::data
