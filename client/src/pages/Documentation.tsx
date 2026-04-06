import { Card } from "@/components/ui/card";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@/components/ui/tabs";
import { BookOpen, Code, Zap, HelpCircle } from "lucide-react";

/**
 * Documentation Page - API Reference and Guides
 * Design: Tabbed documentation with code examples
 * Color Theme: Dark background with neon green accents
 */
export default function Documentation() {
  return (
    <div className="min-h-screen bg-background p-4 lg:p-8">
      <div className="max-w-4xl mx-auto">
        {/* Header */}
        <div className="mb-8">
          <h1 className="text-4xl font-bold glow-text mb-2" style={{ fontFamily: "Space Mono, monospace" }}>
            Documentation
          </h1>
          <p className="text-foreground/60">Complete guide to AI Creator platform</p>
        </div>

        {/* Documentation Tabs */}
        <Tabs defaultValue="getting-started" className="w-full">
          <TabsList className="grid w-full grid-cols-4 bg-card border border-primary/20">
            <TabsTrigger
              value="getting-started"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <BookOpen className="w-4 h-4 mr-2" />
              Getting Started
            </TabsTrigger>
            <TabsTrigger
              value="api-reference"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <Code className="w-4 h-4 mr-2" />
              API Reference
            </TabsTrigger>
            <TabsTrigger
              value="examples"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <Zap className="w-4 h-4 mr-2" />
              Examples
            </TabsTrigger>
            <TabsTrigger
              value="faq"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <HelpCircle className="w-4 h-4 mr-2" />
              FAQ
            </TabsTrigger>
          </TabsList>

          {/* Getting Started Tab */}
          <TabsContent value="getting-started" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-2xl font-bold text-primary mb-4">Getting Started with AI Creator</h2>

              <div className="space-y-6 text-foreground/80">
                <div>
                  <h3 className="text-lg font-semibold text-primary mb-2">1. Create Your First AI Model</h3>
                  <p className="mb-2">Navigate to the "Create AI" section and follow these steps:</p>
                  <ul className="list-disc list-inside space-y-1 text-foreground/70">
                    <li>Enter a name and description for your AI model</li>
                    <li>Select the algorithm type (Neural Network, Decision Tree, etc.)</li>
                    <li>Choose your framework (TensorFlow, PyTorch, etc.)</li>
                    <li>Select target platform (Windows, Linux, macOS)</li>
                    <li>Configure AI skills and deployment options</li>
                  </ul>
                </div>

                <div>
                  <h3 className="text-lg font-semibold text-primary mb-2">2. Compilation Process</h3>
                  <p className="mb-2">AI Creator automatically compiles your models to native binaries:</p>
                  <ul className="list-disc list-inside space-y-1 text-foreground/70">
                    <li><span className="text-primary">.exe files</span> - Windows executable applications</li>
                    <li><span className="text-primary">.dll files</span> - Dynamic link libraries for Windows</li>
                    <li><span className="text-primary">.so files</span> - Shared objects for Linux</li>
                    <li><span className="text-primary">.dylib files</span> - Dynamic libraries for macOS</li>
                  </ul>
                </div>

                <div>
                  <h3 className="text-lg font-semibold text-primary mb-2">3. Deployment & Testing</h3>
                  <p className="mb-2">Deploy your AI models locally with real-time monitoring:</p>
                  <ul className="list-disc list-inside space-y-1 text-foreground/70">
                    <li>Monitor model performance metrics</li>
                    <li>Test with sample data</li>
                    <li>View detailed logs and diagnostics</li>
                    <li>Optimize and retrain as needed</li>
                  </ul>
                </div>
              </div>
            </Card>
          </TabsContent>

          {/* API Reference Tab */}
          <TabsContent value="api-reference" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-2xl font-bold text-primary mb-4">API Reference</h2>

              <div className="space-y-6">
                <div>
                  <h3 className="text-lg font-semibold text-primary mb-3">Core Endpoints</h3>

                  <div className="space-y-4">
                    <div className="bg-background border border-primary/20 rounded-lg p-4">
                      <p className="font-mono text-primary mb-2">POST /api/models/create</p>
                      <p className="text-sm text-foreground/70 mb-3">Create a new AI model with specified configuration</p>
                      <div className="bg-black/30 border border-primary/30 rounded p-3 text-xs text-primary font-mono overflow-x-auto">
                        <pre>{`{
  "name": "string",
  "algorithm": "string",
  "framework": "string",
  "skills": ["string"],
  "targetPlatform": "windows|linux|macos"
}`}</pre>
                      </div>
                    </div>

                    <div className="bg-background border border-primary/20 rounded-lg p-4">
                      <p className="font-mono text-primary mb-2">GET /api/models</p>
                      <p className="text-sm text-foreground/70 mb-3">Retrieve list of all AI models</p>
                      <div className="bg-black/30 border border-primary/30 rounded p-3 text-xs text-primary font-mono overflow-x-auto">
                        <pre>{`Response: {
  "models": [
    {
      "id": "string",
      "name": "string",
      "status": "active|testing|deployed",
      "accuracy": "number"
    }
  ]
}`}</pre>
                      </div>
                    </div>

                    <div className="bg-background border border-primary/20 rounded-lg p-4">
                      <p className="font-mono text-primary mb-2">POST /api/models/{'{id}'}/compile</p>
                      <p className="text-sm text-foreground/70 mb-3">Compile AI model to native binary (.exe, .dll, etc.)</p>
                      <div className="bg-black/30 border border-primary/30 rounded p-3 text-xs text-primary font-mono overflow-x-auto">
                        <pre>{`Response: {
  "status": "compiling|success|error",
  "outputPath": "string",
  "fileSize": "number"
}`}</pre>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </Card>
          </TabsContent>

          {/* Examples Tab */}
          <TabsContent value="examples" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-2xl font-bold text-primary mb-4">Code Examples</h2>

              <div className="space-y-6">
                <div>
                  <h3 className="text-lg font-semibold text-primary mb-3">Example 1: Loading a Compiled AI Model</h3>
                  <div className="bg-black/30 border border-primary/30 rounded-lg p-4 text-xs text-primary font-mono overflow-x-auto">
                    <pre>{`// C++ Example
#include "ai_model.h"

int main() {
    AIModel model("path/to/model.dll");
    
    // Load training data
    model.loadData("training_data.csv");
    
    // Make predictions
    float prediction = model.predict({1.0, 2.5, 3.2});
    
    std::cout << "Prediction: " << prediction << std::endl;
    
    return 0;
}`}</pre>
                  </div>
                </div>

                <div>
                  <h3 className="text-lg font-semibold text-primary mb-3">Example 2: Creating a Neural Network</h3>
                  <div className="bg-black/30 border border-primary/30 rounded-lg p-4 text-xs text-primary font-mono overflow-x-auto">
                    <pre>{`// Configuration Example
{
  "name": "ImageClassifier",
  "algorithm": "Neural Network",
  "framework": "TensorFlow",
  "layers": [
    {"type": "input", "size": 784},
    {"type": "dense", "units": 128, "activation": "relu"},
    {"type": "dropout", "rate": 0.2},
    {"type": "dense", "units": 10, "activation": "softmax"}
  ],
  "skills": ["Image Recognition", "Classification"]
}`}</pre>
                  </div>
                </div>
              </div>
            </Card>
          </TabsContent>

          {/* FAQ Tab */}
          <TabsContent value="faq" className="space-y-4">
            {[
              {
                q: "What file formats does AI Creator support?",
                a: "AI Creator supports .exe and .dll files for Windows, .so for Linux, and .dylib for macOS. All compiled binaries are native C++ applications.",
              },
              {
                q: "Can I use multiple frameworks?",
                a: "Yes! AI Creator supports TensorFlow, PyTorch, OpenCV, Scikit-learn, and custom C++ implementations. Mix and match frameworks as needed.",
              },
              {
                q: "How do I deploy my AI model?",
                a: "After compilation, your AI model is ready for local deployment. Use the Dashboard to monitor performance and test with sample data.",
              },
              {
                q: "Is there a limit to model size?",
                a: "No hard limits, but larger models may take longer to compile. We recommend keeping models under 2GB for optimal performance.",
              },
              {
                q: "Can I update my AI model after deployment?",
                a: "Yes! You can retrain, modify, and recompile your models at any time. The platform supports version control and rollback.",
              },
              {
                q: "How is my data stored?",
                a: "All AI models and training data are stored locally on your computer. No data is sent to external servers unless explicitly configured.",
              },
            ].map((item, index) => (
              <Card key={index} className="bg-card border-primary/20 p-4">
                <h3 className="font-semibold text-primary mb-2">{item.q}</h3>
                <p className="text-foreground/70 text-sm">{item.a}</p>
              </Card>
            ))}
          </TabsContent>
        </Tabs>
      </div>
    </div>
  );
}
