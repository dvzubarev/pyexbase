{
  pkgs ? import <textapp-pkgs> {}
}:
with pkgs;
let pythonEnv = python.withPackages (ps: [
      ps.pybind11
      ps.setuptools
    ]);
in
mkShell rec {
  name = "pyexbase-dev";

  nativeBuildInputs = [ cmake ];
  buildInputs = [
    pythonEnv
    boost
    icu
  ];
}
