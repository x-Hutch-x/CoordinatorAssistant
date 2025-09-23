# Coordinator Assistant

**Coordinator Assistant** is a lightweight desktop tool built with **C++17** and **wxWidgets**.  
It helps streamline coordination workflows by making repetitive file-based tasks easier to manage.

## Features (Planned & In Progress)
- 📂 **File intake** — load daily CSV/Excel files into the app.  
- 🗂 **Tabbed views** — separate panels for vendors, recordings, and exported outputs.  
- ⏱ **Deadline countdown** — visible timer that tracks critical daily cutoffs.  
- 📝 **Quick updates** — add statuses, notes, or tags directly into the interface.  
- 📧 **Email helper** — generate common email templates with merged order details.  
- 📤 **One-click reporting** — export updated files while preserving original formats.  

## Tech Stack
- **Language:** C++17  
- **Framework:** wxWidgets (UI + event handling)  
- **Build System:** CMake (vcpkg dependency management)  
- **Target:** Windows 10/11 desktop  

## Current Status
- ✅ **UI foundation built**  
  - Project structure set up with CMake + vcpkg.  
  - Main window loads with working menus and action IDs.  
  - Event table wiring in place for future actions.  
- 🚧 **Active development**  
  - Adding tabbed workflow panels.  
  - Preparing CSV parsing and vendor/recordings data integration.  
- 📌 **Planned**  
  - Deadline countdown timer.  
  - Metrics dashboard.  
  - Refined UX and advanced reporting tools.  

## Why This Project
This project demonstrates:  
- Practical **desktop GUI development** in modern C++.  
- Clear **event-driven UI design** with wxWidgets.  
- Modular builds using **CMake + vcpkg**.  
- How to take a **real-world workflow problem** and build a clean, extensible solution.  

---

🔗 This repository is public and generic to showcase software design skills.  
  
