#include "PROPOSAL/PROPOSAL.h"
#include <fstream>

using namespace PROPOSAL;

int main(){

    // particle
    auto mu_def = MuMinusDef();

    // open file containing muon energies
    std::string muon_energy_file = "thefile.txt";
    //std::ifstream infile(muon_energy_file);

    // build propagator
    std::string config_file = "/Users/alexwen/muon_propagator/resources/config_muon_rock.json";
    Propagator prop(mu_def, config_file);

    // specify the muon beam direction and position
    Cartesian3D position(0, 0, 0);
    Cartesian3D direction(0, 0, 1);

    std::vector<double> ranges;

    for (int i = 0; i < 5000; i++)
    {
        DECLARE energies[i]
        auto energy = 1e5; // MeV
        auto init_state = ParticleState(position, direction, energy, 0., 0.);

        auto track = prop.Propagate(init_state, 2000000); // distance to propagate in cm

        ranges.push_back(track.back().propagated_distance);

        std::cout << track.back().propagated_distance << std::endl;
    }

// ... Do stuff with ranges, e.g. plot histogram

}
