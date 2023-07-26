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

        inline static float timeScale_ = 1.0f;

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
        float deltaTime();

        /// <summary>
        /// Temps qui s'est ecoul� entre deux appels � update quelque soit la valeur de timeScale_ (en secondes)
        /// </summary>
        float forcedDeltaTime();


        static void setTimeScale(float timeScale) { timeScale_ = timeScale; }


        static float getTimeScale() { return timeScale_; }
};


#endif