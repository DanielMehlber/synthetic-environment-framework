#pragma once
#include <string>

using namespace std;

namespace emit::plugin {

class BasicPlugin {
  public:
    virtual std::string GetDisplayName() noexcept = 0;
    virtual std::string GetDescription() noexcept = 0;

    /**
     * @brief This callback function is called after the plugin has been loaded
     * in.
     */
    virtual void OnInit() = 0;

    /**
     * @brief This callback function is called on every frame update.
     */
    virtual void OnUpdate() = 0;

    /**
     * @brief This callback function is called before the plugin in loaded out.
     */
    virtual void OnShutDown() = 0;
};

} // namespace emit::plugin