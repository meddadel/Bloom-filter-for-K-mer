# Bienvenue dans le Bloom-filter-for-K-mer

## l'architecture de ce programme on peut la decomposer en 3 sous programme:
1. ### le [Bloom-filter](https://github.com/meddadel/Bloom-filter-for-K-mer/blob/master/bloomFilter.cpp), quelques fonction classiques sont présentes, à l'image de:
* add_value
* is_presnte
2. ### le [hash code:hash.cpp](https://github.com/meddadel/Bloom-filter-for-K-mer/blob/master/hash.cpp): c'est un programme utiliser par le bloom-filter pour hasher le codage des K-mer et puis soit les ajouter avec add_value ou verifier leurs présence avec is_presnte, dans le hash.cpp on retrouve deux fonction 
3. * la fonction hash qui utilise les propriétés du xor.
4. * la fonction multihash qui va generer plusieur hashes pour le meme code en en repetant plusieur fois le xorshifts.
