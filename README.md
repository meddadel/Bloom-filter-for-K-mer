# Bienvenue dans le Bloom-filter-for-K-mer

## l'architecture de ce programme on peut la decomposer en 3 sous programme:
1. ### le [Bloom-filter : bloomFilter.cpp](https://github.com/meddadel/Bloom-filter-for-K-mer/blob/master/bloomFilter.cpp), quelques fonction classiques sont présentes, à l'image de:
* add_value
* is_presnte

2. ### le [hash code : hash.cpp](https://github.com/meddadel/Bloom-filter-for-K-mer/blob/master/hash.cpp): c'est un programme utiliser par le bloom-filter pour hasher le codage des K-mer dans le hash.cpp on retrouve deux fonction 
 * la fonction hash qui utilise les propriétés du xor.
 * la fonction multihash qui va generer plusieur hashes pour le meme code en en repetant plusieur fois le xorshifts.
 
3. ### le [main programme : test.cpp](https://github.com/meddadel/Bloom-filter-for-K-mer/blob/master/test.cpp): c'est le programe principal 
* la fonction nexDnaChar qui lis le fichier en entrée
* la fonction encodeKPlus qui va coder le K-mer *à partire d'un K-mer précedent et une lecture du prochain char* en utilisant d'autre fonction comme encodeK, encodeKR,encode et encodeR
* la fonction randKmer qui va generer des K-mer random et puis dans le main on test s'ils figure dans le fichier .fasta en entrée

## Mode d'emploi:
1. ### compilation
*  ####g++ test.cpp -o test
2. ### execution
* ####./test file.fasta k size nf r
* avec k la taille des k_mer, size la taille du bloom filter, nf le nombre des fonction des hashage et puis r le nombre des random request
