/*
 * CZonePlacer.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "float3.h"
#include "../int3.h"
#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

class CZoneGraph;
class CMap;
class CRandomGenerator;
class RmgMap;
class Zone;

typedef std::vector<std::pair<TRmgTemplateZoneId, std::shared_ptr<Zone>>> TZoneVector;
typedef std::map<TRmgTemplateZoneId, std::shared_ptr<Zone>> TZoneMap;
typedef std::map<std::shared_ptr<Zone>, float3> TForceVector;
typedef std::map<std::shared_ptr<Zone>, float> TDistanceVector;
typedef std::map<int, std::map<int, size_t>> TDistanceMap;

class CZonePlacer
{
public:
	explicit CZonePlacer(RmgMap & map);
	int3 cords(const float3 & f) const;
	float metric (const int3 &a, const int3 &b) const;
	float getDistance(float distance) const; //additional scaling without 0 divison
	~CZonePlacer() = default;

	void placeZones(CRandomGenerator * rand);
	void findPathsBetweenZones();
	void placeOnGrid(CRandomGenerator* rand);
	void assignZones(CRandomGenerator * rand);

	const TDistanceMap & getDistanceMap();
	
private:
	void prepareZones(TZoneMap &zones, TZoneVector &zonesVector, const bool underground, CRandomGenerator * rand);
	void attractConnectedZones(TZoneMap & zones, TForceVector & forces, TDistanceVector & distances) const;
	void separateOverlappingZones(TZoneMap &zones, TForceVector &forces, TDistanceVector &overlaps);
	void moveOneZone(TZoneMap & zones, TForceVector & totalForces, TDistanceVector & distances, TDistanceVector & overlaps);

private:
	int width;
	int height;
	//metric coeficients
	float scaleX;
	float scaleY;
	float mapSize;

	float gravityConstant;
	float stiffnessConstant;
	float stifness;
	float stiffnessIncreaseFactor;

	//remember best solution
	float bestTotalDistance;
	float bestTotalOverlap;

	//distance [a][b] = number of zone connections required to travel between the zones
	TDistanceMap distancesBetweenZones;
	std::set<TRmgTemplateZoneId> lastSwappedZones;
	RmgMap & map;
};

VCMI_LIB_NAMESPACE_END
