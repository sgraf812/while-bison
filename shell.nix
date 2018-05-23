with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "while";
  buildInputs = [gcc flex bison];
}

