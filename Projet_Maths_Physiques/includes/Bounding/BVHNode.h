#pragma once
#ifndef BVHNODE_H
#define BVHNODE_H

#include "Components/Rigidbody.h"
#include "Bounding.h"

struct PotentialContact {
	Rigidbody* body[2];
};

template<class T> //T should extends Bounding
class BVHNode {
public:
	///--------------- Constructeurs/Destructeurs ---------------///

	//Constructeur

	BVHNode();
	BVHNode(Rigidbody* rb, BVHNode* fg, BVHNode* fd, const T& vol);
	BVHNode(BVHNode* parent, Rigidbody* rb, const T& vol);

	//Destructeur

	~BVHNode();

	///--------------- Attributes ---------------///
	//En tant que noeud de structure arborescente on peut les avoir en tant que membres public

	Rigidbody* body;
	BVHNode* children[2];
	T volume;
	BVHNode* parent;

	///--------------- Methods ---------------///

	//Indique si ce noeud est une feuille
	bool isLeaf() const { return body != NULL; }

	//Rempli le tableau de contact potentiel pass� en param�tre en descendant l'arbre, puis renvoi leur nombre
	int getPotentialContacts(PotentialContact* contacts, unsigned int limit) const;

	//Indique si on a superposition de notre volume avec celui pass� en param�tre
	bool overlaps(const BVHNode<T>* other) {
		return volume->overlaps(other);
	}

	//Ajoute un volume dans notre hi�rarchie
	void insert(Rigidbody*, const T&);

	//D�cris le noeud, utilse au debug
	void display() const;

private:

	//Fonction auxiliaire de getPotentialContacts
	int getPotentialContactsWith(const BVHNode<T>* other, PotentialContact* contacts, unsigned int limit) const;

	//
	void recalculateBoundingVolume();

};


//-------------------------------------------------------------------------------------------------------------------//
//---------------------------------------            Implementation             -------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

template<class T>
BVHNode<T>::BVHNode() {
	body = nullptr;
	parent = nullptr;
	children[0] = nullptr;
	children[1] = nullptr;
	volume = T();
}

template<class T>
BVHNode<T>::BVHNode(BVHNode* parent, Rigidbody* rb, const T& vol) {
	this->parent = parent;
	this->body = rb;
	this->volume = vol;
	children[0] = nullptr;
	children[1] = nullptr;
}

template<class T>
BVHNode<T>::BVHNode(Rigidbody* rb, BVHNode* fg, BVHNode* fd, const T& vol) {
	body = rb;
	children[0] = fg;
	children[1] = fd;
	volume = vol;
	parent = nullptr;
}

template<class T>
BVHNode<T>::~BVHNode() {
	if (parent) {
		//On r�cup�re le noeud voisin
		BVHNode<T>* sibling;

		if (parent->children[0] == this) { 
			sibling = parent->children[1];
		}
		else sibling = parent->children[0];

		//On mets ses infos dans le parent
		if (sibling) {
			parent->volume = sibling->volume;
			parent->body = sibling->body;
			parent->children[0] = sibling->children[0];
			parent->children[1] = sibling->children[1];
			//On supprime le voisin
			//sibling->volume = NULL;
			//sibling->body = NULL;
			sibling->children[0] = nullptr;
			sibling->children[1] = nullptr;
			delete sibling;
		}

		//Puis on recalcule le volume englobant
		parent->recalculateBoundingVolume();
	}

	//On retire nos enfants
	if (children[0]) {
		//children[0]->parent = nullptr;
		delete children[0];
	}
	if (children[1]) {
		//children[1]->parent = nullptr;
		delete children[1];
	}
}

template<class T>
void BVHNode<T>::recalculateBoundingVolume() {
	if (children[0] && children[1]) {
		volume = T(children[0]->volume, children[1]->volume);
	}
	else if (children[0]) {
		volume = children[0]->volume;
	}
	else if (children[1]) {
		volume = children[1]->volume;
	}
	else {
		return;
	}
	
}

template<class T>
int BVHNode<T>::getPotentialContacts(PotentialContact* contacts, unsigned int limit) const {
	
	//Si on est une feuille pas de contacts
	if (isLeaf()) {
		return 0;
	}

	//On r�cup�re les contacts potentiels de nos enfants
	return 0;
}

template<class T>
int BVHNode<T>::getPotentialContactsWith(const BVHNode<T>* other, PotentialContact* contacts, unsigned int limit) const{

	//Si par de superposition : on sort
	if (!overlaps(other) || limit == 0) return 0;

	//Si on a 2 feuilles : contact potentiel
	if (isLeaf() && other->isLeaf()) {
		contacts->body[0] = body;
		contacts->body[1] = other->body;
		return 1;
	}

	//Boucle r�cursive
	if (other->isLeaf() || !isLeaf() && volume->getSize() >= other->volume->getSize()) {
		int count = children[0]->getPotentialContactsWith(other, contacts, limit);

		if (limit > count) {
			return count + children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
		}
		else {
			return count;
		}
	}
	else {
		int count = getPotentialContactsWith(other->children[0], contacts, limit);

		if (limit > count) {
			return count + getPotentialContactsWith(other->children[1], contacts + count, limit - count);
		}
		else {
			return count;
		}
	}
};

template<class T>
void BVHNode<T>::insert(Rigidbody* newBody, const T& newVolume) {
	//Cas feuille : on ins�re � gauche
	if (isLeaf()) {
		//Notre fils gauche devient copie de nous-m�me
		children[0] = new BVHNode<T>(this, body, volume);

		//Notre fils droit r�cup�re le nouveau body
		children[1] = new BVHNode<T>(this, newBody, newVolume);

		//On n'est plus une feuille donc on perd notre body
		this->body = nullptr;

		//On recalcule notre volume englobant
		recalculateBoundingVolume();
	}
	else {
		if (children[0]->volume.getGrowth(newVolume) < children[1]->volume.getGrowth(newVolume)) {
			children[0]->insert(newBody, newVolume);
		}
		else {
			children[1]->insert(newBody, newVolume);
		}
	}
}

template<class T>
void BVHNode<T>::display() const {
	std::cout << "\nNode : " << std::endl;
	std::cout << "Rigidbody is at pos : " << (body ? body->getPos() : Vecteur3D(-1,-1,-1)) << std::endl;
	std::cout << "Children[0] is defined ? " << ((children[0]) ? "yes" : "no") << std::endl;
	std::cout << "Children[1] is defined ? " << ((children[1]) ? "yes" : "no") << std::endl;
	if (children[0]) std::cout << "Children[0] is at pos" << (children[0]->body ? children[0]->body->getPos() : Vecteur3D(-1, -1, -1)) << std::endl;
	if (children[1]) std::cout << "Children[1] is at pos" << (children[1]->body ? children[1]->body->getPos() : Vecteur3D(-1,-1,-1)) << std::endl;
	std::cout << "Parent is : " << (parent ? (parent->body ? parent->body->getPos() : Vecteur3D(-1,-1,-1)) : Vecteur3D(-2,-2,-2)) << std::endl;
	std::cout << "Volume is : " << volume.display() << std::endl;
}

#endif