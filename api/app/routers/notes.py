from fastapi import APIRouter, Body, Depends, HTTPException
from sqlalchemy.orm import Session
from api.app import crud
from api.app.database import get_db

router = APIRouter(
    prefix="/notes",
    tags=["notes"]
)

@router.get("/")
def get_all_notes(db: Session = Depends(get_db)):
    notes = crud.get_notes(db)

    if notes is None:
        raise HTTPException(status_code=404, detail="No notes found.")
    
    return {"notes": notes}
    

@router.get("/{note_id}")
def get_note(note_id: int, db: Session = Depends(get_db)):
    note = crud.get_note_by_id(db, note_id)
    if note is None:
        raise HTTPException(status_code=404, detail="Note not found.")
    return {"note": note}

@router.post("/")
def create_note(note: dict = Body(...), db: Session = Depends(get_db)):
    if "title" not in note or "content" not in note:
        raise HTTPException(status_code=400, detail="Missing title or content.")

    created_note = crud.create_note(db, note["title"], note["content"])
    return {"message": "Note created successfully.", "note": created_note}

@router.put("/{note_id}")
def update_note(note_id: int, note: dict = Body(...), db: Session = Depends(get_db)):
    if "title" not in note or "content" not in note:
        raise HTTPException(status_code=400, detail="Missing title or content.")

    updated_note = crud.update_note(db, note_id, note["title"], note["content"])

    if updated_note is None:
        raise HTTPException(status_code=404, detail="Note not found.")

    return {"message": "Note updated successfully.", "note": updated_note}

@router.delete("/{note_id}")
def delete_note(note_id: int, db: Session = Depends(get_db)):
    deleted = crud.delete_note(db, note_id)

    if not deleted:
        raise HTTPException(status_code=404, detail="Note not found.")

    return {"message": "Note deleted successfully."}
    