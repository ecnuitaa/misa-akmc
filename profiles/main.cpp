//
// Created by genshen on 2018/11/7.
//

#include <iostream>
#include <cmath>

#include <env.h>
#include <box.h>
#include <utils/random/random.h>
#include <kmc.h>


int main() {
    r::initSeed(); // initialize random number seed // todo generate seed here

    // set configuration
    env::global_env = env::environment{
            6E12, // attempt_freq 6*10^12 // todo too big
            773,  // temperature, K
            3.53, // ef110
            500,  // defect_gen_rate: 10^2 to 10^3
            env::energy{
                    // h
            }
    };

    //  build simulation box
    const _type_box_size box_x = 50;
    const _type_box_size box_y = 50;
    const _type_box_size box_z = 50;
    BoxBuilder builder{};
    builder.setBoxSize(box_x, box_y, box_z);
    Box *sim_box = builder.build();

    // generate lattice type
    sim_box->lattice_list->forAllLattices([](const _type_lattice_coord x,
                                             const _type_lattice_coord y,
                                             const _type_lattice_coord z,
                                             Lattice &lattice) {
        // set lattice types randomly.
        const LatticeTypes::lat_type src_types[] = {LatticeTypes::Fe, LatticeTypes::Cu,
                                                    LatticeTypes::Ni, LatticeTypes::Mn};
        const unsigned int ratio[] = {9866, 134, 0, 0}; // Fe 98.66% ,Cu 1.34%
        lattice.type._type = LatticeTypes::randomAtomsType(src_types, ratio, 4);
        return true;
    });

    // set defects type and defect list.
    struct DefectPosition {
        _type_lattice_coord x, y, z;
        LatticeTypes type;
    };
    std::vector<DefectPosition> defects = {
            DefectPosition{1, 1, 1, LatticeTypes{LatticeTypes::FeCu}},
            DefectPosition{20, 10, 10, LatticeTypes{LatticeTypes::FeCu}},
            DefectPosition{50, 25, 25, LatticeTypes{LatticeTypes::FeCu}},
            DefectPosition{5, 5, 5, LatticeTypes{LatticeTypes::V}},
            DefectPosition{12, 12, 12, LatticeTypes{LatticeTypes::V}},
            DefectPosition{50, 27, 23, LatticeTypes{LatticeTypes::V}},
    };
    for (DefectPosition def :defects) {
        Lattice &lat = sim_box->lattice_list->getLat(def.x, def.y, def.z);
        lat.type = def.type;
        if (def.type.isVacancy()) {
            sim_box->va_list->mp.insert(std::make_pair(lat.getId(), Vacancy{}));
        } else if (def.type.isDumbbell()) {
            Itl itl; // todo set orientation in constructor.
            itl.orient = {orientation::random()};
            sim_box->itl_list->mp.insert(std::make_pair(lat.getId(), itl));
        }
        // todo update avail_trans_dir, not in beforeRatesUpdate.
    }
    // todo update statistics values

    // start simulation
    double current_time = 0;
    const double total_time = 100;
    kmc kmc{sim_box}; // fixme init box pointer
    while (current_time < total_time) {
        const _type_rate total_rates = kmc.updateRates(env::global_env.attempt_freq, env::global_env.temperature);
        const event::SelectedEvent event = kmc.select(r::random() * total_rates, total_rates);
        if (event.event_type == event::DefectGen) {
            std::cout << "Defect generation." << std::endl;
        }
        kmc.execute(event);
        current_time += -log(r::random()) / total_rates;
        std::cout << "rate: " << total_rates << "; time: " << current_time << std::endl;
    }
    return 0;
}
