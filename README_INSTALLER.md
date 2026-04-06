# AI Creator - Installer Package

Welcome to AI Creator! This package contains everything you need to install and run the AI Creator application on your Windows computer.

## Quick Start (2 Minutes)

### Fastest Way to Install

1. **Extract this ZIP file** to any location
2. **Right-click** `QUICK_INSTALL.bat`
3. **Select** "Run as administrator"
4. **Wait** for installation to complete
5. **Done!** Look for the shortcut on your Desktop

That's it! The installer handles everything automatically.

## What's Inside

```
ai-creator-installer/
├── QUICK_INSTALL.bat           ← One-click installer (RECOMMENDED)
├── INSTALL.bat                 ← Custom installer
├── setup_wizard.ps1            ← PowerShell setup wizard
├── INSTALLER_GUIDE.md          ← Detailed installation guide
├── README_INSTALLER.md         ← This file
├── NATIVE_APP_BUILD_GUIDE.md   ← Build documentation
├── cpp-backend/                ← Source code
│   ├── src/                    ← Implementation files
│   ├── include/                ← Header files
│   ├── CMakeLists.txt          ← Build configuration
│   ├── models/                 ← Model storage
│   └── libs/                   ← Framework integrations
└── [other files]
```

## Installation Options

### Option 1: Quick Install (Easiest) ⭐

```
Right-click QUICK_INSTALL.bat → Run as administrator
```

**What it does:**
- Installs to default location: `C:\Users\[YourUsername]\AI Creator`
- Automatically downloads CMake if needed
- Builds the application
- Creates desktop shortcut
- Ready to use!

**Time: 10-15 minutes**

### Option 2: Custom Install

```
Right-click INSTALL.bat → Run as administrator
```

**What it does:**
- Asks for installation location
- Checks prerequisites
- Builds the application
- Creates shortcuts
- More control over installation

**Time: 10-15 minutes**

### Option 3: PowerShell Setup Wizard

```powershell
# Open PowerShell as Administrator
.\setup_wizard.ps1
```

**Features:**
- Graphical prompts
- Automatic CMake installation
- Custom path selection
- Silent mode available

**Time: 10-15 minutes**

## System Requirements

### Minimum
- Windows 7 or later (64-bit)
- 2 GB RAM
- 500 MB free disk space

### Recommended
- Windows 10 or 11 (64-bit)
- 8 GB RAM
- 2 GB free disk space

### Required Software
- **Visual Studio 2017 or later** (with C++ workload)
  - Download: https://visualstudio.microsoft.com/
  - The installer will check for this
- **CMake 3.15+**
  - The installer can download and install automatically

## Installation Steps

### Step 1: Check Prerequisites

**Visual Studio:**
- Do you have Visual Studio 2017 or later installed?
- If not, download from: https://visualstudio.microsoft.com/
- Select "Desktop development with C++" during installation

**CMake:**
- The installer will check and install if needed
- No action required from you

### Step 2: Run the Installer

**Recommended: Quick Install**
1. Right-click `QUICK_INSTALL.bat`
2. Select "Run as administrator"
3. Wait for completion

**Alternative: Custom Install**
1. Right-click `INSTALL.bat`
2. Select "Run as administrator"
3. Follow the prompts

### Step 3: Wait for Build

The installer will:
1. Copy files (~1 minute)
2. Configure project (~2 minutes)
3. Build application (~5-10 minutes)

**Total: 10-15 minutes**

### Step 4: Launch

After installation:
1. Look for "AI Creator" shortcut on Desktop
2. Double-click to launch
3. Application opens
4. Start creating AI models!

## Troubleshooting

### "Access Denied" Error
- Right-click the installer
- Select "Run as administrator"
- Click "Yes" when prompted

### "CMake not found" Error
- The installer will offer to download it
- Click "Y" to proceed
- Or download manually from: https://cmake.org/download/

### "Visual Studio not found" Error
- Download from: https://visualstudio.microsoft.com/
- Install with "Desktop development with C++" option
- Restart your computer
- Run the installer again

### Build Failed
- Ensure Visual Studio is fully installed
- Check you have 2 GB free disk space
- Try running the installer again
- See INSTALLER_GUIDE.md for more help

### Application Won't Start
- Check all .dll files are in the same folder as ai_creator.exe
- Try running from command line to see errors
- See INSTALLER_GUIDE.md for detailed troubleshooting

## After Installation

### Launching the App

**Method 1: Desktop Shortcut** (Easiest)
- Double-click the "AI Creator" shortcut

**Method 2: Start Menu**
- Click Start → Search "AI Creator" → Click result

**Method 3: Manual**
- Navigate to: `C:\Users\[YourUsername]\AI Creator\build\bin\`
- Double-click: `ai_creator.exe`

### First Launch

When you open AI Creator:
1. Main window appears (1200x800)
2. Dark theme with neon green accents
3. Menu bar at top (File, View, Help)
4. Home page displayed

### Navigation

Use the **View** menu to navigate:
- **Home** - Welcome and overview
- **Dashboard** - Real-time statistics
- **Create AI** - Build new models
- **Models** - Manage models
- **Settings** - Configuration

## Uninstalling

### Method 1: Windows Settings
1. Settings → Apps → Apps & features
2. Search "AI Creator"
3. Click "Uninstall"

### Method 2: Manual
1. Delete folder: `C:\Users\[YourUsername]\AI Creator`
2. Delete desktop shortcut
3. Delete Start Menu folder

## Documentation

| File | Purpose |
|------|---------|
| `INSTALLER_GUIDE.md` | Detailed installation guide |
| `NATIVE_APP_BUILD_GUIDE.md` | Build and development guide |
| `QUICK_START.md` | Quick reference |
| `README.md` | Project overview |

## What You're Getting

### Main Application
- **ai_creator.exe** - Native Windows desktop application
- Runs directly on your computer (no browser needed)
- Dark theme with QIX branding

### Components
- **model_manager.dll** - Model management
- **data_loader.dll** - Data loading
- **compiler.dll** - Compilation engine
- **neural_network.dll** - Neural networks
- **decision_tree.dll** - Decision trees

### Features
✅ Native Windows GUI  
✅ Dark theme with neon green accents  
✅ 5 main pages (Home, Dashboard, Create AI, Models, Settings)  
✅ Menu-based navigation  
✅ Modular DLL architecture  
✅ No external dependencies  

## Frequently Asked Questions

**Q: Do I need to install Visual Studio?**
A: Yes, Visual Studio 2017 or later is required. Download from visualstudio.microsoft.com

**Q: Will the installer download CMake?**
A: Yes, if CMake is not found, the installer will offer to download and install it.

**Q: How long does installation take?**
A: Typically 10-15 minutes, depending on your computer speed.

**Q: Can I install to a custom location?**
A: Yes, use INSTALL.bat and choose a custom path when prompted.

**Q: Where are the files installed?**
A: Default: `C:\Users\[YourUsername]\AI Creator`

**Q: Can I run multiple instances?**
A: Yes, install to different locations and each will have its own shortcuts.

**Q: How do I uninstall?**
A: Delete the installation folder or use Windows Settings → Apps & features

**Q: What if the installer fails?**
A: See INSTALLER_GUIDE.md troubleshooting section for detailed help.

## Support

For issues or questions:
1. Check the troubleshooting section above
2. Read INSTALLER_GUIDE.md for detailed help
3. Review NATIVE_APP_BUILD_GUIDE.md for build information
4. Check Windows Event Viewer for error details

## Version Information

- **AI Creator:** 1.0.0
- **Installer:** 1.0.0
- **Windows:** 7, 8, 10, 11 (64-bit)
- **Last Updated:** April 5, 2026

## Next Steps

1. **Extract this ZIP file**
2. **Right-click QUICK_INSTALL.bat**
3. **Select "Run as administrator"**
4. **Wait for installation**
5. **Double-click desktop shortcut to launch**

---

**Ready to install? Start with QUICK_INSTALL.bat!** 🚀
