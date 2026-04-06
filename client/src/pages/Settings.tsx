import { Card } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Switch } from "@/components/ui/switch";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@/components/ui/tabs";
import { useState } from "react";
import { Settings as SettingsIcon, Folder, Bell, Shield, Download } from "lucide-react";

/**
 * Settings Page - Application Configuration
 * Design: Tabbed settings interface with various configuration options
 * Color Theme: Dark background with neon green accents
 */
export default function Settings() {
  const [settings, setSettings] = useState<Record<string, any>>({
    projectName: "AI Creator",
    outputPath: "C:\\Users\\User\\AI_Models",
    autoCompile: true,
    enableNotifications: true,
    autoBackup: true,
    backupInterval: "daily",
    debugMode: false,
    logLevel: "info",
  });

  const handleToggle = (key: string) => {
    setSettings(prev => ({
      ...prev,
      [key]: !prev[key],
    }));
  };

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement | HTMLSelectElement>) => {
    const { name, value } = e.target;
    setSettings(prev => ({
      ...prev,
      [name]: value,
    }));
  };

  return (
    <div className="min-h-screen bg-background p-4 lg:p-8">
      <div className="max-w-4xl mx-auto">
        {/* Header */}
        <div className="mb-8">
          <h1 className="text-4xl font-bold glow-text mb-2" style={{ fontFamily: "Space Mono, monospace" }}>
            Settings
          </h1>
          <p className="text-foreground/60">Configure your AI Creator environment</p>
        </div>

        {/* Settings Tabs */}
        <Tabs defaultValue="general" className="w-full">
          <TabsList className="grid w-full grid-cols-4 bg-card border border-primary/20">
            <TabsTrigger
              value="general"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <SettingsIcon className="w-4 h-4 mr-2" />
              General
            </TabsTrigger>
            <TabsTrigger
              value="compilation"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <Folder className="w-4 h-4 mr-2" />
              Compilation
            </TabsTrigger>
            <TabsTrigger
              value="notifications"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <Bell className="w-4 h-4 mr-2" />
              Notifications
            </TabsTrigger>
            <TabsTrigger
              value="security"
              className="data-[state=active]:bg-primary data-[state=active]:text-background"
            >
              <Shield className="w-4 h-4 mr-2" />
              Security
            </TabsTrigger>
          </TabsList>

          {/* General Tab */}
          <TabsContent value="general" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-xl font-semibold text-foreground mb-4">General Settings</h2>

              <div className="space-y-6">
                <div>
                  <Label htmlFor="projectName" className="text-foreground mb-2 block">
                    Project Name
                  </Label>
                  <Input
                    id="projectName"
                    name="projectName"
                    value={settings.projectName}
                    onChange={handleInputChange}
                    className="bg-background border-primary/30 text-foreground"
                  />
                </div>

                <div>
                  <Label htmlFor="outputPath" className="text-foreground mb-2 block">
                    Output Directory
                  </Label>
                  <div className="flex gap-2">
                    <Input
                      id="outputPath"
                      name="outputPath"
                      value={settings.outputPath}
                      onChange={handleInputChange}
                      className="flex-1 bg-background border-primary/30 text-foreground"
                    />
                    <Button variant="outline" className="border-primary text-primary hover:bg-primary/10">
                      Browse
                    </Button>
                  </div>
                </div>

                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Auto Compile on Save</p>
                    <p className="text-sm text-foreground/60">Automatically compile models when changes are saved</p>
                  </div>
                  <Switch
                    checked={settings.autoCompile}
                    onCheckedChange={() => handleToggle("autoCompile")}
                  />
                </div>

                <Button className="w-full bg-primary text-background hover:bg-primary/90 neon-glow">
                  Save Changes
                </Button>
              </div>
            </Card>
          </TabsContent>

          {/* Compilation Tab */}
          <TabsContent value="compilation" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-xl font-semibold text-foreground mb-4">Compilation Settings</h2>

              <div className="space-y-6">
                <div>
                  <Label htmlFor="logLevel" className="text-foreground mb-2 block">
                    Log Level
                  </Label>
                  <select
                    id="logLevel"
                    name="logLevel"
                    value={settings.logLevel}
                    onChange={handleInputChange}
                    className="w-full px-3 py-2 bg-background border border-primary/30 text-foreground rounded-lg"
                  >
                    <option value="debug">Debug</option>
                    <option value="info">Info</option>
                    <option value="warning">Warning</option>
                    <option value="error">Error</option>
                  </select>
                </div>

                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Debug Mode</p>
                    <p className="text-sm text-foreground/60">Enable detailed compilation and runtime debugging</p>
                  </div>
                  <Switch
                    checked={settings.debugMode}
                    onCheckedChange={() => handleToggle("debugMode")}
                  />
                </div>

                <div className="p-4 bg-primary/10 border border-primary/30 rounded-lg">
                  <p className="text-sm text-foreground/70">
                    <span className="text-primary font-semibold">Note:</span> Compilation settings affect .exe and .dll file generation. Changes will take effect on the next build.
                  </p>
                </div>

                <Button className="w-full bg-primary text-background hover:bg-primary/90 neon-glow">
                  Save Changes
                </Button>
              </div>
            </Card>
          </TabsContent>

          {/* Notifications Tab */}
          <TabsContent value="notifications" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-xl font-semibold text-foreground mb-4">Notification Settings</h2>

              <div className="space-y-4">
                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Enable Notifications</p>
                    <p className="text-sm text-foreground/60">Receive alerts for compilation and deployment events</p>
                  </div>
                  <Switch
                    checked={settings.enableNotifications}
                    onCheckedChange={() => handleToggle("enableNotifications")}
                  />
                </div>

                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Compilation Complete</p>
                    <p className="text-sm text-foreground/60">Notify when model compilation finishes</p>
                  </div>
                  <Switch defaultChecked />
                </div>

                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Deployment Status</p>
                    <p className="text-sm text-foreground/60">Notify when AI model is deployed or fails</p>
                  </div>
                  <Switch defaultChecked />
                </div>

                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Error Alerts</p>
                    <p className="text-sm text-foreground/60">Notify immediately on errors or warnings</p>
                  </div>
                  <Switch defaultChecked />
                </div>

                <Button className="w-full bg-primary text-background hover:bg-primary/90 neon-glow">
                  Save Changes
                </Button>
              </div>
            </Card>
          </TabsContent>

          {/* Security Tab */}
          <TabsContent value="security" className="space-y-6">
            <Card className="bg-card border-primary/20 p-6">
              <h2 className="text-xl font-semibold text-foreground mb-4">Security & Backup</h2>

              <div className="space-y-6">
                <div className="flex items-center justify-between p-4 bg-background border border-primary/20 rounded-lg">
                  <div>
                    <p className="font-semibold text-foreground">Auto Backup</p>
                    <p className="text-sm text-foreground/60">Automatically backup your AI models</p>
                  </div>
                  <Switch
                    checked={settings.autoBackup}
                    onCheckedChange={() => handleToggle("autoBackup")}
                  />
                </div>

                {settings.autoBackup && (
                  <div>
                    <Label htmlFor="backupInterval" className="text-foreground mb-2 block">
                      Backup Interval
                    </Label>
                    <select
                      id="backupInterval"
                      name="backupInterval"
                      value={settings.backupInterval}
                      onChange={handleInputChange}
                      className="w-full px-3 py-2 bg-background border border-primary/30 text-foreground rounded-lg"
                    >
                      <option value="hourly">Hourly</option>
                      <option value="daily">Daily</option>
                      <option value="weekly">Weekly</option>
                      <option value="monthly">Monthly</option>
                    </select>
                  </div>
                )}

                <Button variant="outline" className="w-full border-primary text-primary hover:bg-primary/10">
                  <Download className="w-4 h-4 mr-2" />
                  Create Manual Backup
                </Button>

                <div className="p-4 bg-primary/10 border border-primary/30 rounded-lg">
                  <p className="text-sm text-foreground/70">
                    <span className="text-primary font-semibold">Security Note:</span> All AI models and data are stored locally on your computer. Backups are encrypted and stored securely.
                  </p>
                </div>

                <Button className="w-full bg-primary text-background hover:bg-primary/90 neon-glow">
                  Save Changes
                </Button>
              </div>
            </Card>
          </TabsContent>
        </Tabs>
      </div>
    </div>
  );
}
