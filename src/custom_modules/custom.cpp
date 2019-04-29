/*
 ###############################################################################
 # If you use PhysiCell in your project, please cite PhysiCell and the version #
 # number, such as below:                                                      #
 #                                                                             #
 # We implemented and solved the model using PhysiCell (Version x.y.z) [1].    #
 #                                                                             #
 # [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
 #     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
 #     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
 #     DOI: 10.1371/journal.pcbi.1005991                                       #
 #                                                                             #
 # See VERSION.txt or call get_PhysiCell_version() to get the current version  #
 #     x.y.z. Call display_citations() to get detailed information on all cite-#
 #     able software used in your PhysiCell application.                       #
 #                                                                             #
 # Because PhysiCell extensively uses BioFVM, we suggest you also cite BioFVM  #
 #     as below:                                                               #
 #                                                                             #
 # We implemented and solved the model using PhysiCell (Version x.y.z) [1],    #
 # with BioFVM [2] to solve the transport equations.                           #
 #                                                                             #
 # [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
 #     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
 #     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
 #     DOI: 10.1371/journal.pcbi.1005991                                       #
 #                                                                             #
 # [2] A Ghaffarizadeh, SH Friedman, and P Macklin, BioFVM: an efficient para- #
 #     llelized diffusive transport solver for 3-D biological simulations,     #
 #     Bioinformatics 32(8): 1256-8, 2016. DOI: 10.1093/bioinformatics/btv730  #
 #                                                                             #
 ###############################################################################
 #                                                                             #
 # BSD 3-Clause License (see https://opensource.org/licenses/BSD-3-Clause)     #
 #                                                                             #
 # Copyright (c) 2015-2018, Paul Macklin and the PhysiCell Project             #
 # All rights reserved.                                                        #
 #                                                                             #
 # Redistribution and use in source and binary forms, with or without          #
 # modification, are permitted provided that the following conditions are met: #
 #                                                                             #
 # 1. Redistributions of source code must retain the above copyright notice,   #
 # this list of conditions and the following disclaimer.                       #
 #                                                                             #
 # 2. Redistributions in binary form must reproduce the above copyright        #
 # notice, this list of conditions and the following disclaimer in the         #
 # documentation and/or other materials provided with the distribution.        #
 #                                                                             #
 # 3. Neither the name of the copyright holder nor the names of its            #
 # contributors may be used to endorse or promote products derived from this   #
 # software without specific prior written permission.                         #
 #                                                                             #
 # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" #
 # AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   #
 # IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  #
 # ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   #
 # LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         #
 # CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        #
 # SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    #
 # INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     #
 # CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     #
 # ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  #
 # POSSIBILITY OF SUCH DAMAGE.                                                 #
 #                                                                             #
 ###############################################################################
 */

#include "./custom.h"

// declare cell definitions here

Cell_Definition epithelial_cell, wall_cell;

void create_cell_types( void )
{
    // use the same random seed so that future experiments have the
    // same initial histogram of oncoprotein, even if threading means
    // that future division and other events are still not identical
    // for all runs
    
    SeedRandom( parameters.ints("random_seed") );
    
    // housekeeping
    
    initialize_default_cell_definition();
    cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment );
    int cell_type_id = 0;
    
    // Name the default cell type
    
    cell_defaults.type = cell_type_id;
    cell_type_id +=1;
    cell_defaults.name = "default cell";
    
    // set default cell cycle model
    
    cell_defaults.functions.cycle_model = live;
    
    // set default_cell_functions;
    
    cell_defaults.functions.update_phenotype = NULL; // remove oxygen
    
    // needed for a 2-D simulation:
    
    /* grab code from heterogeneity */
    
    cell_defaults.functions.set_orientation = up_orientation;
    cell_defaults.phenotype.geometry.polarity = 1.0;
    cell_defaults.phenotype.motility.restrict_to_2D = true;
    
    // make sure the defaults are self-consistent.
    
    cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment );
    cell_defaults.phenotype.sync_to_functions( cell_defaults.functions );
    
    // set the rate terms in the default phenotype
    
    // first find index for a few key variables.
    int apoptosis_model_index = cell_defaults.phenotype.death.find_death_model_index( "Apoptosis" );
    int necrosis_model_index = cell_defaults.phenotype.death.find_death_model_index( "Necrosis" );
    
    // initially no necrosis
    cell_defaults.phenotype.death.rates[necrosis_model_index] = 0.0;

//    // variable to hold pressure data for MATLAB
//    cell_defaults.custom_data.add_variable("neighbor_pressure","dimless",0);
    
    // add custom data here, if any
    
	double alpha = parameters.doubles("self_velocity_factor");//I believe that the sum of this factors should be 1
    double beta = parameters.doubles("neigh_velocity_factor");
    double gamma = parameters.doubles("previous_bias_factor");
	double noise_factor = parameters.doubles("noise_factor");
	
	
	cell_defaults.custom_data.add_variable("self_velocity_factor","dimless",alpha);//0.4);//I believe that the sum of this factors should be 1
    cell_defaults.custom_data.add_variable("neigh_velocity_factor","dimless",beta);//0.4);
    cell_defaults.custom_data.add_variable("previous_bias_factor","dimless",gamma);//0.1);
	cell_defaults.custom_data.add_variable("noise_factor","dimless",noise_factor);
	double relative_adhesion_strength = parameters.doubles("relative_adhesion_strength");
	double relative_repulsion_strength = parameters.doubles("relative_repulsion_strength");
	
	cell_defaults.custom_data.add_variable("relative_adhesion_strength","dimless",relative_adhesion_strength);//for motiles to be less adhesive
	cell_defaults.custom_data.add_variable("relative_repulsion_strength","dimless",relative_repulsion_strength);//for walls to be more repelant
	
	double pressure_threshold = parameters.doubles("pressure_threshold");
	
	cell_defaults.custom_data.add_variable("pressure_threshold", "dimless", pressure_threshold);																					
    // define epithelial cell
    
    epithelial_cell = cell_defaults;
    epithelial_cell.parameters.pReference_live_phenotype = &( epithelial_cell.phenotype );
    epithelial_cell.type = cell_type_id;
    cell_type_id += 1;
    epithelial_cell.name = "epithelial cell";
    epithelial_cell.phenotype.motility.persistence_time = parameters.doubles( "motile_cell_persistence_time" );
    epithelial_cell.phenotype.motility.migration_speed = parameters.doubles( "motile_cell_migration_speed" );
    epithelial_cell.phenotype.motility.migration_bias = 1. - noise_factor; //alpha + beta + gamma// noise = 1 - b
    epithelial_cell.functions.update_migration_bias = boids_bias_change; // assign boids function
    epithelial_cell.functions.custom_cell_rule = motility_switch_function; // assign motility and proliferation function
    epithelial_cell.phenotype.death.rates[apoptosis_model_index] = 0.0; // set apoptosis rate to zero
    
    // define wall cell
    
    wall_cell = cell_defaults;
    wall_cell.parameters.pReference_live_phenotype = &( wall_cell.phenotype );
    wall_cell.type = cell_type_id;
    wall_cell.name = "wall";
    cell_type_id +=1;
    wall_cell.phenotype.motility.is_motile = false;
	//wall_cell->is_movable = false;
    wall_cell.phenotype.cycle.data.transition_rate( 0 , 0 ) = 0.0; // turn division off
    wall_cell.phenotype.death.rates[apoptosis_model_index] = 0.0;  // set apoptosis rate to zero
    wall_cell.phenotype.mechanics.cell_cell_repulsion_strength *= relative_repulsion_strength;
    return;
}

void setup_microenvironment( void )
{
    // set domain parameters
    
    // make sure to override and go back to 2D
    if( default_microenvironment_options.simulate_2D == false )
    {
        std::cout << "Warning: overriding XML config option and setting to 2D!" << std::endl;
        default_microenvironment_options.simulate_2D = true;
    }
    
    // no gradients need for this example
    
    default_microenvironment_options.calculate_gradients = false;
    
    // set Dirichlet conditions
    
    default_microenvironment_options.outer_Dirichlet_conditions = true;
    
    // if there are more substrates, resize accordingly
    std::vector<double> bc_vector( 1 , 38.0 ); // 5% o2
    default_microenvironment_options.Dirichlet_condition_vector = bc_vector;
    
    // initialize BioFVM

    initialize_microenvironment();
    
    return;
}

void setup_tissue( void )
{
    Cell* pC;
    
    // initialize variable for wall and wound thickness
    int wall_width = parameters.ints( "wall_thickness" );
    double wound_size = parameters.ints( "wound_size" );
    
    // hexagonal packing
    double x_min= microenvironment.mesh.bounding_box[0];
    double y_min= microenvironment.mesh.bounding_box[1];
    
    double x_max= microenvironment.mesh.bounding_box[3];
    double y_max= microenvironment.mesh.bounding_box[4];
    
    // define begining and end of the wound:
    double init_wound = (wound_size/100) * x_min;
    double end_wound = (wound_size/100) * x_max;
    
    double s = epithelial_cell.phenotype.geometry.radius* 2.0 * 0.952312806863957; // from Lecture 10
    double y_offset= 0.5* sqrt(3.0) * s;
    
    std::vector<double> position = {x_min+s,y_min+s,0};
    std::vector<double> aux_position = position;
    std::vector<double> init_position = position;

    int row = 0;
    while( position[1] < y_max - s )
    {
        position[0] = init_position[0] + 0.5*s*(row % 2 ); // stagger the rows
        
        while( position[0] < x_max - s )
        {
            if( position[1] < y_min + wall_width*s || position[1] > y_max - wall_width*s )
            {
                pC = create_cell( wall_cell );
                pC->assign_position( position );
				pC->is_movable = false;
            }
            else if( position[0] < x_min + wall_width*s || position[0] > x_max - wall_width*s )
            {
                pC = create_cell( wall_cell );
                pC->assign_position( position );
				pC->is_movable = false;
            }
            else if( position[0] < init_wound || position[0] > end_wound)// && or
            {
                
                pC= create_cell(epithelial_cell);
                pC->assign_position( position );
                double theta = 6.28318530718*uniform_random();
                std::vector<double> aux(3,0.0);
                aux[0] = cos(theta); //remember to remove hardcoding
                aux[1] = sin(theta);
                pC->velocity = aux;
                pC->phenotype.motility.migration_bias_direction = aux;
                
            }
            
            position[0] += s;
        }
        
        position[1] += y_offset;
        row++;
    }
    
    return;
}

void motility_switch_function( Cell* pCell, Phenotype& phenotype, double dt )
{
//     // for MATLAB analysis
//     static int pressure_id = pCell->custom_data.find_variable_index( "neighbor_pressure" );
//     pCell->custom_data[pressure_id] = pCell->state.simple_pressure;
    
    double motility_pressure = parameters.doubles("motility_threshold_pressure");
    double division_pressure = parameters.doubles("division_threshold_pressure");
    
	static int rel_id = pCell->custom_data.find_variable_index( "relative_adhesion_strength" ); 
	double rel_strength = pCell->custom_data[rel_id];
	
    if( pCell->state.simple_pressure <= motility_pressure )//&& pCell->phenotype.motility.is_motile == false )
    {
        pCell->phenotype.motility.is_motile = true;
        pCell->phenotype.mechanics.cell_cell_adhesion_strength *= rel_strength;
    }
    
    if( pCell->state.simple_pressure <= division_pressure )//&& pCell->phenotype.motility.is_motile == false )
    {
        pCell->phenotype.cycle.data.transition_rate( 0 , 0 ) = cell_defaults.phenotype.cycle.data.transition_rate( 0 , 0 );
    }
    
    if ( pCell->state.simple_pressure > motility_pressure )// && pCell->phenotype.motility.is_motile == true )
    {
        pCell->phenotype.motility.is_motile = false;
        pCell->phenotype.mechanics.cell_cell_adhesion_strength = cell_defaults.phenotype.mechanics.cell_cell_adhesion_strength;
    }
    
    if ( pCell->state.simple_pressure > division_pressure )// && pCell->phenotype.motility.is_motile == true )
    {
        pCell->phenotype.cycle.data.transition_rate( 0 , 0 ) = 0.0;
    }
    
    return;
}

// get neighbors function
std::vector<Cell*> get_neighborhood( Cell* pCell)
{
    std::vector<Cell*> neighbors = {};
    //1st, on own voxel
    std::vector<Cell*>::iterator neighbor;
    std::vector<Cell*>::iterator end = pCell->get_container()->agent_grid[pCell->get_current_mechanics_voxel_index()].end();
    
    for( neighbor =
        pCell->get_container()->agent_grid[pCell->get_current_mechanics_voxel_index()].begin();
        neighbor!=end; ++neighbor)
    {
        neighbors.push_back( *neighbor );
    }
    //getting neighboring voxels index
    std::vector<int>::iterator neighbor_voxel_index;
    std::vector<int>::iterator neighbor_voxel_index_end =
    pCell->get_container()->underlying_mesh.moore_connected_voxel_indices[pCell->get_current_mechanics_voxel_index()].end();
    
    for(neighbor_voxel_index = pCell->get_container()->underlying_mesh.moore_connected_voxel_indices[pCell->get_current_mechanics_voxel_index()].begin();
        neighbor_voxel_index != neighbor_voxel_index_end;
        ++neighbor_voxel_index)
    {
        if(!is_neighbor_voxel(
                              pCell, pCell->get_container()->underlying_mesh.voxels[
                                                                                    pCell->get_current_mechanics_voxel_index()].center,
                              pCell->get_container()->underlying_mesh.voxels[
                                                                             *neighbor_voxel_index].center, *neighbor_voxel_index))continue;
        //
        end = pCell->get_container()->agent_grid[*neighbor_voxel_index].end();
        for(neighbor = pCell->get_container()->agent_grid[*neighbor_voxel_index].begin();neighbor != end; ++neighbor)
        {
            neighbors.push_back( *neighbor );
        }
    }
    return neighbors;
}

// normalized neighbor velocity function
std::vector<double> get_norm_neigh_vel(Cell* pCell)
{
    
    /* We are going by the definition in CP Beatrici & LG Brunet 2011:
     *cell sorting based on motility differences, physical review E.
     *The sum of the normalized neighbor velocity is used. It is not divided
     *by the number of neighbors (mean).
     */
    
    
    std::vector<double> norm_neig_vel(3,0.0);
    if(pCell->phenotype.motility.is_motile == false)
    {
        return norm_neig_vel;
    }
    
    
    std::vector<Cell*> neighbors = get_neighborhood( pCell);
    if(neighbors.size() == 0)
    {
        return norm_neig_vel;
    }
    
    int number_of_neighbors = neighbors.size();
    
    //getting the total sum of neighbors velocity
    
    Cell* pN = NULL;
    for( int i=0; i<neighbors.size(); i++)
    {
        pN = neighbors[i];
        if( pN != pCell)
        {
            std::vector<double> aux_norm_Vn(3,0.0);
            
            /*  if( norm(pN->velocity) > 1e-16 ) //if speed is too small then it's 0
             {
             aux_norm_Vn = pN->velocity;
             } */
            
            aux_norm_Vn = pN->velocity;
            
            if( norm(aux_norm_Vn) != 0)
            {
                normalize( &aux_norm_Vn );
            }
            
            norm_neig_vel += aux_norm_Vn;
        }
        else
        {
            number_of_neighbors-=1;//if the neighbor cell == current cell then it's not a neighbor and the size of the neighborhood is over estimated by 1
        }
    }
    //i need to review the order of normalization and mean-ization
    //norm_neig_vel = norm_neig_vel/number_of_neighbors;
    
    /* for( int i=0; i<norm_neig_vel.size();i++)
     {
     norm_neig_vel[i] = norm_neig_vel[i]/number_of_neighbors;
     } */
    
    //normalize( &norm_neig_vel ); //the sum is not normalized in the paper
    
    return norm_neig_vel;
    
}

// boids bias function
void boids_bias_change(Cell* pCell, Phenotype& phenotype , double dt )
{
    //add some if dead return stuff here
    
    static int a_id = pCell->custom_data.find_variable_index( "self_velocity_factor" );
    static int b_id = pCell->custom_data.find_variable_index( "neigh_velocity_factor" );
    static int g_id = pCell->custom_data.find_variable_index( "previous_bias_factor" );
    
    double alpha = pCell->custom_data[a_id];
    double beta = pCell->custom_data[b_id];
    double gamma = pCell->custom_data[g_id];
    
    std::vector<double> self_v = pCell->velocity; //normalize( pCell->velocity );
    if( norm(self_v) != 0 )
    {
        normalize( &self_v );
    }
    std::vector<double> neigh_v = get_norm_neigh_vel(pCell);
    if( norm(neigh_v) != 0)
    {
        normalize( &neigh_v );
    }
    std::vector<double> prev_b_direc = pCell->phenotype.motility.migration_bias_direction; //bias is already normalized
    
    std::vector<double> aux(3,0.0);
    
    for( int i=0; i<aux.size();i++)
    {
        aux[i] = alpha*self_v[i] + beta*neigh_v[i] + gamma*prev_b_direc[i];
    }
    
    //aux = alpha*self_v + beta*neigh_v + gamma*prev_b_direc;
    
    if( norm(aux) != 0)
    {
        normalize( &aux );
    }
    else
    {
        double theta = 6.28318530718*uniform_random();
        std::vector<double> aux(3,0.0);
        aux[0] = cos(theta); //remember to remove hardcoding
        aux[1] = sin(theta);
    }
    pCell->phenotype.motility.migration_bias_direction = aux;//no need for the random vector, as the definition of bias in physicell has it already
    
    return;
}

// coloring function
std::vector<std::string> my_coloring_function( Cell* pCell )
{
    std::vector<std::string> output = false_cell_coloring_cytometry(pCell); // start with flow cytometry coloring
    
        if( pCell->phenotype.death.dead == false && pCell->type == 1 )
        {
            output[0] = "violet";
            output[2] = "indigo";
        }
    
        else if ( pCell->phenotype.death.dead == false && pCell->type == 2 )
        {
            output[0] = "silver";
            output[2] = "silver";
        }
    
    
//    // uncomment blocks below and comment out blocks above to visualize pressure
//    if( pCell->state.simple_pressure < 0.1 )
//    {
//        output[0] = "lightgreen";
//        output[2] = "lightgreen";
//    }
//    
//    else if ( 0.1 <= pCell->state.simple_pressure < 0.2 )
//    {
//        output[0] = "green";
//        output[2] = "green";
//    }
//    
//    else if ( 0.2 <= pCell->state.simple_pressure < 0.3 )
//    {
//        output[0] = "darkgreen";
//        output[2] = "darkgreen";
//    }
//    
//    else if ( 0.3 <= pCell->state.simple_pressure < 0.4 )
//    {
//        output[0] = "orange";
//        output[2] = "orange";
//    }
//    
//    else if ( 0.4 <= pCell->state.simple_pressure < 0.5 )
//    {
//        output[0] = "orangered";
//        output[2] = "orangered";
//    }
//    
//    else if ( 0.5 <= pCell->state.simple_pressure < 0.6 )// && pCell->phenotype.motility.is_motile == true )
//    {
//        output[0] = "red";
//        output[2] = "red";
//    }
//    
//    else if ( 0.6 <= pCell->state.simple_pressure )// && pCell->phenotype.motility.is_motile == true )
//    {
//        output[0] = "darkred";
//        output[2] = "darkred";
//    }
    
    return output;
}
