# [JDVPA#5] Pseudo sprites
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=b9hb3fNhAgQ

__main.c jdvpa5.dsk__

![JDVPA5.dsk.png](JDVPA5.dsk.png)

J'ai bêtement ajouté "if (i==1 || i==3) vsync();" pour capturer l'écran, mais du coup ça ralenti.

Mais comme dit dans la vidéo, le nombre de sprite une fois qu'ils marcheront dans le labyrinthe, sera presque divisé par deux.

__combat2.c jdvpa5_combat2.dsk__

Ecriture de la bande sonore MK-BO.SKS par SuTeKH/Epyteor.

___put_inversed_frame()___

Les personnages peuvent changent de sens lorsqu'ils se croisent.

Affichage inversé d'un sprite, utilisation d'un tableau de transposition pour les octets, ça prend un peu de temps de calcul mais ça va.
Pour la répartition de la charge j'ai pensé qu'un personnage était toujours affiché à l'inverse de l'autre, donc changer de sens n'est pas plus couteux.

__COMBAT2.BAS___

J'ai créé un menu afin de passer quelques paramètres de basic vers asm :
* le choix de la partie : "Liu Kang vs Sub Zero", "Johnny Cage vs Scorpion", "Sonya vs Kano". Chacun change le fond, les perso et la palette, la palette de 4 couleurs (mode 1) étant : noir, rouge, neutre, adversaire (rouge étant généralement aussi le héro), ou noir, rouge, hero, adversaire.
* le mode "ARCADE" : ça permet de jouer avec les deux boutons.

___blood()___

![JDVPA5_combat2-sang.dsk.png](JDVPA5_combat2-sang.dsk.png)

Un effet type particules, qui marche un peu.

___hadouken()___

![JDVPA5_combat2-hadouken.dsk.png](JDVPA5_combat2-hadouken.dsk.png)

Un autre effet type particules, qui marche un peu.

TODO :
* OSEF rendre paramétrable le choix des joueurs, mais faire des préselection dans le menu basic
* OSEF terrain paramétrable aussi.
* DONE image dernier terrain OK, mais zone de combat : le 1 est OK, la foret devrait être plus large, et le dernier plus court/centré (genre arène) 
* DONE ajouter 2 sons (OSEF choix paramétrable aussi), dont le son du prototype
* DONE calibrer algo inverse sprite, empécher lock
* DONE finaliser hadouken (dégats, et cible mouvante)
* DONE AI : direction = (old_direction+rnd) à la place de  direction = rnd + mélange
* DONE peaufiner algo sang
* DONE goutte de sang bizarrement suspendue
* DONE le sang semble clignoter parfois quand il est au dessus du calque d'un des deux perso
* DONE optim/debug PHASE_GEL (ne pas utiliser NON_CYCLIQUE+fin anim ? pour ça ?)
* DONE peut-être GEL quand on est à la fin d'un NON_CYCLIQUE comme ça on peut mettre un PORTE_EN_X sur le dernier pas de l'animation.

TODO (hadouken) :
* DONE le hadouken de liu kang devrait être plus bas (ventre)
* DONE le hadouken part pas toujours du bord du bonhomme comme il faut (perso.x c'est pas bon des deux sens)
* DONE le contact de la boule devrait être le milieu du personnage
* DONE l'esquive et le contre devrait avoir un effet différent sur la boule de feux : l'esquive laisse passer,
* DONE le contre hadouken absorbe son énergie (nrj_hadouken++ à la place de vie --)
* DONE un contre ça pare un coup (le stoppant net), une esquive ça ne pare pas un coup, c'est comme si le perso n'était simplement pas là.
* DONE le bot ne hadouken pas côté liu kang du coup... (car j'ai mappé qu'en mode arcade 2 boutons, et le bot il simule le jeu normal 1 bouton)
** DONE mettre droite+gauche à la fois pour le hadouken du bot liu kang.
* DONE si je ne me suis pas retourné et que je dépasse l'adversaire, ça tire à l'envers (et dans le mur)
* DONE le sang qui clignote qu'il faudrait ne pas effacer lorsqu'il dépasse du bord.
* DONE quand on fait un hadouken et on garde la position, l'autre ne peut pas faire un hadouken (en fait ça lance l'hadouken de l'autre :D)
* DONE amélioration pour bot : ne pas dépasser le bonhomme si on ne peut pas se retourner, c'est ridicule. Si au bord, bah c'est foutu pour le gars.
* DONE lors du KO, on peut avoir dépassé le bonhomme, et du coup rester bizarrement bloqué du mauvais côté de la victime
* DONE amélioration pour bot : ne pas lancer hadouken si on ne le peut pas (dans ce cas, lancer REPOS ? |=MARCHER finalement...) => comme ça ça attend pas bêtement la fin de l'animation pour rien
* DONE un truc pour compter le nombre de combats gagnés par un joueur
* DONE un random timer pour initier le random bot
* DONE le nb_victory, dépasse à droite quand le compteur est trop haut (genre 24h de combats)
* DONE le nb_victory est un pixel trop bas, du coup la première victoire n'est pas visible, il devrait dépasser la charge Hadouken d'un pixel en haut.
* DONE sous WinAPE, le détecteur de latence s'affole.
* DONE sous WinAPE, quand le perso se retourne (assez lourd déjà ça comme algo) et que du sang est présent (donc algo en train de calculer), ça rame.
* DONE freezer les deux nb_victory si un nb_victory atteind son max en haut de l'écran ? genre le gars qui lance la partie sur 1 mois il a le score final...
* DONE la barre d'hadouken n'est pas pleine au début, alors qu'il a bien 3 charges Hadouken
* DONE la barre nb_victory a déjà une valeur, alors qu'il n'y a pas encore eu de combats fini
* DONE la barre nb_victory s'incrémente au début du match suivant, elle devrait s'incrémenter dès lors qu'il y a eu KO ou dumoins VICTORY (le bonhomme content là)
* DONE la barre nb_victory de droite a de mauvais symptomes losqu'elle approche des 5 dernières colonnes...

__COMBAT2.BAS__

Passage de COMBAT2.BAS en mode texte, afin d'être éditable sous notepad++ :
<pre>load "combat2.bas"
 save "combat2.bas",a</pre>
Si on ouvre avec notepad++, on peut garder juste le texte + le dernier caractère étrange "(SUB)" (sinon on a Line too long)
