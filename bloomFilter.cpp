#include "hash.cpp"



// bloom filter 
class BloomFilter {
    uint64_t taille;    // la taille du bloom filtre 
    uint64_t nb_hashes; // le nombre des fonction de hash
    bool* cell;         // le bloom filtre
    uint64_t*  hashes;  // le resultat des hashes    

public:

    BloomFilter(unsigned int numbCells, unsigned int numberfunction) : taille(numbCells), nb_hashes(numberfunction) {
        cell = new bool[numbCells]();hashes = new uint64_t [nb_hashes];
    }

    // ---------------fonction add_value-------------
    // on va utiliser multihash et puis on met tout a jour le tableau du bloom filter 
    void add_value(uint64_t x)
    {
        multihash(x,hashes, nb_hashes, taille); 
        for (uint64_t i=0 ; i<nb_hashes ; i++)
        {
            cell[hashes[i]] = true;
        }
    }
    
    //---------------fonction is_prensent-----------------
    /* on va utiliser multihash et puis verifier sur 
    le tableau du bloom filter si tous les bon case sont à true */
    bool is_present(uint64_t x) 
    {
        bool present = true;
        multihash(x,hashes, nb_hashes, taille);
        for (uint64_t i=0 ; i<nb_hashes ; i++)
        {
            if (cell[hashes[i]] == false)
            {
                present = false;
                break;
            }
        }
        return present;
    }
    
    ~BloomFilter() 
    {
        free(cell);
        cell = NULL;
    }

    void afficherEtat() const
{
    cout << "taille : " << taille << endl;
    cout << "le num des fonctions : " << nb_hashes << endl;
}
    
};


