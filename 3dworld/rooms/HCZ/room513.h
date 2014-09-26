#ifndef ROOM513_ROOM_INCLUDED
#define ROOM513_ROOM_INCLUDED

class room513 : public room {
	private:
		static irr::scene::IMeshSceneNode* baseNode;
		static btBvhTriangleMeshShape* baseShape;
		room513() {};
	public:
		virtual roomTypes getType() { return roomTypes::ROOM3; }
		virtual void updateEvent() { return; }
		static void setBase(irr::scene::IMeshSceneNode* inNode,btBvhTriangleMeshShape* inShape);
		static room513* createNew(irr::core::vector3df inPosition,char inAngle);
};

#endif