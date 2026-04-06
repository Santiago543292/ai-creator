# AI Creator Setup Wizard
# PowerShell script to automate installation and setup

param(
    [switch]$Silent = $false,
    [string]$InstallPath = ""
)

# Color constants
$ColorGreen = [System.ConsoleColor]::Green
$ColorRed = [System.ConsoleColor]::Red
$ColorYellow = [System.ConsoleColor]::Yellow
$ColorCyan = [System.ConsoleColor]::Cyan

function Write-Header {
    param([string]$Text)
    Write-Host ""
    Write-Host "╔════════════════════════════════════════╗" -ForegroundColor $ColorCyan
    Write-Host "║ $($Text.PadRight(38)) ║" -ForegroundColor $ColorCyan
    Write-Host "╚════════════════════════════════════════╝" -ForegroundColor $ColorCyan
    Write-Host ""
}

function Write-Success {
    param([string]$Text)
    Write-Host "[✓] $Text" -ForegroundColor $ColorGreen
}

function Write-Error-Custom {
    param([string]$Text)
    Write-Host "[✗] $Text" -ForegroundColor $ColorRed
}

function Write-Info {
    param([string]$Text)
    Write-Host "[*] $Text" -ForegroundColor $ColorCyan
}

function Write-Warning-Custom {
    param([string]$Text)
    Write-Host "[!] $Text" -ForegroundColor $ColorYellow
}

function Test-CMakeInstalled {
    try {
        $cmake = Get-Command cmake -ErrorAction Stop
        Write-Success "CMake found: $($cmake.Source)"
        return $true
    }
    catch {
        Write-Error-Custom "CMake not found"
        return $false
    }
}

function Test-VisualStudioInstalled {
    $vsPath = "C:\Program Files\Microsoft Visual Studio"
    $vsExists = Test-Path $vsPath
    
    if ($vsExists) {
        Write-Success "Visual Studio found"
        return $true
    }
    else {
        Write-Error-Custom "Visual Studio not found"
        return $false
    }
}

function Install-CMake {
    Write-Header "Installing CMake"
    
    Write-Info "Downloading CMake..."
    $cmakeUrl = "https://github.com/Kitware/CMake/releases/download/v3.27.0/cmake-3.27.0-windows-x86_64.msi"
    $cmakePath = "$env:TEMP\cmake-installer.msi"
    
    try {
        Invoke-WebRequest -Uri $cmakeUrl -OutFile $cmakePath -ErrorAction Stop
        Write-Success "CMake downloaded"
        
        Write-Info "Running CMake installer..."
        Start-Process -FilePath $cmakePath -ArgumentList "/quiet" -Wait
        Write-Success "CMake installed successfully"
        
        # Add to PATH
        $env:Path += ";C:\Program Files\CMake\bin"
        [Environment]::SetEnvironmentVariable("Path", $env:Path, [EnvironmentVariableTarget]::Machine)
        
        Remove-Item $cmakePath -Force
        return $true
    }
    catch {
        Write-Error-Custom "Failed to install CMake: $_"
        return $false
    }
}

function Show-Prerequisites {
    Write-Header "Checking Prerequisites"
    
    $cmakeOk = Test-CMakeInstalled
    $vsOk = Test-VisualStudioInstalled
    
    if (-not $cmakeOk) {
        Write-Warning-Custom "CMake is required"
        if (-not $Silent) {
            $response = Read-Host "Install CMake now? (Y/N)"
            if ($response -eq "Y" -or $response -eq "y") {
                Install-CMake
            }
        }
    }
    
    if (-not $vsOk) {
        Write-Error-Custom "Visual Studio 2017 or later is required"
        Write-Info "Download from: https://visualstudio.microsoft.com/"
        return $false
    }
    
    Write-Success "All prerequisites are installed"
    return $true
}

function Select-InstallPath {
    if ($InstallPath -ne "") {
        return $InstallPath
    }
    
    Write-Header "Select Installation Path"
    
    $defaultPath = "$env:USERPROFILE\AI Creator"
    Write-Info "Default path: $defaultPath"
    
    if (-not $Silent) {
        $custom = Read-Host "Use custom path? (Y/N)"
        if ($custom -eq "Y" -or $custom -eq "y") {
            $customPath = Read-Host "Enter installation path"
            return $customPath
        }
    }
    
    return $defaultPath
}

function Build-Application {
    param([string]$SourcePath, [string]$BuildPath)
    
    Write-Header "Building AI Creator"
    
    # Create build directory
    if (-not (Test-Path $BuildPath)) {
        New-Item -ItemType Directory -Path $BuildPath -Force | Out-Null
        Write-Success "Build directory created"
    }
    
    # Configure with CMake
    Write-Info "Configuring project..."
    Push-Location $BuildPath
    
    try {
        & cmake "$SourcePath\cpp-backend" -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
        if ($LASTEXITCODE -ne 0) {
            Write-Error-Custom "CMake configuration failed"
            return $false
        }
        Write-Success "Project configured"
        
        # Build
        Write-Info "Building project (this may take several minutes)..."
        & cmake --build . --config Release
        if ($LASTEXITCODE -ne 0) {
            Write-Error-Custom "Build failed"
            return $false
        }
        Write-Success "Build completed successfully"
        
        return $true
    }
    catch {
        Write-Error-Custom "Build error: $_"
        return $false
    }
    finally {
        Pop-Location
    }
}

function Create-Shortcuts {
    param([string]$InstallPath)
    
    Write-Header "Creating Shortcuts"
    
    $exePath = "$InstallPath\build\bin\ai_creator.exe"
    $desktopPath = [Environment]::GetFolderPath("Desktop")
    $startMenuPath = [Environment]::GetFolderPath("StartMenu")
    
    # Desktop shortcut
    $shell = New-Object -ComObject WScript.Shell
    $shortcut = $shell.CreateShortcut("$desktopPath\AI Creator.lnk")
    $shortcut.TargetPath = $exePath
    $shortcut.WorkingDirectory = "$InstallPath\build\bin"
    $shortcut.Description = "AI Creator - Intelligent AI Generation Platform"
    $shortcut.Save()
    Write-Success "Desktop shortcut created"
    
    # Start Menu shortcut
    $startMenuFolder = "$startMenuPath\Programs\AI Creator"
    if (-not (Test-Path $startMenuFolder)) {
        New-Item -ItemType Directory -Path $startMenuFolder -Force | Out-Null
    }
    
    $shortcut = $shell.CreateShortcut("$startMenuFolder\AI Creator.lnk")
    $shortcut.TargetPath = $exePath
    $shortcut.WorkingDirectory = "$InstallPath\build\bin"
    $shortcut.Description = "AI Creator - Intelligent AI Generation Platform"
    $shortcut.Save()
    Write-Success "Start Menu shortcut created"
}

function Main {
    Write-Header "AI Creator Setup Wizard"
    Write-Host "Version 1.0.0" -ForegroundColor $ColorCyan
    Write-Host "Intelligent AI Generation Platform" -ForegroundColor $ColorCyan
    
    # Check prerequisites
    if (-not (Show-Prerequisites)) {
        Write-Error-Custom "Prerequisites not met. Installation cannot continue."
        exit 1
    }
    
    # Select installation path
    $installPath = Select-InstallPath
    Write-Success "Installation path: $installPath"
    
    # Create installation directory
    if (-not (Test-Path $installPath)) {
        New-Item -ItemType Directory -Path $installPath -Force | Out-Null
        Write-Success "Installation directory created"
    }
    
    # Copy source files
    Write-Header "Copying Files"
    $sourceDir = Split-Path -Parent $MyInvocation.MyCommand.Path
    
    Write-Info "Copying source files..."
    Copy-Item -Path "$sourceDir\cpp-backend" -Destination "$installPath\cpp-backend" -Recurse -Force
    Write-Success "Files copied"
    
    # Build application
    $buildPath = "$installPath\build"
    if (-not (Build-Application $installPath $buildPath)) {
        Write-Error-Custom "Installation failed during build"
        exit 1
    }
    
    # Create shortcuts
    Create-Shortcuts $installPath
    
    # Completion
    Write-Header "Installation Complete!"
    Write-Success "AI Creator has been installed successfully"
    Write-Info "Installation path: $installPath"
    Write-Info "Executable: $installPath\build\bin\ai_creator.exe"
    
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor $ColorCyan
    Write-Host "1. Check your Desktop for the AI Creator shortcut" -ForegroundColor $ColorCyan
    Write-Host "2. Double-click to launch the application" -ForegroundColor $ColorCyan
    Write-Host "3. Explore the interface and create AI models" -ForegroundColor $ColorCyan
    
    Write-Host ""
    if (-not $Silent) {
        $launch = Read-Host "Launch AI Creator now? (Y/N)"
        if ($launch -eq "Y" -or $launch -eq "y") {
            & "$installPath\build\bin\ai_creator.exe"
        }
    }
}

# Run main function
Main
