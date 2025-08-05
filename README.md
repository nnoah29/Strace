# Strace

Strace est un projet développé dans le cadre du module B-PSU-400 à EPITECH. Il s'agit d'une réimplémentation simplifiée de l'outil `strace`, permettant de tracer les appels système effectués par un programme ou un processus sous Linux.

## 📦 Installation

1. Clonez le dépôt ou récupérez les sources.
2. Compilez le projet avec la commande :

```sh
make
```

Le binaire généré s'appelle `strace`.

## 🚀 Utilisation

Lancer le programme avec :

```sh
./strace [-s] [-p <pid> | <commande>]
```

- `-s` : Affiche les arguments des appels système de façon détaillée (mode verbeux).
- `-p <pid>` : Attache le strace à un processus existant identifié par son PID.
- `<commande>` : Lance la commande spécifiée et trace ses appels système.

### Exemples

- Tracer l'exécution d'une commande :
  ```sh
  ./strace ls -l
  ```
- Tracer un processus existant (PID 1234) :
  ```sh
  ./strace -p 1234
  ```
- Mode détaillé :
  ```sh
  ./strace -s ls
  ```

## 🏗️ Architecture

    Strace/
    ├── strace           # Exécutable principal
    ├── src/             # Fichiers sources (main, parsing, tracing)
    ├── includes/        # Fichiers d'en-tête (headers)
    ├── Makefile         # Système de build

## ⚙️ Fonctionnalités principales

- Trace les appels système d'un programme ou d'un processus.
- Affiche le nom de l'appel système, ses arguments (en mode détaillé) et la valeur de retour.
- Supporte l'attachement à un processus existant via son PID.

## 🧑‍💻 Auteur

Noah TOFFA, noah.toffa@epitech.eu

## 📊 Résultats de la soutenance / notation

- **Prérequis** : ✅ 100% validés

### Coding style
- Fatal : 0
- Major : 2
- Minor : 0
- Info  : 0

### Couverture de code
- Branches : 0%
- Lignes   : 0%

### Tests automatiques

| Test                        | Total | Passés | Crash | Échoués/ignorés |
|-----------------------------|-------|--------|-------|-----------------|
| 01 - Rigour                 | 2     | 2      | 0     | 0               |
| 02 - syscall name           | 3     | 3      | 0     | 0               |
| 03 - Return value           | 3     | 3      | 0     | 0               |
| 04 - Parameters             | 2     | 2      | 0     | 0               |

- Advanced syscall : ✅ PASSED
- Basic syscall : ✅ PASSED
- Basic syscall, -s option : ✅ PASSED

## ⚖️ Licence

Ce projet est développé dans le cadre du module B-PSU-400 à EPITECH.

## ⚠️ Notes importantes

------------------------

Le projet suit la norme EPITECH.

Merci de respecter la norme et les bonnes pratiques EPITECH lors de toute modification ou contribution.
