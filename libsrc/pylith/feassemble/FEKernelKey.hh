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
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

/**
 * @file libsrc/feassemble/FEKernelKey.hh
 *
 */

#if !defined(pylith_feassemble_fekernelkey_hh)
#define pylith_feassemble_fekernelkey_hh

#include "feassemblefwd.hh" // forward declarations

#include "pylith/utils/petscfwd.h" // HASA PetscDM
#include "pylith/topology/topologyfwd.hh" // USES Field

class pylith::feassemble::FEKernelKey {
    friend class TestFEKernelKey; // unit testing
    friend class TestInterfacePatches; // unit testing

    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Default constructor.
    FEKernelKey(void);

    /// Default destructor.
    ~FEKernelKey(void);

    /** Factory for creating FEKernelKeyGet starting point.
     *
     * @param[in] weakForm PETSc weak form object.
     * @param[in] name Name of label designating integration domain.
     * @param[in] value Value of label designating integration domain.
     * @param[in] field Name of solution subfield associated with integration kernels.
     *
     * @return Key for finite-element integration.
     */
    static
    FEKernelKey* create(PetscWeakForm weakForm,
                        const char* name,
                        const int value,
                        const char* field=NULL);

    /** Get PETSc weak form.
     *
     * @returns PETSc weak form object.
     */
    const PetscWeakForm getWeakForm(void) const;

    /** Get PETSc weak form key.
     *
     * @param[in] solution Solution field.
     * @param[in] field Name of solution subfield associated with integration kernel.
     *
     * @returns PETSc weak form key.
     */
    PetscFormKey petscKey(const pylith::topology::Field& solution,
                          const char* field=NULL) const;

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    PetscWeakForm _weakForm; ///< PETSc weak form object associated with integration key.
    std::string _name; ///< Name of label designating integration domain.
    std::string _field; ///< Name of solution subfield associated with integration kernels.
    int _value; ///< Value of label designating integration domain.

}; // FEKernelKey

#include "FEKernelKey.icc"

#endif // pylith_feassemble_fekernelkey_hh

// End of file
