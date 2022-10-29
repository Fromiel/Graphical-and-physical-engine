#ifndef TIME_H
#define TIME_H

#include <chrono>
#include "CoreECS/System.h"

/// <summary>
/// Système gérant le temps et les intervalles de temps entre de itérations de la boucle de jeu
/// </summary>
class Time : public System
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> now_;
        float dt_;//Différence de temps

    public:
        /// <summary>
        /// Constructeur initialisant Time
        /// </summary>
        Time();

        /// <summary>
        /// Met à jour le deltaTime
        /// </summary>
        /// <returns></returns>
        void update();

        /// <summary>
        /// Temps qui s'est écoulé entre deux appels à update (en secondes)
        /// </summary>
        float deltaTime() { return dt_; }
};


#endif