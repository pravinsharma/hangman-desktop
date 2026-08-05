$ErrorActionPreference = "Stop"
$source = Join-Path $env:VCPKG_ROOT "installed/x64-windows/bin"
$dest = $args[0]

if (-not (Test-Path $source)) {
    Write-Error "Source directory not found: $source"
    exit 1
}

if (-not (Test-Path $dest)) {
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
}

$copied = 0
Get-ChildItem -LiteralPath $source -Filter "*.dll" -File | ForEach-Object {
    $destPath = Join-Path $dest $_.Name
    if (-not (Test-Path $destPath)) {
        Copy-Item -LiteralPath $_.FullName -Destination $destPath
        $copied++
    }
}
Write-Host "Copied $copied runtime DLL(s) to $dest"
