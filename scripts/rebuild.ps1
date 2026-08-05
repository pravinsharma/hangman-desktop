param(
    [switch]$Help
)

$ErrorActionPreference = "Stop"

foreach ($arg in $args) {
    switch ($arg) {
        "--help" { $Help = $true }
    }
}

if ($Help) {
    Write-Host "Clean and rebuild the SDL3 project."
    Write-Host ""
    Write-Host "Usage: .\scripts\rebuild.ps1 [--help]"
    Write-Host "Options:"
    Write-Host "  --help   Show this help message"
    exit 0
}

Write-Host "Rebuilding project..."
& $PSScriptRoot/clean.ps1
& $PSScriptRoot/build.ps1
