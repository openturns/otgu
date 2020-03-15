// SWIG file otgu_module.i

%module(docstring="otgu module") otgu

%{
#include <openturns/OT.hxx>
#include <openturns/PythonWrappingFunctions.hxx>
%}

// Prerequisites needed
%include typemaps.i
%include exception.i
%ignore *::load(OT::Advocate & adv);
%ignore *::save(OT::Advocate & adv) const;

%import base_module.i
%import uncertainty_module.i

// The new classes
%include otgu/OTGUprivate.hxx
%include GeneralLinearModelResult.i
%include GeneralLinearModelAlgorithm.i
%include KrigingAlgorithm.i


