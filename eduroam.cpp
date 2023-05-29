#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include<unistd.h>

using namespace std;
using namespace chrono;


// Déclaration des fonctions
void reconnect();
int get_heure();
bool check_internet();

void wait(int time_in_seconds) {
    for(int i = 0; i < time_in_seconds;i++) {
        if (time_in_seconds - i == 1) cout << "Attente pendant 1 seconde...            \r";
        else cout << "Pause du programme pendant " << time_in_seconds - i << " secondes...            \r";
        sleep(1);
    }
    cout << "Execution du script en cours...            \r";
}

int main()
{
    bool is_connected = true;
    unsigned int nb_iterations = 0;
    while (get_heure() < 18)
    {
        if (!check_internet())
        {
            cout << "La connexion internet n'a pas abouti. Tentative de reconnexion...\n";
            //cout << "The internet connection failed. Try for reconnection...\n";
            reconnect();
        }
        else cout << "Connexion OK.            \r";
        // Attente de 15 secondes
        wait(15);
    }

    cout << "Fin du script : il est 18h.\n";
    //cout << "The script stopped because it's passed 6 PM..\n";
    return 0;
}

void reconnect()
{
    // Déconnexion de tous les adaptateurs réseau
    system("netsh wlan disconnect");
    // Attente de 5 secondes
    wait(5);
    // Reconnexion de tous les adaptateurs réseau
    system("netsh wlan connect name=\"eduroam\"");
}

int get_heure()
{
    // Obtenir l'heure actuelle
    time_t now = time(nullptr);
    tm ltm = *localtime(&now);
    // Obtenir l'heure en format 24h
    int heure = ltm.tm_hour;
    return heure;
}

bool check_internet()
{
    // Vérifier la connexion à Internet en exécutant une commande ping
    cout << "Ping de Google en cours...            \r";
    system("ping google.com -n 1 > eduroam.tmp");
    cout << "Verification de la connexion...            \r";
    // Lire la sortie du ping
    FILE* file = fopen("eduroam.tmp", "r");
    char buffer[100];
    bool result_ping = false;
    while (fgets(buffer, 100, file))
    {
        if (strstr(buffer, "perte 0%") != nullptr)
        {
            result_ping = true;
            break;
        }
    }
    fclose(file);
    return result_ping;
}
