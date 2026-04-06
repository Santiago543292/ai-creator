# AI Creator - Installer Guide

Complete guide to installing AI Creator using the automated setup wizard.

## What is the Installer?

The AI Creator installer is a fully automated setup wizard that:
- ✅ Checks system requirements
- ✅ Installs missing dependencies (CMake)
- ✅ Builds the application from source
- ✅ Creates desktop and Start Menu shortcuts
- ✅ Launches the application

## Installation Methods

### Method 1: Quick Install (Recommended)

**Fastest way to get started - one click!**

1. **Extract the ZIP file** to any location
2. **Right-click** `QUICK_INSTALL.bat`
3. **Select** "Run as administrator"
4. **Wait** for installation to complete (5-10 minutes)
5. **Done!** Desktop shortcut created automatically

**What it does:**
- Installs to: `C:\Users\[YourUsername]\AI Creator`
- Automatically downloads and installs CMake if needed
- Builds the application
- Creates shortcuts
- Optionally launches the app

### Method 2: Custom Install

**Install to a custom location with options**

1. **Extract the ZIP file**
2. **Right-click** `INSTALL.bat`
3. **Select** "Run as administrator"
4. **Follow the prompts:**
   - Choose installation path (or press Enter for default)
   - Confirm prerequisites
   - Wait for build to complete
5. **Done!** Shortcuts created

### Method 3: PowerShell Setup Wizard

**Advanced installation with more options**

```powershell
# Open PowerShell as Administrator
# Navigate to the extracted folder
cd C:\path\to\ai-creator

# Run the setup wizard
.\setup_wizard.ps1

# Or with custom path
.\setup_wizard.ps1 -InstallPath "D:\MyApps\AI Creator"

# Or silent mode (no prompts)
.\setup_wizard.ps1 -Silent
```

## System Requirements

### Minimum
- **Windows 7** or later (64-bit)
- **2 GB RAM**
- **500 MB free disk space**

### Recommended
- **Windows 10/11** (64-bit)
- **8 GB RAM**
- **2 GB free disk space**

### Required Software
- **Visual Studio 2017** or later (with C++ workload)
  - Download: https://visualstudio.microsoft.com/
  - The installer will check for this
- **CMake 3.15+**
  - The installer can download and install this automatically

## Step-by-Step Installation

### Step 1: Prepare Your Computer

1. **Download** `ai-creator-installer.zip`
2. **Extract** to any location (e.g., `C:\Downloads\ai-creator`)
3. **Note the location** - you'll need it later

### Step 2: Check Prerequisites

**Visual Studio:**
1. Check if you have Visual Studio 2017 or later installed
2. If not, download from: https://visualstudio.microsoft.com/
3. During installation, select "Desktop development with C++"
4. Installation takes 20-30 minutes

**CMake:**
- The installer will check for CMake
- If not found, it will offer to download and install it
- Installation is automatic and takes 2-3 minutes

### Step 3: Run the Installer

**Option A: Quick Install (Easiest)**
```
1. Right-click QUICK_INSTALL.bat
2. Select "Run as administrator"
3. Wait for completion
```

**Option B: Custom Install**
```
1. Right-click INSTALL.bat
2. Select "Run as administrator"
3. Choose installation location when prompted
4. Wait for completion
```

### Step 4: Wait for Build

The installer will:
1. Copy files (~1 minute)
2. Configure the project (~2 minutes)
3. Build the application (~5-10 minutes depending on your computer)

**Total time: 10-15 minutes**

### Step 5: Launch

After installation completes:
1. Look for **"AI Creator"** shortcut on your Desktop
2. Double-click to launch
3. The application window opens
4. Start creating AI models!

## Troubleshooting

### "Access Denied" Error

**Problem:** Installer won't run

**Solution:**
1. Right-click the installer
2. Select "Run as administrator"
3. Click "Yes" when prompted

### "CMake not found" Error

**Problem:** CMake is not installed

**Solution 1 (Automatic):**
- The installer will offer to download and install CMake
- Click "Y" when prompted
- Wait for installation to complete

**Solution 2 (Manual):**
1. Download CMake: https://cmake.org/download/
2. Run the installer
3. Make sure to check "Add CMake to system PATH"
4. Restart the AI Creator installer

### "Visual Studio not found" Error

**Problem:** Visual Studio 2017+ is not installed

**Solution:**
1. Download Visual Studio: https://visualstudio.microsoft.com/
2. Run the installer
3. Select "Desktop development with C++"
4. Complete the installation (20-30 minutes)
5. Restart your computer
6. Run the AI Creator installer again

### Build Failed Error

**Problem:** Compilation failed during build

**Solution:**
1. Ensure Visual Studio is fully installed
2. Check that you have at least 2 GB free disk space
3. Try running the installer again
4. If it still fails, try manual build:
   ```bash
   cd "C:\Users\[YourUsername]\AI Creator\build"
   cmake .. -G "Visual Studio 16 2019"
   cmake --build . --config Release
   ```

### Application Won't Start

**Problem:** ai_creator.exe won't launch

**Solution:**
1. Check that all .dll files are in the same folder as ai_creator.exe
   - Location: `C:\Users\[YourUsername]\AI Creator\build\bin\`
   - Files should be: ai_creator.exe + 5 .dll files
2. Try running from command line to see error:
   ```bash
   cd "C:\Users\[YourUsername]\AI Creator\build\bin"
   ai_creator.exe
   ```
3. Check Windows Event Viewer for error details

## After Installation

### Launching the Application

**Method 1: Desktop Shortcut**
- Double-click the "AI Creator" shortcut on your Desktop

**Method 2: Start Menu**
- Click Start → Search for "AI Creator" → Click the result

**Method 3: Manual**
- Navigate to: `C:\Users\[YourUsername]\AI Creator\build\bin\`
- Double-click: `ai_creator.exe`

### First Launch

When you first launch AI Creator:
1. The main window opens (1200x800 pixels)
2. Dark theme with neon green accents
3. Menu bar at the top (File, View, Help)
4. Home page is displayed by default

### Navigation

Use the **View** menu to navigate between pages:
- **Home** - Welcome and overview
- **Dashboard** - Real-time statistics
- **Create AI** - Build new models
- **Models** - Manage existing models
- **Settings** - Configuration options

## Uninstalling

### Method 1: Windows Settings

1. Open **Settings** → **Apps** → **Apps & features**
2. Search for "AI Creator"
3. Click and select "Uninstall"
4. Follow the prompts

### Method 2: Manual Uninstall

1. Delete the installation folder:
   - Default: `C:\Users\[YourUsername]\AI Creator`
   - Or your custom location
2. Delete the desktop shortcut
3. Delete the Start Menu folder:
   - `C:\Users\[YourUsername]\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\AI Creator`

## Advanced Configuration

### Changing Installation Location

**During Installation:**
- When the installer asks for the path, enter your custom location
- Example: `D:\MyApps\AI Creator`

**After Installation:**
- You can move the entire folder to a new location
- Update the shortcuts to point to the new location

### Running Multiple Instances

You can install AI Creator multiple times in different locations:
1. Extract the ZIP to a different folder
2. Run the installer again
3. Choose a different installation path
4. Each instance will have its own shortcuts

### Command Line Installation

**Silent mode (no prompts):**
```powershell
.\setup_wizard.ps1 -Silent -InstallPath "C:\AI Creator"
```

**Batch mode:**
```bash
INSTALL.bat
# Then press Enter for all prompts to use defaults
```

## Getting Help

### Documentation
- See `NATIVE_APP_BUILD_GUIDE.md` for detailed build information
- See `README.md` for project overview
- See `QUICK_START.md` for quick reference

### Common Issues
1. **Installer won't run** → Run as administrator
2. **CMake not found** → Let installer download it
3. **Visual Studio not found** → Install from visualstudio.microsoft.com
4. **Build fails** → Check disk space and try again
5. **App won't start** → Check all .dll files are present

### Manual Build (If Installer Fails)

If the installer fails, you can build manually:

```bash
# Navigate to installation folder
cd "C:\Users\[YourUsername]\AI Creator"

# Create build directory
mkdir build
cd build

# Configure
cmake ..\cpp-backend -G "Visual Studio 16 2019"

# Build
cmake --build . --config Release

# Run
.\bin\ai_creator.exe
```

## Version Information

- **AI Creator:** 1.0.0
- **Installer Version:** 1.0.0
- **Supported Windows:** 7, 8, 10, 11
- **Architecture:** 64-bit
- **Last Updated:** April 5, 2026

## Support

For issues not covered in this guide:
1. Check the troubleshooting section above
2. Review the build documentation
3. Check Windows Event Viewer for error details
4. Try manual build process

---

**Ready to install? Start with Method 1: Quick Install!**
