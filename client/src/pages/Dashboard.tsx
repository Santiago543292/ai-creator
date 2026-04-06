import { Card } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { BarChart, Bar, LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from "recharts";
import { Cpu, TrendingUp, Zap, Activity } from "lucide-react";
import { Link } from "wouter";

/**
 * Dashboard Page - AI Model Management
 * Design: Grid layout with stats cards, charts, and model list
 * Color Theme: Dark background with neon green accents
 */
export default function Dashboard() {
  const mockData = [
    { name: "Jan", models: 4, performance: 78 },
    { name: "Feb", models: 6, performance: 82 },
    { name: "Mar", models: 8, performance: 85 },
    { name: "Apr", models: 12, performance: 88 },
  ];

  const stats = [
    { icon: Cpu, label: "Active Models", value: "12", color: "text-primary" },
    { icon: TrendingUp, label: "Avg Performance", value: "88%", color: "text-primary" },
    { icon: Zap, label: "Total Deployments", value: "45", color: "text-primary" },
    { icon: Activity, label: "System Status", value: "Optimal", color: "text-primary" },
  ];

  return (
    <div className="min-h-screen bg-background p-4 lg:p-8">
      <div className="max-w-7xl mx-auto">
        {/* Header */}
        <div className="mb-8">
          <h1 className="text-4xl font-bold glow-text mb-2" style={{ fontFamily: "Space Mono, monospace" }}>
            Dashboard
          </h1>
          <p className="text-foreground/60">Monitor and manage your AI models</p>
        </div>

        {/* Stats Grid */}
        <div className="grid md:grid-cols-2 lg:grid-cols-4 gap-4 mb-8">
          {stats.map((stat, index) => {
            const Icon = stat.icon;
            return (
              <Card key={index} className="bg-card border-primary/20 p-6">
                <div className="flex items-center justify-between">
                  <div>
                    <p className="text-foreground/60 text-sm mb-1">{stat.label}</p>
                    <p className={`text-3xl font-bold ${stat.color}`}>{stat.value}</p>
                  </div>
                  <Icon className={`w-8 h-8 ${stat.color} opacity-50`} />
                </div>
              </Card>
            );
          })}
        </div>

        {/* Charts */}
        <div className="grid lg:grid-cols-2 gap-6 mb-8">
          {/* Models Created Chart */}
          <Card className="bg-card border-primary/20 p-6">
            <h2 className="text-lg font-semibold mb-4 text-foreground">Models Created</h2>
            <ResponsiveContainer width="100%" height={300}>
              <BarChart data={mockData}>
                <CartesianGrid strokeDasharray="3 3" stroke="rgba(0, 221, 0, 0.1)" />
                <XAxis dataKey="name" stroke="rgba(232, 232, 232, 0.5)" />
                <YAxis stroke="rgba(232, 232, 232, 0.5)" />
                <Tooltip
                  contentStyle={{
                    backgroundColor: "rgba(26, 26, 26, 0.9)",
                    border: "1px solid rgba(0, 221, 0, 0.3)",
                    borderRadius: "8px",
                  }}
                />
                <Bar dataKey="models" fill="#00DD00" radius={[8, 8, 0, 0]} />
              </BarChart>
            </ResponsiveContainer>
          </Card>

          {/* Performance Trend Chart */}
          <Card className="bg-card border-primary/20 p-6">
            <h2 className="text-lg font-semibold mb-4 text-foreground">Performance Trend</h2>
            <ResponsiveContainer width="100%" height={300}>
              <LineChart data={mockData}>
                <CartesianGrid strokeDasharray="3 3" stroke="rgba(0, 221, 0, 0.1)" />
                <XAxis dataKey="name" stroke="rgba(232, 232, 232, 0.5)" />
                <YAxis stroke="rgba(232, 232, 232, 0.5)" />
                <Tooltip
                  contentStyle={{
                    backgroundColor: "rgba(26, 26, 26, 0.9)",
                    border: "1px solid rgba(0, 221, 0, 0.3)",
                    borderRadius: "8px",
                  }}
                />
                <Line
                  type="monotone"
                  dataKey="performance"
                  stroke="#00DD00"
                  strokeWidth={3}
                  dot={{ fill: "#00DD00", r: 6 }}
                  activeDot={{ r: 8 }}
                />
              </LineChart>
            </ResponsiveContainer>
          </Card>
        </div>

        {/* Recent Models */}
        <Card className="bg-card border-primary/20 p-6">
          <div className="flex justify-between items-center mb-4">
            <h2 className="text-lg font-semibold text-foreground">Recent Models</h2>
            <Link href="/models">
              <Button variant="outline" className="border-primary text-primary hover:bg-primary/10">
                View All
              </Button>
            </Link>
          </div>

          <div className="space-y-3">
            {[
              { name: "Neural Network v3", status: "Active", accuracy: "92%" },
              { name: "Decision Tree Classifier", status: "Testing", accuracy: "87%" },
              { name: "Deep Learning Model", status: "Deployed", accuracy: "95%" },
              { name: "Regression Algorithm", status: "Active", accuracy: "89%" },
            ].map((model, index) => (
              <div
                key={index}
                className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg hover:border-primary/60 transition-all"
              >
                <div className="flex-1">
                  <p className="font-semibold text-foreground">{model.name}</p>
                  <p className="text-sm text-foreground/60">Accuracy: {model.accuracy}</p>
                </div>
                <div className="flex items-center gap-4">
                  <span className={`px-3 py-1 rounded-full text-xs font-semibold ${
                    model.status === "Active"
                      ? "bg-primary/20 text-primary"
                      : model.status === "Deployed"
                        ? "bg-green-500/20 text-green-400"
                        : "bg-yellow-500/20 text-yellow-400"
                  }`}>
                    {model.status}
                  </span>
                </div>
              </div>
            ))}
          </div>
        </Card>
      </div>
    </div>
  );
}
