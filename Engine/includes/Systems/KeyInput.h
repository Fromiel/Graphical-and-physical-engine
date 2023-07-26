#ifndef KEYINPUT_H
#define KEYINPUT_H

#include "IncludeGLFW.h"
#include <map>
#include <vector>

/// <summary>
/// Classe gérant les inputs aux touches du clavier
/// </summary>
class KeyInput {

    private:
        // Map des touches surveillées vers leur état (pressées ou non)
        std::map<int, bool> _keys;
        // Map des touches qui viennent d'etre pressées
        std::map<int, bool> _keysPressed;
        // Si désactivé, KeyInput.getIsKeyDown retourne toujours false
        bool _isEnabled;

        /// <summary>
        /// Utilisé pour mettre à jour les états des touches (Appelé par le callback de GLFW )
        /// </summary>
        /// <param name="key"></param>
        /// <param name="isDown"></param>
        void setIsKeyDown(int key, bool isDown);

        /// <summary>
        /// Utilisé pour mettre à jour les états des touches (Appelé par le callback de GLFW )
        /// </summary>
        /// <param name="key"></param>
        /// <param name="isPressed"></param>
        void setIsKeyPressed(int key, bool isPressed);

    public:

        /// <summary>
        /// Constructeur de KeyInput, prend une liste de touches dont on veut connaitre l'état
        /// </summary>
        /// <param name="keysToMonitor"></param>
        KeyInput(std::vector<int> keysToMonitor);

        /// <summary>
        /// Destructeur de KeyInput, retire l'instance supprimmée de la liste d'instances de KeyInput
        /// </summary>
        ~KeyInput();

        /// <summary>
        /// Si cette instance est activé (isEnabled_ vaut true) et la touche est surveillée, retourne si la touche vient d'etre activée ou non
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        bool getIsKeyPressed(int key);

        /// <summary>
        /// Si cette instance est activé (isEnabled_ vaut true) et la touche est surveillée, retourne l'état de la touche
        /// </summary>
        /// <param name="key"></param>
        /// <returns>true si la touche est pressée, false sinon</returns>
        bool getIsKeyDown(int key);

        /// <summary>
        /// Savoir si cette instance de KeyInput est activé
        /// </summary>
        /// <returns></returns>
        bool getIsEnabled() { return _isEnabled; }

        /// <summary>
        /// Permet d'activer ou de désactiver cette instance de KeyInput
        /// </summary>
        /// <param name="value"></param>
        void setIsEnabled(bool value) { _isEnabled = value; }


    // Membres static

    private:
        // GLFW callback pour les key events, envoie les évèmements à toutes les instances de keyInput
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        // Liste de toutes les instances de KeyInput pour leur notifier des inputs
        static std::vector<KeyInput*> _instances;
        /// <summary>
        /// Permet à la classe de détecter les inputs sur la fenêtre window (doit être appelé pour que les instances de KeyInput fonctionnent)
        /// </summary>
        /// <param name="window"></param>
        static void setupKeyInputs(GLFWwindow* window);
};

#endif