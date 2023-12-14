#!/usr/bin/env nemesis
# =================================================================================================
# This code is part of PyLith, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/pylith).
#
# Copyright (c) 2010-2023, University of California, Davis and the PyLith Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

from pylith.utils.utils import DependenciesVersion

class TestDependenciesVersion(unittest.TestCase):

  def test_mpiVersion(self):
    version = DependenciesVersion.mpiVersion()
    # Check that version is of the form X.X.X or X.X
    import re
    match = re.search("[0-9]+\.[0-9]+\.[0-9]+", version)
    if match is None:
      match = re.search("[0-9]+\.[0-9]+", version)
    self.assertFalse(match is None)
    return


  def test_mpiImplementation(self):
    imp = DependenciesVersion.mpiImplementation()
    self.assertFalse(len(imp) == 0)
    return


  def test_mpiStandard(self):
    version = DependenciesVersion.mpiStandard()
    # Check that version is of the form X.X
    import re
    match = re.search("[0-9]+\.[0-9]+", version)
    self.assertFalse(match is None)
    return


  def test_netcdfVersion(self):
    version = DependenciesVersion.netcdfVersion()
    # Check that version is of the form X.X.X
    import re
    match = re.search("[0-9]+\.[0-9]+\.[0-9]+", version)
    self.assertFalse(match is None)
    return


  def test_hdf5Version(self):
    version = DependenciesVersion.hdf5Version()
    # Check that version is of the form X.X.X
    import re
    match = re.search("[0-9]+\.[0-9]+\.[0-9]+", version)
    self.assertFalse(match is None)
    return


if __name__ == "__main__":
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestDependenciesVersion))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file 
