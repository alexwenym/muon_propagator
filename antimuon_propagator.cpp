#include "PROPOSAL/PROPOSAL.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace PROPOSAL;
using namespace std;

int main(int argc, char *argv[]){

    // particle
    auto mu_def = MuPlusDef();
    cout << "Propagating MuPlus..." << endl; 

    // open file containing muon energies
    std::string LI_data_file(argv[1]);
    // below are some hard-coded example input files
    //std::string LI_data_file = "../LI_NuMu_yColumnDepthInjection.txt";
    //std::string LI_data_file = "../testfile.txt";
    std::ifstream infile(LI_data_file);
    
    // output file
    std::string output_data_file = LI_data_file; 
    output_data_file.insert(output_data_file.size()-4, "_propagated"); 
    std::ofstream outfile;
    outfile.open(output_data_file);

    // build propagator
    // full muon config, with continuous (multiple scattering) AND stochastic energy losses
    std::string config_file = "/Users/alexwen/muon_propagator/resources/config_muon_rock.json";
    // simple case, for testing
    //std::string config_file = "/Users/alexwen/muon_propagator/resources/config_minimal_rock.json";

    Propagator prop(mu_def, config_file);

    // specify the muon beam direction and position
    
    std::vector<double> ranges;

    std::string line; 
    while (std::getline(infile, line)){

        std::istringstream iss(line); 
        // skip comment lines
        if (line[0] == '#') {
            line.insert(line.size()-2, " mu_propagated_dist vtx_dist_to_detector E_mu_at_detector"); 
            outfile << line << endl; 
            continue; 
        } 
        
        double E_nu, E_X, E_l, Pl_x, Pl_y, Pl_z, vtx_x, vtx_y, vtx_z; 
        if (!(iss >> E_nu >> E_X >> E_l >> Pl_x >> Pl_y >> Pl_z >> vtx_x >> vtx_y >> vtx_z)) {
            cout << "ERROR! problematic line, terminated early. Line below: " << endl; 
            cout << line << endl; 
            break;}
        
        // important: read-in inputs from LI are in m, GeV. Must convert to cm/MeV for PROPOSAL

        Cartesian3D position(0, 0, 0);
        Cartesian3D direction(Pl_x, Pl_y, Pl_z);
        Cartesian3D positionRelToDetector(vtx_x*100, vtx_y*100, vtx_z*100);
        double dist_to_detector = positionRelToDetector.magnitude();

        auto init_state = ParticleState(position, direction, E_l*1000, 0., 0.);
        auto track = prop.Propagate(init_state, 3000000);

        double propagated_distance = track.back().propagated_distance ;

        auto state_at_detector = track.GetStateForDistance( dist_to_detector );
        double energy_at_detector = state_at_detector.energy ;

        // just for debugging
        //cout << propagated_distance/100 << " "<< dist_to_detector/100 << " " << energy_at_detector/1000 << endl; 

        // save to output file
        outfile << E_nu << " " << E_X << " " << E_l << " " 
        << Pl_x << " " << Pl_y << " " << Pl_z << " " 
        << vtx_x << " " << vtx_y << " " << vtx_z << " "
        << propagated_distance/100 << " " << dist_to_detector/100 << " " << energy_at_detector/1000 << " "
        << 1.0 << endl; 

    }

    cout << "Done propagating. File saved to " << output_data_file << "." << endl; 

    // ... Do stuff with ranges, e.g. plot histogram
    outfile.close();

}
