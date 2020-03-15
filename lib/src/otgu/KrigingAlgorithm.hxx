//                                               -*- C++ -*-
/**
 *  @brief The class building gaussian process regression
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
#ifndef OTGU_KRIGINGALGORITHM_HXX
#define OTGU_KRIGINGALGORITHM_HXX

#include "otgu/GeneralLinearModelAlgorithm.hxx"

#include "openturns/MetaModelAlgorithm.hxx"
#include "openturns/Basis.hxx"
#include "openturns/CovarianceModel.hxx"
#include "openturns/KrigingResult.hxx"
#include "openturns/HMatrix.hxx"

//BEGIN_NAMESPACE_OPENTURNS
namespace OTGU {

/**
 * @class KrigingAlgorithm
 *
 * The class building kriging process, relying on generalized linear model class (GeneralLinearModelAlgorithm)
 * for the evaluation of the coefficients of the parameters.
 */

class OTGU_API KrigingAlgorithm
  : public OT::MetaModelAlgorithm
{
  CLASSNAME

public:

  typedef OT::KrigingResult::BasisCollection BasisCollection;
  typedef OT::KrigingResult::BasisPersistentCollection BasisPersistentCollection;
  typedef GeneralLinearModelAlgorithm::ScalePrior ScalePrior;

  /** Default constructor */
  KrigingAlgorithm();

  /** Constructor */
  KrigingAlgorithm (const OT::Sample & inputSample,
                    const OT::Sample & outputSample,
                    const OT::CovarianceModel & covarianceModel,
                    const OT::Basis & basis,
                    const OT::Bool normalize = true);

  /** Constructor */
  KrigingAlgorithm (const OT::Sample & inputSample,
                    const OT::Sample & outputSample,
                    const OT::CovarianceModel & covarianceModel,
                    const BasisCollection & basisCollection,
                    const OT::Bool normalize = true);

  /** Virtual constructor */
  KrigingAlgorithm * clone() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Perform regression */
  void run();

  /** Sample accessors */
  OT::Sample getInputSample() const;
  OT::Sample getOutputSample() const;

  /** result accessor */
  OT::KrigingResult getResult();

  /** Optimization solver accessor */
  OT::OptimizationAlgorithm getOptimizationAlgorithm() const;
  void setOptimizationAlgorithm(const OT::OptimizationAlgorithm & solver);

  /** Accessor to optimization bounds */
  void setOptimizationBounds(const OT::Interval & optimizationBounds);
  OT::Interval getOptimizationBounds() const;

  /** Log-Likelihood function accessor */
  OT::Function getReducedLogLikelihoodFunction();

  /** Optimization flag accessor */
  OT::Bool getOptimizeParameters() const;
  void setOptimizeParameters(const OT::Bool optimizeParameters);

  /** Observation noise accessor */
  void setNoise(const OT::Point & noise);
  OT::Point getNoise() const;

  /** Linear algebra method */
  void setMethod(const OT::String & method);
  OT::String getMethod() const;

  /** Scale prior accessor */
  ScalePrior getScalePrior() const;
  void setScalePrior(const ScalePrior likelihoodPrior);

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);


protected:

  /** The method helps to compute the gamma point */
  void computeGamma();

private:

  // The input data
  OT::Sample inputSample_;
  // The associated output data
  OT::Sample outputSample_;
  OT::Bool normalize_;
  // The covariance model parametric family
  OT::CovarianceModel covarianceModel_;
  // Underlying algo used for the evaluation of parameters
  GeneralLinearModelAlgorithm glmAlgo_;
  // The coefficients of the current output deterministic trend
  mutable OT::Point gamma_;
  // Temporarly used to compute gamma
  mutable OT::Point rho_;

  /** Result */
  OT::KrigingResult result_;

  /** Cholesky factor ==>  TriangularMatrix */
  mutable OT::TriangularMatrix covarianceCholeskyFactor_;

  /** Cholesky factor when using hmat-oss */
  mutable OT::HMatrix covarianceCholeskyFactorHMatrix_;

}; // class KrigingAlgorithm


END_NAMESPACE_OPENTURNS

#endif
