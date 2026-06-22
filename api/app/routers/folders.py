from api.app.database import get_db
from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from sqlalchemy import text


router = APIRouter(
    prefix="/folders",
    tags=["folders"]
)

@router.get("/")
def get_folders(db: Session = Depends(get_db)):
    folders = db.execute(
        text("SELECT * FROM folders")
    ).mappings().all()

    if not folders:
        return {"message": "No folders found."}

    return {"folders": folders}
    
