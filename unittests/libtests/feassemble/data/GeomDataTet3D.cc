// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include "GeomDataTet3D.hh"

const int pylith::feassemble::GeomDataTet3D::_cellDim = 3;

const int pylith::feassemble::GeomDataTet3D::_spaceDim = 3;

const int pylith::feassemble::GeomDataTet3D::_numCorners = 4;

const int pylith::feassemble::GeomDataTet3D::_numLocs = 2;

const double pylith::feassemble::GeomDataTet3D::_vertices[] = {
  -1.3, -0.8, 0.2,
  2.1, -0.7, 0.1,
  -1.0, 2.4, -0.3,
  -0.1, 0.2, 3.0
};

const double pylith::feassemble::GeomDataTet3D::_locations[] = {
  0.345, 0.397, 0.319,
  0.459, 0.727, 0.693
};

const double pylith::feassemble::GeomDataTet3D::_jacobian[] = {
  3.4, 0.3, 1.2, 0.1, 3.2, 1.0, -0.1, -0.5, 2.8,
  3.4, 0.3, 1.2, 0.1, 3.2, 1.0, -0.1, -0.5, 2.8
};

const double pylith::feassemble::GeomDataTet3D::_jacobianDet[] = {
  32.374,
  32.374
};

pylith::feassemble::GeomDataTet3D::GeomDataTet3D(void)
{ // constructor
  cellDim = _cellDim;
  spaceDim = _spaceDim;
  numCorners = _numCorners;
  numLocs = _numLocs;
  vertices = const_cast<double*>(_vertices);
  locations = const_cast<double*>(_locations);
  jacobian = const_cast<double*>(_jacobian);
  jacobianDet = const_cast<double*>(_jacobianDet);
} // constructor

pylith::feassemble::GeomDataTet3D::~GeomDataTet3D(void)
{}


// End of file
