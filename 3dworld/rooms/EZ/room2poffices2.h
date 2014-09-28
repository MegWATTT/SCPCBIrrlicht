#ifndef ROOM2POFFICES2_ROOM_INCLUDED
#define ROOM2POFFICES2_ROOM_INCLUDED

class room2poffices2 : public room {
	private:
		static irr::scene::IMeshSceneNode* baseNode;
		static RMesh* baseRMesh;
		room2poffices2() {};
	public:
		virtual roomTypes getType() { return roomTypes::ROOM2; }
		virtual void updateEvent() { return; }
		virtual const std::vector<irr::video::SLight>& getPointLights();
		static void setBase(irr::scene::IMeshSceneNode* inNode,RMesh* inRme);
		static room2poffices2* createNew(irr::core::vector3df inPosition,char inAngle);
};

#endif
