#ifndef ITEMMISC_H_INCLUDED
#define ITEMMISC_H_INCLUDED

#include "../items.h"

class itemMisc : public item {
    private:
        static irr::scene::IMeshSceneNode* baseNode; //the node that's cloned when a new item is created
        static btConvexHullShape* shape; //the collision shape used for the rigid body
        static irr::core::vector3df offset;

        itemMisc();

        //static irr::scene::IMesh* getMesh();
    public:

        itemTempIDs getTempID() {
            return itemTempIDs::ITEM_MISC;
        }

        bool updateItem();

        static itemMisc* createItemMisc();

        static void setMeshNode(irr::scene::IMeshSceneNode* node);
		
		virtual std::string getInvName();

        virtual irr::core::vector3df getOffset();
};

#endif // ITEMMISC_H_INCLUDED