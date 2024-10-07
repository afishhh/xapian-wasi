let
  # a nixpkgs checkout patched with ./nixpkgs.patch
  pkgs = import ./nixpkgs {
    config.allowUnsupportedSystem = true;
  };
  pkgsCross = pkgs.pkgsCross.wasi32;
  zlib = pkgsCross.zlib.overrideAttrs (old: { env = { }; });
  minuuid = pkgsCross.stdenv.mkDerivation {
    pname = "xapian-wasm-polyfills";
    version = "0.0.1";

    src = ./polyfills;

    buildPhase = ''
      $CC uuid.c -c -o uuid.o
      $AR rcs uuid.a uuid.o
    '';

    installPhase = ''
      mkdir -p $out/include/uuid $out/include/sys $out/lib
      mv netdb.h $out/include
      mv wait.h socket.h $out/include/sys
      mv uuid.h $out/include/uuid/
      mv uuid.a $out/lib/libuuid.a
      cp libuuid.la $out/lib
    '';
  };
  xapian = (pkgsCross.xapian.override { inherit zlib; libuuid = minuuid; }).overrideAttrs (old: {
    env.CXXFLAGS = "-DFLINTLOCK_USE_FLOCK";
    configureFlags = (old.configureFlags or [ ]) ++ [
      "--disable-backend-remote"
      "--disable-shared"
      "--enable-static"
    ];
    postPatch = ''
      ${pkgs.git}/bin/git apply ${./xapian.patch}
      ${pkgs.python3}/bin/python3 ${./replace_throw.py} in-place ./*/*.{cc,h} ./*/*/*.{cc,h}
      sed -i '/#include <signal.h>/d' backends/flint_lock.cc
    '';
  });
in
xapian
