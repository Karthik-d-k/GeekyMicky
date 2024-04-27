# ------------------------------------------------------- #
#  `justfile` is used for `arduino` developemnt purposes
#  `Makefile` is used for `local`   developemnt purposes
# ------------------------------------------------------- #

# use PowerShell instead of sh:
set shell := ["powershell.exe", "-c"]

# List commands
default:
    @just --list

# Create a configuration file
config:
    arduino-cli config init

# Check for connected boards
board:
    arduino-cli core update-index
    arduino-cli board list

# Install core for arduino-nano
install:
    arduino-cli core install arduino:avr
    arduino-cli core list

# Build the sketch
build:
    arduino-cli compile --fqbn arduino:avr:nano --output-dir .\build .\src

# Upload the sketch
upload:
    # arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:nano --verify --input-dir .\build

# Clean build artifacts
clean:
    Remove-Item -Recurse -Force .\build

# Git status and diff
git:
    git status
    git diff
