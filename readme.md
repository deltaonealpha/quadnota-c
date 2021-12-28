﻿<link href="https://cdnjs.cloudflare.com/ajax/libs/mermaid/6.0.0/mermaid.css" rel="stylesheet" />
  <script src="https://cdnjs.cloudflare.com/ajax/libs/mermaid/6.0.0/mermaid.js"></script>
  <script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
  
 ![Banner](https://github.com/deltaonealpha/quadnota-c/blob/main/media_assets/banner.png?raw=true)

# QUADNOTA
A clean and minimal **notes and todo webapp** with a backend written in **vanilla C**.
> Frontend Stack: `HTML/ CSS/ SAAS/ Bootstrap5` 
> Backend Stack: `C/ Libpq/ Ulfius/ PostgreSQL`

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
This project is licensed under the GNU-APL-v3 Public License. For more information, read license.md. 