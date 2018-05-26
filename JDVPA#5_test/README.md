# [JDVPA#5] Pseudo sprites
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=b9hb3fNhAgQ

__main.c jdvpa5.dsk__

![JDVPA5.dsk.png](JDVPA5.dsk.png)

J'ai bêtement ajouté "if (i==1 || i==3) vsync();" pour capturer l'écran, mais du coup ça ralenti.

Mais comme dit dans la vidéo, le nombre de sprite une fois qu'ils marcheront dans le labyrinthe, sera presque divisé par deux.

__combat2.c jdvpa5_combat2.dsk__

Test d'affichage inversé d'un sprite, utilisation d'un tableau de transposition pour les octets, ça prend un peu de temps de calcul mais ça va.
Pour la répartition de la charge j'ai pensé qu'un personnage était toujours affiché à l'inverse de l'autre, donc changer de sens n'est pas plus couteux.
