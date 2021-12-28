![Banner](https://github.com/deltaonealpha/quadnota-c/blob/main/media_assets/banner.png?raw=true)

![Build CI](https://img.shields.io/badge/build-passing-brightgreen) 
![License](https://img.shields.io/badge/license-MIT-orange)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/deltaonealpha/quadnota-c) 
![GitHub issues](https://img.shields.io/github/issues/deltaonealpha/quadnota-c)

# QUADNOTA
A clean and minimal **notes and todo webapp** with a backend written in **vanilla C**.
> Frontend Stack: `HTML/ CSS/ SAAS/ Bootstrap5` 
> Backend Stack: `C/ Libpq/ Ulfius/ PostgreSQL`

`🔴 Note: Building QuadNota from source requires C99+`

## The Design
QUADNOTA takes on a design experience inspired by the perspex in nature. Gentle curves flow along transparent tiles that let you see what's behind, as a soothing blur encaptures your attention towards itself.

This accessibility-oriented development of the UI allows for a more relaxed experience.


## Logic Flow
The following sequence diagram shows the flow of logic behind QUADNOTA's working:
```mermaid
sequenceDiagram
Frontend ->> API: Fetches all notes (/list/notes)
Note left of API: jQuery is used for API hits on<br/>QuadNota
API-->>Backend: I require the notes
Backend-->>ORM/Driver: I require the notes
ORM/Driver-->>Backend: Notes as SQL object
Backend-->>Backend: Parses SQL to JSON
Note right of Backend: QuadNota uses the <br/>json_aggregate function <br/>to parse JSON on the db<br/>itself, thereby relieving<br/> backend load
Backend-->>API: Returns JSON
Note right of ORM/Driver: QuadNota uses PostegreSQL
```

## License
This project is licensed under the MIT Public License. For more information, read [LICENSE](/LICENSE). 
