// SWIG file GeneralLinearModelAlgorithm.i

%{
#include "otgu/GeneralLinearModelAlgorithm.hxx"
%}

%include GeneralLinearModelAlgorithm_doc.i

%include otgu/GeneralLinearModelAlgorithm.hxx

namespace OTGU{ %extend GeneralLinearModelAlgorithm { GeneralLinearModelAlgorithm(const GeneralLinearModelAlgorithm & other) { return new OTGU::GeneralLinearModelAlgorithm(other); } } }

