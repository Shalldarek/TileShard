import os

from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from api.app.routers import folders, notes
from fastapi import FastAPI, Request

app = FastAPI()

app.include_router(folders.router)
app.include_router(notes.router)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

static_dir = os.path.join(BASE_DIR, "static")

app.mount("/static", StaticFiles(directory=static_dir), name="static")

templates = Jinja2Templates(directory=os.path.join(BASE_DIR, "templates"))

@app.get("/", response_model=None)
def main(request: Request):
    return templates.TemplateResponse(
        request=request, name="mainpage.html"
    )