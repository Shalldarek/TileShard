# 🗂️ TileShard

> A powerful note-taking application with dual interfaces: CLI and REST API

**TileShard** is a modern note-taking system built on SQLite, offering seamless integration between a C++ command-line interface and a Python REST API. Organize your notes into folders, create rich connections between them, and access your data through your preferred interface.

---

## ✨ Features

- 📝 **Dual Interface**: Access notes via CLI REPL or REST API
- 🗂️ **Folder Organization**: Structure notes into logical folders
- 🔗 **Note Linking**: Create connections between related notes
- 💾 **SQLite Backend**: Reliable, embedded database with no external dependencies
- 🚀 **High Performance**: Native C/C++ with optimized SQLite queries
- 🔄 **Shared Data**: Both interfaces work with the same database

---

## 🏗️ Tech Stack

| Layer | Technology | Purpose |
|-------|-----------|---------|
| **CLI** | C++ with C modules | Command-line interface & core operations |
| **REST API** | Python FastAPI + SQLAlchemy | HTTP API for programmatic access |
| **Database** | SQLite3 | Reliable, embedded data persistence |
| **Build** | Makefile (gcc/g++) | Compilation and linking |

---

## 📂 Project Structure

```
TileShard/
├── worker/                          # CLI application
│   ├── include/DbManager.h          # Database manager class definition
│   └── src/
│       ├── DbManager.cpp            # SQLite wrapper implementation
│       └── main.cpp                 # REPL CLI engine
│
├── modules/                         # Core C operations library
│   ├── include/                     # Function declarations
│   │   ├── getfolders.h / getnotes.h      # Read operations
│   │   ├── addfolder.h / addnote.h        # Create operations
│   │   ├── updatefolder.h / updatenote.h  # Update operations
│   │   ├── deletefolder.h / deletenote.h  # Delete operations
│   │   ├── print_folder_content.h         # Display utilities
│   │   ├── allcommands.h                  # Help system
│   │   └── echo.h                         # Testing utility
│   └── src/                         # Implementation files
│
├── api/                             # REST API application
│   ├── app/
│   │   ├── __init__.py              # FastAPI app initialization
│   │   ├── main.py                  # Root endpoint
│   │   ├── database.py              # SQLAlchemy configuration
│   │   ├── crud.py                  # Raw SQL CRUD operations
│   │   └── routers/
│   │       ├── folders.py           # Folders endpoints
│   │       └── notes.py             # Notes endpoints (future)
│   └── requirements.txt             # Python dependencies
│
├── tiles.db                         # SQLite database (shared)
├── Makefile                         # Build configuration
└── README.md                        # This file
```

---

## 🗄️ Database Schema

The application uses three interconnected tables:

### 📁 **folders**
```sql
CREATE TABLE folders (
  id        INTEGER PRIMARY KEY AUTOINCREMENT,
  name      TEXT UNIQUE NOT NULL,
  created_at TEXT DEFAULT CURRENT_TIMESTAMP
);
```

### 📄 **notes**
```sql
CREATE TABLE notes (
  id        INTEGER PRIMARY KEY AUTOINCREMENT,
  folder_id INTEGER REFERENCES folders(id) ON DELETE SET NULL,
  title     TEXT NOT NULL,
  content   TEXT DEFAULT '',
  created_at TEXT DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT DEFAULT CURRENT_TIMESTAMP
);
-- Indexes: idx_notes_folder_id, idx_notes_title
```

### 🔗 **links**
```sql
CREATE TABLE links (
  id        INTEGER PRIMARY KEY AUTOINCREMENT,
  source_id INTEGER NOT NULL REFERENCES notes(id) ON DELETE CASCADE,
  target_id INTEGER NOT NULL REFERENCES notes(id) ON DELETE CASCADE,
  UNIQUE(source_id, target_id)
);
```

---

## 🖥️ CLI Commands

Launch the interactive CLI with `./tileshard`:

| Command | Usage | Description |
|---------|-------|-------------|
| `getf` | — | 📋 List all folders |
| `addf` | `<name>` | ➕ Create a new folder |
| `updf` | `<id> <name>` | ✏️ Rename a folder |
| `delf` | `<id>` | 🗑️ Delete a folder |
| `getn` | — | 📋 List all notes |
| `addn` | `<folder_id> <title> <content>` | ➕ Create a note in a folder |
| `updn` | `<id> <title> <content>` | ✏️ Update a note |
| `deln` | `<id>` | 🗑️ Delete a note |
| `echo` | `<message>` | 🔊 Echo a message (testing) |
| `help` | — | ❓ Show all commands |
| `exit` | — | 👋 Quit the application |

### Example CLI Session
```bash
$ ./tileshard
TileShard> addf "My Projects"
Folder created with ID: 1
TileShard> addn 1 "Project Alpha" "Initial setup phase"
Note created with ID: 1
TileShard> getn
Note ID: 1 | Title: Project Alpha | Folder: 1
TileShard> exit
```

---

## 🌐 REST API Endpoints

The FastAPI server runs on `http://localhost:8000` by default.

### 📊 Folders Endpoints

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| `GET` | `/` | — | Welcome message |
| `GET` | `/folders/` | — | 📋 List all folders |
| `POST` | `/folders/` | `{"name": "..."}` | ➕ Create a folder |
| `PUT` | `/folders/{id}` | `{"name": "..."}` | ✏️ Rename a folder |
| `DELETE` | `/folders/{id}` | — | 🗑️ Delete a folder |

### Notes Endpoints (Future)
Notes CRUD is implemented in C modules but not yet exposed via REST API.

### Example API Usage
```bash
# List all folders
curl http://localhost:8000/folders/

# Create a folder
curl -X POST http://localhost:8000/folders/ \
  -H "Content-Type: application/json" \
  -d '{"name": "My Projects"}'

# Update a folder
curl -X PUT http://localhost:8000/folders/1 \
  -H "Content-Type: application/json" \
  -d '{"name": "Work Projects"}'

# Delete a folder
curl -X DELETE http://localhost:8000/folders/1
```

---

## 🚀 Getting Started

### Prerequisites
- **C++**: g++ compiler (C++11 or later)
- **C**: gcc compiler
- **SQLite3**: Development libraries (`libsqlite3-dev` on Ubuntu/Debian)
- **Python**: 3.8+ (for REST API only)

### Build & Run CLI

```bash
# Build the CLI application
make

# Run the CLI
./tileshard

# Clean build artifacts
make clean
```

### Build & Run REST API

```bash
# Navigate to the API directory
cd api

# Install Python dependencies
pip install -r requirements.txt

# Start the API server
uvicorn app.main:app --reload

# API will be available at http://localhost:8000
```

### Verify Installation

```bash
# Test CLI functionality
./tileshard
TileShard> echo "Hello, TileShard!"
Hello, TileShard!
TileShard> help
TileShard> exit

# Test API
cd api && uvicorn app.main:app --reload &
sleep 2
curl http://localhost:8000/folders/
```

---

## ⚙️ Configuration

### Database Location
- **CLI**: `./tiles.db` (in the repository root)
- **API**: `/home/venca/TileShard/tiles.db` (absolute path)

Both interfaces share the same database file.

### API Configuration
Edit `api/app/database.py` to modify database connection settings or `api/app/main.py` to adjust API routes.

---

## ⚠️ Known Limitations & Quirks

1. **Concurrent Writes**: Both CLI and API write to the same `tiles.db` file. Use careful coordination to avoid conflicts.

2. **Foreign Key Constraints**: SQLite foreign key enforcement is disabled by default. `ON DELETE SET NULL` and `ON DELETE CASCADE` won't trigger without explicit `PRAGMA foreign_keys = ON`.

3. **Delete Operations**: The delete-folder module doesn't check `sqlite3_changes()`, so deleting a non-existent folder silently succeeds.

4. **Help Text**: The `allCommands()` function hardcodes help text. Adding new CLI commands requires manual updates here.

5. **API Limitations**: Only the folders endpoint is implemented. Notes CRUD exists in C modules but isn't exposed via REST API yet.

---

## 🔧 Development

### Adding New CLI Commands

1. Create a new `.h` and `.c` file in `modules/include/` and `modules/src/`
2. Implement the CRUD function using prepared statements
3. Update `modules/include/allcommands.h` with the help text
4. Add the command handler in `worker/src/main.cpp`
5. Update the Makefile if needed and recompile

### Adding New API Endpoints

1. Create a new router file in `api/app/routers/`
2. Define your endpoints using FastAPI decorators
3. Import and include the router in `api/app/__init__.py`
4. Test and document the new endpoints

---

## 📜 License

This project is provided as-is for personal and educational use.

---

## 🤝 Contributing

Found a bug or have a suggestion? Feel free to improve the project!

---

**Made with ❤️ for note-taking enthusiasts**
