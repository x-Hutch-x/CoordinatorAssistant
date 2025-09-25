# Coordinator Assistant

**Coordinator Assistant** is a lightweight desktop tool built with **C++17** and **wxWidgets**.  
It helps streamline coordination workflows by making repetitive file-based tasks easier to manage.

## Features
- 📂 **File intake** — load daily CSV/Excel files into the app. *(in progress)*  
- 🗂 **Tabbed views** — separate panels for vendors, recordings, and exported outputs. *(in progress)*  
- 🗒️ **State abbreviations cheat sheet** — searchable dialog of all U.S. states + abbreviations. ✅  
- ⏱ **Deadline countdown** — visible timer that tracks critical daily cutoffs. *(planned)*  
- 📝 **Quick updates** — add statuses, notes, or tags directly into the interface. *(planned)*  
- 📧 **Email helper** — generate common email templates with merged order details. *(planned)*  
- 📤 **One-click reporting** — export updated files while preserving original formats. *(planned)*  

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
- ✅ **First utility complete**  
  - State Abbreviations dialog with live search + filtering.  
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
