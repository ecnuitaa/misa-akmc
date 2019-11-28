//
// Created by genshen on 2018-12-12.
//

#ifndef MISA_KMC_KMC_H
#define MISA_KMC_KMC_H

#include <models/model_adapter.h>
#include "type_define.h"
#include "box.h"
#include "event.h"
#include "plugin/event_listener.h"

/*!
 * \brief the main routine of KMC simulation.
 */
class ABVIModel : public ModelAdapter {

public:
    /**
     * \brief initialize kmc with simulation box.
     */
    explicit ABVIModel(Box *box);

    /**
     * \brief calculate the transition rates of each lattice.
     *
     * The calculating methods depends on the lattice type(single atom, vacancy and dumbbell).
     * Different types of lattice have different methods or formulas to calculate the rate.
     * see the implementation for more details.
     *
     * After this step, the rate of every transition direction of each lattice will be set.
     * \return return the sum of rates of all KMC events,
     * including dumbbell transition and vacancy transition and defect generation).
     */
    _type_rate calcRates(double v, double T);

    _type_rate calcRates(const comm::Region<comm::_type_lattice_size> region) override {}; // todo

    /**
     * \brief select an event randomly from rates list.
     *
     * \param excepted_rate which equals to total rate* random number between 0-1.
     * \param total_rates the sum rates
     * \return the selected event.
     */
    event::SelectedEvent select(const double excepted_rate, const _type_rate sum_rates);

    void selectRate() override {}; // todo

    /**
     * \brief perform the selected KMC event.
     *
     */
    void perform(const event::SelectedEvent selected);

    void perform() override {}; // todo

    /**
     * \brief set kmc event listener.
     * \param p_listener pointer to the event listener.
     */
    void setEventListener(EventListener *p_listener);

    unsigned long defectSize() override;

protected:
    double time = 0;

private:
    Box *box = nullptr; // todo init box pointer

    /**
     * \brief pointer to event listener.
     * event callback function will be called when executing a kmc event.
     */
    EventListener *p_event_listener = nullptr;

    /**
     * \brief it returns the rate of defect generation.
     * \return
     */
    _type_rate defectGenRate();
};


#endif //MISA_KMC_KMC_H
