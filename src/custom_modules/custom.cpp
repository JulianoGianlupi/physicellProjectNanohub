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
	//std::cout << "create cell types" << std::endl; 
	// use the same random seed so that future experiments have the 
	// same initial histogram of oncoprotein, even if threading means 
	// that future division and other events are still not identical 
	// for all runs 
	
	SeedRandom( parameters.ints("random_seed") ); // or specify a seed here 
	
	// housekeeping 
	//std::cout << "initialize_default_cell_definition" << std::endl; 
	initialize_default_cell_definition();
	//std::cout << "sync_to_microenvironment" << std::endl; 
	cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment ); 
	int cell_type_id = 0;
	
	// Name the default cell type 
	//std::cout << "create default" << std::endl; 
	cell_defaults.type = cell_type_id; 
	cell_type_id +=1;
	cell_defaults.name = "default cell";
	
	// set default cell cycle model 

	cell_defaults.functions.cycle_model = flow_cytometry_separated_cycle_model; 
	
	// set default_cell_functions; 
	
	cell_defaults.functions.update_phenotype == NULL;//update_cell_and_death_parameters_O2_based;
    cell_defaults.functions.custom_cell_rule = motility_switch_function;
	
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
	int oxygen_substrate_index = microenvironment.find_density_index( "oxygen" );

	int G0G1_index = flow_cytometry_separated_cycle_model.find_phase_index( PhysiCell_constants::G0G1_phase );
	int S_index = flow_cytometry_separated_cycle_model.find_phase_index( PhysiCell_constants::S_phase );

	// initially no necrosis 
	cell_defaults.phenotype.death.rates[necrosis_model_index] = 0.0; 

	// set oxygen uptake / secretion parameters for the default cell type 
	cell_defaults.phenotype.secretion.uptake_rates[oxygen_substrate_index] = 0; 
	cell_defaults.phenotype.secretion.secretion_rates[oxygen_substrate_index] = 0; 
	cell_defaults.phenotype.secretion.saturation_densities[oxygen_substrate_index] = 0; 
	
	// add custom data here, if any 
	

	
    //std::cout << "grab alpha..." << std::endl; 
    double alpha = parameters.doubles("self_velocity_factor");//I believe that the sum of this factors should be 1
    double beta = parameters.doubles("neigh_velocity_factor");
    double gamma = parameters.doubles("previous_bias_factor");
	double noise_factor = parameters.doubles("noise_factor");
	
	
	cell_defaults.custom_data.add_variable("self_velocity_factor","dimless",alpha);//0.4);//I believe that the sum of this factors should be 1
    cell_defaults.custom_data.add_variable("neigh_velocity_factor","dimless",beta);//0.4);
    cell_defaults.custom_data.add_variable("previous_bias_factor","dimless",gamma);//0.1);
	cell_defaults.custom_data.add_variable("noise_factor","dimless",noise_factor);//0.1);
	
	
	double relative_adhesion_strength = parameters.doubles("relative_adhesion_strength");
	double relative_repulsion_strength = parameters.doubles("relative_repulsion_strength");
	
	cell_defaults.custom_data.add_variable("relative_adhesion_strength","dimless",relative_adhesion_strength);//for motiles to be less adhesive
	cell_defaults.custom_data.add_variable("relative_repulsion_strength","dimless",relative_repulsion_strength);//for walls to be more repelant
	
	double pressure_threshold = parameters.doubles("pressure_threshold");
	
	cell_defaults.custom_data.add_variable("pressure_threshold", "dimless", pressure_threshold);
	
	

	// Now, let's define another cell type. 
	// It's best to just copy the default and modify it. 
	
	// make this cell type randomly motile, less adhesive, greater survival, 
	// and less proliferative 
	
	epithelial_cell = cell_defaults;
    // make sure the new cell type has its own reference phenotype
    epithelial_cell.parameters.pReference_live_phenotype = &( epithelial_cell.phenotype );
	epithelial_cell.type = cell_type_id;
	cell_type_id += 1;
	epithelial_cell.name = "epithelial cell";
    //epithelial_cell.phenotype.motility.is_motile = true;

	double p_time = parameters.doubles("motile_cell_persistence_time");
	double mot_speed = parameters.doubles("motile_cell_migration_speed");
	
    epithelial_cell.phenotype.motility.persistence_time = p_time;//3./60.;//parameters.doubles( "motile_cell_persistence_time" ); // 15.0; 
	epithelial_cell.phenotype.motility.migration_speed = mot_speed;//0.25;//parameters.doubles( "motile_cell_migration_speed" ); // 0.25 micron/minute 
	
	epithelial_cell.phenotype.motility.migration_bias = 1. - noise_factor;//0.1;// 1- noise_factor will go here
	//i'm plugging the bias update here 

	epithelial_cell.functions.update_migration_bias = boids_bias_change;
    epithelial_cell.functions.custom_cell_rule = motility_switch_function;
    //epithelial_cell.phenotype.geometry.radius = 6.0;
    
    
    // set division and apoptosis rate to zero
    epithelial_cell.phenotype.cycle.data.transition_rate( S_index , G0G1_index ) = 0.0;
    epithelial_cell.phenotype.cycle.data.transition_rate( G0G1_index , S_index ) = 0.0;
    epithelial_cell.phenotype.death.rates[apoptosis_model_index] = 0.0;
	
	//define wall cell
    
    wall_cell = cell_defaults;
	
	wall_cell.parameters.pReference_live_phenotype = &( wall_cell.phenotype );
    wall_cell.type = cell_type_id;
	wall_cell.name = "wall";
    cell_type_id +=1;
	//wall_cell.parameters.pReference_live_phenotype = &( wall_cell.phenotype ); 
    wall_cell.phenotype.motility.is_motile = false;
    //wall_cell.phenotype=NULL;//.secretion = NULL;
	//wall_cell.functions.cycle_model = NULL;
	wall_cell.phenotype.cycle.data.transition_rate( G0G1_index , S_index ) = 0.0;
	wall_cell.phenotype.cycle.data.transition_rate( S_index , G0G1_index ) = 0.0;
	wall_cell.phenotype.death.rates[apoptosis_model_index] = 0.0; 
	wall_cell.phenotype.death.rates[necrosis_model_index] = 0.0; 
    wall_cell.functions.update_phenotype = NULL;
	wall_cell.functions.custom_cell_rule = NULL;
	
	wall_cell.phenotype.mechanics.cell_cell_repulsion_strength *= relative_repulsion_strength;
	
	
	
	return; 
}

void setup_microenvironment( void )
{
	// set domain parameters 
	
/* now this is in XML 
	default_microenvironment_options.X_range = {-1000, 1000}; 
	default_microenvironment_options.Y_range = {-1000, 1000}; 
	default_microenvironment_options.simulate_2D = true; 
*/
	// make sure to override and go back to 2D 
	if( default_microenvironment_options.simulate_2D == false )
	{
		//std::cout << "Warning: overriding XML config option and setting to 2D!" << std::endl; 
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

// 7-cell hexagonal arrangement
/*
void setup_tissue( void )
{
	// create some cells near the origin
	
	Cell* pC;

	pC = create_cell(epithelial_cell);
	pC->assign_position( 0.0, 0.0, 0.0 );

	pC = create_cell(epithelial_cell);
	pC->assign_position( 2.0, 0, 0.0 );
	
	pC = create_cell(epithelial_cell);
	pC->assign_position( 1.0, 1.73205080757, 0.0 );
	
	pC = create_cell(epithelial_cell);
	pC->assign_position( -1.0, 1.73205080757, 0.0 );
    
    pC = create_cell(epithelial_cell);
    pC->assign_position( -2.0, 0, 0.0 );
    
    pC = create_cell(epithelial_cell);
    pC->assign_position( -1.0, -1.73205080757, 0.0 );
    
    pC = create_cell(epithelial_cell);
    pC->assign_position( 1.0, -1.73205080757, 0.0 );
    
    return; 
}
*/
 
void setup_tissue( void )
{
    Cell* pC;
    
    // hexagonal packing
    double x_min= microenvironment.mesh.bounding_box[0];
    double y_min= microenvironment.mesh.bounding_box[1];
    
    double x_max= microenvironment.mesh.bounding_box[3];
    double y_max= microenvironment.mesh.bounding_box[4];
	
	//begining and end of the wound:
	//double center = 0.5*(x_max - x_min);
	double init_wound = 0.1*x_min;
	double end_wound =  0.1*x_max;
    
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
            if( position[1] < y_min + 4*s || position[1] > y_max - 4*s )
			{
				pC = create_cell( wall_cell );
				pC->assign_position( position );
			}
			else if( position[0] < x_min + 4*s || position[0] > x_max - 4*s )
			{
				pC = create_cell( wall_cell );
				pC->assign_position( position );
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

std::vector<std::string> my_coloring_function( Cell* pCell )
{
	// start with flow cytometry coloring 
	
	std::vector<std::string> output = false_cell_coloring_cytometry(pCell); 
		
	if( pCell->phenotype.death.dead == false && pCell->type == 1 )
	{
		 output[0] = "red";
		 output[2] = "red";
	}
	
	return output; 
}

void motility_switch_function( Cell* pCell, Phenotype& phenotype, double dt )
{
	static int p_id = pCell->custom_data.find_variable_index( "pressure_threshold" ); 
	static int rel_id = pCell->custom_data.find_variable_index( "relative_adhesion_strength" ); 
	
	double p_tresh = pCell->custom_data[p_id];
	double rel_strength = pCell->custom_data[rel_id];
	
	
    if( pCell->state.simple_pressure < p_tresh && pCell->phenotype.motility.is_motile == false)
    {
		////std::cout << pCell->state.simple_pressure << std::endl;
        pCell->phenotype.motility.is_motile = true;

		pCell->phenotype.mechanics.cell_cell_adhesion_strength *= rel_strength;

    }
    return;
}


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
	////std::cout << self_v << std::endl;
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
	
	if( norm(aux) == 0)
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
	////std::cout << pCell->phenotype.motility.migration_bias_direction << std::endl;
    return;
}

