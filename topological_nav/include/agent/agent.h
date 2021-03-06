#ifndef TOPOLOGY_AGENT_H_
#define TOPOLOGY_AGENT_H_

#include <armadillo>
#include <visualise/vis_grid.h>
#include <visualise/vis_points.h>

#include "topological_map/rviz_topology.h"
#include "topological_map/occupancygrid_listener.h"
#include "topological_map/costmap2topology.h"

#include "online_search/online_search.h"
#include "online_search/objective_functions.h"
#include "finite_state_machine/finite_state_machine.h"

#include "topological_nav/String_cmd.h"

#include <vector>

#include <tf/LinearMath/Vector3.h>

namespace search{

class Agent{

public:

    Agent(const std::string&        name,
                ros::NodeHandle&    nh,
          const arma::mat&          grid,
          const arma::colvec3&      agent_pos_3D,
                objective_func&     obj_func,
                arma::ucolvec&      occupancy);

    void start();

    void update(const ros::Time &now);

    void publish();

    void initialise_visualisation(ros::NodeHandle& nh, const std::string &fixed_frame);

    bool has_finished_task();

private:

    bool service_callback(topological_nav::String_cmd::Request& req, topological_nav::String_cmd::Response& res);

private:

     const arma::mat&                               grid;
     arma::ucolvec&                                 occupancy;
     std::string                                    name;

     arma::Mat<int>                                 Adj;
     state                                          current_state, target_state, last_state;

     bool                                           bVisionInit;

     double                                         max_speed = 0.2; // m/s
     double                                         period;
     arma::colvec3                                  velocity;
     arma::colvec3                                  agent_pos_3D;
     arma::rowvec2                                  agent_pos_2D;
     arma::colvec3                                  target_pos_3D;

     std::unique_ptr<search::FSM>                   fsm_ptr;
     std::unique_ptr<search::Online_search>         online_search_ptr;

     std::unique_ptr<opti_rviz::Vis_gird>           vis_grid_ptr;
     std::unique_ptr<opti_rviz::Vis_points>         vis_point_ptr;
     std::unique_ptr< opti_rviz::Vis_points>        vis_neighbours_ptr;

     std::vector<tf::Vector3>                       agent_pos_vis;

     std::vector<tf::Vector3>                       neighbours;
     opti_rviz::acolor                              colors;

     bool                                           bRun;


     ros::ServiceServer                             service;

};



}

#endif
