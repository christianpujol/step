# STEP
## Un émulateur "pas à pas" pour [l'ordinateur en papier][1]  



### INSTALLATION ET INVOCATION
L'installation se fait a l'aide de la commande `make`

    $ make

Elle produit un fichier exécutable nommé `step` La commande

    $ step

Lance le programme.
### USAGE

    usage:   step [OPTION]
        -h           display this help
        -i <file>    use this file to load memory image
        -n number    set PC using decimal
        -x number    set PC using hexadecimal

### UTILISATION
Une fois lancé `my-shell` présente a l'utilisateur un prompt:  

    stepper>

et interprètes les commandes lues sur l'entrée standard.

#### INPUT / OUTPUT
Les entrées de l'ordinateur en papier se font via le clavier après le prompt: 

     in ?

L'utilisateur doit entrer les valeurs en base 16.

L'output se fait a l'écran:

     out: 0x48

 

#### LISTE DES COMMANDES

Les commandes ne sont pas sensible a la case. 

Les nombres (`number` ci-après) sont lu soit sous
format décimal soit sous la forme hexadécimale `0xca`, 
sauf pour la commande `run` qui n'accepte que des nombres
décimaux.

* `q` ou `quit` ou `exit`:  
   Sort du programme.
* `l filename` ou `load filename`:    
   Charge l'image mémoire contenu dans `filename` 
   (ATTENTION: `filename` est sensible a la case).
* `run number` ou `r number` ou `number`:   
   exécute `number` instruction.
* `s pc number` ou `set pc number`:    
   Fixe la valeur du __PROGRAM COUNTER__ à `number`
* `s  a number` ou `set a number`:    
   Fixe la valeur du __REGISTRE A__ à `number`.
* `set adresse number`:  
   Enregistre la valeur `number` dans la case mémoire
   d'adresse `adresse`.
* `p s` ou `print state`:  
   Affiche la valeur du __PROGRAM COUNTER__ et
   la valeur du __REGISTRE A__
* `p pc` ou `print pc`:  
   Affiche la valeur du __PROGRAM COUNTER__
* `p a` ou `print a`:  
   Affiche la valeur du __REGISTRE A__
* `p adresse` ou `print adresse`:  
   Affiche la valeur de la case mémoire d'adresse 
   `adresse`.
* `p mem` ou `print mem`:  
  Affiche un tableau des case mémoire.

#### FICHIER IMAGE MÉMOIRE

Les fichiers d'image mémoire ont le format suivant:

Chaque ligne contient deux nombres au format hexadécimale `0xae`.  
Le premier des nombres représente l'adresse mémoire,
le deuxième la valeur présente à cette adresse.  
Les adresses peuvent ne pas se présenter dans l'ordre numérique.  

Le fichier `mnemo.md` présente de façon succincte les instructions disponible
ainsi que leur codes hexadécimal..

### BUGS

Les bugs peuvent êtres signalé a l'auteur par mail: pujolchr (AT) gmail (DOT) com. 

##### Liste des bugs connus:
* Prompt: après la commande `run` le prompt peut ne pas s'afficher
  ou s'afficher deux fois de suite.

[1]: http://foad.iedparis8.net/claroline/courses/ELI/document/pdf/m-papier.pdf


