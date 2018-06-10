# [JDVPA#5] Pseudo sprites
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=b9hb3fNhAgQ

__main.c jdvpa5.dsk__

![JDVPA5.dsk.png](JDVPA5.dsk.png)

J'ai bêtement ajouté "if (i==1 || i==3) vsync();" pour capturer l'écran, mais du coup ça ralenti.

Mais comme dit dans la vidéo, le nombre de sprite une fois qu'ils marcheront dans le labyrinthe, sera presque divisé par deux.

__combat2.c jdvpa5_combat2.dsk__

___put_inversed_frame()___

Les personnages peuvent changent de sens lorsqu'ils se croisent.

Affichage inversé d'un sprite, utilisation d'un tableau de transposition pour les octets, ça prend un peu de temps de calcul mais ça va.
Pour la répartition de la charge j'ai pensé qu'un personnage était toujours affiché à l'inverse de l'autre, donc changer de sens n'est pas plus couteux.

___CHOICE.BAS___

J'ai créé un menu afin de passer quelques paramètres de basic vers asm :
* le choix de la partie : "Liu Kang vs Sub Zero", "Johnny Cage vs Scorpion", "Sonya vs Kano". Chacun change le fond, les perso et la palette, la palette de 4 couleurs (mode 1) étant : noir, rouge, neutre, adversaire (rouge étant généralement aussi le héro), ou noir, rouge, hero, adversaire.
* le mode "ARCADE" : ça permet de jouer avec les deux boutons.

___blood()___

![JDVPA5_combat2-sang.dsk.png](JDVPA5_combat2-sang.dsk.png)

Un effet type particules, qui marche un peu.

___hadouken()___

![JDVPA5_combat2-hadouken.dsk.png](JDVPA5_combat2-hadouken.dsk.png)

Un autre effet type particules, qui marche un peu.