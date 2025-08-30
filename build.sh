#!/bin/bash

# build-and-run.sh - Clean CMake build and run script with CLI/GUI options

# Configuration
BUILD_DIR="build"
SERVER_EXECUTABLE="server/server"
CLIENT_EXECUTABLE="client/client"
QUIET_MODE=false
RUN_SERVER=false
RUN_CLIENT=false

# Help function
show_help() {
    echo "Usage: $0 [--server] [--client] [--both] [--quiet]"
    echo "Options:"
    echo "  --server     Run only the server executable"
    echo "  --client     Run only the client executable"
    echo "  --both    Run both server and client"
    echo "  --quiet   Suppress status messages"
    echo "  --help    Show this help message"
}

# Parse arguments
for arg in "$@"; do
    case $arg in
        --server)
            RUN_SERVER=true
            ;;
        --client)
            RUN_CLIENT=true
            ;;
        --both)
            RUN_SERVER=true
            RUN_CLIENT=true
            ;;
        --quiet)
            QUIET_MODE=true
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            echo "Unknown option: $arg"
            show_help
            exit 1
            ;;
    esac
done

# Default behavior if no flag is set
if ! $RUN_SERVER && ! $RUN_CLIENT; then
    RUN_SERVER=true
    RUN_CLIENT=true
fi

# Function for clean output
status() {
    if ! $QUIET_MODE; then
        echo "==> $*"
    fi
}

# Clean previous build
status "Preparing build environment..."
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

# Configure with CMake
status "Configuring project..."
cmake .. -DCMAKE_BUILD_TYPE=Debug > /dev/null || {

    echo "Configuration failed!"
    exit 1
}

# Build the project
status "Building project..."
if [[ "$OSTYPE" == "darwin"* ]]; then
    CPU_COUNT=$(sysctl -n hw.ncpu)
else
    CPU_COUNT=$(nproc)
fi

cmake --build . --config Release --parallel "$CPU_COUNT" > /dev/null || {
    echo "Build failed!"
    exit 1
}

# Run CLI
if $RUN_CLI; then
    status "Running Server..."
    if [ -f "$SERVER_EXECUTABLE" ]; then
        echo ""
        ./"$SERVER_EXECUTABLE"
        echo ""
    else
        echo "Error: Server executable not found: $SERVER_EXECUTABLE" >&2
        exit 1
    fi
fi

# Run GUI
if $RUN_GUI; then
    status "Running Client..."
    if [ -f "$CLIENT_EXECUTABLE" ]; then
        echo ""
        (cd client && ./client)
        echo ""
    else
        echo "Error: client executable not found: $CLIENT_EXECUTABLE" >&2
        exit 1
    fi
fi

status "Build and run completed successfully"
