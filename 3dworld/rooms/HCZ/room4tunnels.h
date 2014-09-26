#ifndef ROOM4TUNNELS_ROOM_INCLUDED
#define ROOM4TUNNELS_ROOM_INCLUDED

class room4tunnels : public room {
	private:
		static irr::scene::IMeshSceneNode* baseNode;
		static btBvhTriangleMeshShape* baseShape;
		room4tunnels() {};
	public:
		virtual roomTypes getType() { return roomTypes::ROOM4; }
		virtual void updateEvent() { return; }
		static void setBase(irr::scene::IMeshSceneNode* inNode,btBvhTriangleMeshShape* inShape);
		static room4tunnels* createNew(irr::core::vector3df inPosition,char inAngle);
};

#endif