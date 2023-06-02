#include <iostream>

#include "boost/stacktrace.hpp"
#include "core/core.hpp"
#include <string>

using namespace emit::core::data;

class MyChangeListener : public PropertyGroupChangeListener {
  public:
    virtual void ApplyProperties(
        const std::string &property_group_id,
        const std::set<std::string> &changed_property_ids) override {
        std::cout << "Group has changed: " << property_group_id << std::endl;
        for (auto prop_id : changed_property_ids) {
            std::cout << "- Property '" << prop_id << "' changed" << std::endl;
        }
    }
};

int main() {
    std::cout << "Hello Vulkan" << std::endl;
    PropertyGroup group1("triton", "Water Surface");
    group1.RegisterProperty(
        Property<float>("height", 0.0f, "Ocean Height (m)"));

    group1.RegisterProperty(Property<long>("id", 0, "Ocean Id"));
    group1.RegisterProperty(
        Property<std::string>("name", "ocean", "Ocean Name"));
    group1.RegisterProperty(Property<std::set<float>>(
        "someFloats", std::set<float>(), "Some random floats"));

    MyChangeListener listener;
    group1.AddChangeListener(&listener);

    group1.Set<float>("height", 11.0);
    group1.Set<std::string>("name", "Carl the Ocean");

    group1.Apply();

    return 0;
}