CORE_NCORE X = nombre de coeurs que l'on veut actif
CORE_ENABLE1 = permet l'utilisation de plusieurs coeurs, exclusif avec MMU
CORE_STATUS = tableau contenant les coeurs et leur état : 1 il est actif
A l'activation d'un coeur, celui-ci active la fonction qui est dans IRQ_VECTOR[0]
CORE_ID = variable qui récupère le numéro du coeur courant

IRQ_VECTOR[0] pointe vers une fonction qui affiche le numéro du coeur courant et compte jusque 2^20

/home/enseign/ASE/.. core.ini à télécharger

CORE_IRQMAPPER = registre qui redirige les interruptions qui contient 16 registres (1 par coeur)
Chaque registre indique par une position binaire si l'interruption doit être traité localement par le coeur
Lancer un timer et sur les coeurs de rangs impair afficher quelquechose lorsqu'ils ont une interruption et sur les autres rien



CORE_LOCK : si 1 le verrou est prit c'est OK. Sinon on boucle dessus jusquà ce qu'on ait eu le verrou


Ajout de listes de contextes que de core
    core i <=> liste i
    

[Avant d'activer les cores, le core 0 remplit toutes les listes]


Chaque core contient un ring de contextes et une méthode coreboot qui tourne indéfiniment.
Quand une interruption apparait, yield passe la main à un contexte du ring et quand tous les contextes du ring sont finis, on retourne dans coreboot();
