// SWIG file KrigingAlgorithm.i

%{
#include "otgu/KrigingAlgorithm.hxx"
%}

%include KrigingAlgorithm_doc.i

%include otgu/KrigingAlgorithm.hxx

namespace OTGU{ %extend KrigingAlgorithm { KrigingAlgorithm(const KrigingAlgorithm & other) { return new OTGU::KrigingAlgorithm(other); } } }
