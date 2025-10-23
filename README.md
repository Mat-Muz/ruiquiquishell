# RiquiquiShell

RiquiquiShell est un projet de shell minimaliste écrit en C. Il permet d'exécuter des commandes système, de gérer des redirections, des pipes, et des commandes en arrière-plan.

## Structure du projet

```
.
├── makefile
├── readme
├── bin/
├── build/
├── Include/
│   ├── function.h
│   ├── input.h
│   ├── main.h
│   ├── utilities.h
├── src/
│   ├── function.c
│   ├── input.c
│   ├── main.c
│   ├── utilities.c
```

### Répertoires principaux

- **Include/** : Contient les fichiers d'en-tête (`.h`) pour les différentes fonctionnalités du projet.
- **src/** : Contient les fichiers source (`.c`) implémentant les fonctionnalités.
- **bin/** : Contiendra l'exécutable généré après compilation.
- **build/** : Contiendra les fichiers objets (`.o`) générés lors de la compilation.

## Fonctionnalités

- **Exécution de commandes** : Permet d'exécuter des commandes système comme `ls`, `pwd`, etc.
- **Redirections** : Gère les redirections de sortie (`>`).
- **Pipes** : Supporte les pipes (`|`) pour connecter plusieurs commandes.
- **Commandes en arrière-plan** : Permet d'exécuter des commandes en arrière-plan avec `&`.
- **Commandes intégrées** :
  - `cd` : Change le répertoire courant.
  - `pwd` : Affiche le répertoire courant.
  - `exit` : Quitte le shell.

## BUGS

- ne pas utiliser le `|` avec le `&`

## Compilation et exécution

### Prérequis

- GCC (GNU Compiler Collection)
- Make

### Étapes

1. Clonez le dépôt ou téléchargez les fichiers.
2. Compilez le projet avec la commande suivante :

   ```bash
   make
   ```

   Cela génère un exécutable dans le répertoire bin nommé `riquiquishell`.

3. Exécutez le shell avec :

   ```bash
   ./bin/riquiquishell
   ```

### Nettoyage

Pour supprimer les fichiers objets et les dépendances générés :

```bash
make clean
```

Pour supprimer également l'exécutable :

```bash
make aclean
```
