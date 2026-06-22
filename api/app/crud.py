from fastapi import HTTPException, status
from sqlalchemy import text
from sqlalchemy.orm import Session


def get_folders(db: Session):
    folders = db.execute(
        text("SELECT * FROM folders")
    ).mappings().all()

    if not folders:
        return {"message": "No folders found."}

    return {"folders": folders}


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

    return {"message": "Folder created successfully.", "folder": folder}


def update_folder(db: Session, folder_id: int, name: str):
    existing_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    if not existing_folder:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Folder not found."
        )

    db.execute(
        text("UPDATE folders SET name = :name WHERE id = :folder_id"),
        {"name": name, "folder_id": folder_id}
    )
    db.commit()

    updated_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    return {"message": "Folder updated successfully.", "folder": updated_folder}


def delete_folder(db: Session, folder_id: int):
    existing_folder = db.execute(
        text("SELECT * FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    ).mappings().first()

    if not existing_folder:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Folder not found."
        )

    db.execute(
        text("DELETE FROM folders WHERE id = :folder_id"),
        {"folder_id": folder_id}
    )
    db.commit()

    return {"message": "Folder deleted successfully."}