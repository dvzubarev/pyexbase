{
  description = "Python bindings for common C++ functions";

  inputs.textapp-pkgs.url = "git+ssh://git@tsa04.isa.ru/textapp/textapp-pkgs";

  outputs = { self, textapp-pkgs }:
    let
      pkgs = import textapp-pkgs.inputs.nixpkgs {
          system = "x86_64-linux";
          overlays = [ textapp-pkgs.overlays.default self.overlays.default ];
          config = textapp-pkgs.passthru.pkgs-config;
      };
      python-overlay = pyfinal: pyprev: {pyexbase = pyfinal.callPackage ./nix {src=self;};};
      tlib = textapp-pkgs.lib;
    in {
      overlays.default = final: prev: tlib.overrideAllPyVersions python-overlay prev;

      packages.x86_64-linux = tlib.allPyVersionsAttrSet {final-pkgs=pkgs;
                                                         default="pyexbase";};

      devShells.x86_64-linux.default =
        pkgs.mkShell {
          inputsFrom = [ pkgs.python.pkgs.pyexbase ];
          buildInputs = [pkgs.ccls];
          dontUseSetuptoolsShellHook = true;
        };

    };

}
