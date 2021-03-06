#ifndef LOCKROOM2_ROOM_INCLUDED
#define LOCKROOM2_ROOM_INCLUDED

class RoomLockroom2 : public Room {
	private:
		static RMesh* baseRMesh;
		RoomLockroom2() {};
	public:
		virtual RoomTypes getType() const { return RoomTypes::ROOM2C; }
		virtual void updateEvent() { return; }
		static void setBase(RMesh* inRme);
		static RoomLockroom2* createNew(irr::core::vector3df inPosition,char inAngle);
		virtual void findWPPath(irr::core::vector3df startPos,irr::core::vector3df destPos,std::vector<irr::core::vector3df> &posList);
};

#endif
