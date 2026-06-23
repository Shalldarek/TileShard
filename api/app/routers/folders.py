from api.app.crud import (
    create_folder as create_folder_in_db,
    delete_folder as delete_folder_in_db,
    get_folders as get_folders_in_db,
    update_folder as update_folder_in_db,
)
from api.app.database import get_db
from fastapi import APIRouter, Body, Depends, HTTPException, status
from sqlalchemy.orm import Session


router = APIRouter(
    prefix="/folders",
    tags=["folders"]
)

@router.get("/")
def get_folders(db: Session = Depends(get_db)):
    folders = get_folders_in_db(db)

    if folders is None:
        raise HTTPException(status_code=404, detail="No folders found.")

    return {"folders": folders}


@router.post("/", status_code=status.HTTP_201_CREATED)
def create_folder(name: str = Body(...), db: Session = Depends(get_db)):
    folder = create_folder_in_db(db, name)

    return {"message": "Folder created successfully.", "folder": folder}


@router.put("/{folder_id}")
def update_folder(folder_id: int, name: str = Body(...), db: Session = Depends(get_db)):
    folder = update_folder_in_db(db, folder_id, name)

    if folder is None:
        raise HTTPException(status_code=404, detail="Folder not found.")

    return {"message": "Folder updated successfully.", "folder": folder}


@router.delete("/{folder_id}")
def delete_folder(folder_id: int, db: Session = Depends(get_db)):
    deleted = delete_folder_in_db(db, folder_id)

    if not deleted:
        raise HTTPException(status_code=404, detail="Folder not found.")

    return {"message": "Folder deleted successfully."}
    
