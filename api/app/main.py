from api.app.routers import folders, notes
from fastapi import FastAPI

app = FastAPI()

app.include_router(folders.router)
app.include_router(notes.router)

@app.get("/")
def main():
    return {"message": "Welcome to TileShard API!"}