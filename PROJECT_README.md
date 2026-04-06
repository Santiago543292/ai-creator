# AI Creator - Intelligent AI Generation Platform

A complete platform for creating, training, and deploying AI models with native C++ compilation to .exe, .dll, .so, and .dylib files.

## Project Overview

AI Creator enables users to:
- **Create AI Models** - Configure and generate custom AI models using various algorithms
- **Train Models** - Train models with your own data and monitor performance
- **Deploy Locally** - Compile models to native binaries for local deployment
- **Monitor Performance** - Track accuracy, metrics, and real-time statistics
- **Manage Models** - Organize, version, and manage multiple AI models

## Project Structure

```
ai-creator/
├── client/                    # React/TypeScript Frontend
│   ├── public/               # Static assets (favicon, robots.txt)
│   ├── src/
│   │   ├── pages/           # Page components
│   │   │   ├── Home.tsx
│   │   │   ├── Dashboard.tsx
│   │   │   ├── CreateAI.tsx
│   │   │   ├── AIModels.tsx
│   │   │   ├── Settings.tsx
│   │   │   ├── Documentation.tsx
│   │   │   └── NotFound.tsx
│   │   ├── components/      # Reusable UI components
│   │   │   ├── Navigation.tsx
│   │   │   └── ErrorBoundary.tsx
│   │   ├── contexts/        # React contexts
│   │   ├── hooks/           # Custom React hooks
│   │   ├── lib/             # Utility functions
│   │   ├── App.tsx          # Main app component
│   │   ├── main.tsx         # React entry point
│   │   └── index.css        # Global styles (QIX theme)
│   └── index.html           # HTML template
├── cpp-backend/             # C++ Backend for AI Compilation
│   ├── include/             # Header files
│   │   ├── types.h
│   │   ├── ai_model.h
│   │   ├── neural_network.h
│   │   ├── decision_tree.h
│   │   ├── model_manager.h
│   │   ├── data_loader.h
│   │   └── compiler.h
│   ├── src/                 # Implementation files
│   │   ├── main.cpp
│   │   ├── ai_model.cpp
│   │   ├── neural_network.cpp
│   │   ├── decision_tree.cpp
│   │   ├── model_manager.cpp
│   │   ├── data_loader.cpp
│   │   └── compiler.cpp
│   ├── models/              # Trained AI models
│   │   ├── neural_networks/
│   │   ├── decision_trees/
│   │   ├── clustering/
│   │   ├── regression/
│   │   └── custom/
│   ├── libs/                # External framework integrations
│   │   ├── tensorflow/
│   │   ├── pytorch/
│   │   ├── opencv/
│   │   └── scikit_learn/
│   ├── output/              # Compiled binaries (.exe, .dll, .so, .dylib)
│   ├── build/               # CMake build directory
│   ├── CMakeLists.txt       # C++ build configuration
│   └── README.md            # C++ backend documentation
├── package.json             # Node.js dependencies
├── tsconfig.json            # TypeScript configuration
├── vite.config.ts           # Vite build configuration
├── tailwind.config.ts       # Tailwind CSS configuration
├── PROJECT_README.md        # This file
└── .gitignore               # Git ignore rules
```

## Technology Stack

### Frontend
- **React 19** - UI framework
- **TypeScript** - Type-safe JavaScript
- **Tailwind CSS 4** - Utility-first CSS
- **Shadcn/UI** - Component library
- **Recharts** - Data visualization
- **Wouter** - Client-side routing
- **Framer Motion** - Animations

### Backend (C++)
- **C++17** - Modern C++ standard
- **CMake** - Build system
- **TensorFlow** - Machine learning framework
- **PyTorch** - Deep learning framework
- **OpenCV** - Computer vision library

### Design Theme
- **QIX Branding** - Neon green (#00DD00) on dark background
- **Typography** - Space Mono (display) + Roboto (body)
- **Animations** - Smooth transitions and neon pulse effects

## Getting Started

### Prerequisites

- Node.js 22.13.0+
- npm or pnpm
- CMake 3.15+ (for C++ backend)
- C++17 compatible compiler

### Installation

1. **Clone and Install Dependencies**
```bash
cd ai-creator
pnpm install
```

2. **Start Development Server**
```bash
pnpm dev
```

3. **Build Frontend**
```bash
pnpm build
```

4. **Build C++ Backend**
```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make
```

## Frontend Features

### Pages

#### Home Page
- Hero section with project overview
- Feature highlights with icons
- Call-to-action buttons
- Responsive design

#### Dashboard
- Real-time model statistics
- Performance charts and graphs
- Recent models list
- Model status indicators

#### Create AI
- Multi-step model creation wizard
- Algorithm selection
- Framework configuration
- Skills and deployment options
- Configuration preview

#### AI Models
- Grid and list view modes
- Search and filter capabilities
- Model management actions
- Performance metrics display
- Download and delete options

#### Settings
- General configuration
- Compilation settings
- Notification preferences
- Security and backup options
- Tabbed interface

#### Documentation
- Getting started guide
- API reference
- Code examples
- FAQ section

### Design Features

- **Neon Green Theme** - QIX brand colors throughout
- **Dark Mode** - Professional dark interface
- **Responsive Design** - Mobile, tablet, and desktop support
- **Smooth Animations** - Neon pulse effects and transitions
- **Accessibility** - Keyboard navigation and ARIA labels

## C++ Backend Features

### Core Components

#### AIModel (Base Class)
- Abstract interface for all models
- Training and prediction methods
- Model persistence
- Metadata management

#### NeuralNetwork
- Multi-layer perceptron
- Configurable layers
- Multiple activation functions
- Backpropagation training

#### DecisionTree
- Classification and regression
- Gini impurity calculation
- Tree pruning support

#### ModelManager
- Create and manage models
- Model persistence
- Training orchestration
- Metrics tracking

#### DataLoader
- CSV, JSON, Binary format support
- Data normalization and standardization
- Train/test splitting
- Data augmentation

#### Compiler
- C++ code generation
- Platform-specific compilation
- .exe, .dll, .so, .dylib support
- Optimization levels

### Supported Algorithms

- Neural Networks
- Decision Trees
- Random Forests
- Support Vector Machines
- K-Means Clustering
- Linear Regression
- Deep Learning
- Custom implementations

### Supported Frameworks

- TensorFlow
- PyTorch
- OpenCV
- Scikit-learn
- Custom C++

### Target Platforms

- Windows (.exe, .dll)
- Linux (.so)
- macOS (.dylib)

## API Endpoints

### Model Management
- `POST /api/models/create` - Create new model
- `GET /api/models` - List all models
- `GET /api/models/{id}` - Get model details
- `DELETE /api/models/{id}` - Delete model
- `POST /api/models/{id}/compile` - Compile to binary

### Training
- `POST /api/models/{id}/train` - Train model
- `GET /api/models/{id}/metrics` - Get metrics

### Prediction
- `POST /api/models/{id}/predict` - Make prediction
- `POST /api/models/{id}/batch-predict` - Batch predictions

## Configuration

### Environment Variables

```env
VITE_APP_TITLE=AI Creator
VITE_APP_LOGO=QIX
VITE_ANALYTICS_ENDPOINT=https://analytics.example.com
VITE_ANALYTICS_WEBSITE_ID=your-website-id
```

### Tailwind Theme

Colors are defined in `client/src/index.css`:
- Primary: #00DD00 (Neon Green)
- Background: #0A0A0A (Deep Black)
- Card: #1A1A1A (Dark Gray)

## Building for Production

### Frontend Build
```bash
pnpm build
```

### C++ Backend Build
```bash
cd cpp-backend
mkdir build-release
cd build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Deployment

### Frontend
- Deploy `dist/` directory to any static hosting
- Supports Netlify, Vercel, GitHub Pages

### C++ Backend
- Compile to platform-specific binaries
- Distribute .exe/.dll (Windows), .so (Linux), .dylib (macOS)
- Include required runtime dependencies

## Development Workflow

1. **Frontend Development**
   - Edit React components in `client/src/`
   - Styles use Tailwind CSS utilities
   - Hot reload with Vite

2. **C++ Development**
   - Edit source files in `cpp-backend/src/`
   - Update headers in `cpp-backend/include/`
   - Rebuild with CMake

3. **Testing**
   - Frontend: Manual testing in browser
   - Backend: Unit tests with C++ testing framework

## Performance Optimization

### Frontend
- Code splitting with React lazy loading
- Image optimization
- CSS minification
- JavaScript bundling

### Backend
- Compiler optimization levels (0-3)
- SIMD vectorization
- GPU acceleration support
- Memory pooling

## Security Considerations

- All data stored locally on user's computer
- No external API calls for AI processing
- Secure model serialization
- Input validation for all data

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

MIT License - See LICENSE file for details

## Support

For issues, questions, or feature requests:
- GitHub Issues: https://github.com/your-repo/issues
- Documentation: See `cpp-backend/README.md` and `client/README.md`

## Roadmap

- [ ] GPU acceleration support
- [ ] Distributed training
- [ ] Model versioning system
- [ ] Advanced visualization tools
- [ ] REST API server
- [ ] Web-based model deployment
- [ ] Automated hyperparameter tuning
- [ ] Model ensemble support

## Acknowledgments

- QIX Logo Design
- React and TypeScript communities
- TensorFlow, PyTorch, and OpenCV teams
- Shadcn/UI component library

---

**Version:** 1.0.0  
**Last Updated:** April 5, 2026  
**Status:** Active Development
