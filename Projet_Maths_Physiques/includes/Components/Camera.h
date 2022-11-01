#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES

#include <cmath>
#include "Maths/Matrix4D.h"
#include "Maths/Matrix3D.h"
#include "Transform.h"
#include "CoreECS/ECS.h"

/// <summary>
/// Cette classe permet de représenter la caméra qui va permettre de fixer le point de vue de la scène
/// </summary>
class Camera
{
    private:
        /**la distance la plus proche à observer*/
        float near_;
        /**la distance la plus loin à observer*/
        float far_;
        /**fov de la caméra*/
        float fov_;
        /**ratio de la caméra*/
        float ratio_;
        /**View matrice permettant de passer des coordonnées du monde au coordonnées de la caméra*/
        Matrix4D viewMatrix_;
        //Lien vers l'entité parente
        Entity cameraEntity_;
          
    public:
        Camera() {}

        /// <summary>
        /// Constructeur de la caméra avec chacun des attributs à initialiser
        /// </summary>
        /// <param name="entity">entité parente</param>
        /// <param name="near">la distance la plus proche à observer</param>
        /// <param name="far">la distance la plus loin à observer</param>
        /// <param name="position">position de la caméra</param>
        /// <param name="fov">le fov de la caméra</param>
        /// <param name="ratio">le ratio de l'écran</param>
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
        /// <returns>la distance la plus proche à observer</returns>
        float getNear() const { return near_; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>la distance la plus loin à observer</returns>
        float getFar() const { return far_; }

        //Temporaire
        void movePosition(Vecteur3D move);


        /// <summary>
        /// 
        /// </summary>
        /// <returns>le fov de la caméra</returns>
        float getFov() const { return fov_; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>le ratio de la caméra</returns>
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
        /// Les plans du near et du far correspondent respectivement à la coordonnée z normalisée de -1 et 1 respectivement 
        /// </summary>
        /// <returns></returns>
        Matrix4D projectionMatrix();

        /// <summary>
        /// Bouge la caméra du vecteur mis en argument dans les coordonnées de la caméra (on modifie la viewMatrix)
        /// </summary>
        /// <param name="vect"></param>
        void move(const Vecteur3D &vect);

        /// <summary>
        /// Effectue la rotation de la caméra dans ses coordonnées (on modifie la viewMatrix)
        /// </summary>
        /// <param name="angle"></param>
        /// <param name="pivot"></param>
        void rotate(float angle, const Vecteur3D &pivot);

        /// <summary>
        /// Permet de placer la caméra aux coordonnées eye, qui va regarder le point center en ayant sa rotation défini par le vecteur up représentant la direction du "haut" de la caméra
        /// </summary>
        /// <param name="eye">Position de la camera</param>
        /// <param name="center">Position que l'on souhaite observer</param>
        /// <param name="up">Le "up vector"</param>
        void lookAt(const Vecteur3D &eye, const Vecteur3D &center, const Vecteur3D &up);



};

#endif
