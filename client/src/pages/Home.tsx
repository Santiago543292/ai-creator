import { Link } from "wouter";
import { Button } from "@/components/ui/button";
import { Zap, Brain, Cpu, Code2, Rocket, Shield } from "lucide-react";

/**
 * Home Page - QIX AI Creator Platform
 * Design: Hero section with feature cards, CTA buttons, neon green accents
 * Color Theme: Dark background (#0A0A0A) with neon green (#00DD00) highlights
 */
export default function Home() {
  const features = [
    {
      icon: Brain,
      title: "AI Generation",
      description: "Create intelligent AI models using advanced algorithms and machine learning",
    },
    {
      icon: Cpu,
      title: "C++ Compilation",
      description: "Compile AI models to native .exe and .dll files for optimal performance",
    },
    {
      icon: Code2,
      title: "Custom Features",
      description: "Define AI algorithms, skills, and deployment configurations",
    },
    {
      icon: Rocket,
      title: "Deploy & Test",
      description: "Deploy AI creations locally with real-time monitoring and testing",
    },
    {
      icon: Shield,
      title: "Data Security",
      description: "Secure storage and management of AI models and training data",
    },
    {
      icon: Zap,
      title: "Performance",
      description: "Lightning-fast AI inference with optimized native compilation",
    },
  ];

  return (
    <div className="min-h-screen bg-background">
      {/* Hero Section */}
      <section className="relative min-h-screen flex items-center justify-center px-4 pt-20 lg:pt-0">
        {/* Background Grid Effect */}
        <div className="absolute inset-0 opacity-10">
          <div className="absolute inset-0 bg-gradient-to-br from-primary/20 to-transparent" />
          <svg className="w-full h-full" xmlns="http://www.w3.org/2000/svg">
            <defs>
              <pattern id="grid" width="40" height="40" patternUnits="userSpaceOnUse">
                <path d="M 40 0 L 0 0 0 40" fill="none" stroke="rgba(0, 221, 0, 0.1)" strokeWidth="1" />
              </pattern>
            </defs>
            <rect width="100%" height="100%" fill="url(#grid)" />
          </svg>
        </div>

        {/* Hero Content */}
        <div className="relative z-10 max-w-4xl mx-auto text-center">
          <div className="mb-8 inline-block">
            <div className="relative">
              <Zap className="w-16 h-16 text-primary mx-auto animate-neon-pulse" />
              <div className="absolute inset-0 bg-primary/30 blur-2xl rounded-full" />
            </div>
          </div>

          <h1 className="text-5xl md:text-7xl font-bold mb-6 glow-text" style={{ fontFamily: "Space Mono, monospace" }}>
            AI Creator
          </h1>

          <p className="text-xl md:text-2xl text-foreground/80 mb-8 max-w-2xl mx-auto">
            Create, train, and deploy intelligent AI models using AI-assisted generation. Build native C++ applications with .exe and .dll compilation.
          </p>

          <div className="flex flex-col sm:flex-row gap-4 justify-center mb-12">
            <Link href="/create">
              <Button className="bg-primary text-background hover:bg-primary/90 px-8 py-6 text-lg font-semibold neon-glow">
                Start Creating
              </Button>
            </Link>
            <Link href="/docs">
              <Button variant="outline" className="border-primary text-primary hover:bg-primary/10 px-8 py-6 text-lg font-semibold">
                Learn More
              </Button>
            </Link>
          </div>

          <p className="text-sm text-muted-foreground">
            ✨ No external dependencies required • 🚀 Full C++ compilation support • 🔒 Local deployment
          </p>
        </div>
      </section>

      {/* Features Section */}
      <section className="py-20 px-4 bg-card/30 border-t border-primary/20">
        <div className="max-w-6xl mx-auto">
          <h2 className="text-4xl font-bold text-center mb-4 glow-text" style={{ fontFamily: "Space Mono, monospace" }}>
            Powerful Features
          </h2>
          <p className="text-center text-foreground/60 mb-16 max-w-2xl mx-auto">
            Everything you need to create, manage, and deploy intelligent AI systems
          </p>

          <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6">
            {features.map((feature, index) => {
              const Icon = feature.icon;
              return (
                <div
                  key={index}
                  className="group p-6 bg-background border border-primary/20 rounded-lg hover:border-primary/60 transition-all duration-300 hover:shadow-lg hover:shadow-primary/20"
                >
                  <div className="mb-4 relative">
                    <Icon className="w-8 h-8 text-primary group-hover:animate-neon-pulse" />
                    <div className="absolute inset-0 bg-primary/20 blur-lg rounded-full opacity-0 group-hover:opacity-100 transition-opacity" />
                  </div>
                  <h3 className="text-lg font-semibold mb-2 text-foreground group-hover:text-primary transition-colors">
                    {feature.title}
                  </h3>
                  <p className="text-foreground/60 text-sm">{feature.description}</p>
                </div>
              );
            })}
          </div>
        </div>
      </section>

      {/* CTA Section */}
      <section className="py-20 px-4 border-t border-primary/20">
        <div className="max-w-2xl mx-auto text-center">
          <h2 className="text-3xl md:text-4xl font-bold mb-6 glow-text" style={{ fontFamily: "Space Mono, monospace" }}>
            Ready to Build?
          </h2>
          <p className="text-foreground/70 mb-8">
            Start creating your first AI model now. No setup required, just pure AI generation power.
          </p>
          <Link href="/create">
            <Button className="bg-primary text-background hover:bg-primary/90 px-8 py-6 text-lg font-semibold neon-glow">
              Create Your First AI
            </Button>
          </Link>
        </div>
      </section>
    </div>
  );
}
