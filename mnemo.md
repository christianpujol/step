## Mnémoniques    Co0xde opératoire   description
#### ARITHMETIQUE

* ADD #           0x20        A ← + V
* ADD α           0x60        A ← + (α)
* ADD ∗α          0xe0        A ← + ∗(α)
* SUB #           0x21        A ← - V
* SUB α           0x61        A ← - (α)
* SUB ∗α          0xe1        A ← - ∗(α)

#### LOGIQUE

* NAND #          0x22        A ← ¬[A & V ]
* NAND α          0x62        A ← ¬[A & (α)]
* NAND ∗α         0xe2        A ← ¬[A & ∗(α)]

#### TRANSFERTS

* LOAD #          0x00        A    ← V
* LOAD α          0x40        A    ← (α)
* LOAD ∗α         0xc0        A    ← ∗(α)
* STORE α         0x48        (α)  ← A
* STORE ∗α        0xc8        ∗(α) ← A

#### Entrées / Sorties

* IN α            0x49        (α)    ← Entrée
* IN ∗α           0xc9        ∗(α)   ← Entrée
* OUT α           0x41        Sortie ← (α)
* OUT ∗α          0xc1        Sortie ← ∗(α)

#### Branchement

##### inconditionnel

* JUMP α           0x10       PC ← α

##### conditinonels

* BRN α            0x11       si A < 0 alors PC ← α
* BRZ α            0x12       si A = 0 alors PC ← α


Légende:

* ← La flèche représente l’affectation.
* (α) représente le contenu de la case d’adresse alpha.
* ∗(α) représente le contenu de la case dont l’adresse
  est dans la * case d’adresse alpha.
* V est la valeur donnée immédiatement.
* ¬ représente le non logique.
* & représente le et logique.
* Les crochets [ ] groupent les termes sur lesquels
  s’applique une opération.
