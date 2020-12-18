/*
 * Axial.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: raphael
 */

#include "Axial.hpp"

namespace HE
{
namespace Coord
{

Axial::Axial(int r, int q):data(r,q){};
Axial::Axial():data(0,0){};


int Axial::r() const {return std::get<0>(data);};
int Axial::q() const {return std::get<1>(data);};

int& Axial::r() {return std::get<0>(data);};
int& Axial::q() {return std::get<1>(data);};

// member operators
Axial Axial::operator+(const Axial& rhs) const {return Axial(r() + rhs.r(), q() + rhs.q());};
Axial& Axial::operator+=(const Axial& rhs){r()+=rhs.r() ; q() += rhs.q(); return *this;};

// friend operators
bool operator==(const Axial& lhs, const Axial& rhs){return operator==(lhs.data, rhs.data);};
bool operator!=(const Axial& lhs, const Axial& rhs){return operator!=(lhs.data, rhs.data);};

bool operator<(const Axial& lhs, const Axial& rhs){return operator<(lhs.data, rhs.data);};
bool operator>(const Axial& lhs, const Axial& rhs){return operator>(lhs.data, rhs.data);};
}
}


