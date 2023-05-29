#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include<unistd.h>

using namespace std;
using namespace chrono;

unsigned int SCRIPT_END_TIME_HOUR = 18;

/**
 * @brief The programm sleeps for a moment. It prompts the remaining time he is sleeping.
 * 
 * @param time_in_seconds The time during the programm will sleep.
 */
void wait(int time_in_seconds) 
{
    for(int i = 0; i < time_in_seconds;i++) {
        if (time_in_seconds - i == 1) cout << "Attente pendant 1 seconde...            \r";
        else cout << "Pause du programme pendant " << time_in_seconds - i << " secondes...            \r";
        sleep(1);
    }
    cout << "Execution du script en cours...            \r";
}

/**
 * @brief Use Windows shell command to disconnect and reconnect eduroam.
 * 
 */
void reconnect()
{
    // Déconnexion de tous les adaptateurs réseau
    system("netsh wlan disconnect");
    // Attente de 5 secondes
    wait(5);
    // Reconnexion de tous les adaptateurs réseau
    system("netsh wlan connect name=\"eduroam\"");
}

/**
 * @brief Forget the eduroam network and reconnect to it.
 * 
 */
void reset_eduroam()
{
    system("netsh wlan delete profile name=\"eduroam\"");
    wait(5);
    system("netsh wlan add profile filename=\"eduroam.xml\"");
}

/**
 * @brief Get the current hour of the system.
 * 
 * @return int The current hour of the system.
 */
int get_hour()
{
    time_t now = time(nullptr);
    tm ltm = *localtime(&now);
    int heure = ltm.tm_hour;
    return heure;
}

/**
 * @brief Check if the device is connected to the internet.
 * 
 * @return true if the device is connected to the internet.
 * @return false if the devise isn't connected to the internet.
 */
bool check_if_connected_to_the_internet()
{
    // Check the connection to the internet by running a ping command
    cout << "Ping de Google en cours...            \r";
    system("ping google.com -n 1 > eduroam.tmp");
    cout << "Verification de la connexion...            \r";

    // Read the ping output
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

int main()
{
    bool is_connected;
    unsigned int nb_iterations;
    while (get_hour() < SCRIPT_END_TIME_HOUR)
    {
        is_connected = false;
        nb_iterations = 0;
        while(!is_connected && nb_iterations < 5) {
            if(check_if_connected_to_the_internet()) is_connected = true;
            else {
                nb_iterations ++;
                cout << "La connexion internet n'a pas abouti. Tentative de reconnexion...\n";
                reconnect();
            }
        }
        if (is_connected) cout << "Connexion OK.            \r";
        // Waiting for 15 seconds for the next attempt.
        wait(15);
    }

    cout << "Fin du script : il est " << SCRIPT_END_TIME_HOUR << "h.\n";
    return 0;
}