param(
    [switch]$Clean,
    [switch]$Help
)

$ErrorActionPreference = "Stop"
$buildDir = "build"

foreach ($arg in $args) {
    switch ($arg) {
        "--help" { $Help = $true }
        "--clean" { $Clean = $true }
    }
}

if ($Help) {
    Write-Host "Configure, build, and run the SDL3 project."
    Write-Host ""
    Write-Host "Usage: .\scripts\build.ps1 [--clean] [--help]"
    Write-Host "Options:"
    Write-Host "  --clean  Remove build directory before building"
    Write-Host "  --help   Show this help message"
    exit 0
}

if (-not $env:VCPKG_ROOT) {
    Write-Error "VCPKG_ROOT environment variable is not set."
    exit 1
}

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Error "cmake not found in PATH."
    exit 1
}

if (-not (Get-Command ninja -ErrorAction SilentlyContinue)) {
    Write-Error "ninja not found in PATH."
    exit 1
}

$toolchain = Join-Path $env:VCPKG_ROOT "scripts/buildsystems/vcpkg.cmake"
if (-not (Test-Path $toolchain)) {
    Write-Error "Vcpkg toolchain not found at: $toolchain"
    exit 1
}

if ($Clean) {
    Write-Host "Cleaning build directory..."
    if (Test-Path $buildDir) {
        Remove-Item -LiteralPath $buildDir -Recurse -Force
    }
}

Write-Host "Configuring project in '$buildDir'..."
cmake -B $buildDir -G Ninja -DCMAKE_BUILD_TYPE=Release

Write-Host "Building project..."
cmake --build $buildDir

Write-Host "Build complete."
