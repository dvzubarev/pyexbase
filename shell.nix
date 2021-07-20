{
  pkgs ? import <textapp-pkgs> {},
  version ? "0.1"
}:
with pkgs;
let pythonEnv = python.withPackages (ps: [
      ps.pybind11
    ]);
in
mkShell rec {
  name = "pyexbase-${version}";
  inherit version;

  nativeBuildInputs = [ cmake ];
  buildInputs = [
    pythonEnv
  ];
}
