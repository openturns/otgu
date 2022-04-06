//                                               -*- C++ -*-
/**
 *  @brief The class builds generalized linear models
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
#ifndef OTGU_GENERALLINEARMODELALGORITHM_HXX
#define OTGU_GENERALLINEARMODELALGORITHM_HXX

#include "otgu/GeneralLinearModelResult.hxx"

#include "openturns/MetaModelAlgorithm.hxx"
#include "openturns/Basis.hxx"
#include "openturns/CovarianceModel.hxx"
#include "openturns/KrigingResult.hxx"
#include "openturns/HMatrix.hxx"
#include "openturns/OptimizationAlgorithm.hxx"

namespace OTGU {

/**
 * @class GeneralLinearModelAlgorithm
 *
 * The class building generalized linear model
 */
class OTGU_API GeneralLinearModelAlgorithm
  : public OT::MetaModelAlgorithm
{
  CLASSNAME

public:

  typedef GeneralLinearModelResult::BasisCollection BasisCollection;
  typedef GeneralLinearModelResult::BasisPersistentCollection BasisPersistentCollection;
  typedef enum {NONE, JOINTLYROBUST, REFERENCE, FLAT} ScalePrior;

  /** Default constructor */
  GeneralLinearModelAlgorithm();

  /** Parameters constructor */
  GeneralLinearModelAlgorithm (const OT::Sample & inputSample,
                               const OT::Sample & outputSample,
                               const OT::CovarianceModel & covarianceModel,
                               const OT::Bool keepCholeskyFactor = OT::ResourceMap::GetAsBool("GeneralLinearModelAlgorithm-KeepCovariance"));

  GeneralLinearModelAlgorithm (const OT::Sample & inputSample,
                               const OT::Sample & outputSample,
                               const OT::CovarianceModel & covarianceModel,
                               const OT::Basis & basis,
                               const OT::Bool keepCholeskyFactor = OT::ResourceMap::GetAsBool("GeneralLinearModelAlgorithm-KeepCovariance"));

  /** Parameters constructor */
  GeneralLinearModelAlgorithm (const OT::Sample & inputSample,
                               const OT::Sample & outputSample,
                               const OT::CovarianceModel & covarianceModel,
                               const BasisCollection & basisCollection,
                               const OT::Bool keepCholeskyFactor = OT::ResourceMap::GetAsBool("GeneralLinearModelAlgorithm-KeepCovariance"));

  /** Virtual constructor */
  GeneralLinearModelAlgorithm * clone() const;

  /** String converter */
  OT::String __repr__() const;

  /** Perform regression */
  void run();

  /** Sample accessors */
  OT::Sample getInputSample() const;
  OT::Sample getOutputSample() const;

  /** result accessor */
  OTGU::GeneralLinearModelResult getResult();

  /** Objective function (reduced log-Likelihood) accessor */
  OT::Function getObjectiveFunction();

  /** Optimization solver accessor */
  OT::OptimizationAlgorithm getOptimizationAlgorithm() const;
  void setOptimizationAlgorithm(const OT::OptimizationAlgorithm & solver);

  /** Optimization flag accessor */
  OT::Bool getOptimizeParameters() const;
  void setOptimizeParameters(const OT::Bool optimizeParameters);

  /** Accessor to optimization bounds */
  void setOptimizationBounds(const OT::Interval & optimizationBounds);
  OT::Interval getOptimizationBounds() const;

  /** Observation noise accessor */
  void setNoise(const OT::Point & noise);
  OT::Point getNoise() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:
  // Maximize the reduced log-likelihood
  OT::Scalar maximizeReducedLogLikelihood();

  // Compute the output log-likelihood function
  OT::Point computeReducedLogLikelihood(const OT::Point & parameters) const;
  OT::Scalar computeLapackLogDeterminantCholesky() const;
  OT::Scalar computeHMatLogDeterminantCholesky() const;

  // Compute the design matrix on the normalized input sample
  void computeF();

  // Normalize the input sample
  void normalizeInputSample();

  /** Method accessor (lapack/hmat) */
  void initializeMethod();
  void setMethod(const OT::UnsignedInteger method);
  OT::UnsignedInteger getMethod() const;

  /** reset method - If one change method */
  void reset();

  // Initialize default optimization solver
  void initializeDefaultOptimizationAlgorithm();

  // when the likelihood is integrated: log(\det{FtR^{-1}F})
  OT::Scalar correctIntegratedLikelihoodLogDeterminant() const;

  // If a prior is used, compute its value as a penalization term
  OT::Scalar computeLogIntegratedLikelihoodPenalization() const;

  friend class KrigingAlgorithm;
  OT::Point getRho() const;

  // Scale prior accessor
  ScalePrior getScalePrior() const;
  void setScalePrior(const ScalePrior likelihoodPrior);

private:

  // Helper class to compute the reduced log-likelihood function of the model
  class ReducedLogLikelihoodEvaluation: public OT::EvaluationImplementation
  {
  public:
    // Constructor from a GLM algorithm
    ReducedLogLikelihoodEvaluation(GeneralLinearModelAlgorithm & algorithm)
      : OT::EvaluationImplementation()
      , algorithm_(algorithm)
    {
      // Nothing to do
    }

    ReducedLogLikelihoodEvaluation * clone() const
    {
      return new ReducedLogLikelihoodEvaluation(*this);
    }

    // It is a simple call to the computeReducedLogLikelihood() of the algo
    OT::Point operator() (const OT::Point & point) const
    {
      const OT::Point value(algorithm_.computeReducedLogLikelihood(point));
      return value;
    }

    OT::UnsignedInteger getInputDimension() const
    {
      return algorithm_.getReducedCovarianceModel().getParameter().getDimension();
    }

    OT::UnsignedInteger getOutputDimension() const
    {
      return 1;
    }

    OT::Description getInputDescription() const
    {
      return algorithm_.getReducedCovarianceModel().getParameterDescription();
    }

    OT::Description getOutputDescription() const
    {
      return OT::Description(1, "ReducedLogLikelihood");
    }

    OT::Description getDescription() const
    {
      OT::Description description(getInputDescription());
      description.add(getOutputDescription());
      return description;
    }

    OT::String __repr__() const
    {
      OT::OSS oss;
      // Don't print algorithm_ here as it will result in an infinite loop!
      oss << "ReducedLogLikelihoodEvaluation";
      return oss;
    }

    OT::String __str__(const OT::String & offset) const
    {
      // Don't print algorithm_ here as it will result in an infinite loop!
      return OT::OSS() << offset << __repr__();
    }

  private:
    GeneralLinearModelAlgorithm & algorithm_;
  }; // ReducedLogLikelihoodEvaluation

  /** set sample  method */
  void setData(const OT::Sample & inputSample,
               const OT::Sample & outputSample);

  /** Covariance model accessor */
  void setCovarianceModel(const OT::CovarianceModel & covarianceModel);
  OT::CovarianceModel getCovarianceModel() const;
  OT::CovarianceModel getReducedCovarianceModel() const;

  /** Set basis collection method */
  void setBasisCollection(const BasisCollection & basisCollection);

  /** check that sample is centered to precison eps */
  void checkYCentered(const OT::Sample & Y);

  // The input data
  OT::Sample inputSample_;

  // Standardized version of the input data
  OT::Sample normalizedInputSample_;

  // The associated output data
  OT::Sample outputSample_;

  // The covariance model parametric familly
  OT::CovarianceModel covarianceModel_;
  mutable OT::CovarianceModel reducedCovarianceModel_;

  // The optimization algorithm used for the meta-parameters estimation
  mutable OT::OptimizationAlgorithm solver_;

  // Bounds used for parameter optimization
  OT::Interval optimizationBounds_;

  // The coefficients of the current output conditional expectation part
  mutable OT::Point beta_;
  // Temporarly used to compute gamma
  mutable OT::Point rho_;
  // The current output Gram matrix
  mutable OT::Matrix F_;

  /** Result */
  GeneralLinearModelResult result_;

  /** BasisCollection */
  BasisPersistentCollection basisCollection_;

  /** Cholesky factor ==>  TriangularMatrix */
  mutable OT::TriangularMatrix covarianceCholeskyFactor_;

  /** Cholesky factor when using hmat-oss */
  mutable OT::HMatrix covarianceCholeskyFactorHMatrix_;

  /** Boolean argument for keep covariance */
  OT::Bool keepCholeskyFactor_;

  /** Method : 0 (lapack), 1 (hmat) */
  OT::UnsignedInteger method_;

  /** Bool to tell if optimization has run */
  mutable OT::Bool hasRun_;

  /** Flag to tell if the parameters of the covariance model
      have to be optimized */
  OT::Bool optimizeParameters_;

  /** Observation noise */
  OT::Point noise_;

  /** Flag to tell if the amplitude parameters are estimated using an analytical derivation */
  OT::Bool analyticalAmplitude_;

  /** Cache of the last computed reduced log-likelihood */
  mutable OT::Scalar lastReducedLogLikelihood_;

  // scale prior
  ScalePrior scalePrior_;

}; // class GeneralLinearModelAlgorithm


END_NAMESPACE_OPENTURNS

#endif
