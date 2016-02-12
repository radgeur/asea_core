CORE_NCORE X = nombre de coeurs que l'on veut actif
CORE_ENABLE1 = permet l'utilisation de plusieurs coeurs, exclusif avec MMU
CORE_STATUS = tableau contenant les coeurs et leur état : 1 il est actif
A l'activation d'un coeur, celui-ci active la fonction qui est dans IRQ_VECTOR[0]
CORE_ID = variable qui récupère le numéro du coeur courant

IRQ_VECTOR[0] pointe vers une fonction qui affiche le numéro du coeur courant et compte jusque 2^20

/home/enseign/ASE/.. core.ini à télécharger
