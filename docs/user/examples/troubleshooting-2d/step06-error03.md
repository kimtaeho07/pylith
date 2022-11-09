# Step 6: Error 3

## Error Message

```{code-block} console
---
caption: Error message 3 when running Step 6.
linenos: True
emphasize-lines: 14
---
$ pylith step06_twofaults.cfg

 -- Verifying compatibility of problem configuration.
Fatal error. Calling MPI_Abort() to abort PyLith application.
Traceback (most recent call last):
  File "/software/baagaard/py38-venv/pylith-debug/lib/python3.8/site-packages/pylith/apps/PetscApplication.py", line 61, in onComputeNodes
    self.main(*args, **kwds)
  File "/software/baagaard/py38-venv/pylith-debug/lib/python3.8/site-packages/pylith/apps/PyLithApp.py", line 108, in main
    self.problem.verifyConfiguration()
  File "/software/baagaard/py38-venv/pylith-debug/lib/python3.8/site-packages/pylith/problems/Problem.py", line 177, in verifyConfiguration
    ModuleProblem.verifyConfiguration(self)
  File "/software/baagaard/py38-venv/pylith-debug/lib/python3.8/site-packages/pylith/problems/problems.py", line 167, in verifyConfiguration
    return _problems.Problem_verifyConfiguration(self)
RuntimeError: Cannot find 'lagrange_multiplier_fault' subfield in solution field for fault implementation in component 'splay'.
```

## Troubleshooting Strategy

We no longer have errors during the problem configuration.
Now we have errors while doing additional verification of the problem.
After the Python Traceback, we see the error message on line 14.
The faults check to make sure the solution field contains the necessary subfields, and the splay fault cannot find the `lagrange_multiplier_fault` subfield.
The easiest way to diagnose an error like this is to view the JSON file automatically generated by PyLith; it contains all of the parameters, including any defaults used.
We point our web browser to <https://geodynamics.github.io/pylith_parameters/> and load the parameter file `output/step06_twofaults-parameters.json`.
In the left panel we navigate to the solution field and see that it the subfields are set to `pylith.problems.SolnDisp`, so that the solution field only contains a single subfield, `displacement`.
We want the solution field to contain both `displacement` and `lagrange_multiplier_fault`.

## Resolution

```{code-block} cfg
---
caption: Correct error in `step06_twofaults.cfg`.
---
[pylithapp.problem]
solution = pylith.problems.SolnDispLagrange
```