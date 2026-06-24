from sqlalchemy import text
from sqlalchemy.orm import Session


def get_folders(db: Session):
    folders = db.execute(
        text("SELECT * FROM folders")
    ).mappings().all()

    if not folders:
        return None

    return folders


def create_folder(db: Session, name: str):
    result = db.execute(
        text("INSERT INTO folders (name) VALUES (:name)"),
        {"name": name}
    )
    db.commit()

    folder_id = result.lastrowid
    folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    return folder


def update_folder(db: Session, folder_id: int, name: str):
    existing_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    if not existing_folder:
        return None

    db.execute(
        text("UPDATE folders SET name = :name WHERE id = :folder_id"),
        {"name": name, "folder_id": folder_id}
    )
    db.commit()

    updated_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    return updated_folder


def delete_folder(db: Session, folder_id: int):
    existing_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    if not existing_folder:
        return False

    db.execute(
        text("DELETE FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    )
    db.commit()

    return True

def get_notes(db: Session):
    notes = db.execute(
        text(
            """
            SELECT
                notes.id,
                notes.folder_id,
                folders.name AS folder_name,
                notes.title,
                notes.content,
                notes.created_at,
                notes.updated_at
            FROM notes
            LEFT JOIN folders ON folders.id = notes.folder_id
            ORDER BY notes.updated_at DESC, notes.id DESC
            """
        )
    ).mappings().all()

    if not notes:
        return None

    return notes

def get_note_by_id(db: Session, note_id: int):
    note = db.execute(
        text("SELECT * FROM notes WHERE id = :note_id"),
        {"note_id": note_id}
    ).mappings().first()

    if not note:
        return None

    return note


def create_note(db: Session, title: str, content: str):
    result = db.execute(
        text("INSERT INTO notes (title, content) VALUES (:title, :content)"),
        {"title": title, "content": content}
    )
    db.commit()

    note_id = result.lastrowid
    note = db.execute(
        text("SELECT * FROM notes WHERE id = :note_id"),
        {"note_id": note_id}
    ).mappings().first()

    return note


def update_note(db: Session, note_id: int, title: str, content: str):
    result = db.execute(
        text("UPDATE notes SET title = :title, content = :content WHERE id = :note_id"),
        {"title": title, "content": content, "note_id": note_id}
    )
    db.commit()

    if result.rowcount == 0:
        return None

    updated_note = db.execute(
        text("SELECT * FROM notes WHERE id = :note_id"),
        {"note_id": note_id}
    ).mappings().first()

    return updated_note


def delete_note(db: Session, note_id: int):
    result = db.execute(
        text("DELETE FROM notes WHERE id = :note_id"),
        {"note_id": note_id}
    )
    db.commit()

    if result.rowcount == 0:
        return False

    return True