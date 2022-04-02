# Buttons with-interruption

Voici un exemple de 3 boutons dont l’action est détectée sous interruption sur un ESP32.

Il détecte s’il s’agit d’un appui court ou long selon une valeur prédéterminée BTN_PUSH_TIME ici réglée à 500 millisecondes.

Le programme gère également le debounce qui peut être réglé différemment pour chaque bouton.
C’est le dernier paramètre à entrer lorsque que l’on instancie l’objet et que l’on initialise ses attributs.
Ici le debounce est réglé à 10 millisecondes :

button[0] = {18, 0, false, 0, 0, 0, 10};

Le premier paramètre est la pin utilisée.

Le nombre de boutons peut bien sûr être augmenté, la plus-part des pins de l’ESP32 permettant de provoquer une interruption.

