#ifndef SimTK_SIMBODY_HUNT_CROSSLEY_FORCE_IMPL_H_
#define SimTK_SIMBODY_HUNT_CROSSLEY_FORCE_IMPL_H_
/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simbody(tm)                         *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "SimTKcommon.h"
#include "simbody/internal/common.h"
#include "simbody/internal/ElasticFoundationForce.h"
#include "ForceImpl.h"

namespace SimTK {

class ElasticFoundationForceImpl : public ForceImpl {
public:
    class Parameters;
    ElasticFoundationForceImpl(GeneralContactSubsystem& subystem, ContactSetIndex set, int meshIndex);
    ElasticFoundationForceImpl* clone() const {
        return new ElasticFoundationForceImpl(*this);
    }
    void calcForce(const State& state, Vector_<SpatialVec>& bodyForces, Vector_<Vec3>& particleForces, Vector& mobilityForces) const;
    Real calcPotentialEnergy(const State& state) const;
    void realizeTopology(State& state) const;
private:
    friend class ElasticFoundationForce;
    const GeneralContactSubsystem& subsystem;
    const ContactSetIndex set;
    const int meshIndex;
    std::vector<Vec3> springPosition;
    std::vector<UnitVec3> springNormal;
    std::vector<Real> springArea;
    Real young, poisson, thickness;
    Real transitionVelocity;
    mutable int energyCacheIndex;
};

} // namespace SimTK

#endif // SimTK_SIMBODY_HUNT_CROSSLEY_FORCE_IMPL_H_