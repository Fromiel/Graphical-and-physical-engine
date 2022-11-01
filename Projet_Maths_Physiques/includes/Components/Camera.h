#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES

#include <cmath>
#include "Maths/Matrix4D.h"
#include "Maths/Matrix3D.h"
#include "Transform.h"
#include "CoreECS/ECS.h"

/// <summary>
/// Cette classe permet de repr�senter la cam�ra qui va permettre de fixer le point de vue de la sc�ne
/// </summary>
class Camera
{
    private:
        /**la distance la plus proche � observer*/
        float near_;
        /**la distance la plus loin � observer*/
        float far_;
        /**fov de la cam�ra*/
        float fov_;
        /**ratio de la cam�ra*/
        float ratio_;
        /**View matrice permettant de passer des coordonn�es du monde au coordonn�es de la cam�ra*/
        Matrix4D viewMatrix_;
        //Lien vers l'entit� parente
        Entity cameraEntity_;
          
    public:
        Camera() {}

        /// <summary>
        /// Constructeur de la cam�ra avec chacun des attributs � initialiser
        /// </summary>
        /// <param name="entity">entit� parente</param>
        /// <param name="near">la distance la plus proche � observer</param>
        /// <param name="far">la distance la plus loin � observer</param>
        /// <param name="position">position de la cam�ra</param>
        /// <param name="fov">le fov de la cam�ra</param>
        /// <param name="ratio">le ratio de l'�cran</param>
        Camera(Entity entity, float near = 0.1, float far = 100, float fov = 110, float ratio = 640. / 480.0);

        /// <summary>
        /// Constructeur pour les tests
        /// </summary>
        /// <param name="transform"></param>
        /// <param name=""></param>
        /// <param name=""></param>
        /// <param name="fov"></param>
        /// <param name="ratio"></param>
        Camera(Transform transform, float near = 0.1, float far = 100, float fov = 110, float ratio = 640. / 480.0);

        /// <summary>
        /// 
        /// </summary>
        /// <returns>la distance la plus proche � observer</returns>
        float getNear() const { return near_; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>la distance la plus loin � observer</returns>
        float getFar() const { return far_; }

        //Temporaire
        void movePosition(Vecteur3D move);


        /// <summary>
        /// 
        /// </summary>
        /// <returns>le fov de la cam�ra</returns>
        float getFov() const { return fov_; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>le ratio de la cam�ra</returns>
        float getRatio() const { return ratio_; }

        /// <summary>
        /// Setter du ratio
        /// </summary>
        /// <param name="fov"></param>
        void setRatio(float ratio) { ratio_ = ratio; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>la view matrice</returns>
        Matrix4D getViewMatrix() const { return viewMatrix_; }

        /// <summary>
        /// 
        /// </summary>
        ///<returns>la matrice normale</returns>
        Matrix3D getNormalMatrix(Matrix4D modelMatrix);

        /// <summary>
        /// Matrice de projection de perspective symetrique
        /// Les plans du near et du far correspondent respectivement � la coordonn�e z normalis�e de -1 et 1 respectivement 
        /// </summary>
        /// <returns></returns>
        Matrix4D projectionMatrix();

        /// <summary>
        /// Bouge la cam�ra du vecteur mis en argument dans les coordonn�es de la cam�ra (on modifie la viewMatrix)
        /// </summary>
        /// <param name="vect"></param>
        void move(const Vecteur3D &vect);

        /// <summary>
        /// Effectue la rotation de la cam�ra dans ses coordonn�es (on modifie la viewMatrix)
        /// </summary>
        /// <param name="angle"></param>
        /// <param name="pivot"></param>
        void rotate(float angle, const Vecteur3D &pivot);

        /// <summary>
        /// Permet de placer la cam�ra aux coordonn�es eye, qui va regarder le point center en ayant sa rotation d�fini par le vecteur up repr�sentant la direction du "haut" de la cam�ra
        /// </summary>
        /// <param name="eye">Position de la camera</param>
        /// <param name="center">Position que l'on souhaite observer</param>
        /// <param name="up">Le "up vector"</param>
        void lookAt(const Vecteur3D &eye, const Vecteur3D &center, const Vecteur3D &up);



};

#endif
