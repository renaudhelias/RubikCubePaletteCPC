# RubikCubePaletteCPC
Inspiré d'une vidéo CPC de MacDeath26 : http://www.youtube.com/watch?v=iMo0bCSMAQ0

RubikCube aux couleurs de la palette CPC qu'on peut acheter physiquement en utilisant le site suivant : http://www.rubiksphotocube.com/fr/designer

![RubikCubePaletteCPC.png](RubikCubePaletteCPC.png)

Après on peut l'utiliser pour sélectionner les INK dans ConvImgCpc

ConvImgCpc http://amstrad.eu/modules/TDMDownloads/(amstrad.eu) > http://amstrad.eu/modules/TDMDownloads/singlefile.php?cid=13&lid=186(ConvImgCpc)

ManageDsk

10 MODE 2
20 BORDER 0
30 INK 0,0:INK 1,1:INK 2,2...
40 LOAD"image.scr",&C000
50 CALL &BB18
