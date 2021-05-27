# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
# Charles A. Williams, GNS Science
# Matthew G. Knepley, University of Chicago
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#
# Application for searching for and running PyLith .cfg files.

import sys
import argparse
import pathlib
import textwrap
import os

from pylith.utils.SimulationMetadata import fromFile
from pylith.apps.PyLithApp import PyLithApp

class RunnerApp():
    """Application for searching for and running PyLith .cfg files.
    """

    def main(self, **kwargs):
        """Main entry point.

        Keyword arguments:
            searchpath (str), default: "."
                Search path for .cfg files.
        """
        args = argparse.Namespace(
            **kwargs) if kwargs else self._parse_command_line()

        for filename in sorted(pathlib.Path(args.searchpath).glob("**/*.cfg")):
            metadata = fromFile(filename)
            if metadata:
                if metadata.arguments:
                    self._run_pylith(filename, metadata.arguments)
                elif args.verbose:
                    print(f"WARNING: File {filename} missing PyLith arguments.")
            elif args.verbose:
                print(f"INFO: File {filename} missing simulation metadata.")

    def _run_pylith(self, filename, arguments):
        """Run PyLith simulation using given arguments.

        Args:
            filename (str)
                Path to simulation parameter file.
            arguments (list of str)
                Command line arguments.
        """
        workdir = filename.parent.name
        cwd = os.getcwd()

        if workdir:
            os.chdir(workdir)
            print("RUNNING: {} - pylith {}...".format(workdir, " ".join(arguments)))
        else:
            print("RUNNING: - pylith {}...".format(" ".join(arguments)))

        app = PyLithApp()
        app.run(argv=["pylith"] + arguments)
        os.chdir(cwd)

    def _parse_command_line(self):
        """Parse command line arguments.

        Returns (argsparse.Namespace)
           Command line arguments.
        """
        DESCRIPTION = (
            "Application for searching for and running PyLith simulations."
        )

        parser = argparse.ArgumentParser(description=DESCRIPTION,
            formatter_class=argparse.ArgumentDefaultsHelpFormatter)
        parser.add_argument("--path", action="store",
                            dest="searchpath", default=".", help="Search path for .cfg files.")
        parser.add_argument("--verbose", action="store_true",
                            dest="verbose", help="Report missing metadata.")

        args = parser.parse_args()

        return args


# End of file
