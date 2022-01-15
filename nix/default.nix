{
  src,
  buildPythonPackage,
  cmake,
  pybind11,
  boost,
  icu,

}:
buildPythonPackage {
  pname = "pyexbase";
  version = "0.2.0";
  inherit src;

  nativeBuildInputs=[cmake];
  buildInputs=[pybind11 boost icu ];
  dontUseCmakeConfigure=true;
  dontInstallCheck=true;
  dontUseSetuptoolsCheck=true;

}
