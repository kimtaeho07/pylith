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
# @file tests/pytests/problems/TestProgressMonitor.py
#
# @brief Unit testing of Python ProgressMonitor object.

import unittest

from pylith.testing.UnitTestApp import TestAbstractComponent
from pylith.problems.ProgressMonitor import ProgressMonitor


class TestProgressMonitor(TestAbstractComponent):
    """Unit testing of ProgressMonitor object.
    """
    _class = ProgressMonitor


if __name__ == "__main__":
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestProgressMonitor))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
