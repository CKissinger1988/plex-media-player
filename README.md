## Deprecation

Note: Plex is no longer actively maintaining SpartanAI-Media.  This repository is preserved as it was when last developed.  See https://www.plex.tv/media-server-downloads/#plex-app for replacement applications.

## Building

The project now uses a modern, target-based CMake structure.

You need:
* Qt 6.5.0
* cmake 3.20 or newer
* ninja

### Building

* ``mkdir build ; cd build``
* ``cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..``
* ``ninja``

## License

SpartanAI-Media is licensed under GPL v2. See the ``LICENSE`` file.
Licenses of dependencies are summarized under ``resources/misc/licenses.txt``.
This file can also be printed at runtime when using the ``--licenses`` option.
