# Projet PCA "Follow"

### Projet logiciel en langage C (L3 Informatique, parcours Ingénierie Informatique, UBO, 2021-2022)

Le but du projet est de développer un logiciel qui sera baptisé "follow", pour le suivi *a posteriori* des modifications documentaires. Ce logiciel a pour objectif d'aider à la comparaison de deux texte, normalement relativement proches, en faisant apparaître leurs différences. Un alignement des deux textes est recherché afin de minimiser le nombre d'opérations à réaliser pour passer d'un texte à l'autre. Par opération, on entend des opérations d'édition de type *remplacement*, *insertion* ou *suppression* de mots. Le logiciel ne fait pas apparaître les modifications de la mise en page (retour à la ligne, blanc, tabulation). En revanche, la ponctuation et les caractères spéciaux sont pris en compte.


Les fonctionnalités du logiciel sont les suivantes :

- Chargement du texte à comparer au texte de réfrence, qualifié de "nouveau" par la suite, et affichage dans la zone de texte à droite de la fenêtre. Le nom du fichier chargé apparaît en dessous de cette zone. Le nom du fichier est fourni sur la ligne de commande (second argument) au moment du lancement du logiciel, ou obtenu à partir d'un sélecteur de fichiers déclenché par le menu déroulant *Fichier*, option *Ouvrir*.
- Chargement du texte de référence. Si le nouveau texte n'est pas encore chargé, alors le texte de référence est affiché tel quel dans la zone de texte à gauche de la fenêtre. Dans le cas contraire, les différences avec le nouveau texte sont affichées dans la zone de texte à gauche par une présentation en couleur :
    - un mot affiché en rouge apparaît dans la référence, mais a été supprimé dans un nouveau texte,
    - un mot affiché en vert a été inséré dans le nouveau texte,
    - un couple de mots affiché en rouge et bleu indique le remplacement du mot rouge dans le texte de référence par le mot bleu dans le nouveau texte.

La mise en page est celle du nouveau texte. Le nom du fichier de référence apparaît en dessous de la zone de texte. Le nom du fichier est fourni sur la ligne de commande (premier argument) au momeny du lancemeny du logiciel, ou obtenu à partir d'un sélecteur de fichiers déclenché par le menu déroulant *Fichier*, option *Ouvrir référence*.
