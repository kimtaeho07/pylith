(sec-user-mesh)=
# Finite-Element Mesh

The finite-element mesh specifies the geometry and topology of the discretization.
It must be generated using external software before running PyLith.
PyLith supports triangular and quadrilateral cells in 2D and tetrahedral and hexahedral cells in 3D.
The vertex ordering must follow the convention shown in {numref}`fig:2d:cells` and {numref}`fig:3d:cells`.
The cells define the geometry of the domain; the basis order and quadrature order used to discretize the solution subfields are specified separately.

The mesh information specifies the vertex coordinates and the vertices composing each cell in the mesh.
The mesh information must also define at least one set of vertices for which displacement (Dirichlet) boundary conditions will be provided.
In most realistic problems, there will be several vertex groups, each with a unique identifying label.
For example, one group might define a surface of the mesh where displacement (Dirichlet) boundary conditions will be applied, another might define a surface where traction (Neumann) boundary conditions will be applied, while a third might specify a surface that defines a fault.
Similarly, the mesh information contains cell labels that define the material type for each cell in the mesh.
For a mesh with a single material type, there will only be a single label for every cell in the mesh.
See {ref}`sec-user-physics-materials` and {ref}`sec-user-physics-boundary-conditions` for more detailed discussions of setting the materials and boundary conditions.

:::{figure-md} fig:2d:cells
<img src="figs/cells2d.*" alt="2D cell types" width="400px">

Cells available for 2D problems are the triangle and the quadrilateral.
:::

:::{figure-md} fig:3d:cells
<img src="figs/cells3d.*" alt="3D cell types" width="400px">

Cells available for 3D problems are the tetrahedron and the hexahedron.
:::

## Mesh Importer

The default component for the PyLithApp `mesher` facility is `MeshImporter`, which provides the capabilities of reading the finite-element mesh from files.
The `MeshImporter` includes a facility for reordering the mesh.
Reordering the mesh so that vertices and cells connected topologically reside close together in memory improves overall performance.

:::{admonition} Pyre User Interface
:class: seealso
See [`MeshImporter` component](../components/topology/MeshImporter.md)
:::

PyLith supports reading meshes generated by Cubit (Exodus II files), LaGriT (GMV and pset files), and Gmsh.
We have implemented our own readers for Exodus II files and GMV and pset files.
For Gmsh files we use the reader included in PETSc; PETSc also supports several other formats, but they have not been tested for use with PyLith.
Currently, PyLith requires that boundary conditions be specified by marking vertices and all materials are marked by the same label `material-id` with different label values for each material.
The PyLith Cubit and LaGriT readers automatically create the labels from the Exodus II and GMV and pset files.

### Mesh generation with Cubit and Gmsh

Cubit and Gmsh can generate quadrilateral or triangular meshes in 2D and hexahedral or tetrahedral meshes in 3D.
In each case, you first create the geometry, specify the meshing algorithm and discretization size, and then generate the mesh.
You can build up the geometry from points, curves, surfaces, and volumes or use the geometry engines to construct the domain using simple shapes.

#### Cubit

We have tended to construct Cubit meshes using journal files and leverage the Cubit APREPRO scripting language.
Cubit also provides a Python interface, but you must use the Python interpreter provided with Cubit.
The functionality of the two interfaces is quite similar, although one could argue that the Python interface leverages a more complete development experience through a commonly used programming language.

#### Gmsh

We only recently started using Gmsh and have only used the Python interface.
Gmsh also offers a simple scripting language, similar to Cubit journal files.
The Gmsh Python interface integrates well with the rest of Python; it can be installed so that it is compatible with the Python interpreter used by PyLith.
This means one can leverage additional Python packages, such as geographic projection libraries. 
Gmsh includes its own geometry engine as well as an interface to the Open CASCADE engine.

:::{warning}
Gmsh does not construct quadrilateral or hexahedral meshes directly; instead, it first constructs a triangular or tetrahedral mesh and then combines triangles or tetrahedra to form quadrilaterals or hexahedra.

Sometimes it will not be able to remove all triangular or hexahedral cells, resulting in meshes with multiple shapes, which PyLith does not support.
:::

#### 2D meshing

Constructing surfaces from points and curves for 2D meshing with Cubit and Gmsh is very similar.
Cubit provides more geometric operations than Gmsh, but many simple geometric operations in Gmsh can be implemented by the user when using the Python interface.
Gmsh includes a simple yet powerful interface for specifying the discretization size.
Generating unstructured quadrilateral meshes for complex geometry is often easier in Cubit, whereas generating meshes with complex specification of discretization size is often easier with Gmsh.

#### 3D meshing

Cubit provides an extensive suite of tools for constructing complex 3D geometry.
This includes building surfaces and performing geometric operations on surfaces and volumes.
The suite of tools in the Gmsh geometry engine is more limited; the Open CASCADE engine interface provides additional tools.
With either Cubit or Gmsh, you can use external CAD tools to generate the geometry.
As in the case with 2D meshing, generating unstructure hexahedral meshes is often easier in Cubit, whereas generating meshes with complex specification of discretization size is often eaiser in Gmsh.

## ASCII Mesh Files - `MeshIOAscii`

The `MeshIOAscii` object is intended for reading small, simple ASCII files containing a mesh constructed by hand.
We use this file format extensively in small tests.
{ref}`sec-user-file-formats-meshio-ascii` describes the format of the files.

```{table} Translation of ASCII mesh "tags" to PyLith mesh 'label' and 'label_value'.
:name: tab:mesh:tags:translation:ascii
| MeshIOAscii entity |  `label`      | `label_value`   |
|:-------------------|:--------------|:---------------:|
| `material-ids`     | `material-id` (hardwired) | value           |
| Group name         | name          | 1 (default)     |
```

:::{admonition} Pyre User Interface
:class: seealso
[`MeshIOAscii` Component](../components/meshio/MeshIOAscii.md)
:::

(sec-user-run-pylith-meshiocubit)=
## Cubit (Exodus II) Mesh Files - `MeshIOCubit`

The `MeshIOCubit` object reads the NetCDF Exodus II files output from Cubit.
Beginning with Cubit 11.0, the names of the nodesets are included in the Exodus II files and PyLith can use these nodeset names or revert to using the nodeset ids.

```{table} Translation of Cubit mesh "tags" to PyLith mesh 'label' and 'label_value'.
:name: tab:mesh:tags:translation:cubit
| Cubit entity   |  `label`      | `label_value`   |
|:---------------|:--------------|:---------------:|
| Material block | `material-id` (hardwired) | Block value |
| Nodeset        | Nodeset name  | 1 (default)     |
```

:::{admonition} Pyre User Interface
:class: seealso
[`MeshIOCubit` Component](../components/meshio/MeshIOCubit.md)
:::

:::{warning}
There are two versions of Cubit: Sandia National Laboratory provides a version to U.S. government agencies, and Coreform provides another version to all other users.
The two verisions used to be essentially the same, but the differences have started to grow.
We strive to provide Cubit Journal scripts that work with both versions without modification, but this is becoming more difficult.

**Please be aware that we cannot guarantee that all Cubit Journal files will work with all versions of Cubit.** You may need to make small adjustments (usually updating geometry ids) to get them to work with the version of Cubit you are using.
:::

(sec-user-run-pylith-meshiopetsc)=
## Gmsh Files - `MeshIOPetsc`

The `MeshIOPetsc` object supports reading a variety of mesh formats.
We have only thoroughly tested this interface using Gmsh files.

```{table} Translation of Gmsh mesh "tags" to PyLith mesh 'label' and 'label_value'.
:name: tab:mesh:tags:translation:gmsh
| Gmsh entity   |  `label`      | `label_value`   |
|:---------------|:--------------|:---------------:|
| Material physical groups | `material-id` (hardwired)     | tag |
| Boundary condition physical groups | Physical group name | tag |
```

:::{important}
The Gmsh file must end in `.msh` for the reader to recognize that it is a Gmsh file.
:::

:::{tip}
You can view the mesh quality in Gmsh using `Tools`&#8594;`Statistics`.
We prefer the condition number quality metric, which Gmsh provides as SICN (signed inverse of the condition number).
Click on `3D` next to `SICN` to color the cells by mesh quality.
Click on `Plot` to view the cumulative distribution of the metric over the cells.
:::

:::{admonition} Pyre User Interface
:class: seealso
[`MeshIOPetsc` Component](../components/meshio/MeshIOPetsc.md)
:::

(sec-usr-run-pylith-gmsh-utils)=
### `gmsh_utils`

In Gmsh we use physical groups to associate cells with materials and mark entities for boundary conditions and faults.
The names of physical groups for materials must follow the syntax `material-id:TAG`, where TAG is the tag of the physical group.
PyLith includes a Python module `pylith.meshio.gmsh_utils` to make it easy to generate a PyLith compatible Gmsh file.

The function `create_material()` generates physical groups following the required naming convention of `material-id:TAG` given the tag and names of entities.
Similarly, the function `create_group()` will construct physical groups for boundary conditions and faults compatible with PyLith.

The physical groups for boundary conditions and faults must include entities at the topological dimension of the boundary condition as well as all lower dimensions.
For example, for a boundary condition on curves a physical group must include the entities on the curves as well as the vertices defining the curves.
For a boundary condition on surfaces a physical group must include the entities on the surfaces as well as the curves and vertices defining the surfaces.

#### `GenerateMesh` Application Template

The `gmsh_utils` module also includes a application template object (Python abstract base class) called `GenerateMesh` for writing Python scripts that generate meshes using Gmsh.
The application template defines the steps for generating the mesh with a separate function (to be implemented by the user) for each step:

1. `initialize()`: Initialize Gmsh;
2. `create_geometry()`: Create the geometry (implemented in user application);
3. `mark()`: Create physical groups for boundary conditions, faults, and materials (implemented in user application);
4. `generate_mesh()`: Generate the finite-element mesh (implemented in user application);
5. `write()`: Save the mesh to a file; and
6. `finalize()`: Start the Gmsh graphical user interface, if requested, and then finalize Gmsh.

The command line arguments specify which step(s) to run, the output filename, and whether to invoke the Gmsh graphical user interface upon completing the steps:

:`--geometry`: Generate the geometry by calling `create_geometry()`.
:`--mark`: Create physical groups by calling `mark()`.
:`--generate`: Generate the mesh by calling `generate_mesh()`.
:`--write`: Save the mesh by calling `write()`.
:`--name`: Name of the mesh in Gmsh (default="mesh").
:`--filename=FILENAME`: Name of output mesh file (default="mesh.msh").
:`--ascii`: Write mesh to ASCII file (default is binary).
:`--cell=[tri,quad,tet,hex]`: Generate mesh with specified cell type.
:`--gui`: Start the Gmsh graphical user interface after running steps.

The application template always calls the `initialize()` and `finalize()` methods.
Additionally, the application will run any prerequisite steps.
For example, specifying `--generate` will trigger creating the geometry and physical groups before generating the mesh.

The application is discussed in more detail in the examples.

#### MaterialGroup

`MaterialGroup` is a Python data class that holds information about a physical group associated with a material.
The data members include:

:tag (int): Integer tag for the physical group.
:entities (list): List (array) of entities for the material.

The `MaterialGroup` data class include a method `create_physical_group()` that will create a physical group from the information in the `MaterialGroup`.

#### VertexGroup

`VertexGroup` is a Python data class that holds information about a physical group associated with a boundary or fault.
The data members include:

:name (str): Name for the physical group.
:tag (int): Integer tag for the physical group.
:dim (int): Dimension of the entities (0=points, 1=curves, 2=surfaces)
:entities: List (array) of entities for the boundary condition or fault.

The `VertexGroup` data class include a method `create_physical_group()` that will create a physical group from the information in the `VertexGroup`.

## LaGriT Mesh Files - `MeshIOLagrit`

The `MeshIOLagrit` object is used to read ASCII and binary GMV and PSET files output from [LaGriT](https://lanl.github.io/LaGriT/`).
PyLith will automatically detect whether the files are ASCII or binary.
We attempt to provide support for experimental 64-bit versions of LaGriT via flags indicating whether the FORTRAN code is using 32-bit or 64-bit integers.

:::{danger}
The PyLith developers have not used LaGriT since around 2008 and there have been a few releases since then so the interface may not be up to date.

We plan to remove support for LaGriT mesh files in v3.2.
:::

:::{admonition} Pyre User Interface
:class: seealso
[`MeshIOLagrit` Component](../components/meshio/MeshIOLagrit.md)
:::

## Distribution among Processes - `Distributor`

The distributor uses a partitioner to compute which cells should be placed on each processor, computes the overlap among the processors, and then distributes the mesh among the processors.
The type of partitioner is set via PETSc settings.

:::{note}
METIS/ParMETIS are not included in the PyLith binaries due to licensing issues.
:::

:::{admonition} Pyre User Interface
:class: seealso
[`Distributor` Component](../components/topology/Distributor.md)
:::

## Uniform Global Refinement - `Refiner`

The refiner is used to decrease node spacing by a power of two by recursively subdividing each cell by a factor of two.
In a 2D triangular mesh a node is inserted at the midpoint of each edge, splitting each cell into four cells (see {numref}`fig:uniform:refinement:2x`).
In a 2D quadrilateral mesh a node is inserted at the midpoint of each edge and at the centroid of the cell, splitting each cell into four cells.
In a 3D tetrahedral mesh a node is inserted at the midpoint of each edge, splitting each cell into eight cells.
In a 3D hexahedral mesh a node is inserted at the midpoint of each edge, the centroid of each face, and at the centroid of the cell, splitting each cell into eight cells.

:::{figure-md} fig:uniform:refinement:2x
<img src="figs/refinement2x.*" alt="Global refinement" width="100%"/>

Global uniform mesh refinement of 2D and 3D linear cells.
The blue lines and orange circles identify the edges and vertices in the original cells.
The purple lines and green circles identify the new edges and vertices added to the original cells to refine the mesh by a factor of two.
:::

Refinement occurs after distribution of the mesh among processors.
This allows one to run much larger simulations by (1) permitting the mesh generator to construct a mesh with a node spacing larger than that needed in the simulation and (2) operations performed in serial during the simulation setup phase, such as, adjusting the topology to insert cohesive cells and distribution of the mesh among processors uses this much smaller coarse mesh.
For 2D problems the global mesh refinement increases the maximum problem size by a factor of $4^{n}$, and for 3D problems it increases the maximum problem size by a factor of $8^{n}$, where $n$ is the number of recursive refinement levels.
For a tetrahedral mesh, the element quality decreases with refinement so $n$ should be limited to 1-2.

% End of file