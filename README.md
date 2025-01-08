# Simple File Versioning System (SFVS)

A lightweight C++ application for managing file versions using a linked list-based version control system. This tool allows users to track, compare, and restore previous versions of a file while maintaining simplicity.

## Features

- **Version Control**: 
  - Add file content as new versions only if changes are detected.
  - Remove specific versions and renumber remaining versions.
  - Restore any version to the original file.
- **Comparison**: Compare two versions line-by-line, highlighting differences.
- **Search**: Search all versions for a specific keyword.
- **Persistence**: Save and load version data from a file for session continuity.

## How It Works

- Each file version is stored in a linked list, with unique hashes for change detection.
- Users interact through a simple menu for adding, removing, printing, comparing, and searching versions.
- File data and metadata are saved to a persistent storage file.

## How to Run

1. Compile the program:
   ```bash
   g++ -o file_versioning SVC.cpp
