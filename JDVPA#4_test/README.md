# [JDVPA#4] Le labyrinthe
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=NEontG3vo6o

__main.c jdvpa4.dsk__

![JDVPA4.dsk.png](JDVPA4.dsk.png)

![GraphicsGale.png](GraphicsGale.png)

GraphicsGale http://graphicsgale.com/us/download.html

Je prend : "Install version".

Si je fais ouvrir, ça propose d'ouvrir sample1.gal ou sample2.gal

Ouvrons "Tiles.bmp", hop.

![GraphicsGale_grille.png](GraphicsGale_grille.png)

Je rajoute une grille custom 2x8 (Setup>add dans cette sélection sourie)

Tiled http://www.mapeditor.org

Je prend : "Download at  itch.io" > "Tiled for Windows (64-bit), snapshot". Je décompresse le contenu dans C:\Program Files\tiled-windows-64bit-snapshot

L'exécutable est "tiled.exe"...

"Nouveau Tileset...">nom:"pacmanTileset",source:"tiles.bmp",largeur:"8px",hauteur:"8px">Enregistrer (ça crée pacmanTileset.tsx)

![Tiled.png](Tiled.png)

"Nouvelle carte...">largeur:"40 Tiles",hauteur:"25 Tiles",largeur:"8px",hauteur:"8px",ordreDAffichageDesTiles:"En haut à gauche" => ça confirme : 320x200 pixels>Enregistrer (ça crée labyPac.tmx)

menu Cartes>"Ajouter un Tileset externe...">choisir "pacmanTileset.tsx".

![Tiled-hop.png](Tiled-hop.png)

Cliquer bêtement sur une des tiles (en bas à droite) et puis ensuite sur la map (au milieu), ho ça marche.

![JDVPA4_labyPac.dsk.png](JDVPA4_labyPac.dsk.png)

perl Tiled_tmx2c.pl labyPac.tmx

permet de générer automatiquement labyPac_map.h et labyPac_map.c à partir de labyPac.tmx

__combat2.c jdvpa4_combat2.dsk__

![JDVPA4_COMBAT2.dsk.png](JDVPA4_COMBAT2.dsk.png)

Passage en mode 1 (4 couleurs), recentrage de quelques animations, révision de la zone de contact.

__combat2m.c jdvpa4_combat2.dsk__

Ajout d'une musique MK.

Afin de convertir un mod en son CPC, j'utilise "Arkos Tracker 2" http://www.julien-nevo.com/arkos/arkos-tracker-2-0-alpha/

On peut lire les mod originaux avec https://milkytracker.titandemo.org/downloads/ afin de se faire une idée, j'utilise juste les boutons "Load", "Play Sng" et "Stop". Je mute les pistes 4 à 8 (il suffit de cliquer droite sur le numéro en haut de la piste) car à l'import le CPC va importer que les 3 premières voies. Quand on clique droit sur le haut d'une piste, il y a "Swap channels" qui permet d'échanger la piste avec la piste où on a posé le curseur clavier (flèche droite/gauche, le carré bleu)

avmk-mod.mod https://modarchive.org/index.php?request=view_by_moduleid&query=34353 est plutôt pas mal avec les pistes 2/3/4 mais pèse lourd 287KB.
mk_bo.mod https://modarchive.org/index.php?request=view_by_moduleid&query=52118 35KB est le plus petit que j'ai trouvé en mod... version bidouillé pour avoir que 3 voies : mk_bo-3voies-4cut.mod

Je lis mk_bo-3voies-4cut.mod sur Arkos Tracker 2, certains son ne sont pas pris en compte, certains sont mauvais, mais la batterie elle passe très bien elle, la voie (qui est aussi moche que l'original mk_bo.mod donc parfais), le timing est correct.

L'export choisi : AKY, en &3000, maigre fichier je trouve.

Bon faut jarter tout les "SAMPLES" et mettre des "FM". Je vais prendre pour le moment les "FM" de Solarium (sks), mais l'octave du coup est mauvais (trop aigu), faudrait réécrire toutes les notes hum.

Bon, allons de l'autre bord, testons un Hello World AKY, Targhan dit qu'il y a un hello world dans le dossier testers/.

Que tout ça se compile avec SJasmPlus ou Rasm... Faudra tenter avec SJasmPlus, une prochaine fois.