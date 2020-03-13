// SWIG file KrigingAlgorithmImplementation.i

%{
#include "otgu/KrigingAlgorithmImplementation.hxx"
%}

%include KrigingAlgorithmImplementation_doc.i

%template(KrigingAlgorithmImplementationdInterfaceObject)           OT::TypedInterfaceObject<OTGU::KrigingAlgorithmImplementation>;

%include otgu/KrigingAlgorithmImplementation.hxx
namespace OTGU { %extend KrigingAlgorithmImplementation { KrigingAlgorithmImplementation(const KrigingAlgorithmImplementation & other) { return new OTGU::KrigingAlgorithmImplementation(other); } } }
