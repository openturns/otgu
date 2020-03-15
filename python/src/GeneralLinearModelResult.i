// SWIG file GeneralLinearModelResult.i

%{
#include "otgu/GeneralLinearModelResult.hxx"
namespace OT {
template <>
  struct traitsPythonType< OT::Basis >
  {
    typedef _PyObject_ Type;
  };

template <>
  inline
  bool
  canConvert< _PyObject_, OT::Basis >(PyObject * pyObj)
  {
    void * ptr = 0;
    if (SWIG_IsOK(SWIG_ConvertPtr(pyObj, &ptr, SWIGTYPE_p_OT__Basis, 0))) {
      OT::Basis * p_nmf = reinterpret_cast< OT::Basis * >(ptr);
      return p_nmf != NULL;
    } else if (SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIGTYPE_p_OT__BasisImplementation, 0 ))) {
      OT::BasisImplementation * p_impl = reinterpret_cast< OT::BasisImplementation * >(ptr);
      return p_impl != NULL;
    }
    // Case of Collection<NMF>?
    return false;
  }

template <>
  inline
  OT::Basis
  convert< _PyObject_, OT::Basis >(PyObject * pyObj)
  {
    void * ptr = 0;
    if (SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIGTYPE_p_OT__Basis, 0)))
    {
      OT::Basis * p_nmf = reinterpret_cast< OT::Basis * >(ptr);
      return *p_nmf;
    }
    else if (SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIGTYPE_p_OT__BasisImplementation, 0)))
    {
      OT::BasisImplementation * p_impl = reinterpret_cast< OT::BasisImplementation * >(ptr);
      return *p_impl;
    }
    // Case of Collection<NMF>?
    throw OT::NotYetImplementedException(HERE) << "convert< _PyObject_, OT::Basis >"; 
  }
}
%}

%include GeneralLinearModelResult_doc.i

%include otgu/GeneralLinearModelResult.hxx

namespace OTGU{ %extend GeneralLinearModelResult { GeneralLinearModelResult(const GeneralLinearModelResult & other) { return new OTGU::GeneralLinearModelResult(other); } } }


