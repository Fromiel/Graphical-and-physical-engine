#ifndef KEYINPUT_H
#define KEYINPUT_H

#include "IncludeGLFW.h"
#include <map>
#include <vector>

/// <summary>
/// Classe g�rant les inputs aux touches du clavier
/// </summary>
class KeyInput {

    private:
        // Map des touches surveill�es vers leur �tat (press�es ou non)
        std::map<int, bool> _keys;
        // Map des touches qui viennent d'etre press�es
        std::map<int, bool> _keysPressed;
        // Si d�sactiv�, KeyInput.getIsKeyDown retourne toujours false
        bool _isEnabled;

        /// <summary>
        /// Utilis� pour mettre � jour les �tats des touches (Appel� par le callback de GLFW )
        /// </summary>
        /// <param name="key"></param>
        /// <param name="isDown"></param>
        void setIsKeyDown(int key, bool isDown);

        /// <summary>
        /// Utilis� pour mettre � jour les �tats des touches (Appel� par le callback de GLFW )
        /// </summary>
        /// <param name="key"></param>
        /// <param name="isPressed"></param>
        void setIsKeyPressed(int key, bool isPressed);

    public:

        /// <summary>
        /// Constructeur de KeyInput, prend une liste de touches dont on veut connaitre l'�tat
        /// </summary>
        /// <param name="keysToMonitor"></param>
        KeyInput(std::vector<int> keysToMonitor);

        /// <summary>
        /// Destructeur de KeyInput, retire l'instance supprimm�e de la liste d'instances de KeyInput
        /// </summary>
        ~KeyInput();

        /// <summary>
        /// Si cette instance est activ� (isEnabled_ vaut true) et la touche est surveill�e, retourne si la touche vient d'etre activ�e ou non
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        bool getIsKeyPressed(int key);

        /// <summary>
        /// Si cette instance est activ� (isEnabled_ vaut true) et la touche est surveill�e, retourne l'�tat de la touche
        /// </summary>
        /// <param name="key"></param>
        /// <returns>true si la touche est press�e, false sinon</returns>
        bool getIsKeyDown(int key);

        /// <summary>
        /// Savoir si cette instance de KeyInput est activ�
        /// </summary>
        /// <returns></returns>
        bool getIsEnabled() { return _isEnabled; }

        /// <summary>
        /// Permet d'activer ou de d�sactiver cette instance de KeyInput
        /// </summary>
        /// <param name="value"></param>
        void setIsEnabled(bool value) { _isEnabled = value; }


    // Membres static

    private:
        // GLFW callback pour les key events, envoie les �v�mements � toutes les instances de keyInput
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        // Liste de toutes les instances de KeyInput pour leur notifier des inputs
        static std::vector<KeyInput*> _instances;
        /// <summary>
        /// Permet � la classe de d�tecter les inputs sur la fen�tre window (doit �tre appel� pour que les instances de KeyInput fonctionnent)
        /// </summary>
        /// <param name="window"></param>
        static void setupKeyInputs(GLFWwindow* window);
};

#endif