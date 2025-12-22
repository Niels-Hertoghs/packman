# Packman Project

Project gemaakt door Niels Hertoghs (s0241591).
Defense video: https://1drv.ms/v/c/b96c3d903af24271/IQCXGMJIODgWTZb9ogGu888HAUDFQ8PGpYDHNWkVX-67bBk?e=JqkxvF

> Checklist om bij te houden welke onderdelen geïmplementeerd zijn en waar ze zich in de code bevinden.


---

## 🎮 Core Game Requirements — **/40**

- [x] **Startup screen + scoreboard**  
  _Toelichting:_ Te vinden in de menu state klasse, code/view/state_maneger/state.h(.cpp)


- [x] **Maze & collision correctness**  
  _Toelichting:_  het inladen en collision handelen tussen de entities gebeurt in de world klasse. code/logic/world.h(.cpp)

- [x] **Smooth continuous movement**  
  _Toelichting:_  Het bewegen van de entities gebeurt in de klasse movableEntities in logic, de richting wordt bepaald door de afgeleide klasse.

- [x] **Ghost AI**
    - [x] 4 modes (scatter / chase / frightened / eaten)
    - [x] Manhattan distance
    - [x] Direction locking  
      _Toelichting:_  Dit is te vinden in de ghost klasse en de afgeleide klasse ervan.


- [x] **Coin & fruit score modifiers**

- [x] **Fear mode + ghost reversal**  
  _Toelichting:_  De ghosts gaan in fear mode als een fruit geconsumeerd word, dit gebeurt in de world klasse, die detecteerd waneer de ghosts in fear moete moeten en laat alles in fear mode gaan.

- [x] **Level clearing + scaling difficulty**  
  _Toelichting:_  Bij het initialiseren van de wereld (start world method in de world klasse) wordt het level meegegeven en vervolgens worden de correcte sneleheden van de ghostst en pacman berekent. als de ghosts in fear mode gaan wordt de lengte van de fear mode berekent op basis van het level (hoger level kortere fear mode).

- [x] **Life system & game over**

---

## 🧠 Software Design & Code Architecture — **/40**

- [x] **Clear MVC separation**
    - Model (logic)
    - View (SFML rendering)
    - Controller (input / state transitions)  
      _Toelichting:_ Gescheiden gehouden door te werken met namespaces en de view krijgt events door de observers. Met verschillende controllers: voor de observers worldView, voor de logic World en voor de states stateManager

- [x] **Design patterns**
    - [x] MVC
    - [x] Observer
    - [x] Abstract Factory
    - [x] Singleton
    - [x] State  
      _Toelichting:_ geimplementeerd zoals staat uitgelegd in de opdracht.

- [x] **Logic as standalone library (no SFML dependency)**  
  _Toelichting:_ Er is een aparte cmake in de logic, die enkel de logic van de game compileerd.

- [x] **Camera & normalized coordinates**  
  _Toelichting:_ Camera is geimplementeerd en alle objecten in de logic werken met een normalized coordinaten systeem, de normalized coo worden vertaald naar effectieve coordinaten in de camera klasse en dan door de view correct afgebeeld in de window.

- [x] **Polymorphism & extensibility**  
  _Toelichting:_ Zoals u kan zien in de html folder van de doxygen is er veel gebruik gemaakt van polymorphisme.

---

## 🎥 Project Defence Video — **/10**

- [x] **3 min gameplay demo**  
  _Link:_ //TODO: dd

- [ ] **7 min technical explanation**  
  _Link:_

---

## 📄 Documentation — **/10**

- [x] **~2 page written report**
    - Design rationale
    - Architecture overview
    - Pattern motivation  
      _Bestand:_ In de root van het project: pacmanReport.word

- [x] **Code comments & API documentation**  
  _Toelichting:_ Bij elke methode staat duidelijke doxygen commentaar, voor parameters, return types, ... Doorheen de code is ook nog veel gewone comentaar toegevoegd "//" voor verdere verduidelijking van bepaalde code.

---

## 🧪 Build & Architecture Verification

- [x] **Logic library builds without SFML**
  _Toelichting:_ In de logic map staat een aparte cmake, de taak van die cmake is om de logic van de game apart de compileren, zodat dit niets nodig heeft van de representatie. In de cmake in de root wordt de gecompileerde logic dan gelinkt met de representatie.

