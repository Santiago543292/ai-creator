import { Link } from "wouter";
import { Menu, X, Zap } from "lucide-react";
import { useState } from "react";

/**
 * Navigation Component
 * QIX Brand Theme: Neon green accents on dark background
 * Features: Responsive sidebar navigation, logo branding, active route highlighting
 */
export default function Navigation() {
  const [isOpen, setIsOpen] = useState(false);

  const navItems = [
    { label: "Home", path: "/" },
    { label: "Dashboard", path: "/dashboard" },
    { label: "Create AI", path: "/create" },
    { label: "AI Models", path: "/models" },
    { label: "Settings", path: "/settings" },
    { label: "Documentation", path: "/docs" },
  ];

  return (
    <>
      {/* Mobile Menu Button */}
      <div className="fixed top-4 left-4 z-50 lg:hidden">
        <button
          onClick={() => setIsOpen(!isOpen)}
          className="p-2 bg-card border border-primary rounded-lg text-primary hover:bg-primary hover:text-background transition-all duration-300"
        >
          {isOpen ? <X size={24} /> : <Menu size={24} />}
        </button>
      </div>

      {/* Sidebar Navigation */}
      <aside
        className={`fixed left-0 top-0 h-screen w-64 bg-background border-r border-primary/30 transition-transform duration-300 z-40 ${
          isOpen ? "translate-x-0" : "-translate-x-full lg:translate-x-0"
        }`}
      >
        {/* Logo Section */}
        <div className="p-6 border-b border-primary/30">
          <Link href="/">
            <a className="flex items-center gap-3 group">
              <div className="relative">
                <Zap className="w-8 h-8 text-primary group-hover:animate-neon-pulse" />
                <div className="absolute inset-0 bg-primary/20 blur-lg rounded-full group-hover:bg-primary/40 transition-all" />
              </div>
              <div className="flex flex-col">
                <span className="font-bold text-lg glow-text">QIX</span>
                <span className="text-xs text-muted-foreground">AI Creator</span>
              </div>
            </a>
          </Link>
        </div>

        {/* Navigation Links */}
        <nav className="p-4 space-y-2">
          {navItems.map((item) => (
            <Link key={item.path} href={item.path}>
              <a
                onClick={() => setIsOpen(false)}
                className="block px-4 py-3 rounded-lg text-foreground hover:bg-card hover:text-primary transition-all duration-200 border border-transparent hover:border-primary/50 hover:neon-border group"
              >
                <span className="group-hover:glow-text">{item.label}</span>
              </a>
            </Link>
          ))}
        </nav>

        {/* Footer Info */}
        <div className="absolute bottom-4 left-4 right-4 p-4 bg-card rounded-lg border border-primary/20">
          <p className="text-xs text-muted-foreground mb-2">AI Creator Platform</p>
          <p className="text-xs text-primary font-semibold">v1.0.0</p>
        </div>
      </aside>

      {/* Mobile Overlay */}
      {isOpen && (
        <div
          className="fixed inset-0 bg-black/50 z-30 lg:hidden"
          onClick={() => setIsOpen(false)}
        />
      )}

      {/* Main Content Offset */}
      <div className="lg:ml-64" />
    </>
  );
}
