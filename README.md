# lzw_p8
Compresseur/Decompresseur de fichiers utilisant l'algorithme LZW

=====================---------

Overview :
- Un simple compresseur décompresseur.
- Commence avec un dictionnaire ASCII de 256 entrées.
- Lorsqu'il faut augmenter la taille du code à compresser, j'ajoute x * 1 au binaire du fichier compressé avant d'incrémenter x (x étant la taille du code)

Procédé et apport personnel :
Je suis parti de la page wikipédia parlant de l'algorithme. Il ne restait alors qu'à choisir comment représenter les données, j'ai choisi d'utiliser les listes chainées car je me sens à l'aise avec leur utilisation, qui me semble plus propre et agréable que de déclarer des choses figées.
