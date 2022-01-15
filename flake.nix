{
  description = "Python bindings for common C++ functions";

  inputs.textapp-pkgs.url = "git+ssh://git@ids/textapp/textapp-pkgs?ref=flakes";
  inputs.nixpkgs.follows = "textapp-pkgs/nixpkgs";

  outputs = { self, nixpkgs, textapp-pkgs }:
    let pkgs = import nixpkgs {
          system = "x86_64-linux";
          overlays = [ textapp-pkgs.overlay self.overlay ];
        };
    in {
      overlay = final: prev:
        let merged-overlay = pkgs.lib.composeExtensions
          prev.python-overlay
          (pyfinal: pyprev: {pyexbase = pyfinal.callPackage ./nix {src=self;};});
        in {
          python-overlay = merged-overlay;
          python = prev.base-python.override{packageOverrides = merged-overlay;};
        };
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
