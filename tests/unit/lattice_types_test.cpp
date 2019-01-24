//
// Created by genshen on 2018/11/13.
//

#include <gtest/gtest.h>
#include <lattice/lattice_types.h>

TEST(lattice_type_test_case1, lattice_type_test) {
    LatticeTypes type(LatticeTypes::Fe);
    EXPECT_EQ(type.isAtom(), true);
    EXPECT_EQ(type.isDumbbell(), false);

    LatticeTypes type2(LatticeTypes::FeFe);
    EXPECT_EQ(type2.isAtom(), false);
    EXPECT_EQ(type2.isDumbbell(), true);

    LatticeTypes type3(LatticeTypes::V);
    EXPECT_EQ(type3.isAtom(), false);
    EXPECT_EQ(type3.isDumbbell(), false);
}

TEST(lattice_type_combineToInter_test, lattice_type_test) {
    auto tp_new = LatticeTypes::combineToInter(LatticeTypes::Fe, LatticeTypes::Cu);
    EXPECT_EQ(tp_new, LatticeTypes::FeCu);

    auto tp_new2 = LatticeTypes::combineToInter(LatticeTypes::Cu, LatticeTypes::Fe);
    EXPECT_EQ(tp_new2, LatticeTypes::FeCu);

    auto tp_new3 = LatticeTypes::combineToInter(LatticeTypes::Mn, LatticeTypes::Mn);
    EXPECT_EQ(tp_new3, LatticeTypes::MnMn);

    auto tp_new4 = LatticeTypes::combineToInter(LatticeTypes::Cu, LatticeTypes::Mn);
    EXPECT_EQ(tp_new4, LatticeTypes::CuMn);
}

TEST(lattice_type_getHighLowEnd_test, lattice_type_test) {
    LatticeTypes type1(LatticeTypes::FeCu);
    EXPECT_EQ(type1.getHighEnd(), LatticeTypes::Fe);
    EXPECT_EQ(type1.getLowEnd(), LatticeTypes::Cu);

    LatticeTypes type2(LatticeTypes::Cu);
    EXPECT_EQ(type2.getHighEnd(), LatticeTypes::V);
    EXPECT_EQ(type2.getLowEnd(), LatticeTypes::Cu);

    LatticeTypes type3(LatticeTypes::V);
    EXPECT_EQ(type3.getHighEnd(), LatticeTypes::V);
    EXPECT_EQ(type3.getLowEnd(), LatticeTypes::V);
}

TEST(lattice_type_FirstSecondAtom_test, lattice_type_test) {
    LatticeTypes type1(LatticeTypes::FeCu);
    EXPECT_EQ(type1.getFirst(true), LatticeTypes::Fe);
    EXPECT_EQ(type1.getSecond(true), LatticeTypes::Cu);

    EXPECT_EQ(type1.getFirst(false), LatticeTypes::Cu);
    EXPECT_EQ(type1.getSecond(false), LatticeTypes::Fe);


    LatticeTypes type3(LatticeTypes::CuCu);
    EXPECT_EQ(type3.getFirst(true), LatticeTypes::Cu);
    EXPECT_EQ(type3.getSecond(true), LatticeTypes::Cu);
    EXPECT_EQ(type3.getFirst(false), LatticeTypes::Cu);
    EXPECT_EQ(type3.getSecond(false), LatticeTypes::Cu);
}

TEST(lattice_type_diff_test, lattice_type_test) {
    LatticeTypes type1(LatticeTypes::FeCu);
    LatticeTypes type2(LatticeTypes::Cu);
    EXPECT_EQ(type1.diff(type2), LatticeTypes::Fe);

    LatticeTypes type3(LatticeTypes::V);
    EXPECT_EQ(type1.diff(type3), LatticeTypes::FeCu);

    LatticeTypes type4(LatticeTypes::Ni);
    EXPECT_EQ(type1.diff(type4), LatticeTypes::FeCu);
}