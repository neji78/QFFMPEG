#!/bin/bash

# Set the path to FFmpeg source directory
FFMPEG_SOURCE_DIR="../ffmpeg"

# Set the path to Android NDK
ANDROID_NDK_ROOT="C:/android-sdk3/ndk/21.4.7075529"

# Output directories for each platform
ANDROID_BUILD_DIR="./android_build"
WINDOWS_BUILD_DIR="./windows_build"

# Function to configure and build FFmpeg for Android
build_for_android() {
    local ARCH=$1
    echo "Building FFmpeg for Android for architecture: $ARCH"
    if [ ! -d "$ANDROID_BUILD_DIR" ]; then
        # If it doesn't exist, create the directory
        mkdir -p "$ANDROID_BUILD_DIR"
    fi
    rm -rf "$ANDROID_BUILD_DIR/*"  # Use rm -rf to remove all files and directories

    # Set Android-specific flags and toolchain paths
    export TOOLCHAIN="$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/windows-x86_64"
    export API=30

    # Determine target and CPU based on architecture
    if [[ "$ARCH" == "armv7" ]]; then
        TARGET="armv7a-linux-androideabi"
        CPU="armv7-a"
    elif [[ "$ARCH" == "arm64-v8a" ]]; then
        TARGET="aarch64-linux-android"
        CPU="armv8-a"
    elif [[ "$ARCH" == "armeabi-v7a" ]]; then
        TARGET="armeabi-v7a"
        CPU="armv7-a"
    else
        echo "Unsupported architecture: $ARCH"
        return
    fi

    # Configure FFmpeg for Android
    "$FFMPEG_SOURCE_DIR"/configure \
        --prefix="$ANDROID_BUILD_DIR/$ARCH" \
        --target-os=android \
        --arch="$ARCH" \
        --cpu="$CPU" \
        --cross-prefix="$TOOLCHAIN/bin/$TARGET-" \
        --cc="$TOOLCHAIN/bin/$TARGET$API-clang" \
        --cxx="$TOOLCHAIN/bin/$TARGET$API-clang++" \
        --enable-cross-compile \
        --sysroot="$TOOLCHAIN/sysroot" \
        --extra-cflags="-Os -fPIC" \
        --extra-ldflags="" \
        --disable-static \
        --enable-shared \
        --disable-debug \
        --disable-doc \
        --disable-zlib \
        --disable-iconv \
        --disable-encoders --disable-muxers --disable-decoders --disable-bsfs --disable-protocols --disable-parsers --disable-demuxers \
        --disable-network \
        --disable-indevs \
        --disable-postproc \
        --disable-asm \
        --disable-vaapi \
        --disable-programs \
        --disable-filters \
        --disable-hwaccels \
        --enable-pixelutils \
        --enable-gpl \
        --enable-parser=h264 \
        --enable-parser=aac \
        --enable-filter=hflip \
        --enable-protocol=file \
        --enable-demuxer=mp3 \
        --enable-demuxer=wav \
        --enable-demuxer=ogg \
        --enable-demuxer=gsm \
        --enable-demuxer=aac \
        --enable-demuxer=avi \
        --enable-demuxer=mov

    # Build and install
    make -j$(nproc)
    make install
    echo "FFmpeg built and installed for Android ($ARCH) in $ANDROID_BUILD_DIR/$ARCH"
}

# Function to configure and build FFmpeg for Windows
build_for_windows() {
    local ARCH=$1
    echo "Building FFmpeg for Windows for architecture: $ARCH"
    if [ ! -d "$WINDOWS_BUILD_DIR" ]; then
        # If it doesn't exist, create the directory
        mkdir -p "$WINDOWS_BUILD_DIR"
    fi
    rm -rf "$WINDOWS_BUILD_DIR/*"  # Use rm -rf to remove all files and directories

    # Determine architecture and set configuration flags
    if [[ "$ARCH" == "x86" ]]; then
        TARGET_OS="mingw32"
        ARCH_TYPE="x86"
    elif [[ "$ARCH" == "x86_64" ]]; then
        TARGET_OS="mingw64"
        ARCH_TYPE="x86_64"
    else
        echo "Unsupported Windows architecture: $ARCH"
        return
    fi

    # Configure FFmpeg for Windows
    "$FFMPEG_SOURCE_DIR"/configure \
        --prefix="$WINDOWS_BUILD_DIR/$ARCH_TYPE" \
        --target-os="$TARGET_OS" \
        --arch="$ARCH_TYPE" \
        --enable-static \
        --disable-shared \
        --disable-debug \
        --disable-doc \
        --disable-zlib \
        --disable-iconv \
        --disable-encoders --disable-muxers --disable-decoders --disable-bsfs --disable-protocols --disable-parsers --disable-demuxers \
        --disable-network \
        --disable-indevs \
        --disable-postproc \
        --disable-asm \
        --disable-vaapi \
        --disable-programs \
        --disable-filters \
        --disable-hwaccels \
        --enable-pixelutils \
        --enable-gpl \
        --enable-parser=h264 \
        --enable-parser=aac \
        --enable-filter=hflip \
        --enable-protocol=file \
        --enable-demuxer=mp3 \
        --enable-demuxer=wav \
        --enable-demuxer=ogg \
        --enable-demuxer=gsm \
        --enable-demuxer=aac \
        --enable-demuxer=avi \
        --enable-demuxer=mov

    # Build and install
    make -j$(nproc)
    make install
    echo "FFmpeg built and installed for Windows ($ARCH_TYPE) in $WINDOWS_BUILD_DIR/$ARCH_TYPE"
}

# Main script logic
case "$1" in
    android)
        # List of architectures to build for Android
        ARCHS=("armv7" "arm64-v8a" "armeabi-v7a")
        for ARCH in "${ARCHS[@]}"; do
            build_for_android "$ARCH"
        done
        ;;
    windows)
        # List of architectures to build for Windows
        ARCHS=("x86" "x86_64")
        for ARCH in "${ARCHS[@]}"; do
            build_for_windows "$ARCH"
        done
        ;;
    all)
        # Build for all Android architectures
        ARCHS=("armv7" "arm64-v8a" "armeabi-v7a")
        for ARCH in "${ARCHS[@]}"; do
            build_for_android "$ARCH"
        done
        # Build for all Windows architectures
        ARCHS=("x86" "x86_64")
        for ARCH in "${ARCHS[@]}"; do
            build_for_windows "$ARCH"
        done
        ;;
    *)
        echo "Usage: $0 {android|windows|all}"
        exit 1
        ;;
esac
