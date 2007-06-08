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

/**
 * @file pylith/feassemble/GeometryQuad2D.hh
 *
 * @brief C++ implementation of cell geometry calculations for 2-D
 * quadrilateral cell.
 */

#if !defined(pylith_feassemble_geometryquad2d_hh)
#define pylith_feassemble_geometryquad2d_hh

#include "CellGeometry.hh" // ISA CellGeometry

namespace pylith {
  namespace feassemble {
    class GeometryQuad2D;
  } // feassemble
} // pylith

class pylith::feassemble::GeometryQuad2D : public CellGeometry
{ // GeometryQuad2D

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
  
  /// Default constructor.
  GeometryQuad2D(void);

  /// Default destructor.
  ~GeometryQuad2D(void);

  /** Create a copy of geometry.
   *
   * @returns Copy of geometry.
   */
  CellGeometry* clone(void) const;

  /** Get cell geometry for lower dimension cell.
   *
   * @returns Pointer to cell geometry object corresponding to next
   * lower dimension, NULL if there is no lower dimension object.
   */
  CellGeometry* geometryLowerDim(void) const;

  /** Compute Jacobian at location in cell.
   *
   * @param jacobian Jacobian at location.
   * @param det Determinant of Jacobian at location.
   * @param vertices Coordinates of vertices of cell.
   * @param location Location in reference cell at which to compute Jacobian.
   */
  void jacobian(double_array* jacobian,
		double* det,
		const double_array& vertices,
		const double_array& location) const;

// PROTECTED ////////////////////////////////////////////////////////////
protected :

  /** Copy constructor.
   *
   * @param g Geometry to copy.
   */
  GeometryQuad2D(const GeometryQuad2D& g);

}; // GeometryQuad2D

#endif // pylith_feassemble_geometryquad2d_hh


// End of file
