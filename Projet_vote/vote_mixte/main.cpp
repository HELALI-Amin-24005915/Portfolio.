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


int main() {
    // Initialisation des variables
    vector<unsigned> votes(4, 0); // Utilisation d'un vector au lieu d'un tableau statique
    unsigned int totalVotants = 102; // Nombre total de votants

    // Lecture des noms des glaces
    vector<string> vGlacePref;
    for (unsigned i = 0; i < 4; ++i) {
        vGlacePref.push_back(litUneString());
    }
    affichVectString(vGlacePref);

    // Lecture et traitement des votes
    vector<participant> vParticipant;
    for (unsigned i = 0; i < totalVotants; ++i) {
        string nom = litUneString();
        string prenom = litUneString();
        int numGlace = litUnEntier();
        
        // Vérification de la validité du vote
        if (numGlace >= 1 && numGlace <= 4) {
            vParticipant.push_back(participant{nom, prenom, numGlace});
            votes[numGlace - 1]++; // Incrémentation du compteur de votes
        }
    }

    // Calcul des pourcentages et détermination des gagnants
    vector<pair<float, unsigned>> resultats;
    for (size_t i = 0; i < votes.size(); ++i) {
        float pourcentage = (static_cast<float>(votes[i]) * 100.0) / totalVotants;
        cout << fixed << setprecision(2) << pourcentage << "% " 
             << vGlacePref[i] << " (" << votes[i] << " votes)" << endl;
        resultats.push_back({pourcentage, i});
    }

    // Tri des résultats par pourcentage décroissant
    sort(resultats.rbegin(), resultats.rend());

    // Attribution des places selon le système mixte
    cout << "\nRésultats du système mixte:" << endl;
    cout << "8 places pour la glace " << vGlacePref[resultats[0].second] << endl;
    cout << "4 places pour la glace " << vGlacePref[resultats[1].second] << endl;
    cout << "2 places pour la glace " << vGlacePref[resultats[2].second] << endl;
    cout << "2 places pour la glace " << vGlacePref[resultats[3].second] << endl;

    cout << "\nLa glace " << vGlacePref[resultats[0].second] 
         << " remporte le plus de places avec 8 places." << endl;

    return 0;
}
