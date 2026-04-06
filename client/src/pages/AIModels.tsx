import { Card } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { useState } from "react";
import { Search, Download, Trash2, Eye, Settings } from "lucide-react";
import { Link } from "wouter";

/**
 * AIModels Page - AI Model Library and Management
 * Design: Grid/list view of all created AI models with actions
 * Color Theme: Dark background with neon green accents
 */
export default function AIModels() {
  const [searchQuery, setSearchQuery] = useState("");
  const [viewMode, setViewMode] = useState<"grid" | "list">("grid");

  const mockModels = [
    {
      id: 1,
      name: "Neural Network v3",
      algorithm: "Deep Learning",
      framework: "TensorFlow",
      accuracy: "92%",
      status: "Active",
      skills: ["Image Recognition", "Classification"],
      createdDate: "2026-03-15",
      fileSize: "245 MB",
    },
    {
      id: 2,
      name: "Decision Tree Classifier",
      algorithm: "Decision Tree",
      framework: "Scikit-learn",
      accuracy: "87%",
      status: "Testing",
      skills: ["Classification"],
      createdDate: "2026-03-10",
      fileSize: "12 MB",
    },
    {
      id: 3,
      name: "Deep Learning Model",
      algorithm: "Neural Network",
      framework: "PyTorch",
      accuracy: "95%",
      status: "Deployed",
      skills: ["Image Recognition", "NLP"],
      createdDate: "2026-03-05",
      fileSize: "512 MB",
    },
    {
      id: 4,
      name: "Regression Algorithm",
      algorithm: "Linear Regression",
      framework: "Custom C++",
      accuracy: "89%",
      status: "Active",
      skills: ["Regression", "Time Series"],
      createdDate: "2026-02-28",
      fileSize: "8 MB",
    },
    {
      id: 5,
      name: "Clustering Engine",
      algorithm: "K-Means",
      framework: "OpenCV",
      accuracy: "84%",
      status: "Active",
      skills: ["Clustering", "Anomaly Detection"],
      createdDate: "2026-02-20",
      fileSize: "156 MB",
    },
    {
      id: 6,
      name: "NLP Transformer",
      algorithm: "Transformer",
      framework: "PyTorch",
      accuracy: "91%",
      status: "Testing",
      skills: ["Natural Language Processing"],
      createdDate: "2026-02-15",
      fileSize: "1.2 GB",
    },
  ];

  const filteredModels = mockModels.filter(model =>
    model.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
    model.algorithm.toLowerCase().includes(searchQuery.toLowerCase())
  );

  return (
    <div className="min-h-screen bg-background p-4 lg:p-8">
      <div className="max-w-7xl mx-auto">
        {/* Header */}
        <div className="mb-8">
          <h1 className="text-4xl font-bold glow-text mb-2" style={{ fontFamily: "Space Mono, monospace" }}>
            AI Models
          </h1>
          <p className="text-foreground/60">Manage and deploy your AI models</p>
        </div>

        {/* Controls */}
        <div className="flex flex-col md:flex-row gap-4 mb-8">
          <div className="flex-1 relative">
            <Search className="absolute left-3 top-1/2 -translate-y-1/2 w-5 h-5 text-primary/50" />
            <Input
              placeholder="Search models..."
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              className="pl-10 bg-background border-primary/30 text-foreground placeholder:text-foreground/40"
            />
          </div>

          <div className="flex gap-2">
            <Button
              onClick={() => setViewMode("grid")}
              variant={viewMode === "grid" ? "default" : "outline"}
              className={viewMode === "grid" ? "bg-primary text-background" : "border-primary text-primary"}
            >
              Grid
            </Button>
            <Button
              onClick={() => setViewMode("list")}
              variant={viewMode === "list" ? "default" : "outline"}
              className={viewMode === "list" ? "bg-primary text-background" : "border-primary text-primary"}
            >
              List
            </Button>
          </div>

          <Link href="/create">
            <Button className="bg-primary text-background hover:bg-primary/90 neon-glow">
              Create New
            </Button>
          </Link>
        </div>

        {/* Models Grid View */}
        {viewMode === "grid" && (
          <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6">
            {filteredModels.map((model) => (
              <Card
                key={model.id}
                className="bg-card border-primary/20 p-6 hover:border-primary/60 transition-all group cursor-pointer"
              >
                <div className="flex justify-between items-start mb-4">
                  <div className="flex-1">
                    <h3 className="text-lg font-semibold text-foreground group-hover:text-primary transition-colors">
                      {model.name}
                    </h3>
                    <p className="text-sm text-foreground/60">{model.algorithm}</p>
                  </div>
                  <span className={`px-2 py-1 rounded text-xs font-semibold ${
                    model.status === "Active"
                      ? "bg-primary/20 text-primary"
                      : model.status === "Deployed"
                        ? "bg-green-500/20 text-green-400"
                        : "bg-yellow-500/20 text-yellow-400"
                  }`}>
                    {model.status}
                  </span>
                </div>

                <div className="space-y-2 mb-4 text-sm">
                  <p className="text-foreground/70"><span className="text-primary">Framework:</span> {model.framework}</p>
                  <p className="text-foreground/70"><span className="text-primary">Accuracy:</span> {model.accuracy}</p>
                  <p className="text-foreground/70"><span className="text-primary">Size:</span> {model.fileSize}</p>
                </div>

                <div className="mb-4">
                  <p className="text-xs text-foreground/60 mb-2">Skills:</p>
                  <div className="flex flex-wrap gap-1">
                    {model.skills.map((skill) => (
                      <span
                        key={skill}
                        className="px-2 py-1 bg-primary/10 text-primary text-xs rounded border border-primary/30"
                      >
                        {skill}
                      </span>
                    ))}
                  </div>
                </div>

                <div className="flex gap-2">
                  <Button size="sm" variant="outline" className="flex-1 border-primary text-primary hover:bg-primary/10">
                    <Eye className="w-4 h-4 mr-1" /> View
                  </Button>
                  <Button size="sm" variant="outline" className="border-primary text-primary hover:bg-primary/10">
                    <Download className="w-4 h-4" />
                  </Button>
                  <Button size="sm" variant="outline" className="border-primary text-primary hover:bg-primary/10">
                    <Settings className="w-4 h-4" />
                  </Button>
                </div>
              </Card>
            ))}
          </div>
        )}

        {/* Models List View */}
        {viewMode === "list" && (
          <div className="space-y-3">
            {filteredModels.map((model) => (
              <Card
                key={model.id}
                className="bg-card border-primary/20 p-4 hover:border-primary/60 transition-all"
              >
                <div className="flex flex-col md:flex-row md:items-center md:justify-between gap-4">
                  <div className="flex-1">
                    <h3 className="text-lg font-semibold text-foreground mb-1">{model.name}</h3>
                    <div className="flex flex-wrap gap-4 text-sm text-foreground/60">
                      <span>{model.algorithm}</span>
                      <span>•</span>
                      <span>{model.framework}</span>
                      <span>•</span>
                      <span>Accuracy: {model.accuracy}</span>
                      <span>•</span>
                      <span>{model.fileSize}</span>
                    </div>
                  </div>

                  <div className="flex items-center gap-4">
                    <span className={`px-3 py-1 rounded text-xs font-semibold ${
                      model.status === "Active"
                        ? "bg-primary/20 text-primary"
                        : model.status === "Deployed"
                          ? "bg-green-500/20 text-green-400"
                          : "bg-yellow-500/20 text-yellow-400"
                    }`}>
                      {model.status}
                    </span>
                    <div className="flex gap-2">
                      <Button size="sm" variant="outline" className="border-primary text-primary hover:bg-primary/10">
                        <Eye className="w-4 h-4" />
                      </Button>
                      <Button size="sm" variant="outline" className="border-primary text-primary hover:bg-primary/10">
                        <Download className="w-4 h-4" />
                      </Button>
                      <Button size="sm" variant="outline" className="border-primary text-primary hover:bg-primary/10">
                        <Trash2 className="w-4 h-4" />
                      </Button>
                    </div>
                  </div>
                </div>
              </Card>
            ))}
          </div>
        )}

        {filteredModels.length === 0 && (
          <div className="text-center py-12">
            <p className="text-foreground/60 mb-4">No models found matching your search</p>
            <Link href="/create">
              <Button className="bg-primary text-background hover:bg-primary/90">
                Create Your First Model
              </Button>
            </Link>
          </div>
        )}
      </div>
    </div>
  );
}
