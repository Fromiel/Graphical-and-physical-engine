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

        inline static float timeScale_ = 1.0f;

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
        float deltaTime();

        /// <summary>
        /// Temps qui s'est ecoulé entre deux appels à update quelque soit la valeur de timeScale_ (en secondes)
        /// </summary>
        float forcedDeltaTime();


        static void setTimeScale(float timeScale) { timeScale_ = timeScale; }


        static float getTimeScale() { return timeScale_; }
};


#endif