## Usage

### ``messageToJson``

    $ messageToJson -h
    Valid Usage:
        -h, --help                          see this little message
        -w, --webhook <webhook_url>         the webhook url
        -m, --message <message_id>          message id to query for
        -p, --pretty                        pretty print outputed json
        -d, --discohook                     strip content for discohook
        -o, --output <filepath>             file to output to. if ignored, prints to console


## How to build

### Dependencies
+ [cmake](https://cmake.org/)
+ a c++ compiler

### *nix
    git clone https://github.com/EvysGarden/EvysDiscordUtils.git && cd EvysDiscordUtils
    git submodule update --init --recursive
    ./vcpkg/bootstrap-vcpkg.sh
    cmake -B build -S .
    cmake --build build

### Windows
    git clone https://github.com/EvysGarden/EvysDiscordUtils.git ; cd EvysDiscordUtils
    git submodule update --init --recursive
    .\vcpkg\bootstrap-vcpkg.bat
    cmake -B build -S .
    cmake --build build
