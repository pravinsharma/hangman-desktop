param(
    [switch]$Help
)

$ErrorActionPreference = "Stop"
$buildDir = "build"
$exe = Join-Path $buildDir "hangman.exe"

foreach ($arg in $args) {
    switch ($arg) {
        "--help" { $Help = $true }
    }
}

if ($Help) {
    Write-Host "Run the built SDL3 executable."
    Write-Host ""
    Write-Host "Usage: .\scripts\run.ps1 [--help]"
    Write-Host "Options:"
    Write-Host "  --help   Show this help message"
    exit 0
}

if (-not (Test-Path $exe)) {
    Write-Error "Executable not found: $exe. Run .\scripts\build.ps1 first."
    exit 1
}

Write-Host "Running $exe..."
& $exe
