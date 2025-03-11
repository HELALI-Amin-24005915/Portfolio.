#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

struct participant {
    string nom;
    string prenom;
    int glacePref;
};

bool compare2part (const participant & p1, const participant & p2){
    return p1.prenom < p2.prenom;
}

void affichVectString (const vector<string> & v){
    for (const string & val : v)
        cout << val << '\t';
    cout << endl;
}

void affichVectParticipants (const vector<participant> & vPart){
    for (const participant & part : vPart){
        cout << part.nom << endl;
        cout << part.prenom << endl;
        cout << part.glacePref << endl;
    }
}


int main()
{
    unsigned V[4]= {0};//on mais toute les cases du tableau V a 0

    // on mais w a 0
    //cout << "Hello World!" << endl;
    //vector<participant> vParticipant (19);
    /* on va detecter les glaces preférées des votants
    * tout en virant les commentaires
    */

    /* on vote sur 4 glaces */
    vector <string> vGlacePref;
    for (unsigned i (0); i < 4; ++i)
        vGlacePref.push_back(litUneString());

    affichVectString (vGlacePref);// affiche les glace dans la première ligne séparer par un tab fait par le truc du dessus

    //On lit les datas du clavier, et on les stocke
    vector<participant> vParticipant;

    for (unsigned i (0); i < 102/*le nombres de participants */; ++i){
        string nom (litUneString());//récupère le nom de la personne i
        string prenom  (litUneString());//récupère le prénom de la personne i
        int numGlace (litUnEntier());//récupère la glace Pref de la personne i
            //cout << nom << endl << prenom << endl << numGlace << endl;
        vParticipant.push_back(participant{nom, prenom, numGlace});
            //  vJoueur[numEquipe-1].push_back(joueur {nom, prenom, numEquipe});
        if (numGlace == 1){V[0] = V[0] + 1 ;} //je trie tout les votes dans un tableau V 0
        else if  (numGlace == 2){V[1] = V[1] + 1;}//je trie tout les votes dans un tableau V 1
        else if  (numGlace == 3){V[2] = V[2] + 1 ;}//je trie tout les votes dans un tableau V 2
        else if  (numGlace == 4){V[3] = V[3] + 1 ;}//je trie tout les votes dans un tableau V 3
    }

    // Recherche du vainqueur avec gestion des égalités
    unsigned int maxVotes = 0;
    vector<unsigned int> gagnants;

    // Trouve le nombre maximum de votes
    for (size_t i = 0; i < 4; ++i) {
        if (V[i] > maxVotes) {
            maxVotes = V[i];
            gagnants.clear();
            gagnants.push_back(i);
        }
        else if (V[i] == maxVotes) {
            gagnants.push_back(i);
        }
    }

    // Affichage des résultats détaillés
    cout << "\nRésultats du vote majoritaire :" << endl;
    for (size_t i = 0; i < 4; ++i) {
        float pourcentage = (static_cast<float>(V[i]) * 100.0f) / 102;
        cout << vGlacePref[i] << " : " << V[i] << " votes (" 
             << fixed << setprecision(2) << pourcentage << "%)" << endl;
    }

    // Affichage du ou des gagnants
    cout << "\n";
    if (gagnants.size() == 1) {
        cout << "La glace " << vGlacePref[gagnants[0]] 
             << " remporte l'élection avec " << maxVotes << " votes ("
             << fixed << setprecision(2) 
             << (static_cast<float>(maxVotes) * 100.0f) / 102 << "%)" << endl;
    }
    else {
        cout << "Il y a une égalité entre les glaces suivantes :" << endl;
        for (unsigned int index : gagnants) {
            cout << "- " << vGlacePref[index] << " avec " << maxVotes << " votes" << endl;
        }
    }

    return 0;
}
