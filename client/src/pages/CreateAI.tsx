import { Card } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Textarea } from "@/components/ui/textarea";
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from "@/components/ui/select";
import { useState } from "react";
import { Zap, Code2, Settings } from "lucide-react";

/**
 * CreateAI Page - AI Model Creation Wizard
 * Design: Multi-step form with configuration options
 * Color Theme: Dark background with neon green accents
 */
export default function CreateAI() {
  const [step, setStep] = useState(1);
  const [formData, setFormData] = useState({
    name: "",
    description: "",
    algorithmType: "",
    framework: "",
    targetPlatform: "windows",
    skills: [] as string[],
  });

  const algorithmTypes = [
    "Neural Network",
    "Decision Tree",
    "Random Forest",
    "SVM",
    "K-Means Clustering",
    "Linear Regression",
    "Deep Learning",
    "Custom Algorithm",
  ];

  const frameworks = [
    "TensorFlow",
    "PyTorch",
    "OpenCV",
    "Scikit-learn",
    "Custom C++",
  ];

  const availableSkills = [
    "Image Recognition",
    "Natural Language Processing",
    "Time Series Analysis",
    "Anomaly Detection",
    "Classification",
    "Regression",
    "Clustering",
    "Reinforcement Learning",
  ];

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSelectChange = (name: string, value: string) => {
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const toggleSkill = (skill: string) => {
    setFormData(prev => ({
      ...prev,
      skills: prev.skills.includes(skill)
        ? prev.skills.filter(s => s !== skill)
        : [...prev.skills, skill],
    }));
  };

  return (
    <div className="min-h-screen bg-background p-4 lg:p-8">
      <div className="max-w-4xl mx-auto">
        {/* Header */}
        <div className="mb-8">
          <h1 className="text-4xl font-bold glow-text mb-2" style={{ fontFamily: "Space Mono, monospace" }}>
            Create AI Model
          </h1>
          <p className="text-foreground/60">Configure and generate your custom AI model</p>
        </div>

        {/* Progress Steps */}
        <div className="flex justify-between mb-8">
          {[1, 2, 3].map((s) => (
            <div key={s} className="flex items-center flex-1">
              <div
                className={`w-10 h-10 rounded-full flex items-center justify-center font-bold transition-all ${
                  s <= step
                    ? "bg-primary text-background neon-glow"
                    : "bg-card border border-primary/30 text-foreground/60"
                }`}
              >
                {s}
              </div>
              {s < 3 && (
                <div
                  className={`flex-1 h-1 mx-2 transition-all ${
                    s < step ? "bg-primary" : "bg-primary/20"
                  }`}
                />
              )}
            </div>
          ))}
        </div>

        {/* Step 1: Basic Information */}
        {step === 1 && (
          <Card className="bg-card border-primary/20 p-8">
            <div className="space-y-6">
              <div>
                <Label htmlFor="name" className="text-foreground mb-2 block">
                  Model Name
                </Label>
                <Input
                  id="name"
                  name="name"
                  value={formData.name}
                  onChange={handleInputChange}
                  placeholder="e.g., Advanced Neural Network v2"
                  className="bg-background border-primary/30 text-foreground placeholder:text-foreground/40"
                />
              </div>

              <div>
                <Label htmlFor="description" className="text-foreground mb-2 block">
                  Description
                </Label>
                <Textarea
                  id="description"
                  name="description"
                  value={formData.description}
                  onChange={handleInputChange}
                  placeholder="Describe what this AI model will do..."
                  className="bg-background border-primary/30 text-foreground placeholder:text-foreground/40 min-h-32"
                />
              </div>

              <div className="flex gap-4">
                <Button
                  onClick={() => setStep(2)}
                  disabled={!formData.name || !formData.description}
                  className="flex-1 bg-primary text-background hover:bg-primary/90 neon-glow"
                >
                  Next Step
                </Button>
              </div>
            </div>
          </Card>
        )}

        {/* Step 2: Algorithm Configuration */}
        {step === 2 && (
          <Card className="bg-card border-primary/20 p-8">
            <div className="space-y-6">
              <div>
                <Label htmlFor="algorithmType" className="text-foreground mb-2 block flex items-center gap-2">
                  <Code2 className="w-4 h-4" /> Algorithm Type
                </Label>
                <Select value={formData.algorithmType} onValueChange={(value) => handleSelectChange("algorithmType", value)}>
                  <SelectTrigger className="bg-background border-primary/30 text-foreground">
                    <SelectValue placeholder="Select algorithm type" />
                  </SelectTrigger>
                  <SelectContent className="bg-card border-primary/30">
                    {algorithmTypes.map((algo) => (
                      <SelectItem key={algo} value={algo} className="text-foreground">
                        {algo}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
              </div>

              <div>
                <Label htmlFor="framework" className="text-foreground mb-2 block flex items-center gap-2">
                  <Zap className="w-4 h-4" /> Framework
                </Label>
                <Select value={formData.framework} onValueChange={(value) => handleSelectChange("framework", value)}>
                  <SelectTrigger className="bg-background border-primary/30 text-foreground">
                    <SelectValue placeholder="Select framework" />
                  </SelectTrigger>
                  <SelectContent className="bg-card border-primary/30">
                    {frameworks.map((fw) => (
                      <SelectItem key={fw} value={fw} className="text-foreground">
                        {fw}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
              </div>

              <div>
                <Label htmlFor="targetPlatform" className="text-foreground mb-2 block">
                  Target Platform
                </Label>
                <Select value={formData.targetPlatform} onValueChange={(value) => handleSelectChange("targetPlatform", value)}>
                  <SelectTrigger className="bg-background border-primary/30 text-foreground">
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent className="bg-card border-primary/30">
                    <SelectItem value="windows" className="text-foreground">Windows (.exe, .dll)</SelectItem>
                    <SelectItem value="linux" className="text-foreground">Linux (.so)</SelectItem>
                    <SelectItem value="macos" className="text-foreground">macOS (.dylib)</SelectItem>
                  </SelectContent>
                </Select>
              </div>

              <div className="flex gap-4">
                <Button
                  onClick={() => setStep(1)}
                  variant="outline"
                  className="flex-1 border-primary text-primary hover:bg-primary/10"
                >
                  Back
                </Button>
                <Button
                  onClick={() => setStep(3)}
                  disabled={!formData.algorithmType || !formData.framework}
                  className="flex-1 bg-primary text-background hover:bg-primary/90 neon-glow"
                >
                  Next Step
                </Button>
              </div>
            </div>
          </Card>
        )}

        {/* Step 3: Skills & Deployment */}
        {step === 3 && (
          <Card className="bg-card border-primary/20 p-8">
            <div className="space-y-6">
              <div>
                <Label className="text-foreground mb-4 block flex items-center gap-2">
                  <Settings className="w-4 h-4" /> AI Skills
                </Label>
                <div className="grid md:grid-cols-2 gap-3">
                  {availableSkills.map((skill) => (
                    <button
                      key={skill}
                      onClick={() => toggleSkill(skill)}
                      className={`p-3 rounded-lg border transition-all text-left ${
                        formData.skills.includes(skill)
                          ? "bg-primary/20 border-primary text-primary"
                          : "bg-background border-primary/20 text-foreground hover:border-primary/60"
                      }`}
                    >
                      {skill}
                    </button>
                  ))}
                </div>
              </div>

              <div className="p-4 bg-background border border-primary/20 rounded-lg">
                <h3 className="font-semibold text-primary mb-2">Configuration Summary</h3>
                <div className="space-y-1 text-sm text-foreground/70">
                  <p><span className="text-primary">Name:</span> {formData.name}</p>
                  <p><span className="text-primary">Algorithm:</span> {formData.algorithmType}</p>
                  <p><span className="text-primary">Framework:</span> {formData.framework}</p>
                  <p><span className="text-primary">Platform:</span> {formData.targetPlatform}</p>
                  <p><span className="text-primary">Skills:</span> {formData.skills.join(", ") || "None selected"}</p>
                </div>
              </div>

              <div className="flex gap-4">
                <Button
                  onClick={() => setStep(2)}
                  variant="outline"
                  className="flex-1 border-primary text-primary hover:bg-primary/10"
                >
                  Back
                </Button>
                <Button
                  className="flex-1 bg-primary text-background hover:bg-primary/90 neon-glow"
                >
                  Generate AI Model
                </Button>
              </div>
            </div>
          </Card>
        )}
      </div>
    </div>
  );
}
