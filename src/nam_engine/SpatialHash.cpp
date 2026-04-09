#include "pch.h"
#include "SpatialHash.h"
#include "PointHasher.h"

using namespace DirectX;

namespace nam
{
	SpatialHash::SpatialHash(float size) : m_cellSize(size), m_invCellSize(1.0f / size)
	{
	}

	void SpatialHash::Clear()
	{ 
		m_grid.clear();
	}

    bool SpatialHash::IsEmpty()
    {
        return m_grid.empty();
    }

    void SpatialHash::Insert(u32 entity, const DirectX::BoundingOrientedBox& box)
    {
        DirectX::XMFLOAT3 corners[8];
        box.GetCorners(corners);

        int minX = INT_MAX;
        int maxX = INT_MIN;
        int minY = INT_MAX;
        int maxY = INT_MIN;
        int minZ = INT_MAX;
        int maxZ = INT_MIN;

        for (int i = 0; i < 8; i++) {
            int x = (int)floor(corners[i].x * m_invCellSize);
            int y = (int)floor(corners[i].y * m_invCellSize);
            int z = (int)floor(corners[i].z * m_invCellSize);

            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
            minZ = min(minZ, z);
            maxZ = max(maxZ, z);
        }

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                for (int z = minZ; z <= maxZ; z++) {
                    size h = PointHasher::Hash(x, y, z);
                    m_grid[h].push_back(entity);
                }
            }
        }
    }

    void SpatialHash::Insert(u32 entity, const DirectX::BoundingSphere& sphere)
    {
        int centerX = (int)floor(sphere.Center.x * m_invCellSize);
        int centerY = (int)floor(sphere.Center.y * m_invCellSize);
        int centerZ = (int)floor(sphere.Center.z * m_invCellSize);

        int radiusCells = (int)ceil(sphere.Radius * m_invCellSize);

        for (int dx = -radiusCells; dx <= radiusCells; dx++) {
            for (int dy = -radiusCells; dy <= radiusCells; dy++) {
                for (int dz = -radiusCells; dz <= radiusCells; dz++) {
                    size h = PointHasher::Hash(centerX + dx, centerY + dy, centerZ + dz);
                    m_grid[h].push_back(entity);
                }
            }
        }
    }

    void SpatialHash::GetNearby(u32 entity, const BoundingOrientedBox& box, Vector<u32>& result)
    {
        result.clear();
        result.reserve(128);

        DirectX::XMFLOAT3 corners[8];
        box.GetCorners(corners);

        int minX = INT_MAX, maxX = INT_MIN;
        int minY = INT_MAX, maxY = INT_MIN;
        int minZ = INT_MAX, maxZ = INT_MIN;

        for (int i = 0; i < 8; i++) {
            int x = (int)floor(corners[i].x * m_invCellSize);
            int y = (int)floor(corners[i].y * m_invCellSize);
            int z = (int)floor(corners[i].z * m_invCellSize);

            minX = min(minX, x); maxX = max(maxX, x);
            minY = min(minY, y); maxY = max(maxY, y);
            minZ = min(minZ, z); maxZ = max(maxZ, z);
        }

        UnSet<u32> uniqueEntities;
        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                for (int z = minZ; z <= maxZ; z++) {
                    size h = PointHasher::Hash(x, y, z);
                    auto it = m_grid.find(h);
                    if (it != m_grid.end()) {
                        for (u32 e : it->second) {
                            uniqueEntities.insert(e);
                        }
                    }
                }
            }
        }
        uniqueEntities.erase(entity);
        result.assign(uniqueEntities.begin(), uniqueEntities.end());
    }

    void SpatialHash::GetNearby(u32 entity, const BoundingSphere& sphere, Vector<u32>& result)
    {
        result.clear();
        result.reserve(128);

        int centerX = (int)floor(sphere.Center.x * m_invCellSize);
        int centerY = (int)floor(sphere.Center.y * m_invCellSize);
        int centerZ = (int)floor(sphere.Center.z * m_invCellSize);
        int radiusCells = (int)ceil(sphere.Radius * m_invCellSize);

        UnSet<u32> uniqueEntities;
        for (int dx = -radiusCells; dx <= radiusCells; dx++) {
            for (int dy = -radiusCells; dy <= radiusCells; dy++) {
                for (int dz = -radiusCells; dz <= radiusCells; dz++) {
                    size h = PointHasher::Hash(centerX + dx, centerY + dy, centerZ + dz);
                    auto it = m_grid.find(h);
                    if (it != m_grid.end()) {
                        for (u32 e : it->second) {
                            uniqueEntities.insert(e);
                        }
                    }
                }
            }
        }
        uniqueEntities.erase(entity);
        result.assign(uniqueEntities.begin(), uniqueEntities.end());
    }

}