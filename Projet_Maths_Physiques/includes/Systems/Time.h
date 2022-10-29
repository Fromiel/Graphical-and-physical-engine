#ifndef TIME_H
#define TIME_H

#include <chrono>
#include "CoreECS/System.h"

/// <summary>
/// Syst�me g�rant le temps et les intervalles de temps entre de it�rations de la boucle de jeu
/// </summary>
class Time : public System
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> now_;
        float dt_;//Diff�rence de temps

    public:
        /// <summary>
        /// Constructeur initialisant Time
        /// </summary>
        Time();

        /// <summary>
        /// Met � jour le deltaTime
        /// </summary>
        /// <returns></returns>
        void update();

        /// <summary>
        /// Temps qui s'est �coul� entre deux appels � update (en secondes)
        /// </summary>
        float deltaTime() { return dt_; }
};


#endif