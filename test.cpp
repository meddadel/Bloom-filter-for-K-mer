
#include "test.h"
#include "bloomFilter.cpp"
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

//------------------------lire dans fichier---------------------------------------

int  global_compt=0;        //variable globale pour sauvgarder notre position dans le fichier

/* la fonction nexDnaChar prend en entrer le fichier FASTA "le path en string"
et grace à un compteur global_compt qu'on a declarer global elle renvoir 
le i eme char du fichier fasta avec global_compt=i */

char nexDnaChar(string file)
{

    string filename(file); // le fichier qu'on veut traiter 
    char byte = 0;         // la variable qui contiendra le char renvoyer par la fonction 

    // ovrire le fichier file
    ifstream input_file(filename);
    if (!input_file.is_open()) 
    {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return 'F';
    }
    
    // il faut qu'on soit sur que c'est un fichier de bonne format c à d il commence par '>'
    if(!(input_file.get(byte)))
    {
      return 'F';
    }  
    if (byte!='>')
    {
        return 'F';
    }
    
    

    string line;            // variable pour pouvoire toujour sauter la premier ligne en utilisant la fonction getline()

    /*la fonction getline va me permetre de deplacer 
    le pointeur apres la premier ligne*/ 
    getline(input_file,line);

    /* dans cette etape on vas mettre a la variable byte le i eme char
    jusqua arriver à notre char voulue */
    for(int i=0;i<=::global_compt;i++) 
    {
       if(!(input_file.get(byte)))
       {
          return 'F'; 
       }     
    }
    
    //cette partie va nous permettre de ignorer les N ainsi que les \n
    while (byte=='N'||byte=='\n')
    {
        ++global_compt;
        if(!input_file.get(byte)) return 'F';
    }
   
    //on increment la variabe globale pour se souvenir du prochain char a lire
    ++global_compt;
   
    input_file.close();

    return byte;
    
}

//--------------------------codage-----------------------------------

// cette fonction va nous permettre de code un char.
int encode(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
}

/* cette fonction va nous permettre de coder le complement d'un char
 on va l'utiliser apres pour code le Reverse complement. */
int encodeR(char c)
{
    if (c == 'T') return 0;
    if (c == 'G') return 1;
    if (c == 'C') return 2;
    if (c == 'A') return 3;
}

// la fonction encodeK code un Kmer en un entier 
uint64_t encodeK(string Kmer)
{
    int code = 0;
    for(std::string::size_type i = 0; i < Kmer.length(); ++i)
    {
        code <<= 1;
        code += encode(Kmer[i]);
    }
    return code; 
}
// la fonction encodeKR code le le Reverse complement d'un Kmer en un entier 
uint64_t encodeKR(string Kmer)
{
    int code2= 0;
    for(int i = Kmer.length()-1; i >=0; --i)
    {
        code2 <<= 1;
        code2 += encodeR(Kmer[i]);
    }
    return code2;
}

/* la fonction encodeKPlus utilise la fonction encodeK et encodeKR pour coder un kmer 
a partire d'un kmer précédent et une lecture du caractère suivant dans le fichier.
*/
uint64_t encodeKPlus(string Kmer,char c)
{
    int result=encodeK(Kmer);       // result contien le codage de l'ancien kmer
    int first=encode(Kmer[0]);      // first  contien le codage du char de poid fort de l'ancien kmer
    first <<=Kmer.length()-1;       // on prepare le first pour faire la soustraction à l'étape suivante
    result=result-first;        
    result <<=1;
    result += encode(c);            // le codage du kmer
    
    /* maintenant on a calculer le codage du kmer mais 
    il nous reste a calculer le codage de son Reverse complement */
    
    // codage du Reverse complement
    string kmer2=Kmer.erase(0, 1);  // suprimer le premier char du kmer
    int resultR=encodeKR(kmer2);    // coder le Reverse complement 
    int first2=encodeR(c);
    first2<<=kmer2.length();
    resultR +=first2;               // le codage du Reverse complement pour le prochain kmer                                  
    
    /* l'etape suivante on choisi le codage minimum entre le kmer et son Reverse complement*/

    if(resultR<result)
    {
        return resultR;
    }
    else return result;  
}


//---------------generer un random Kmer------------------------------
 string randKmer(uint64_t k){
        string randomKmer="";
        for (size_t i = 0; i < k; i++)
        {
            int c;
            c = (rand()%10)+1; 
            if (c<5)
            {
             c = (rand()%100)+1;
             if (c<5)
             {
                 randomKmer=randomKmer+"A";
             }
             else randomKmer=randomKmer+"T";         
            }
            else
            {
                c = (rand()%10)+1;
             if (c<5)
             {
                 randomKmer=randomKmer+"C";    
             }
             else randomKmer=randomKmer+"G";
            }
        }
        return randomKmer;    
    }
//-------------------------------------------------------------------

// le main programe, ici on va lire le fichier passer en entrer pour le code puis le hasher sur le bloom filter
int main(int argc, char *argv[])
{
    uint64_t taille = atoi(argv[3]);
    uint64_t fonctions = atoi(argv[4]);
    std::string file=argv[1];
    uint64_t k=atoi(argv[2]);
    uint64_t r=atoi(argv[5]);
    BloomFilter  bloom1(taille,fonctions);
    bloom1.afficherEtat();
    string kmer="";
    char nextchar;
    //-----dans cette etape on code les k premier char pour le premier K-mer--------- 
    for (size_t i = 0; i < k; i++)
    {
        nextchar=nexDnaChar(file);
        kmer=kmer+nextchar;
    }
    uint64_t code=encodeK(kmer);
    uint64_t code2=encodeKR(kmer);

    if(code<code2)
    {
        bloom1.add_value(code);
        cout<< kmer<<":"<<code<<endl;
    }
    else 
    {
        bloom1.add_value(code2);
        //cout<< kmer<<":"<<code2<<endl;
    }

    //--------ici on taritera le reste du fichier----------------------
    while (true)
    {
        if((nextchar=nexDnaChar(file))=='F')
        {
            break;
        }
        bloom1.add_value(code=encodeKPlus(kmer,nextchar));
        kmer=kmer.erase(0, 1);
        kmer=kmer+nextchar;

        //vous pouvez decommenter la prochaine ligne pour voir a chaque etape le K-mer et son code 
        //cout<< kmer<<":"<<code<<endl;
       
    }
     

    // r requêtes aléatoires is_present sur le filtre de bloom (ie générer r kmers aléatoires et les rechercher)

   
    srand(time(0));
    for (size_t i = 0; i < r; i++)
    {    
        string randomkmer= randKmer(k);
        if(encodeKR(randomkmer)<encodeK(randomkmer))
        {
            cout <<"is the "<<k<<"-mer "<<randomkmer<<" present ?"<< bloom1.is_present(encodeKR(randomkmer))<< endl;
        }
        else cout <<"is the "<<k<<"-mer "<<randomkmer<<" present ?"<< bloom1.is_present(encodeK(randomkmer))<< endl;     
    }

    return 0;
}
