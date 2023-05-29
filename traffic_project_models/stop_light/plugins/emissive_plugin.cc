#include <gazebo/gazebo.hh>
#include <gazebo/rendering/Visual.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
namespace gazebo
{
  class StopLightPlugin : public VisualPlugin
  {
  public:
    StopLightPlugin() {}

    virtual void Load(rendering::VisualPtr _visual, sdf::ElementPtr _sdf)
    {
      // Get the parent link of the visual
      this->link = boost::dynamic_pointer_cast<physics::Link>(_visual->GetParent());

      // Set the initial color to green
      this->currentColor = Color::Green;

      // Parse the update rate from the SDF
      if (_sdf->HasElement("update_rate"))
      {
        this->updatePeriod = 1.0 / _sdf->Get<double>("update_rate");
      }

      // Listen to the world update event
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&StopLightPlugin::OnUpdate, this));
    }

    virtual void Init() {}
    virtual void Reset() {}

  private:
    void OnUpdate()
    {if (this->updateCount % static_cast<int>(this->updatePeriod / this->updateRate) == 0)
  {
    auto link = this->visual->GetLink();
    auto visuals = link->GetVisuals();
    int index = 0;
    if (this->color == "green")
    {
      index = 2;
    }
    else if (this->color == "yellow")
    {
      index = 1;
    }
    visuals[index]->SetEmissive(ignition::math::Color(1, 1, 1, 1));
    for (int i = 0; i < visuals.size(); i++)
    {
      if (i != index)
      {
        visuals[i]->SetEmissive(ignition::math::Color(0, 0, 0, 1));
      }
    }
    if (this->color == "green")
    {
      this->color = "yellow";
    }
    else if (this->color == "yellow")
    {
      this->color = "red";
    }
    else
    {
      this->color = "green";
    }
  }
  this->updateCount++;
    }

    // The parent link of the traffic light
    physics::LinkPtr link;

    // The current color of the traffic light
    enum Color { Red, Yellow, Green } currentColor;

    // The next time when the traffic light needs to be updated
    common::Time nextUpdateTime = common::Time::Zero;

    // The period between updates
    double updatePeriod;

    // Pointer to the update event connection
    event::ConnectionPtr updateConnection;
  };
  GZ_REGISTER_VISUAL_PLUGIN(StopLightPlugin)
}
