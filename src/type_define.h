//
// Created by genshen on 2018/11/9.
//

#ifndef MISA_KMC_TYPE_DEFINE_H
#define MISA_KMC_TYPE_DEFINE_H

/**
 * the type of atom lattice position in cartesian coordinate system
 */
typedef unsigned long _type_box_size;
typedef unsigned long _type_atom_coord;
typedef _type_atom_coord _type_atom_size;
typedef unsigned long _type_atom_id;

typedef std::pair<_type_atom_coord, std::pair<_type_atom_coord, _type_atom_coord> > _type_atom_pair;

/*!
 * \brief the type of transition rate
 */
typedef double _type_rate;

/*!
 * the number of all the lattices
 */
#define MAX_X 100
#define MAX_Y 100
#define MAX_Z 100

#endif //MISA_KMC_TYPE_DEFINE_H
