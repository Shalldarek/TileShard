# 🗂️ TileShard

> A powerful note-taking application with dual interfaces: CLI and REST API

**TileShard** is a modern note-taking system built on SQLite, offering seamless integration between a C++ command-line interface and a Python REST API. Organize your notes into folders, create rich connections between them, and access your data through your preferred interface.

---

## ✨ Features

- 📝 **Dual Interface**: Access notes via CLI REPL or REST API
- 🖼️ **Rendered Web UI**: Browse folders and notes through FastAPI-backed HTML pages
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
│   ├── include/
│   │   └── DbManager.h              # Database manager class definition
│   └── src/
│       ├── DbManager.cpp            # SQLite wrapper implementation
│       └── main.cpp                 # REPL CLI engine
│
├── modules/                         # Core C operations library
│   ├── include/
│   │   ├── addfolder.h              # Create folder command
│   │   ├── addnote.h                # Create note command
│   │   ├── allcommands.h            # CLI help text
│   │   ├── deletefolder.h           # Delete folder command
│   │   ├── deletenote.h             # Delete note command
│   │   ├── echo.h                   # Utility echo command
│   │   ├── getfolders.h             # List folders command
│   │   ├── getnotes.h               # List notes command
│   │   ├── print_folder_content.h   # Folder content display helper
│   │   ├── updatefolder.h           # Rename folder command
│   │   └── updatenote.h             # Note update command
│   └── src/
│       ├── addfolder.c              # Folder insert implementation
│       ├── addnote.c                # Note insert implementation
│       ├── allcommands.c            # Help text output
│       ├── deletefolder.c           # Folder delete implementation
│       ├── deletenote.c             # Note delete implementation
│       ├── echo.c                   # Echo utility
│       ├── getfolders.c             # Folder query implementation
│       ├── getnotes.c               # Note query implementation
│       ├── print_folder_content.c   # Folder content renderer
│       ├── updatefolder.c           # Folder update implementation
│       └── updatenote.c             # Note update implementation
│
├── api/                             # REST API application
│   ├── app/
│   │   ├── __init__.py              # FastAPI app initialization
│   │   ├── main.py                  # Root HTML page
│   │   ├── database.py              # SQLAlchemy configuration
│   │   ├── crud.py                  # Raw SQL CRUD operations
│   │   ├── routers/
│   │   │   ├── folders.py           # Folder routes and HTML list view
│   │   │   └── notes.py             # Note routes and HTML list view
│   │   ├── static/
│   │   │   ├── style.css            # Shared page styling
│   │   │   └── script.js            # Frontend script placeholder
│   │   └── templates/
│   │       ├── mainpage.html        # Landing page template
│   │       ├── folders.html         # Folder list template
│   │       └── notes.html           # Note list template
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

## 🌐 Web UI & API Endpoints

The FastAPI server runs on `http://localhost:8000` by default.

### HTML Pages

| Method | Path | Description |
|--------|------|-------------|
| `GET` | `/` | Landing page |
| `GET` | `/folders/` | Folder browser rendered from `folders.html` |
| `GET` | `/notes/` | Note browser rendered from `notes.html` |

### Static Assets

| Path | Description |
|------|-------------|
| `/static/style.css` | Shared styling for the web UI |
| `/static/script.js` | Frontend script asset placeholder |

### 📊 Folders Endpoints

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| `GET` | `/` | — | Landing page HTML |
| `GET` | `/folders/` | — | 📋 List all folders |
| `POST` | `/folders/` | `{"name": "..."}` | ➕ Create a folder |
| `PUT` | `/folders/{id}` | `{"name": "..."}` | ✏️ Rename a folder |
| `DELETE` | `/folders/{id}` | — | 🗑️ Delete a folder |

### Notes Endpoints

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| `GET` | `/notes/` | — | 📋 List all notes with folder context |
| `GET` | `/notes/{id}` | — | Show a single note |
| `POST` | `/notes/` | `{"title": "...", "content": "..."}` | ➕ Create a note |
| `PUT` | `/notes/{id}` | `{"title": "...", "content": "..."}` | ✏️ Update a note |
| `DELETE` | `/notes/{id}` | — | 🗑️ Delete a note |

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
