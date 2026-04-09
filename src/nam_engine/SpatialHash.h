#pragma once

namespace nam
{
    class SpatialHash
    {
    private:
        UnMap<size_t, Vector<u32>> m_grid;
        float m_cellSize;
        float m_invCellSize;

    public:
        SpatialHash(float size = 10.0f);

        void Clear();
        bool IsEmpty();

        void Insert(u32 entity, const DirectX::BoundingOrientedBox& box);
        void Insert(u32 entity, const DirectX::BoundingSphere& sphere);

        void GetNearby(u32 entity, const DirectX::BoundingOrientedBox& box, Vector<u32>& result);
        void GetNearby(u32 entity, const DirectX::BoundingSphere& sphere, Vector<u32>& result);
    };

}
