from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from api.app.routers import folders, notes
from fastapi import FastAPI, Request

app = FastAPI()

app.include_router(folders.router)
app.include_router(notes.router)

app.mount("/static", StaticFiles(directory="static"), name="static")

templates = Jinja2Templates(directory="templates")

@app.get("/", response_model=None)
def main(request: Request):
    return templates.TemplateResponse(
        request=request, name="mainpage.html"
    )