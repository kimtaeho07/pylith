// -*- C++ -*-
//
// ----------------------------------------------------------------------
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
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestDataWriterVTKSubmesh.hh" // Implementation of class methods

#include "pylith/topology/Mesh.hh" // USES Mesh
#include "pylith/topology/Field.hh" // USES Field
#include "pylith/meshio/DataWriterVTK.hh" // USES DataWriterVTK
#include "pylith/meshio/OutputSubfield.hh" // USES OutputSubfield

// ----------------------------------------------------------------------
// Setup testing data.
void
pylith::meshio::TestDataWriterVTKSubmesh::setUp(void) {
    PYLITH_METHOD_BEGIN;

    TestDataWriterSubmesh::setUp();
    _data = NULL;

    PYLITH_METHOD_END;
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
void
pylith::meshio::TestDataWriterVTKSubmesh::tearDown(void) {
    PYLITH_METHOD_BEGIN;

    TestDataWriterSubmesh::tearDown();
    delete _data;_data = NULL;

    PYLITH_METHOD_END;
} // tearDown


// ----------------------------------------------------------------------
// Test openTimeStep() and closeTimeStep()
void
pylith::meshio::TestDataWriterVTKSubmesh::testTimeStep(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_submesh);
    CPPUNIT_ASSERT(_data);

    DataWriterVTK writer;

    writer.filename(_data->timestepFilename);
    writer.timeFormat(_data->timeFormat);

    CPPUNIT_ASSERT_EQUAL(false, writer._wroteVertexHeader);
    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);

    const PylithScalar t = _data->time;
    const bool isInfo = false;
    writer.open(*_submesh, isInfo);
    writer.openTimeStep(t, *_submesh);

    CPPUNIT_ASSERT_EQUAL(false, writer._wroteVertexHeader);
    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);

    writer.closeTimeStep();
    writer.close();

    CPPUNIT_ASSERT_EQUAL(false, writer._wroteVertexHeader);
    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);

    // Nothing to check. We do not create VTK files without fields anymore.

    PYLITH_METHOD_END;
} // testTimeStep


// ----------------------------------------------------------------------
// Test writeVertexField.
void
pylith::meshio::TestDataWriterVTKSubmesh::testWriteVertexField(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_mesh);
    CPPUNIT_ASSERT(_submesh);
    CPPUNIT_ASSERT(_data);

    DataWriterVTK writer;

    pylith::topology::Field vertexField(*_mesh);
    _createVertexField(&vertexField);

    writer.filename(_data->vertexFilename);
    writer.timeFormat(_data->timeFormat);

    const PylithScalar t = _data->time;
    const bool isInfo = false;
    writer.open(*_submesh, isInfo);
    writer.openTimeStep(t, *_submesh);

    const pylith::string_vector& subfieldNames = vertexField.subfieldNames();
    const size_t numFields = subfieldNames.size();
    for (size_t i = 0; i < numFields; ++i) {
        const FieldFilter* filter = NULL;
        OutputSubfield* subfield = OutputSubfield::create(vertexField, subfieldNames[i].c_str(), filter, _submesh);
        CPPUNIT_ASSERT(subfield);
        subfield->extract(vertexField.outputVector());
        writer.writeVertexField(t, *subfield);
        CPPUNIT_ASSERT(writer._wroteVertexHeader);
        CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);
        delete subfield;subfield = NULL;
    } // for
    writer.closeTimeStep();
    writer.close();

    CPPUNIT_ASSERT_EQUAL(false, writer._wroteVertexHeader);
    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);

    checkFile(_data->vertexFilename, t, _data->timeFormat);

    PYLITH_METHOD_END;
} // testWriteVertexField


// ----------------------------------------------------------------------
// Test writeCellField.
void
pylith::meshio::TestDataWriterVTKSubmesh::testWriteCellField(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_submesh);
    CPPUNIT_ASSERT(_data);

    DataWriterVTK writer;

    pylith::topology::Field cellField(*_submesh);
    _createCellField(&cellField);

    writer.filename(_data->cellFilename);
    writer.timeFormat(_data->timeFormat);

    const PylithScalar t = _data->time;
    const bool isInfo = false;
    writer.open(*_submesh, isInfo);
    writer.openTimeStep(t, *_submesh);

    const pylith::string_vector& subfieldNames = cellField.subfieldNames();
    const size_t numFields = subfieldNames.size();
    for (size_t i = 0; i < numFields; ++i) {
        const FieldFilter* filter = NULL;
        OutputSubfield* subfield = OutputSubfield::create(cellField, subfieldNames[i].c_str(), filter);
        CPPUNIT_ASSERT(subfield);
        subfield->extract(cellField.outputVector());
        writer.writeCellField(t, *subfield);
        CPPUNIT_ASSERT_EQUAL(false, writer._wroteVertexHeader);
        CPPUNIT_ASSERT(writer._wroteCellHeader);
        delete subfield;subfield = NULL;
    } // for
    writer.closeTimeStep();
    writer.close();

    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);
    CPPUNIT_ASSERT_EQUAL(false, writer._wroteCellHeader);

    checkFile(_data->cellFilename, t, _data->timeFormat);

    PYLITH_METHOD_END;
} // testWriteCellField


// ----------------------------------------------------------------------
// Get test data.
pylith::meshio::TestDataWriterSubmesh_Data*
pylith::meshio::TestDataWriterVTKSubmesh::_getData(void) {
    return _data;
} // _getData


// End of file
