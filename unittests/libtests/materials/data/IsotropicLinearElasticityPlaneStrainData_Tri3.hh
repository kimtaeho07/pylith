// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

#if !defined(pylith_materials_isotropiclinearelasticityplanestraindata_tri3_hh)
#define pylith_materials_isotropiclinearelasticityplanestraindata_tri3_hh

#include "IsotropicLinearElasticityPlaneStrainData.hh"

namespace pylith {
  namespace materials {
    class IsotropicLinearElasticityPlaneStrainData_Tri3;
  } // pylith
} // materials

class pylith::materials::IsotropicLinearElasticityPlaneStrainData_Tri3 : public IsotropicLinearElasticityPlaneStrainData
{

public: 

  /// Constructor
  IsotropicLinearElasticityPlaneStrainData_Tri3(void);

  /// Destructor
  ~IsotropicLinearElasticityPlaneStrainData_Tri3(void);

private:

  static const char* _filenameMesh;
  static const char* _label;
  static const int _id;
  static const int _dimension;

  static const bool _useInertia;
  static const bool _useBodyForce;

  static const int _numSolnFields;
  static const pylith::topology::Field::DiscretizeInfo _solnDiscretizations[2];

  static const int _numAuxFields;
  static const char* _auxFields[3];
  static const pylith::topology::Field::DiscretizeInfo _auxDiscretizations[3];

  static const char* _filenameAuxFieldsDB;

  static const PetscPointFunc _kernelsRHSResidual[2*2];
  static const PetscPointJac _kernelsRHSJacobian[2*2*4];
  static const PetscPointFunc _kernelsLHSResidual[2*2];
  static const PetscPointJac _kernelsLHSJacobianImplicit[2*2*4];
  static const PetscPointJac _kernelsLHSJacobianExplicit[2*2*4];

  static const PylithReal _lengthScale;
  static const PylithReal _timeScale;
  static const PylithReal _densityScale;
  static const PylithReal _pressureScale;

};

#endif // pylith_materials_isotropiclinearelasticityplanestraindata_tri3_hh

// End of file