# Gebruiksaanwijzing

### opladen / vervangen batterijen
Af en toe ga je de 9V batterij moeten losmaken en een nieuwe 9V batterij in steken.

### draadloze communicatie
#### verbinding maken
Eerst zorg je ervoor dat de auto spanning heeft (de lichtjes van de arduino, de HC-05 en DRV8833 gaan branden), daarna open je de app Serial Bluetooth Terminal op je gsm, als je dat gedaan hebt klik je op het verbindings icoontje dat zich rechts boven bevind en je hebt een verbinden. NOTE: als het de 1ste keer is dan moet je eerst links in de app naar opties gaan dan op devices klikken en dan je HC-05 module selecteren.
#### commando's
debug [alle waardes bekijken]  
on [starten]  
off [stoppen] 
set cycle [µs]  
set power [0..255]  
set diff [0..1]  
set kp [0..]  
set ki [0..]  
set kd [0..]  
calibrate black  
calibrate white  

### kalibratie
Er moet worden gekalibreerd omdat er een verschil is tussen de verschillende sensoren, door een tolerantie op de onderdelen, wat eigen is aan productie. Positioneer de sensoren boven een zwart vlak en voer het commando calibrate black uit in de Terminal. Breng vervolgens de sensoren boven een wit vlak en voer het commando calibrate white uit. De sensoren zijn nu gekalibreerd.  

### settings
De robot rijdt stabiel met volgende parameters:  power = 130, kp = 40, diff = 3

