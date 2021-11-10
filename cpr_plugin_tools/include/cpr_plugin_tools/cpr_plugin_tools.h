/**
Software License Agreement (proprietary)

\file      cpr_plugin_tools.h
\authors   Jordan Liviero<jliviero@clearpath.ai>
\copyright Copyright (c) 2017, Clearpath Robotics, Inc., All rights reserved.

Redistribution and use in source and binary forms, with or without modification, is not permitted without the
express permission of Clearpath Robotics.
*/

#ifndef CPR_PLUGIN_TOOLS_CPR_PLUGIN_TOOLS_H
#define CPR_PLUGIN_TOOLS_CPR_PLUGIN_TOOLS_H

// Clearpath-external
#include <string>
#include <typeinfo>
#include <ros/ros.h>
#include <sdformat-4.0/sdf/Element.hh>

namespace sim_tools
{

// Get parameters according to type
template<typename T>
void getSingleParam(const sdf::ElementPtr& _sdf, const std::string& name,
                    const std::string& plugin_name, T *var, bool mandatory = true)
{
  typedef T value_type;  // Get the data type of T, so it can be passed into Get<>()

  if (_sdf->HasElement(name))
  {
    *var = _sdf->GetElement(name)->Get<value_type>();
    ROS_DEBUG("%s read parameter %s, of type %s", plugin_name.c_str(), name.c_str(), typeid(*var).name());
  }
  else if (mandatory)
  {
    const std::string err_msg = plugin_name + " failed to load; no '" + name + "' specified";
    ROS_FATAL("%s", err_msg.c_str());
    throw std::runtime_error(err_msg);
  }
  else
  {
    ROS_WARN("Expected '%s' for %s, but none was specified", name.c_str(), plugin_name.c_str());
  }
}

}  // namespace sim_tools

#endif  // CPR_PLUGIN_TOOLS_CPR_PLUGIN_TOOLS_H
