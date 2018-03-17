# [JDVPA#2] C'est le pacman !
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=5lgHTfqISnk

__main.c jdvpa2.dsk__

![JDVPA2.dsk.png](JDVPA2.dsk.png)

Le pacman bouge bien, via les touches A,Q,O,P.

__combat2.c jdvpa2_combat2.dsk__

Pour le moment combat2.c contient une structure constante pour l'énumération des calques, ce qui permet d'avoir l'offset et le nombre de calques utilisé par une animation : J2R.hadouken2_fire.o (offset) et J2R.hadouken2_fire.l (lenght)

L'objectif va être de rajouter le clavier et faire bouger 2 personnages.

![JDVPA2_COMBAT2.dsk.png](JDVPA2_COMBAT2.dsk.png)

Le border raster permet de chronométrer les routines exécutées lors de l'affiche d'une image, en blanc le temps dédié au son (moins d'une interruption), et le violet le reste des calculs (affichage des bonhommes, transfert mémoire)

L'algo de déplacement et d'animation de sprite commence à faire des trucs, pas tout bien, mais bon faut de toute façon que je le refasse car j'ai oublié quelques conceptes.