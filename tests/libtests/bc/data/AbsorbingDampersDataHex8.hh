// =================================================================================================
// This code is part of PyLith, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/pylith).
//
// Copyright (c) 2010-2023, University of California, Davis and the PyLith Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information. 
// =================================================================================================

    /// Constructor
    AbsorbingDampersDataHex8(void);

    /// Destructor
    ~AbsorbingDampersDataHex8(void);

private:

    static const char* _meshFilename;

    static const int _numBasis;
    static const int _numQuadPts;
    static const PylithScalar _quadPts[];
    static const PylithScalar _quadWts[];
    static const PylithScalar _basis[];
    static const PylithScalar _basisDerivRef[];

    static const char* _spatialDBFilename;
    static const int _id;
    static const char* _label;

    static const PylithScalar _dt;
    static const PylithScalar _fieldTIncr[];
    static const PylithScalar _fieldT[];
    static const PylithScalar _fieldTmdt[];

    static const int _spaceDim;
    static const int _cellDim;
    static const int _numVertices;
    static const int _numCells;
    static const int _numCorners;
    static const int _cells[];

    static const PylithScalar _dampingConsts[];
    static const PylithScalar _valsResidual[];
    static const PylithScalar _valsJacobian[];

};

#endif // pylith_bc_absorbingdampersdatahex8_hh

// End of file
