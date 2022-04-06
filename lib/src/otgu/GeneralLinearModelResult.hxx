//                                               -*- C++ -*-
/**
 *  @brief The result of a linear model estimation
 *
 *  Copyright 2005-2020 Airbus-EDF-IMACS-ONERA-Phimeca
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
#ifndef OTGU_GENERALLINEARMODELRESULT_HXX
#define OTGU_GENERALLINEARMODELRESULT_HXX

#include "otgu/OTGUprivate.hxx"

#include "openturns/MetaModelResult.hxx"
#include "openturns/CovarianceModel.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Collection.hxx"
#include "openturns/PersistentCollection.hxx"
#include "openturns/Basis.hxx"
#include "openturns/Function.hxx"
#include "openturns/Process.hxx"
#include "openturns/HMatrix.hxx"
#include "openturns/Basis.hxx"

// BEGIN_NAMESPACE_OPENTURNS
namespace OTGU {

/**
 * @class GeneralLinearModelResult
 *
 * The result of a generalized linear model evaluation
 */

class OTGU_API GeneralLinearModelResult
  : public OT::MetaModelResult
{
  CLASSNAME

public:

  typedef OT::Collection<OT::Point> PointCollection;
  typedef OT::PersistentCollection<OT::Point> PointPersistentCollection;
  typedef OT::Collection<OT::Basis> BasisCollection;
  typedef OT::PersistentCollection<OT::Basis> BasisPersistentCollection;

  /** Default constructor */
  GeneralLinearModelResult();

  /** Parameter constructor without any cholesky factor*/
  GeneralLinearModelResult(const OT::Sample & inputData,
                           const OT::Sample & outputData,
                           const OT::Function & metaModel,
                           const OT::Point & residuals,
                           const OT::Point & relativeErrors,
                           const BasisCollection & basis,
                           const PointCollection & trendCoefficients,
                           const OT::CovarianceModel & covarianceModel,
                           const OT::Scalar optimalLogLikelihood);

  /** Parameter constructor with Cholesky factor (Lapack)*/
  GeneralLinearModelResult(const OT::Sample & inputData,
                           const OT::Sample & outputData,
                           const OT::Function & metaModel,
                           const OT::Point & residuals,
                           const OT::Point & relativeErrors,
                           const BasisCollection & basis,
                           const PointCollection & trendCoefficients,
                           const OT::CovarianceModel & covarianceModel,
                           const OT::Scalar optimalLogLikelihood,
                           const OT::TriangularMatrix & covarianceCholeskyFactor,
                           const OT::HMatrix & covarianceHMatrix);

  /** Virtual constructor */
  GeneralLinearModelResult * clone() const;

  /** String converter */
  OT::String __repr__() const;
  OT::String __str__(const OT::String & offset = "") const;

  /** Trend basis accessor */
  BasisCollection getBasisCollection() const;

  /** Trend coefficients accessor */
  PointCollection getTrendCoefficients() const;

  /** Conditional covariance models accessor */
  OT::CovarianceModel getCovarianceModel() const;

  /** process accessor */
  OT::Process getNoise() const;

  /** Optimal likelihood accessor */
  OT::Scalar getOptimalLogLikelihood() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);


protected:

  // KrigingAlgorithm::run could ask for the Cholesky factor
  friend class KrigingAlgorithm;
  /** Method that returns the covariance factor - lapack */
  OT::TriangularMatrix getCholeskyFactor() const;

  /** Method that returns the covariance factor - hmat */
  OT::HMatrix getHMatCholeskyFactor() const;

private:

  /** inputData should be keeped*/
  OT::Sample inputData_;

  /** The trend basis */
  BasisPersistentCollection basis_;

  /** The trend coefficients */
  PointPersistentCollection beta_;

  /** The covariance model */
  OT::CovarianceModel covarianceModel_;

  /** The optimal log-likelihood value */
  OT::Scalar optimalLogLikelihood_;

  /** Boolean for cholesky. */
  OT::Bool hasCholeskyFactor_;

  /** Cholesky factor  */
  mutable OT::TriangularMatrix covarianceCholeskyFactor_;

  /** Cholesky factor when using hmat-oss/hmat */
  mutable OT::HMatrix covarianceHMatrix_;

} ; /* class GeneralLinearModelResult */


END_NAMESPACE_OPENTURNS

#endif /* OTGU_KRIGINGRESULT_HXX */
