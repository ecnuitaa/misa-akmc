//
// Created by runchu on 2019-09-24.
//

#ifndef MISA_KMC_SIMULATION_H
#define MISA_KMC_SIMULATION_H

#include <mpi.h>
#include <cstring>
#include <io/io_writer.h>
#include <comm/domain/colored_domain.h>

#include "lattice/period_lattice_list.h"
#include "abvi/box.h"

class simulation {
public:

    simulation() = default;

    //virtual ~simulation();

    /**
     * Denote N as the count of all processors.
     * {@memberof domainDecomposition} will divide the simulation box into N parts,
     * we call each part as a sub-box.
     * And each sub-box will bind to a processor.
     * @param phase_space the lattice count in each dimension.
     * @param lattice_const lattice constance
     * @param cutoff_radius cutoff radius factor = cutoff/lattice_const
     */
    void createDomain(const unsigned long phase_space[comm::DIMENSION_SIZE],
                      const double lattice_const, const double cutoff_radius);

    /**
     * \brief allocate memory for lattice list with ghost regions, and set ids for each lattice site.
     * \note the lattice types are not set here.
     */
    void createLattice();

    /**
     * Initialize ghost area for starting simulation.
     */
    void prepareForStart();

    /**
     * \brief perform simulation.
     * \param time_limit the max simulation time.
     */
    void simulate(const double time_limit);

public:
    Box *box = nullptr;
    comm::ColoredDomain *_p_domain = nullptr;
};


#endif //MISA_KMC_SIMULATION_H