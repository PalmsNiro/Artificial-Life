let
  pkgs = import <nixpkgs> {};
  buildInputs = with pkgs; [
    cmake
    gcc
    pkg-config
    sfml
    xorg.libX11.dev
    xorg.libXrandr.dev
    xorg.libXcursor.dev
    xorg.libXinerama.dev
    xorg.libXi.dev
    libGL
    openal
    flac
    libvorbis
    udev
    freetype
  ];
in
pkgs.mkShell {
  inherit buildInputs;

  shellHook = ''
    export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath buildInputs}:$LD_LIBRARY_PATH
  '';
}
