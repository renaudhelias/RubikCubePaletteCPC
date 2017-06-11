# RubikCubePaletteCPC
Inspiré d'une vidéo CPC de MacDeath26 : http://www.youtube.com/watch?v=iMo0bCSMAQ0

RubikCube aux couleurs de la palette CPC qu'on peut acheter physiquement en utilisant le site suivant : http://www.rubiksphotocube.com/fr/designer

![RubikCubePaletteCPC.png](RubikCubePaletteCPC.png)

Après on peut l'utiliser pour sélectionner les INK d'une image CPC créé via ConvImgCpc :

ConvImgCpc [amstrad.eu](http://amstrad.eu/modules/TDMDownloads/) > [ConvImgCpc](http://amstrad.eu/modules/TDMDownloads/singlefile.php?cid=13&lid=186)

Puis Transférer le fichier image.scr résultat sur une disquette via ManageDsk :

ManageDsk [amstrad.eu](http://amstrad.eu/modules/TDMDownloads/) > [ManageDsk](http://amstrad.eu/modules/TDMDownloads/singlefile.php?cid=13&lid=187)

Puis écrire un petit script basic directement sur le CPC pour afficher l'image :
```10 MODE 2
20 BORDER 0
30 INK 0,0:INK 1,1:INK 2,2...
40 LOAD"image.scr",&C000
50 CALL &BB18
save"hop.bas
```
Ici j'utilise le RubikCube pour remplir la palette ligne 30 avec les couleurs de la palette affiché en bas de ConvImgCpc.
