from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import text
from sqlalchemy.orm import Session
from api.app.database import get_db

router = APIRouter(
    prefix="/notes",
    tags=["notes"]
)

@router.get("/")
def get_notes(db: Session = Depends(get_db)):
    notes = db.execute(
        text("SELECT * FROM notes")
    ).mappings().all()

    if not notes:
        raise HTTPException(status_code=404, detail="No notes found")
    
    return notes

@router.get("/{note_id}")
def get_note(note_id: int, db: Session = Depends(get_db)):
    note = db.execute(
        text("SELECT * FROM notes WHERE id = :id"),
        {"id": note_id}
    ).mappings().first()

    if not note:
        raise HTTPException(status_code=404, detail="Note not found")
    
    return note

@router.post("/")
def create_note(note: dict, db: Session = Depends(get_db)):
    if "title" not in note or "content" not in note:
        raise HTTPException(status_code=400, detail="Missing title or content")

    db.execute(
        text("INSERT INTO notes (title, content) VALUES (:title, :content)"),
        {"title": note["title"], "content": note["content"]}
    )
    db.commit()
    return {"message": "Note created successfully"}

@router.put("/{note_id}")
def update_note(note_id: int, note: dict, db: Session = Depends(get_db)):
    if "title" not in note or "content" not in note:
        raise HTTPException(status_code=400, detail="Missing title or content")

    result = db.execute(
        text("UPDATE notes SET title = :title, content = :content WHERE id = :id"),
        {"title": note["title"], "content": note["content"], "id": note_id}
    )
    db.commit()

    if result.rowcount == 0:
        raise HTTPException(status_code=404, detail="Note not found")

    return {"message": "Note updated successfully"}

@router.delete("/{note_id}")
def delete_note(note_id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("DELETE FROM notes WHERE id = :id"),
        {"id": note_id}
    )
    db.commit()

    if result.rowcount == 0:
        raise HTTPException(status_code=404, detail="Note not found")

    return {"message": "Note deleted successfully"}
    