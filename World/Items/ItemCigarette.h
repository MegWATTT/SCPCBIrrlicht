#ifndef ITEMCIGARETTE_H_INCLUDED
#define ITEMCIGARETTE_H_INCLUDED

#include "Items.h"

class ItemCigarette : public Item {
    private:
        static irr::scene::IMeshSceneNode* baseNode; //the node that's cloned when a new Item is created
        static btConvexHullShape* shape; //the collision shape used for the rigid body
        static irr::core::vector3df offset;

        ItemCigarette();

        //static irr::scene::IMesh* getMesh();
    public:

        ItemTempIDs getTempID() {
            return ItemTempIDs::ITEM_CIGARETTE;
        }

        bool updateItem();
		void updateWearing();
		void drawItem();

        static ItemCigarette* createItemCigarette();

        static void setMeshNode(irr::scene::IMeshSceneNode* node);
		
		virtual std::string getInvName();
		virtual std::string getInvImgPath();

        virtual irr::core::vector3df getOffset();
};

#endif // ITEMCIGARETTE_H_INCLUDED