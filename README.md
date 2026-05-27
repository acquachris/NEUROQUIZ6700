# Sistema Nervoso Quiz — Arduino Mega

Un progetto didattico interattivo realizzato per biologia, dedicato allo studio del **Sistema Nervoso (SN)** attraverso giochi educativi sviluppati con Arduino Mega.  
Il sistema combina elettronica, programmazione e apprendimento tramite un’esperienza coinvolgente con display LCD, tastierino, RFID, pulsanti, LED e buzzer.

---

# 📚 Descrizione del progetto

Il progetto consiste in una piattaforma quiz multifunzione basata su **Arduino Mega**, progettata per aiutare nello studio del Sistema Nervoso in modo dinamico e interattivo.

L’interfaccia utilizza uno **schermo LCD** e un sistema di controllo composto da:
- pulsanti;
- LED;
- buzzer;
- tastierino numerico;
- lettore RFID;
- selettore a levetta a 3 posizioni.

Ogni modalità di gioco presenta feedback sonori e luminosi per indicare risposte corrette o errate.

---

# 🎮 Modalità di gioco

## 1️⃣ Cruciverba Interattivo

Il giocatore deve completare un cruciverba sul Sistema Nervoso.

Una volta risolto:
- viene ottenuto un codice finale;
- il codice deve essere inserito tramite un **keypad a membrana**;
- il sistema verifica automaticamente la correttezza della soluzione.

### Componenti utilizzati
- Tastierino numerico a membrana
- LCD
- LED
- Buzzer

---

## 2️⃣ Quiz a Risposta Multipla

Modalità quiz classica con:
- domanda visualizzata sul display LCD;
- 4 possibili risposte:
  - A
  - B
  - C
  - D

L’utente seleziona la risposta tramite i pulsanti dedicati.

### Funzionalità
- Domande sul Sistema Nervoso
- Controllo automatico delle risposte
- Feedback immediato con LED e buzzer

### Componenti utilizzati
- LCD
- Pulsanti
- LED
- Buzzer

---

## 3️⃣ Associa la Carta (RFID)

Sono presenti **6 carte RFID**, ciascuna associata a una parte del Sistema Nervoso.

Sul display viene mostrata una funzione o un compito del Sistema Nervoso e il giocatore deve:
1. identificare la parte corretta;
2. avvicinare la relativa carta RFID al lettore.

Il sistema controlla automaticamente l’associazione.

### Componenti utilizzati
- Lettore RFID
- Carte RFID
- LCD
- LED
- Buzzer

---

# ⚙️ Menu e Navigazione

Il progetto include un menu principale completamente interattivo.

Le modalità di gioco vengono selezionate tramite:
- uno **switch a 3 posizioni**.

L’interfaccia è progettata per essere:
- intuitiva;
- responsive sul display LCD;
- semplice da utilizzare durante l’attività didattica.

---

# 🧩 Componenti Hardware

- Arduino Mega
- Display LCD
- Keypad a membrana
- Pulsanti
- LED
- Resistenze
- Buzzer
- Lettore RFID
- Carte RFID
- Switch a 3 posizioni
- Breadboard e cablaggio

---

# 💻 Software

Il progetto è stato programmato utilizzando:
- Visual Studio Code
- Linguaggio C++

Il codice gestisce:
- menu;
- logica dei giochi;
- input hardware;
- controllo display;
- lettura RFID;
- effetti sonori e luminosi.

---

# 🎯 Obiettivo Didattico

L’obiettivo del progetto è rendere lo studio del Sistema Nervoso:
- più interattivo,
- più coinvolgente,
- più pratico.

Il sistema unisce:
- informatica;
- elettronica;
- biologia;
- problem solving.

---

# 📷 Funzionamento

Il dispositivo permette agli studenti di:
- imparare attraverso il gioco;
- verificare le proprie conoscenze;
- ricevere feedback immediato;
- interagire fisicamente con il sistema.

---

# 👨‍💻 Autore Repository

**Christian Acquarola**  
Classe **4CLS**  
Anno scolastico **2025/2026**

# 🤝 Gruppo di lavoro

Membri del gruppo:
- Acquarola Andrea
- Acquarola Christian
- Pasciullo Gioele
- Santobuono Antonello
- Simone Francesco Pio

---

## Crediti

Il progetto è stato realizzato come lavoro di gruppo per biologia.
Io, **Christian Acquarola**, mi sono occupato di:
- progettazione elettronica;
- cablaggio dei componenti;
- sviluppo del software;
- programmazione dell’Arduino;
- logica dei giochi;
- integrazione hardware/software;
- gestione del display LCD, RFID, keypad, LED e buzzer.
