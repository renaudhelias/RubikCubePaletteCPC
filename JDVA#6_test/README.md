# [JDVA#6] ON FAIT BOUGER UN POULPE
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=88MaOZglJQA


![JDVA6.dsk.png](JDVA6.dsk.png)

Un vieux jeu que je jouais quand j'étais tout petit, je ne sais plus son nom, je l'ai recréé de mémoire. Un jeu de puzzle et de mémoire :

![puzzmem.dsk.png](puzzmem.dsk.png)

![puzzmem_mist-board.png](puzzmem_mist-board.png)

keys : ENTER, SPACE, arrows.

combat

J'utilise ici la technique du "décalage d'un pixel" afin que mes sprites bougent un pixel par un pixel en mode 2, changeant donc de sprite pixel par pixel sur un écran de 640 pixels de large. Et j'ai eu pas mal de surprises :

- En fait un écran ici fait 640 pixels de large, et est à 50Hz, donc si je met la vitesse maximal tout en déplaçant les pixels un par un à 50Hz, en fait mon personnage prend 6 secondes à atteindre le milieu de l'écran ! et c'est normal : (640/2)/25=12 secondes à 25Hz (donc humainement)

- A contrario changer de sprite à chaque fois, c'est trop rapide : mon bonhomme cours/clignote sur place. Voyons, il me faut 40 secondes pour atteindre le milieu de l'écran si à chaque appui on avance d'un pixel et qu'on bourrine sur la touche comme un malade (donc sans déplacement automatique). Donc au niveau du nombre d'action faites automatiquement par le déplacement du sprite à sa vitesse maxi, cette vitesse qui nous semble lente est 40/6=6 fois trop rapide. Dans quand je pensais que marcher était une action, tout comme donner un coup de poing dans mon jeu, je suis déjà 6 fois trop rapide niveau action, donc niveau sprite (je voulais un sprite par action...)

- Niveau perf, SDCC semble lacher l'affaire à partir d'un certain nombre de fonctions appelées par une fonction :
 error 9: FATAL Compiler Internal Error in file '/home/sdcc-builder
 /build/sdcc-build/orig/sdcc/src/z80/ralloc.c' line number '1354' : isSymbolEqual
 (sym, OP_SYMBOL (IC_RESULT (ic)))

- Niveau taille, le fichier final sature à 64KB, et ne marche plus un peu après les 32KB. Du coup j'arrive à avoir 64 sprites de 56x100 noir et blanc, mes 128 sprites ne rentrent pas ! De ce côté une solution serait de mettre les sprites dans un fichier à part, et tant qu'à faire les charger dans des bank RAM de la mémoire externe. Et tant qu'à faire se baser sur une seule image (de sprites non tous verticalement...) que je découpe lors du passage entre le format fichier et format RAM.

- Niveau perf, je peux afficher 2 sprites de 56x100 pendant un vsync, au delà ça sature. Mais bon on peut mettre deux vsync vue qu'on est à 50Hz... au dela il faudrait s'organiser (utiliser deux zones écran qu'on alterne ?)

![combat.dsk.png](combat.dsk.png)

Donc le poisson... il prend 1.5 secondes à traverser l'écran, sautant un pixel sur deux en mode 0 (écran de 160 pixels de large), disons sur un écran de 30 cm, donc il se déplace visuellement à 0.75km/h maximum (si on ne saute pas plus de pixels)

Et si on le compare à un vrai poisson, 8 fois plus grand donc, il ferait du 6km/h.

Ce serait bien pour "combat" de jongler avec deux zones d'affichage histoire d'avoir un buffer, .

J'ai calculé que pour une action (marcher/taper), 50Hz pour un sprite c'est humainement 6 fois trop rapide, donc j'aurai logiquement le temps de calculer une superposition de deux calques.

Mais niveau rendu, faudrait afficher ça d'un coup, on a beau se dire qu'un humain voit à 25Hz et que donc je peux poutrer les sprites durant deux vsync, c'est quand même une plus belle qualité si les pixels bougent tous en même temps.

http://www.cpcwiki.eu/index.php/Retro_Game_Asset_Studio - avec "View sprite animation preview at any frame rate"

http://github.com/lronaldo/cpctelera - comprend la dernière version de Retro_Game_Asset_Studio

Gimp si on tire une règle sur le dessin, ça fait des zones, et lorsqu'on utilise l'outil de sélection, en fait il est magnétisé par la règle, ce qui facilite les sélections. De plus on peut travailler sur une sélection, ce qui empèche de baver d'un sprite sur l'autre.