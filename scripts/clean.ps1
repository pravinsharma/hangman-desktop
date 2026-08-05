param(
    [switch]$Help
)

$ErrorActionPreference = "Stop"
$buildDir = "build"

foreach ($arg in $args) {
    switch ($arg) {
        "--help" { $Help = $true }
    }
}

if ($Help) {
    Write-Host "Remove the CMake build directory."
    Write-Host ""
    Write-Host "Usage: .\scripts\clean.ps1 [--help]"
    Write-Host "Options:"
    Write-Host "  --help   Show this help message"
    exit 0
}

if (Test-Path $buildDir) {
    Write-Host "Removing '$buildDir'..."
    Remove-Item -LiteralPath $buildDir -Recurse -Force
} else {
    Write-Host "Nothing to clean."
}
