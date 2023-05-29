# eduroam
Programme qui lance un ping régulièrement. Si le ping échoue, le programme se déconnecte d'eduroam et s'y reconnecte. Ce programme ne sert qu'à une chose : réparer l'eduroam italien qui plante souvent.

Pour compile : 
````console
g++ -o eduroam.exe eduroam.cpp
````

## Problème connu
Parfois se déconnecter et s'y reconnecter ne suffit pas, il faudrait pouvoir oublier le réseau et l'enregistrer à nouveau.

## Historique des versions
### Version 1
Le script marche mais n'affiche rien. Le script s'arrête tout seul après 18h car on arrête de travailler vers 17h.
### Version 2
Le script affiche tout ce qu'il fait. Le nombre de ping à Google passe de 4 à 1 (le script mettait un peu de temps avant de comprendre qu'il n'était pas connecté à internet avant).