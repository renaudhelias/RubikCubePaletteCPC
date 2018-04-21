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

génère labyPac_map.h et labyPac_map.c