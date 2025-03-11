 #include <algorithm>
#include<string>
#include <fstream>
#include"enTetes/params.h"

using namespace std;

void InitParams (CMyParam &Param){

    Param.MapParamChar["HAUTJ1"]= 'z';
    Param.MapParamChar["BASJ1"]= 's';
    Param.MapParamChar["GAUCHEJ1"]= 'q';
    Param.MapParamChar["DROITEJ1"]= 'd';

    //Joueur 2
    Param.MapParamChar["HAUTJ2"]= 'o';
    Param.MapParamChar["BASJ2"]= 'l';
    Param.MapParamChar["GAUCHEJ2"]= 'k';
    Param.MapParamChar["DROITEJ2"]= 'm';



}
void LoadParams (CMyParam & Param){
    ifstream ifs ("../../fichiers_config/config.yaml");
    if (!ifs){
        cerr<<"pas de FICHIER"<<endl;
        exit(-1);
    }
    for (string cle, poubelle;ifs>>cle; ) {
        char deuxpoints;
        ifs>>deuxpoints;
        if (find(KAuthorizedKey.VParamChar.begin() ,KAuthorizedKey.VParamChar.end(), cle )
            != KAuthorizedKey.VParamChar.end()){
            char val;
            ifs>>val;
            Param.MapParamChar[cle] = val;
        }
        else
            getline(ifs,poubelle);

    }
}
