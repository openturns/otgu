//                                               -*- C++ -*-
/**
 *  @brief KrigingAlgorithm
 *
 *  Copyright 2005-2019 Airbus-EDF-IMACS-ONERA-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OTGU_KRIGINGALGORITHM_HXX
#define OTGU_KRIGINGALGORITHM_HXX

#include <openturns/TypedInterfaceObject.hxx>
#include <openturns/StorageManager.hxx>
#include <openturns/Point.hxx>
#include "otgu/OTGUprivate.hxx"

namespace OTGU
{

/* forward declaration */
class KrigingAlgorithmImplementation;

/**
 * @class KrigingAlgorithm
 *
 * KrigingAlgorithm is some krigingalgorithm type to illustrate how to add some classes in Open TURNS
 */
class OTGU_API KrigingAlgorithm
  : public OT::TypedInterfaceObject<KrigingAlgorithmImplementation>
{
  CLASSNAME;

public:

  /** Default constructor */
  KrigingAlgorithm();

  /** Constructor from implementation */
  KrigingAlgorithm(const KrigingAlgorithmImplementation & implementation);

  /** a func that return a point squared. **/
  OT::Point square(OT::Point & p) const;

  /** String converter */
  OT::String __repr__() const;

private:

}; /* class KrigingAlgorithm */

} /* namespace OTGU */

#endif /* OTGU_KRIGINGALGORITHM_HXX */
