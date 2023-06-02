#include "PropertyGroup.hpp"

using namespace emit::core::data;

emit::core::data::PropertyGroup::PropertyGroup(
    std::string id, std::string display_name = "Unnamed Group")
    : m_id{id}, m_display_name{display_name} {}

emit::core::data::PropertyGroup::~PropertyGroup() {
    RemoveAllChangeListeners();
}

std::optional<std::shared_ptr<PropertyBase>>
PropertyGroup::GetBase(const std::string &prop_id) const {
    if (/* this group */ Contains(prop_id)) {
        std::shared_ptr<PropertyBase> base = m_property_map.at(prop_id);
        return base;
    } else {
        return {}; // empty optional
    }
}

void emit::core::data::PropertyGroup::Apply() {
    for (auto listener : m_change_listeners) {
        listener->ApplyProperties(m_id);
    }
}

void PropertyGroup::AddChangeListener(PropertyGroupChangeListener *listener) {
    if (!/* not */ HasChangeListener(listener)) {
        m_change_listeners.push_back(listener);
    }
}

void PropertyGroup::RemoveChangeListener(
    PropertyGroupChangeListener *listener) {
    if (HasChangeListener(listener)) {
        m_change_listeners.remove(listener);
    }
}

void PropertyGroup::RemoveAllChangeListeners() { m_change_listeners.clear(); }
