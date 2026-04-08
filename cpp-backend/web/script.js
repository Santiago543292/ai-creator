// Mobile Navigation Toggle
const hamburger = document.querySelector('.hamburger');
const navMenu = document.querySelector('.nav-menu');
const navLinks = document.querySelectorAll('.nav-link');

if (hamburger) {
    hamburger.addEventListener('click', () => {
        hamburger.classList.toggle('active');
        navMenu.classList.toggle('active');
    });
}

// Close mobile menu when clicking on a link
navLinks.forEach(link => {
    link.addEventListener('click', () => {
        if (hamburger) {
            hamburger.classList.remove('active');
            navMenu.classList.remove('active');
        }
    });
});

// Smooth Scrolling
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            const offsetTop = target.offsetTop - 100;
            window.scrollTo({
                top: offsetTop,
                behavior: 'smooth'
            });
        }
    });
});

// Active Nav Link Detection
window.addEventListener('scroll', () => {
    let current = '';
    const sections = document.querySelectorAll('section');
    
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        const sectionHeight = section.clientHeight;
        if (pageYOffset >= (sectionTop - 150)) {
            current = section.getAttribute('id');
        }
    });

    navLinks.forEach(link => {
        if (link.getAttribute('href') === `#${current}`) {
            link.classList.add('active');
        }
    });
});

// Animated Counter for Stats
function animateCounter(element, target, duration) {
    let start = 0;
    const increment = target / (duration / 16);
    
    const timer = setInterval(() => {
        start += increment;
        if (start >= target) {
            element.textContent = target;
            clearInterval(timer);
        } else {
            element.textContent = Math.floor(start);
        }
    }, 16);
}

// Intersection Observer for Stats Animation
const statsObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const statNumbers = document.querySelectorAll('.stat-number');
            statNumbers.forEach(stat => {
                const target = parseInt(stat.getAttribute('data-target'));
                animateCounter(stat, target, 2000);
            });
            statsObserver.unobserve(entry.target);
        }
    });
}, { threshold: 0.5 });

const statsSection = document.querySelector('.stats');
if (statsSection) {
    statsObserver.observe(statsSection);
}

// Parallax Effect on Hero
window.addEventListener('scroll', () => {
    const scrolled = window.pageYOffset;
    const hero = document.querySelector('.hero');
    if (hero && scrolled < window.innerHeight) {
        hero.style.transform = `translateY(${scrolled * 0.5}px)`;
    }
});

// Card Hover Effects
const cards = document.querySelectorAll('.feature-card, .model-box, .update-card, .capability-card');
cards.forEach(card => {
    card.addEventListener('mouseenter', function() {
        this.style.transition = 'all 0.3s ease';
    });
});

// Add glow effect to buttons
const buttons = document.querySelectorAll('.btn-primary');
buttons.forEach(button => {
    button.addEventListener('mouseenter', function() {
        this.style.boxShadow = '0 0 40px rgba(0, 255, 136, 0.6)';
    });
    
    button.addEventListener('mouseleave', function() {
        this.style.boxShadow = '0 0 20px rgba(0, 255, 136, 0.3)';
    });
});

// Fade in elements on scroll
const fadeInElements = document.querySelectorAll('.feature-card, .model-box, .stat-box, .update-card, .skill-card');

const fadeInObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.style.opacity = '0';
            entry.target.style.transform = 'translateY(20px)';
            
            setTimeout(() => {
                entry.target.style.transition = 'all 0.6s ease';
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }, 100);
            
            fadeInObserver.unobserve(entry.target);
        }
    });
}, { threshold: 0.1 });

fadeInElements.forEach(element => {
    fadeInObserver.observe(element);
});

// Navbar background on scroll
window.addEventListener('scroll', () => {
    const navbar = document.querySelector('.navbar');
    if (window.scrollY > 100) {
        navbar.style.background = 'rgba(0, 0, 0, 0.98)';
        navbar.style.boxShadow = '0 5px 20px rgba(0, 255, 136, 0.1)';
    } else {
        navbar.style.background = 'rgba(0, 0, 0, 0.95)';
        navbar.style.boxShadow = 'none';
    }
});

// Add ripple effect to buttons
function createRipple(event) {
    const button = event.currentTarget;
    const circle = document.createElement('span');
    const diameter = Math.max(button.clientWidth, button.clientHeight);
    const radius = diameter / 2;

    circle.style.width = circle.style.height = `${diameter}px`;
    circle.style.left = `${event.clientX - button.offsetLeft - radius}px`;
    circle.style.top = `${event.clientY - button.offsetTop - radius}px`;
    circle.classList.add('ripple');

    const ripple = button.getElementsByClassName('ripple')[0];
    if (ripple) {
        ripple.remove();
    }

    button.appendChild(circle);
}

const btnElements = document.querySelectorAll('.btn');
btnElements.forEach(btn => {
    btn.addEventListener('click', createRipple);
});

// Add CSS for ripple effect dynamically
const style = document.createElement('style');
style.textContent = `
    .btn {
        position: relative;
        overflow: hidden;
    }
    
    .ripple {
        position: absolute;
        border-radius: 50%;
        background-color: rgba(255, 255, 255, 0.6);
        transform: scale(0);
        animation: ripple-animation 0.6s ease-out;
    }
    
    @keyframes ripple-animation {
        to {
            transform: scale(4);
            opacity: 0;
        }
    }
`;
document.head.appendChild(style);

// Dynamic year in footer
const currentYear = new Date().getFullYear();
const footerYear = document.querySelector('.footer-bottom p');
if (footerYear) {
    footerYear.textContent = `© ${currentYear} QIX. All rights reserved.`;
}

// Add particle effect to hero section
function createParticles() {
    const hero = document.querySelector('.hero');
    if (!hero) return;
    
    const particlesCount = 50;
    
    for (let i = 0; i < particlesCount; i++) {
        const particle = document.createElement('div');
        particle.className = 'particle';
        particle.style.cssText = `
            position: absolute;
            width: 2px;
            height: 2px;
            background: var(--primary-green);
            border-radius: 50%;
            left: ${Math.random() * 100}%;
            top: ${Math.random() * 100}%;
            opacity: ${Math.random() * 0.5};
            animation: float ${5 + Math.random() * 10}s ease-in-out infinite;
            animation-delay: ${Math.random() * 5}s;
        `;
        hero.appendChild(particle);
    }
}

// Add particle animation CSS
const particleStyle = document.createElement('style');
particleStyle.textContent = `
    @keyframes float {
        0%, 100% {
            transform: translateY(0) translateX(0);
        }
        50% {
            transform: translateY(-20px) translateX(10px);
        }
    }
`;
document.head.appendChild(particleStyle);

// Initialize particles
createParticles();

// Progress bar animations
const progressBars = document.querySelectorAll('.progress-fill');
const progressObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const bar = entry.target;
            const width = bar.style.width;
            bar.style.width = '0';
            setTimeout(() => {
                bar.style.transition = 'width 1s ease-out';
                bar.style.width = width;
            }, 100);
            progressObserver.unobserve(entry.target);
        }
    });
}, { threshold: 0.5 });

progressBars.forEach(bar => {
    progressObserver.observe(bar);
});

// Interactive slider for playground
const sliders = document.querySelectorAll('.playground-slider');
sliders.forEach(slider => {
    slider.addEventListener('input', function() {
        const value = (this.value / 100).toFixed(1);
        const valueDisplay = this.parentElement.querySelector('.slider-value');
        if (valueDisplay) {
            valueDisplay.textContent = value;
        }
    });
});

// Simulated chart rendering (placeholder)
function renderChart(canvasId) {
    const canvas = document.getElementById(canvasId);
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    canvas.width = canvas.parentElement.offsetWidth;
    canvas.height = 200;
    
    // Simple line chart simulation
    ctx.strokeStyle = 'rgba(0, 255, 136, 0.8)';
    ctx.lineWidth = 2;
    ctx.beginPath();
    
    const points = 20;
    for (let i = 0; i < points; i++) {
        const x = (canvas.width / points) * i;
        const y = canvas.height / 2 + Math.sin(i / 2) * 50 + Math.random() * 30;
        
        if (i === 0) {
            ctx.moveTo(x, y);
        } else {
            ctx.lineTo(x, y);
        }
    }
    
    ctx.stroke();
}

// Render charts on page load
window.addEventListener('load', () => {
    renderChart('videoChart');
    renderChart('storageChart1');
    renderChart('storageChart2');
    renderChart('learningChart');
});

// Configuration panel interactions
const configInputs = document.querySelectorAll('.config-input, .config-select');
configInputs.forEach(input => {
    input.addEventListener('change', function() {
        console.log('Configuration updated:', this.name || this.id, this.value);
    });
});

// Skill checkbox interactions
const skillCheckboxes = document.querySelectorAll('.skill-option input[type="checkbox"]');
skillCheckboxes.forEach(checkbox => {
    checkbox.addEventListener('change', function() {
        const label = this.nextElementSibling;
        if (this.checked) {
            label.style.borderColor = 'var(--primary-green)';
            label.style.background = 'rgba(0, 255, 136, 0.1)';
        } else {
            label.style.borderColor = 'var(--border-color)';
            label.style.background = 'var(--bg-card)';
        }
    });
});

// AI radio button interactions
const aiRadios = document.querySelectorAll('.ai-option input[type="radio"]');
aiRadios.forEach(radio => {
    radio.addEventListener('change', function() {
        // Remove active styling from all labels
        document.querySelectorAll('.ai-option label').forEach(label => {
            label.style.borderColor = 'var(--border-color)';
            label.style.background = 'var(--bg-card)';
        });
        
        // Add active styling to selected label
        if (this.checked) {
            const label = this.nextElementSibling;
            label.style.borderColor = 'var(--primary-green)';
            label.style.background = 'rgba(0, 255, 136, 0.1)';
        }
    });
});

// Playground textarea functionality
const playgroundTextarea = document.querySelector('.playground-textarea');
const playgroundOutput = document.querySelector('.playground-output');
const runButton = document.querySelector('.action-bar .btn-primary');
const clearButton = document.querySelector('.action-bar .btn-secondary');

if (runButton) {
    runButton.addEventListener('click', function() {
        if (playgroundTextarea && playgroundOutput) {
            const input = playgroundTextarea.value;
            if (input.trim()) {
                playgroundOutput.innerHTML = `<p style="color: var(--primary-green);">Processing...</p>`;
                
                // Simulate AI processing
                setTimeout(() => {
                    playgroundOutput.innerHTML = `
                        <p style="color: var(--text-primary); margin-bottom: 1rem;">AI Response:</p>
                        <p style="color: var(--text-secondary);">[This is a demo - actual AI processing would occur here]</p>
                        <p style="color: var(--text-secondary); margin-top: 1rem;">Input received: "${input.substring(0, 50)}${input.length > 50 ? '...' : ''}"</p>
                    `;
                    
                    // Update metrics
                    document.querySelectorAll('.metrics-bar .metric-value').forEach((metric, index) => {
                        if (index === 0) metric.textContent = '0.5s';
                        if (index === 1) metric.textContent = Math.floor(input.split(' ').length * 1.3);
                        if (index === 2) metric.textContent = '2.4MB';
                    });
                }, 500);
            } else {
                playgroundOutput.innerHTML = `<p style="color: #ef4444;">Please enter a prompt first.</p>`;
            }
        }
    });
}

if (clearButton && playgroundTextarea && playgroundOutput) {
    clearButton.addEventListener('click', function() {
        playgroundTextarea.value = '';
        playgroundOutput.innerHTML = '<p class="output-placeholder">AI response will appear here...</p>';
        
        // Reset metrics
        document.querySelectorAll('.metrics-bar .metric-value').forEach(metric => {
            metric.textContent = '--';
        });
    });
}

// Keyboard shortcut for running AI (Ctrl/Cmd + Enter)
if (playgroundTextarea) {
    playgroundTextarea.addEventListener('keydown', function(e) {
        if ((e.ctrlKey || e.metaKey) && e.key === 'Enter') {
            e.preventDefault();
            if (runButton) runButton.click();
        }
    });
}

// Auto-resize textarea
if (playgroundTextarea) {
    playgroundTextarea.addEventListener('input', function() {
        this.style.height = 'auto';
        this.style.height = (this.scrollHeight) + 'px';
    });
}

// Initialize tooltips and animations
document.addEventListener('DOMContentLoaded', () => {
    // Add hover effects to all interactive elements
    const interactiveElements = document.querySelectorAll('button, a, input, select, textarea');
    interactiveElements.forEach(element => {
        element.style.transition = 'all 0.3s ease';
    });

    // Log initialization
    console.log('%c QIX Platform Initialized ', 'background: #00ff88; color: #000; font-size: 20px; padding: 10px;');
    console.log('A New Future of AI Creation');
    
    // Initialize any page-specific features
    const currentPage = window.location.pathname.split('/').pop() || 'index.html';
    console.log('Current Page:', currentPage);
});

// Export functions for use in inline scripts
window.QIX = {
    selectModel: function(model) {
        console.log('Model selected:', model);
    },
    switchMode: function(mode) {
        console.log('Mode switched:', mode);
    }
};
