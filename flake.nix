{
  description = "Python bindings for common C++ functions";

  inputs.textapp-pkgs.url = "git+ssh://git@tsa04.isa.ru/textapp/textapp-pkgs?ref=flakes";

  outputs = { self, textapp-pkgs }:
    let
      pkgs = import textapp-pkgs.inputs.nixpkgs {
          system = "x86_64-linux";
          overlays = [ textapp-pkgs.overlay self.overlay ];
        };
      python-overlay = pyfinal: pyprev: {pyexbase = pyfinal.callPackage ./nix {src=self;};};
    in {
      overlay = final: prev: {
        python = textapp-pkgs.lib.overridePython python-overlay final prev;
      };
      defaultPackage.x86_64-linux = pkgs.python.pkgs.pyexbase;
      packages.x86_64-linux = {
        inherit (pkgs)
          python;

      };
      devShell.x86_64-linux =
        pkgs.mkShell {
          inputsFrom = [ pkgs.python.pkgs.pyexbase ];
          buildInputs = [pkgs.ccls];
          dontUseSetuptoolsShellHook = true;
        };

    };

}
