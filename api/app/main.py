from api.app.routers import folders
from fastapi import FastAPI

app = FastAPI()

app.include_router(folders.router)

@app.get("/")
def main():
    return {"message": "Welcome to TileShard API!"}