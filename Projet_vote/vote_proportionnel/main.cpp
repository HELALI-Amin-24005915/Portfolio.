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
    vector<unsigned> votes(4, 0);
    const unsigned totalVotants = 102;

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
        
        if (numGlace >= 1 && numGlace <= 4) {
            vParticipant.push_back(participant{nom, prenom, numGlace});
            votes[numGlace - 1]++;
        }
    }

    // Calcul des pourcentages et stockage des résultats
    vector<pair<float, unsigned>> resultats;
    cout << "\nRésultats du vote proportionnel :" << endl;

    for (size_t i = 0; i < votes.size(); ++i) {
        float pourcentage = (static_cast<float>(votes[i]) * 100.0f) / totalVotants;
        cout << vGlacePref[i] << " : " << votes[i] << " votes (" 
             << fixed << setprecision(2) << pourcentage << "%)" << endl;
        resultats.push_back({pourcentage, i});
    }

    // Tri des résultats par pourcentage décroissant
    sort(resultats.rbegin(), resultats.rend());

    // Attribution des sièges de manière proportionnelle
    const int totalSieges = 16; // Total des places à distribuer
    vector<int> siegesAttribues(4, 0);

    // Calcul des sièges selon la méthode proportionnelle
    for (size_t i = 0; i < resultats.size(); ++i) {
        int sieges = static_cast<int>((resultats[i].first * totalSieges) / 100);
        siegesAttribues[resultats[i].second] = sieges;
    }

    // Affichage de la répartition finale
    cout << "\nRépartition proportionnelle des places :" << endl;
    for (size_t i = 0; i < siegesAttribues.size(); ++i) {
        cout << vGlacePref[i] << " : " << siegesAttribues[i] << " places" << endl;
    }

    return 0;
}
